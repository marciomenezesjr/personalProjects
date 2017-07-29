import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.collections import PatchCollection
from matplotlib.patches import Rectangle, Polygon
import numpy as np

logFile = 'ble-measurements.csv'
outputLogFile = 'packetAnalysis.log'
sourceAddress = 'b8:27:eb:35:34:89'
rateDeviationTol = 0.1
maxTxRate = 15
averageTime = 10

logData = open(logFile, 'r').readlines()
outputLog = open(outputLogFile, 'w')

def logPrint(data, logFile):
    print(data)
    logFile.write(data+'\n')

class dasPaket(object):
    def __init__(self):
        self.rawPacket = []
        self.addr = []
        self.timeStamp = []
        self.payload = []
        self.testCode = []

    def unpack(self, data):
        self.addr.append(data[0])
        self.timeStamp.append(data[1])
        self.payload.append(data[2])
        self.testCode.append(10 * int(data[3]) + int(data[4]))

    def appendPacket(self, rawPacket, addr='none', filtered=True):
        rps = rawPacket.split(';')
        if(filtered == True):
            if(addr == rps[0]):
                self.unpack(rps)
        else:
            self.unpack(rps)

    def getTestIds(self):
        return set(self.testCode)

    def packetsPerTest(self, testId):
        if(testId == -1):
            return len(self.testCode)
        else:
            return self.testCode.count(testId)

    def getTestRunTime(self, testId, gtime=0.0):
        start = float(self.timeStamp[self.testCode.index(testId)]) - gtime
        end = float(self.timeStamp[len(self.testCode) - 1 - self.testCode[::-1].index(testId)]) - gtime
        return [(end - start), start, end]

    def avgPacketRate(self, testId):
        runTime = self.getTestRunTime(testId)[0]
        packetCount = self.packetsPerTest(testId)
        return (runTime/packetCount)

    def predominantPacketRate(self, testId):
        timeStampPrev = 0.0
        rate = []
        for timeStamp,id in zip(self.timeStamp, self.testCode):
            if(id == testId):
                rate.append(float(timeStamp) - timeStampPrev)
                timeStampPrev = float(timeStamp)

        accountedRate = []                          # First rate element is always garbage
        rateDictionay = [rate[1]]
        for timepiece in rate[1:len(rate)]:
            ilk = False
            for newTp in rateDictionay:
                diff = abs(timepiece-newTp)
                tol = rateDeviationTol*newTp
                if(diff<tol):
                    accountedRate.append(newTp)
                    ilk = True
                    break
            if not ilk:
                rateDictionay.append(timepiece)
                accountedRate.append(timepiece)

        packetTimingMap = []
        for gRate in set(accountedRate):
            packetTimingMap.append([gRate, accountedRate.count(gRate)])

        # Predominant packet rate is returned on the first position
        maxV = 0
        for i in range(0,len(packetTimingMap)):
            if(packetTimingMap[i][1] > maxV):
                maxV = packetTimingMap[i][1]
                idx = i
        packetTimingMap = [packetTimingMap[idx]] + packetTimingMap
        del packetTimingMap[idx+1]

        return packetTimingMap

    def averagePacketRate(self, timeStart, timeEnd, avgTime):
        pktCountInWindow = []
        currentTimestamp = timeStart + avgTime
        pktIdx = 0
        while(currentTimestamp < timeEnd):
            pktCounter = 0
            pktToProcess = True
            while((pktToProcess)and(pktIdx < len(self.timeStamp))):
                if(float(self.timeStamp[pktIdx]) > currentTimestamp):
                    pktToProcess = False
                else:
                    pktIdx += 1
                    pktCounter += 1
            pktCountInWindow.append(pktCounter)
            currentTimestamp += avgTime

        return pktCountInWindow

packetData = dasPaket()                 # Object to handle the filtred data according to our MAC address
allPackets = dasPaket()          # Object to handle all packets
for rawPacket in logData:
    packetData.appendPacket(rawPacket, sourceAddress, True)
    allPackets.appendPacket(rawPacket, sourceAddress, False)

# Overall network analysis
totalCollectedPkts = allPackets.packetsPerTest(-1)
globalStartTime = float(allPackets.timeStamp[0])
globalEndTime = float(allPackets.timeStamp[-1])
totalRunTime = globalEndTime - globalStartTime
testIds = packetData.getTestIds()
logPrint('Available test ids: ' + str(testIds), outputLog)

expVec = []
lossVec = []
for id in testIds:
    timeInfo = packetData.getTestRunTime(id, globalStartTime)
    expVec.append([id, timeInfo[1], timeInfo[2]])
    pktCnt = packetData.packetsPerTest(id)
    predominantPacketRate = packetData.predominantPacketRate(id)

    estimatedPackets = int(timeInfo[0] / predominantPacketRate[0][0])
    estimatedPktLoss = estimatedPackets - pktCnt
    estimatedPktLossPer = (1.0 - pktCnt / estimatedPackets)*100.0
    lossVec.append(estimatedPktLossPer)

    logPrint('\n#################################################################################################', outputLog)
    logPrint('Test ID = {:d}\nCollected Packets = {:d}'.format(id, pktCnt), outputLog)
    logPrint('Average data rate = {:.4f}ms'.format(packetData.avgPacketRate(id)), outputLog)
    logPrint('Sampled time = {:.2f}s\nStart time = {:.2f}s\nEnd time = {:.2f}s'.format(timeInfo[0], timeInfo[1], timeInfo[2]), outputLog)
    logPrint('Expected packets = {:d}'.format(estimatedPackets), outputLog)
    logPrint('Packet loss = {:d} / {:.4f}%'.format(estimatedPktLoss, estimatedPktLossPer), outputLog)
    logPrint('\nObserved rates:', outputLog)
    for rate in predominantPacketRate:
        logPrint('{:.4f}: {:d} packets'.format(rate[0], rate[1]), outputLog)


pktTraffic = allPackets.averagePacketRate(globalStartTime, globalEndTime, averageTime)
pktTrafficFiltered = packetData.averagePacketRate(globalStartTime, globalEndTime, averageTime)

fig, ax = plt.subplots(figsize=(14, 10))
xTime = [x * averageTime for x in list(range(len(pktTraffic)))]

ax.stackplot(xTime, pktTrafficFiltered, pktTraffic, edgecolor='white', colors=['#55BA87','#7E1137'])
#ax.stackplot(xTime, pktTraffic, color='blue')
#ax.stackplot(xTime, pktTrafficFiltered, color='green')


ax.set_title('Network Packet Traffic with {:.2f}s average'.format(averageTime), fontsize=20)
ax.grid()
ax.set_xlabel('relative time (s)', fontsize=20)
ax.set_ylabel('Packets', fontsize=20)

yTxtCoord = max(pktTraffic)/1.25
fontSize = 15
neglected_tests = [11, 18, 21, 24, 26]
for element,loss in zip(expVec,lossVec):
    if(element[0] not in neglected_tests):
        xTxtCoord = (element[2] - element[1])/2.0 + element[1] - fontSize - averageTime
        ax.text(xTxtCoord, yTxtCoord, r'Id: {:d}     Loss: {:.2f}%'.format(element[0],loss), fontsize=fontSize, rotation=90)
        ax.axvspan(element[1] - averageTime, element[2] - averageTime, facecolor='0.5', alpha=0.5)

# creating the legend manually
plt.legend([mpatches.Patch(color='#7E1137'), mpatches.Patch(color='#55BA87')], ['network traffic','filtered node traffic'])
plt.show()
#fig.savefig('networkTraffic_{:d}s.png'.format(averageTime), dpi=800)


logPrint('\n#################################################################################################', outputLog)
logPrint('Total collected packets: {:d}'.format(totalCollectedPkts), outputLog)
logPrint('Experiment run rime: {:.2f}s'.format(totalRunTime), outputLog)
outputLog.close()
