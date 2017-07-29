# Load pickled data
import tensorflow as tf
from tensorflow.contrib.layers import flatten
import pickle
import os
import numpy as np
from sklearn.utils import shuffle
from sklearn.model_selection import train_test_split
import matplotlib.pyplot as plt
import random
import time
import math
import scipy
from PIL import Image
import cv2
from random import randint, uniform
import collections
import time
from scipy import misc


# Model configuration parameters
rate = 0.001
EPOCHS = 150
BATCH_SIZE = 128
training_file = './data/train.p'
testing_file = './data/test.p'
validation_file = './data/valid.p' # Must be an odd number (3, 5, 7...)
newImagesPath = '/home/marcio/Desktop/projects/carnd/CarND-Traffic-Sign-Classifier-Project/resizedImgs/'
dropout = 0.5 # Dropout, probability to keep units
newImages = 0
statusFile = 'stat_' + time.strftime("%d_%m_%Y_%H_%M_%S") + '.csv'
log = open(statusFile,'w')

def trainingDataAugmentation(imgVector, yVector):
    unique, counts = np.unique(yVector, return_counts=True)
    targetImgCount = max(counts) #sum(counts)/len(counts) #max(counts)
    expansionMap = []
    generatedImgVector = []
    generatedLabelVector = []
    for label,count in zip(unique, counts):
        expansion = round(((targetImgCount - count) + targetImgCount*newImages)/count)
        if(expansion <= 0.0):
            expansion = newImages
        expansionMap.append(expansion)

    for img,label in zip(imgVector, yVector):
        img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
        img = normalizeGrayscale(img)
        generatedImgVector.append(img)
        generatedLabelVector.append(label)
        imgCod = 0
        genCounter = expansionMap[label]
        while(genCounter > 0):
            if(imgCod == 3):
                imgGen = rollImage(img, 5)
                imgGen = shearImage(imgGen, 10)
                imgGen = rotateImage(imgGen, 20)
                imgCod = imgCod + 1
            elif(imgCod == 2):
                imgGen = rollImage(img, 5)
                imgCod = imgCod + 1
            elif(imgCod == 1):
                imgGen = shearImage(img, 10)
                imgCod = imgCod + 1
            elif(imgCod == 0):
                imgGen = rotateImage(img, 20)
                imgCod = imgCod + 1

            if(imgCod > 3):
                imgCod = 0

            genCounter = genCounter - 1
            generatedImgVector.append(imgGen)
            generatedLabelVector.append(label)
    generatedImgVector = np.array(generatedImgVector)[..., np.newaxis]
    generatedLabelVector = np.array(generatedLabelVector)

    return generatedImgVector, generatedLabelVector

def rotateImage(img, range):
    rows, cols = img.shape
    M = cv2.getRotationMatrix2D((cols / 2, rows / 2), range * np.random.uniform() - range / 2, 1)
    img = cv2.warpAffine(img, M, (cols, rows))
    return img

def rollImage(img, range):
    rows, cols = img.shape
    x = range * np.random.uniform() - range / 2
    y = range * np.random.uniform() - range / 2
    M = np.float32([[1, 0, x], [0, 1, y]])
    img = cv2.warpAffine(img, M, (cols, rows))
    return img

def shearImage(img, range):
    rows, cols = img.shape
    pts1 = np.float32([[5, 5], [20, 5], [5, 20]])
    pt1 = 5 + range * np.random.uniform() - range / 2
    pt2 = 20 + range * np.random.uniform() - range / 2
    pts2 = np.float32([[pt1, 5], [pt2, pt1], [5, pt2]])
    M = cv2.getAffineTransform(pts1, pts2)
    img = cv2.warpAffine(img, M, (cols, rows))
    return img

def normalizeGrayscale(img):
    a = -0.5
    b = 0.5
    grayscale_min = 0
    grayscale_max = 255
    return a + (((img - grayscale_min)*(b - a))/(grayscale_max - grayscale_min))

def inputImgPreprocStage(imgVector):
    resultVector = []
    for img in imgVector:
        img = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)
        img = normalizeGrayscale(img)
        resultVector.append(img)

    return np.array(resultVector)[..., np.newaxis]

def evaluateModel(X_data, y_data):
    num_examples = len(X_data)
    total_accuracy = 0
    sess = tf.get_default_session()
    for offset in range(0, num_examples, BATCH_SIZE):
        batch_x, batch_y = X_data[offset:offset+BATCH_SIZE], y_data[offset:offset+BATCH_SIZE]
        accuracy = sess.run(accuracy_operation, feed_dict={x: batch_x, y: batch_y, keep_prob: 1.0})
        total_accuracy += (accuracy * len(batch_x))
    return total_accuracy / num_examples

def conv2d(x, W):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='VALID')

def maxPool(x):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='VALID')

def weightVariable(shape, mu = 0, sigma = 0.1):
  initial = tf.truncated_normal(shape, mean=mu, stddev=sigma)
  return tf.Variable(initial)

def biasVariable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)

def cnnTSClassifier(x, dropout):
    # First convolutional layer
    # input = 32x32x3
    # output = 14x14x6
    conv1_W = weightVariable([5, 5, 1, 64])
    conv1_b = biasVariable([64])
    conv1 = conv2d(x, conv1_W) + conv1_b
    conv1Relu = tf.nn.relu(conv1)
    conv1MaxPool = maxPool(conv1Relu)
    conv1MaxPool = tf.nn.dropout(conv1MaxPool, dropout)

    # Second convolutional layer
    # input = 14x14x6
    # output = 5x5x16
    conv2_W = weightVariable([5, 5, 64, 128])
    conv2_b = biasVariable([128])
    conv2 = conv2d(conv1MaxPool, conv2_W) + conv2_b
    conv2Relu = tf.nn.relu(conv2)
    conv2MaxPool = maxPool(conv2Relu)
    conv2MaxPool = tf.nn.dropout(conv2MaxPool, dropout)

    #conv3_W = weightVariable([5, 5, 128, 256])
    #conv3_b = biasVariable([256])
    #conv3 = conv2d(conv2MaxPool, conv3_W) + conv3_b
    #conv3Relu = tf.nn.relu(conv3)
    #conv3MaxPool = maxPool(conv3Relu)
    #conv3MaxPool = tf.nn.dropout(conv3MaxPool, dropout)


    # SOLUTION: Flatten. Input = 5x5x16. Output = 400.
    fc0 = flatten(conv2MaxPool)


    # Densely connected layer 1
    fc1_W = weightVariable([5 * 5 * 128, 120])
    fc1_b = biasVariable([120])
    fc1Relu = tf.nn.relu(tf.matmul(fc0, fc1_W) + fc1_b)
    fc1Relu = tf.nn.dropout(fc1Relu, dropout)


    # Densely connected layer 1
    fc2_W = weightVariable([120, 84])
    fc2_b = biasVariable([84])
    fc2Relu = tf.nn.relu(tf.matmul(fc1Relu, fc2_W) + fc2_b)
    fc2Dropout = tf.nn.dropout(fc2Relu, dropout)

    # SOLUTION: Layer 4: Fully Connected. Input = 120. Output = 84.
    # SOLUTION: Layer 5: Fully Connected. Input = 84. Output = 43.
    fc3_W = weightVariable([84, 43])
    fc3_b = biasVariable([43])

    logits = tf.matmul(fc2Dropout, fc3_W) + fc3_b
    return logits

# Load the pickle data
with open(training_file, mode='rb') as f:
    train = pickle.load(f)
with open(testing_file, mode='rb') as f:
    test = pickle.load(f)
with open(validation_file, mode='rb') as f:
    validate = pickle.load(f)

# Separate the input data
X_train, y_train = train['features'], train['labels']
X_test, y_test = test['features'], test['labels']
X_validation, y_validation = validate['features'], validate['labels']

# Sizes
n_test = len(X_test)
image_shape = X_train[0].shape
n_classes = max(y_test) + 1

# Preprocess the training data
#X_train, X_validation, y_train, y_validation = train_test_split(X_train, y_train, test_size=training2testRatio, random_state=0)
n_train = len(X_train)
X_train, y_train = trainingDataAugmentation(X_train, y_train)

X_test = inputImgPreprocStage(X_test)
X_validation = inputImgPreprocStage(X_validation)

#unique, counts = np.unique(y_test, return_counts=True)

# Asserts if each image has a label
assert(len(X_train) == len(y_train))
assert(len(X_validation) == len(y_validation))
assert(len(X_test) == len(y_test))

# shuffle the training data
X_train, y_train = shuffle(X_train, y_train)

n_trainPostProc = len(X_train)
n_validation = len(X_validation)

# Plot Image
'''index = random.randint(0, len(X_train))
image = X_train[index].squeeze()
plt.figure(figsize=(1,1))
plt.imshow(image, cmap="gray")'''
print("Number of training examples =", n_train)
print("Number of training examples after preprocessing pipeline =", n_trainPostProc)
print("Number of testing examples =", n_test)
print("Number of validation examples =", n_validation)
print("Image data shape =", image_shape)
print("Number of classes =", n_classes)



# TF placeholders
x = tf.placeholder(tf.float32, (None, 32, 32, 1))
y = tf.placeholder(tf.int32, (None))
keep_prob = tf.placeholder(tf.float32) #dropout (keep probability)
one_hot_y = tf.one_hot(y, n_classes)

logits = cnnTSClassifier(x, keep_prob)
detailedEvaluation = tf.argmax(logits, 1)
cross_entropy = tf.nn.softmax_cross_entropy_with_logits(logits=logits, labels=one_hot_y)
loss_operation = tf.reduce_mean(cross_entropy)
optimizer = tf.train.AdamOptimizer(learning_rate = rate)
training_operation = optimizer.minimize(loss_operation)

correct_prediction = tf.equal(tf.argmax(logits, 1), tf.argmax(one_hot_y, 1))
accuracy_operation = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
saver = tf.train.Saver()


# Train the model
statPoints = []
with tf.Session() as sess:
    wallTime = time.time()
    procTime = time.process_time()
    sess.run(tf.global_variables_initializer())

    print("Training...")
    print()
    log.write('Epoch\ttrainingError\tvalidationError\n')
    for i in range(EPOCHS):
        X_train, y_train = shuffle(X_train, y_train)
        for offset in range(0, n_train, BATCH_SIZE):
            end = offset + BATCH_SIZE
            batch_x, batch_y = X_train[offset:end], y_train[offset:end]
            sess.run(training_operation, feed_dict={x: batch_x, y: batch_y, keep_prob: dropout})

        training_accuracy = evaluateModel(X_train, y_train)
        validation_accuracy = evaluateModel(X_validation, y_validation)

        print("EPOCH {} ...".format(i + 1))
        print("Training Accuracy = {:.3f}".format(training_accuracy))
        print("Validation Accuracy = {:.3f}".format(validation_accuracy))
        print()
        log.write(str(i)+'\t'+str(1.0 - training_accuracy)+'\t'+str(1.0 - validation_accuracy)+'\n')


    saver.save(sess, 'trafficClassifier_normImgplusYUV')
    print("Model saved")
    print('Wall time: {:.4}'.format(time.time() - wallTime))
    print('Processor time: {:.4}'.format(time.process_time() - procTime))
    log.write('#Wall time: {:.4}\n'.format(time.time() - wallTime))

# Evaluate the model
with tf.Session() as sess:
    saver.restore(sess, tf.train.latest_checkpoint('.'))
    test_accuracy = evaluateModel(X_test, y_test)
    print("Test Accuracy = {:.3f}".format(test_accuracy))
    log.write("#Test Accuracy = {:.3f}".format(test_accuracy))
log.close()

# Test model against new downloaded images
dirContent = os.listdir(newImagesPath)

imgVec = []
idLabel = []
for imgName in dirContent:
    imgVec.append(misc.imread(newImagesPath+imgName))
    idLabel.append(int(imgName.split('_')[0]))

#plt.imshow(img)

imgVec = inputImgPreprocStage(imgVec)

with tf.Session() as sess:
    saver.restore(sess, tf.train.latest_checkpoint('.'))
    prediction = sess.run(detailedEvaluation, feed_dict={x: imgVec, keep_prob: 1.0})
    probVec = sess.run(tf.nn.top_k(sess.run(logits, feed_dict={x: imgVec, keep_prob: 1.0}), k=5))

correct = 0
for pred,ans in zip(prediction, idLabel):
    if pred == ans:
        correct = correct + 1

print("Model accuracy with new images = {:.3f}%".format(100*correct/len(prediction)))
print(probVec)
print(idLabel)
print(prediction)

