import os
import pickle
import time
import numpy as np
import folium
from folium.plugins import MarkerCluster
from folium.plugins import HeatMap
from itertools import tee
import json
import matplotlib.pyplot as plt
from math import sin, cos, sqrt, atan2, radians
from datetime import datetime as dt
import pandas as pd
import matplotlib.pyplot as plt

maxSpeed = 0
minSpeed = 0

start = time.time()

rebuildDatabase = False
statsByHour = True
generateMaps = False
saveModel = True
dbName = 'sanFrancisco200.pkl'
mapName = 'sanFranciscoClustering200.html'
datasetPath = "C:\\Users\\marcio\\Google Drive\\Studies\\Master Bremen\\01. Semester\\06. Communication Networks Theory\\assignment2\\dataset\\"

latMax = 37.814443
latMin = 37.6
lonMax = -122.355961
lonMin = -122.5194
centerLat = (latMax - latMin)/2.0 + latMin
centerLon = (lonMax - lonMin)/2.0 + lonMin
gridDecompositionFactor = 101.0
earthRadius = 6371.0
coordTol = 0.0025
clusterCoefficient = 200

# TODO: fix all the vector types to be ndarrays instead of tuples and lists
def saveObject(obj, filename):
    with open(filename, 'wb') as output:
        pickle.dump(obj, output, pickle.HIGHEST_PROTOCOL)

def loadObject(obj, filename):
    with open(filename, 'rb') as input:
        obj = pickle.load(input)
    return obj

def populateDatabase(currentCity):
    currentCity.gridDecomposition()
    datasetDirContent = os.listdir(datasetPath)
    # Remove info files from dataset list dir
    taxiDatasetMap = []
    for taxi in datasetDirContent:
        if ('new_' in taxi):
            taxiDatasetMap.append(taxi)

    # Move the content to RAM to optimize speed
    counter = 0
    for taxi in taxiDatasetMap:         # todo: this part shall become a method of classCity
        print(counter)
        currentTaxi = classTaxi(taxi.replace('.txt', '').replace('new_', ''), datasetPath + taxi)
        currentCity.addTaxi(currentTaxi)
        counter += 1
    currentCity.taxis = np.asarray(currentCity.taxis)
    currentCity.pandasFrame = currentCity.generatePandasFrame()
    return currentCity

def pairwise(iterable):
    a, b = tee(iterable)
    next(b, None)
    return zip(a, b)

# todo: reestruct the classes architectures, the way it's built will eventually crash the program
class classCity(object):
    def __init__(self, latMax, latMin, lonMax, lonMin, gridDecompositionFactor):
        self.taxis = []
        self.districts = []
        self.clusteredGridTraffic = []
        self.noOfTaxis = 0
        self.noOfDistricts = 0
        self.noOfClusteredDistricts = 0
        self.ghostDistricts = 0
        self.boundaryUpper = latMax
        self.boundaryLower = latMin
        self.boundaryLeft = lonMin
        self.boundaryRight = lonMax
        self.gridDecFactor = gridDecompositionFactor
        self.trafficFlow = np.zeros([1, 5], dtype=np.float32)
        self.pandasFrame = 0

    def addTaxi(self, taxi):
        self.taxis.append(taxi)
        self.noOfTaxis += 1

    def gridDecomposition(self):
        latSpan = self.boundaryUpper - self.boundaryLower
        lonSpan = self.boundaryRight - self.boundaryLeft
        latStride = latSpan / (self.gridDecFactor)
        lonStride = lonSpan / (self.gridDecFactor)
        latDivision = np.arange(latMin, latMax, latStride)
        lonDivision = np.arange(lonMin, lonMax, lonStride)

        for lat in pairwise(latDivision):
            for lon in pairwise(lonDivision):
                self.districts.append(np.array([self.noOfDistricts, lat[0], lat[1], lon[0], lon[1]]))
                self.noOfDistricts += 1
        self.districts = np.asarray(self.districts)
        self.trafficFlow = np.zeros([self.noOfDistricts, 5], dtype=np.float32)
        self.trafficFlow[:, 0] = self.districts[:, 0]
        self.trafficFlow[:, 1] = self.districts[:, 1]
        self.trafficFlow[:, 2] = self.districts[:, 3]


    def clusterGrid(self):
        # First we delete all districts which are never visited
        ghostDistricts = []
        for i in range(0, len(self.trafficFlow)):
            if((self.trafficFlow[i,3]==0) and (self.trafficFlow[i,4]==0)):
                ghostDistricts.append(i)
                self.ghostDistricts += 1

        #self.districts = np.delete(self.districts, ghostDistricts, axis=0)
        self.trafficFlow = np.delete(self.trafficFlow, ghostDistricts, axis=0)

        srcEdges = 0
        dstEdges = 0

        # todo: clustering is not refactoring the clustered area, what means that all the traffic flow of the clustered
        # todo: neighborhood is concentrated on the last clustered district
        clusteredDistricts = []
        for i in range(0, len(self.trafficFlow)):
            currentDistrict = self.trafficFlow[i, 0]
            srcEdges += self.trafficFlow[i, 3]
            dstEdges += self.trafficFlow[i, 4]
            inOutEdges = srcEdges + dstEdges
            clusteredDistricts.append(currentDistrict)

            # besides the clustering coeficient, we only cluster in series (row) districts
            if((inOutEdges > clusterCoefficient)or((currentDistrict+1) % (gridDecompositionFactor-1) == 0)):
                [lat, lon] = self.getClusterMidPoint(np.array(clusteredDistricts).astype(int))
                self.clusteredGridTraffic.append(np.array([currentDistrict, lat, lon, srcEdges, dstEdges]))
                srcEdges = 0
                dstEdges = 0
                clusteredDistricts = []

        self.clusteredGridTraffic = np.asarray(self.clusteredGridTraffic)

    def getClusterMidPoint(self, cluster):
        clusteredDistricts = self.districts[cluster]
        latInf = min(clusteredDistricts[:, 1])
        latSup = max(clusteredDistricts[:, 2])
        lonInf = min(clusteredDistricts[:, 3])
        lonSup = max(clusteredDistricts[:, 4])
        clusterLat = (latSup - latInf) / 2.0 + latInf
        clusterLon = (lonSup - lonInf) / 2.0 + lonInf

        return [clusterLat, clusterLon]

    def generatePandasFrame(self):
        # Join all the taxis information
        counter = 0
        for taxi in sanFrancisco.taxis:
            if (len(taxi.trips) > 0):
                data = taxi.trips[:, 3:taxi.trips.shape[1]]
                tmpTime = taxi.trips[:, 2] - 25200                      # Correction to GMT -0700
                idx = tmpTime.astype('datetime64[s]')

                currentFrame = pd.DataFrame(data, index=idx, columns=list(['trips', 'duration', 'distance', 'avgSpeed', 'cost']))
                if (counter > 0):
                    macroFrame = pd.concat([macroFrame, currentFrame])
                else:
                    macroFrame = currentFrame
                counter += 1
        return macroFrame
gcounter = 0
class classTaxi(object):
    def __init__(self, ID, taxiDataFile):
        self.id = ID
        self.states = np.loadtxt(taxiDataFile, dtype='float32')
        self.states = np.flipud(self.states)                        # reverse the array order to have time ascending order
        self.startDate = self.states[0, 3]
        self.validTripCounter = 0
        self.loopCounter = 0
        self.glitchCounter = 0
        self.trips = []
        self.speeds = []
        self.filterOutliers()                                       # TODO: this cannot stay here, shall be moved out class initialization
        self.extractFares()                                         # TODO: this cannot stay here, shall be moved out class initialization

    def filterOutliers(self):
        latitudes = self.states[:, 0]
        longitudes = self.states[:, 1]
        latIdxs = np.where(latitudes > latMax) # or latitudes < latMin)
        longIdxs = np.where(longitudes > lonMax)  # or longitudes < lonMin)
        latIdxs = np.concatenate((np.where(latitudes < latMin), latIdxs), axis=1)
        longIdxs = np.concatenate((np.where(longitudes < lonMin), longIdxs), axis=1)
        idxs2Filter = np.concatenate((latIdxs, longIdxs), axis=1)
        idxs2Filter = np.unique(idxs2Filter)
        self.states = np.delete(self.states, idxs2Filter, axis=0)

    def extractFares(self):
        hasFare = self.states[:, 2]
        bounded = np.concatenate(([0], hasFare, [0]))
        # The differentiation over the bounded array will result in 1 at fare starts and -1 at fare ends
        difs = np.diff(bounded)
        fareStarts, = np.where(difs > 0)
        fareEnds, = np.where(difs < 0)

        vecLen = len(self.states)
        for begin, end in zip(fareStarts, fareEnds):
            if(end == vecLen):                          # if trip ends in the eof the end is then the last point
                end -= 1

            fareSrc = self.getDistrictAddr(self.states[begin, [0, 1]])
            fareDst = self.getDistrictAddr(self.states[end, [0, 1]])
            if(fareSrc == fareDst):
                self.loopCounter += 0
            else:
                fareStartTime = self.states[begin, 3]
                fareDuration = self.states[end, 3] - fareStartTime
                fareTrace = self.states[begin:end+1, [0, 1]]            # trip starts at transition 0 -> [1] and finishes at 1 -> [0]
                fareDistance = self.calcFareDistance(fareTrace)

                if((fareDuration > 0.0)and(fareDistance > 800.0)and(fareDistance < 60000.0) and (fareDuration < 7200)):      # remove fare duration smaller than 0 and distance outliers
                    fareAvgSpeed = (fareDistance / fareDuration) * 3.6
                    if(fareAvgSpeed < 110):
                        self.speeds.append(fareAvgSpeed)
                        # Fare cost is an gross estimation based on fares calculated by www.taxifarefinder.com in USD
                        fareCost = fareDistance * 0.00341755005157393714193396050555 + 3.5
                        self.trips.append(np.array([fareSrc, fareDst, fareStartTime, 1, fareDuration, fareDistance, fareAvgSpeed, fareCost], dtype='float32'))
                        self.validTripCounter += 1
                        sanFrancisco.trafficFlow[fareSrc, 3] += 1
                        sanFrancisco.trafficFlow[fareDst, 4] += 1

                else:
                    self.glitchCounter += 1
        self.trips = np.asanyarray(self.trips, dtype=np.float32)


    def calcFareDistance(self, coordinates):
        distance = 0
        for pair in pairwise(coordinates):
            distance += self.calcDistBetweenPoints(np.concatenate((pair[0], pair[1])))
        return distance

    def calcDistBetweenPoints(self, coordinates):
        lat1 = radians(coordinates[0])
        lon1 = radians(coordinates[1])
        lat2 = radians(coordinates[2])
        lon2 = radians(coordinates[3])
        dlon = lon2 - lon1
        dlat = lat2 - lat1

        a = sin(dlat / 2) ** 2 + cos(lat1) * cos(lat2) * sin(dlon / 2) ** 2
        c = 2 * atan2(sqrt(a), sqrt(1 - a))
        distance = (earthRadius * c) * 1000.0                   # Multiply by 1000 to have distance in meters
        return abs(distance)

    def getDistrictAddr(self, coordinates):
        latitude = coordinates[0]
        longitude = coordinates[1]

        lat0 = sanFrancisco.districts[:, 1]
        lat0Idxs = np.where(lat0 < latitude+coordTol)

        lat1 = sanFrancisco.districts[lat0Idxs, 2].reshape(-1,)
        lat1Idxs = np.where(lat1 > latitude-coordTol)

        lon0 = sanFrancisco.districts[lat1Idxs, 3].reshape(-1,)
        districtAdjacency = sanFrancisco.districts[lat1Idxs, 0].reshape(-1, )
        lon0Idxs = np.array(np.where(lon0 < longitude+coordTol)).reshape(-1, )

        # Since we are halving the matrix it's necessary to add an offset to keep the reference as the original vector
        districtAdjacency = districtAdjacency[lon0Idxs]
        offset = int(districtAdjacency[0])
        lon0Idxs += offset

        lon1 = sanFrancisco.districts[lon0Idxs, 4].reshape(-1, )
        lon1Idxs = np.array(np.where(lon1 > longitude-coordTol)).reshape(-1, )
        lon1Idxs += offset

        # Finally we decode the district
        district = sanFrancisco.districts[lon1Idxs]
        return int(district[0,0])

    def generateStatisctsDB(self):
        data = self.trips[:, 3:self.trips.shape[1]]
        idx = self.trips[:, 2].astype('datetime64[s]')
        df = pd.DataFrame(data, index=idx, columns=list(['trips', 'duration', 'distance', 'avgSpeed', 'cost']))
        df_avg = df.resample('D', how={'trips':'count', 'duration':'mean', 'distance':'mean', 'avgSpeed':'mean', 'cost':'mean'}).fillna(0)
        #df_avg = df.resample('D', how=['mean', 'count']).fillna(0)
        df_avgCabs = df['duration'].resample('D', how=['count']).fillna(0)


        ax = df_avg.plot(y='duration', kind='bar')

        df_avg.columns = df_avg.columns.droplevel(0)

        # anchor B

        weekday_map = {0: 'MON', 1: 'TUE', 2: 'WED', 3: 'THU',
                       4: 'FRI', 5: 'SAT', 6: 'SUN'}

        xs = sorted(ax.get_xticks())
        wd = df_avg.index[xs - xs[0]].map(pd.Timestamp.weekday)
        ax.set_xticks(xs)
        ax.set_xticks([], minor=True)
        ax.set_xticklabels([weekday_map[d] for d in wd])

        #fig, axes = plt.subplots(nrows=2, ncols=2)
        #ax = df_avg.plot(y='duration')


        ax.set_xticklabels(df_avg.index.format())
        ax.grid()


        #ax2 = ax.twinx()
        #ax2.plot(ax.get_xticks(), df_avg['duration'], color='green')
        #plt.show()

        #df_avg.plot()
        #series = pd.Series(data, index=idx)
        #average = df.groupby('time').mean()
        print(df.describe())
        print("ok")


sanFrancisco = classCity(latMax, latMin, lonMax, lonMin, gridDecompositionFactor)
if(rebuildDatabase == True):
    sanFrancisco = populateDatabase(sanFrancisco)
    sanFrancisco.clusterGrid()

    if (saveModel == True):
        saveObject(sanFrancisco, dbName)
else:
    sanFrancisco = loadObject(sanFrancisco, dbName)

#sanFrancisco.pandasFrame = sanFrancisco.generatePandasFrame()

print(sanFrancisco.pandasFrame.describe())
avgspeed = sum(sanFrancisco.taxis[0].speeds)/len(sanFrancisco.taxis[0].speeds)
minim = min(sanFrancisco.taxis[0].speeds)
maxim = max(sanFrancisco.taxis[0].speeds)

print('Time Elapsed: ' + str(time.time() - start))

sanFranciscoMask = json.load(open('SanFrancisco.Neighborhoods.json'))

distCoordinates = sanFrancisco.clusteredGridTraffic[:, 1:3]
distIds = sanFrancisco.clusteredGridTraffic[:, 0].astype(int)
degIn = sanFrancisco.clusteredGridTraffic[:, 3].astype(int)
degOut = sanFrancisco.clusteredGridTraffic[:, 4].astype(int)

if(generateMaps):
    popups = ['District {}        In: {}        Out: {}'.format(loc, din, dout) for loc, din, dout in zip(distIds, degIn, degOut)]
    map = folium.Map(location=[centerLat, centerLon], zoom_start=12)
    map.add_child(MarkerCluster(locations=distCoordinates, popups=popups))
    folium.GeoJson(sanFranciscoMask).add_to(map)
    #map.save(mapName)

    heatMap = folium.Map(location=[centerLat, centerLon], zoom_start=12)
    heatWeight = np.add(degIn, degOut).reshape(-1, 1)
    #heatWeight = degIn.reshape(-1, 1)
    #heatWeight = degOut.reshape(-1, 1)
    heatWeight = 20*(heatWeight / max(heatWeight))
    heatData = np.concatenate((distCoordinates, heatWeight), axis=1)

    HeatMap(heatData).add_to(map)
    map.save('sanFranciscoStackedMap.html')

    #HeatMap(heatData).add_to(heatMap)
    #folium.GeoJson(sanFranciscoMask).add_to(heatMap)
    #heatMap.save('sanFranciscoHeatmap.html')


if statsByHour:
    fig, axes = plt.subplots(nrows=2, ncols=1)
    df_avg = sanFrancisco.pandasFrame.resample('H', how={'trips': 'count', 'duration': 'mean', 'distance': 'mean', 'avgSpeed': 'mean', 'cost': 'mean'}).fillna(0)
    sanFrancisco.pandasFrame['hour'] = [ts.hour for ts in sanFrancisco.pandasFrame.index]
    tripCount = sanFrancisco.pandasFrame.groupby('hour').count()
    avgStats = sanFrancisco.pandasFrame.groupby('hour').mean()

    a1 = avgStats.plot(y='duration', kind='bar', ax=axes[0], title='Average Duration according to hour of the day', color='b')
    #a3 = avgStats['avgSpeed'].plot.box(ax=axes[0])
    a2 = avgStats.plot(y='distance', kind='bar', ax=axes[1], title='Average distance according to hour of the day', color='r')

    print(avgStats.describe())

    a1.set_ylabel("Duration (s)")
    a2.set_ylabel("Distance (m)")
    plt.show()

else:
    df_avg = sanFrancisco.pandasFrame.resample('D', how={'trips': 'count', 'duration': 'mean', 'distance': 'mean', 'avgSpeed': 'mean', 'cost': 'mean'}).fillna(0)

    ax = df_avg.plot(y='cost', kind='bar', title='Average cost of a trip according to each recorded day')
    ax.set_ylabel("Estimated Cost (USD)")
    ax.set_xlabel("Day of week")

    print(df_avg.describe())
    print(sanFrancisco.pandasFrame.describe())

    weekday_map = {0: 'MON', 1: 'TUE', 2: 'WED', 3: 'THU', 4: 'FRI', 5: 'SAT', 6: 'SUN'}

    xs = sorted(ax.get_xticks())
    wd = df_avg.index[xs - xs[0]].map(pd.Timestamp.weekday)
    ax.set_xticks(xs)
    ax.set_xticks([], minor=True)
    ax.set_xticklabels([weekday_map[d] for d in wd])

print('success!')