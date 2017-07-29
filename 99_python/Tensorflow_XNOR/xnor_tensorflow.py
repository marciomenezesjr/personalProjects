import tensorflow as tf
import matplotlib.pyplot as plt
sess = tf.InteractiveSession()

lRate = [0.01, 0.1, 0.5, 1.0]   # Optimizer learning rate
classes = 2                     # True or False
inSize = 2                      # Number of inputs
steps = 2000                    # Number of training steps
tolerance = 0.1                 # cross entropy tolerance for early termination
hiddenNeurons = 20

# XNOR dataset
input = [[0, 0], [0, 1], [1, 0], [1, 1]]
output = [[0, 1],  [1, 0],  [1, 0], [0, 1]]    # one hot encoded outputs


# tensorflow placeholders
x = tf.placeholder("float", [None, inSize])
y_ = tf.placeholder("float", [None, classes])

# first NN layer, weights and bias are initialized with random uniform distribution
weight1 = tf.Variable(tf.random_uniform([inSize, hiddenNeurons], -1, 1))
bias1 = tf.Variable(tf.random_uniform([hiddenNeurons], -1, 1))
hidden = tf.nn.relu(tf.matmul(x, weight1) + bias1)

# second NN layer, weights and bias are initialized with random uniform distribution
weight2 = tf.Variable(tf.random_uniform([hiddenNeurons, classes], -1, 1))
bias2 = tf.Variable(tf.zeros([classes]))
final = tf.matmul(hidden, weight2) + bias2

# compute softmax activation (classification algorithm)
y = tf.nn.softmax(final)

# Loss operation and optimizer
crossEntropy = -tf.reduce_sum(y_*tf.log(y))


# Model evaluation
correctPrediction = tf.equal(tf.argmax(y, 1), tf.argmax(y_, 1))
accuracyOperation = tf.reduce_mean(tf.cast(correctPrediction, "float"))

# Train
entropyVec = []
accuracyVec = []

for learningRate in lRate:
    trainStep = tf.train.GradientDescentOptimizer(learningRate).minimize(crossEntropy)
    entropyVecAux = []
    accuracyVecAux = []
    print('\nLearning rate = %f' % learningRate)
    tf.global_variables_initializer().run()
    for step in range(steps):
        entropy, a = sess.run([crossEntropy, trainStep], feed_dict={x: input, y_: output})
        accuracy = accuracyOperation.eval({x: input, y_: output})

        # allows early termination if minimum tolerance is achieved
        if entropy < tolerance:
            break
        print("step %d : entropy %s : accuracy %s" % (step, entropy, accuracy))
        entropyVecAux.append(entropy)
        accuracyVecAux.append(accuracy)
    entropyVec.append(entropyVecAux/max(entropyVecAux))
    accuracyVec.append(accuracyVecAux)

learnedLogic = tf.argmax(y, 1)
print(learnedLogic.eval({x: input}))

fig, ax = plt.subplots(nrows=2, ncols=2)

ax[0, 0].plot(entropyVec[0], color='b', label="Entropy")
ax[0, 0].plot(accuracyVec[0], color='r', label="Accuracy")
ax[0, 0].set_title('Learning Rate = 0.01')
ax[0, 0].grid()
ax[0, 0].set_ylabel('Cross Entropy / Accuracy')
ax[0, 0].legend()

ax[0, 1].plot(entropyVec[1], color='g', label="Entropy")
ax[0, 1].plot(accuracyVec[1], color='r', label="Accuracy")
ax[0, 1].set_title('Learning Rate = 0.1')
ax[0, 1].grid()
ax[0, 1].set_ylabel('Cross Entropy / Accuracy')
ax[0, 1].legend()

ax[1, 0].plot(entropyVec[2], color='m', label="Entropy")
ax[1, 0].plot(accuracyVec[2], color='r', label="Accuracy")
ax[1, 0].set_title('Learning Rate = 0.5')
ax[1, 0].grid()
ax[1, 0].set_xlabel('Step')
ax[1, 0].set_ylabel('Cross Entropy / Accuracy')
ax[1, 0].legend()

ax[1, 1].plot(entropyVec[3], color='k', label="Entropy")
ax[1, 1].plot(accuracyVec[3], color='r', label="Accuracy")
ax[1, 1].set_title('Learning Rate = 1.0')
ax[1, 1].grid()
ax[1, 1].set_xlabel('Step')
ax[1, 1].set_ylabel('Cross Entropy / Accuracy')
ax[1, 1].legend()



print('Success!')






