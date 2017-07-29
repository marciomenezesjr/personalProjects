/********************************************************           
    * 			SubSpy Graphical User Interface	           *   
    *                                                      *   
    * Author:  Marcio, Menezes                         	   *   
    * Date: 29.06.17                                       *   
    * Additional: this program is based on the GNU   	   *
	*	project Serial Port Plotter by Borislav  		   *   
    ********************************************************/  

#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QtSerialPort/QtSerialPort>
#include <QSerialPortInfo>
#include <fstream>
#include <iostream>
#include <numeric>

#define START_MSG       '$'
#define END_MSG         ';'

#define WAIT_START      1
#define IN_MESSAGE      2
#define UNDEFINED       3
#define BYTE2X          2
#define BYTE3X          3
#define BYTE4X          4
#define DEVPASSWD       0xAB
#define ENABLE_DEVICE   0xEF
#define DISABLE_DEVICE  0xFE

namespace Ui {
    class MainWindow;
}

class Payload{
public:
    int sinkId;
    int packetType;
    int packetLength;
    int sourceId;
    int epoch;
    int dielectric;
    int temperature;
    int packetsSent;
    int sendingRetries;
    int packetsLost;
    int rtt;
    int rssi;
    int memoryPage;

    //Payload();
    void unpack(QByteArray data);
    int fetch(uint8_t *data, int size);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_comboPort_currentIndexChanged(const QString &arg1);                           // Slot displays message on status bar
    void on_devPeriod_currentIndexChanged(const QString &arg1);
    void on_devDutyCycle_currentIndexChanged(const QString &arg1);
    void on_customCommand_currentIndexChanged(const QString &arg1);

    void on_connectButton_clicked();                                                      // Manages connect/disconnect
    void portOpenedSuccess();                                                             // Called when port opens OK
    void portOpenedFail();                                                                // Called when port fails to open
    void onPortClosed();                                                                  // Called when closing the port
    void on_stopPlotButton_clicked();                                                     // Starts and stops plotting
    void on_autoscaleButton_clicked();
    void on_resetMonWindow_clicked();
    void on_refreshPortsButton_clicked();
    void on_sendDevCmd_clicked();
    void onNewDataArrived();                                                              // Slot for new data from serial port
    void readData();                                                                      // Slot for inside serial port
    void on_comboNodes_currentIndexChanged();                                             // Display number of axes and colors in status bar
    void on_saveJPGButton_clicked();                                                      // Button for saving JPG
    void on_resetPlotButton_clicked();                                                    // Resets plot to initial zoom and coordinates
    void onMouseMoveInPlot(QMouseEvent *event);                                           // Displays coordinates of mouse pointer when clicked in plot in status bar
    void onMouseWheel();
    void on_spinPoints_valueChanged(int arg1);                                            // Spin box controls how many data points are collected and displayed
    void openLogFile();
    void writeCmd2Device(int code);

signals:
    void portOpenFail();                                                                  // Emitted when cannot open port
    void portOpenOK();                                                                    // Emitted when port is open
    void portClosed();                                                                    // Emitted when port is closed
    void newData();                                                                       // Emitted when new data has arrived

private:
    Ui::MainWindow *ui;

    bool connected;                                                                       // Status connection variable
    bool plotting;                                                                        // Status plotting variable
    bool autoScale;
    int dataPointNumber;                                                                  // Keep track of data points
    int gCounter;
    char dutyCycle;
    char periodS;
    char customCmd;
    QTimer updateTimer;                                                                   // Timer used for replotting the plot
    QTime timeOfFirstData;                                                                // Record the time of the first data point
    double timeBetweenSamples;                                                            // Store time between samples
    QSerialPort *serialPort;                                                              // Serial port; runs in this thread
    int STATE;                                                                            // State of recieiving message from port
    int NUMBER_OF_POINTS;                                                                 // Number of points plotted
    int currentNode;
    Payload upkPld;
    QVector<int> mappedNodes;
    QVector<int> avgVecTmp;
    QVector<int> avgVecDie;
    QVector<int> avgVecRate;
    QVector<int> avgVecRssi;
    qint64 prevTime;
    int filteredCounter;

    std::ofstream logFile;
    std::ofstream logFileFiltered;

    void createUI();                                                                      // Populate the controls
    void enableControls(bool enable);                                                     // Enable/disable controls
    void setupPlot();                                                                     // Setup the QCustomPlot
                                                                                          // Open the inside serial port with these parameters
    void openPort(QSerialPortInfo portInfo, int baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits);
};

#endif                                                                                    // MAINWINDOW_HPP
