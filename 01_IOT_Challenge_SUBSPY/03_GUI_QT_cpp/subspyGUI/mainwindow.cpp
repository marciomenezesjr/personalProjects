/********************************************************           
    * 			SubSpy Graphical User Interface	           *   
    *                                                      *   
    * Author:  Marcio, Menezes                         	   *   
    * Date: 29.06.17                                       *   
    * Additional: this program is based on the GNU   	   *
	*	project Serial Port Plotter by Borislav  		   *   
    ********************************************************/  

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

/******************************************************************************************************************/
/* Constructor */
/******************************************************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    connected(false), plotting(false), autoScale(true), dataPointNumber(0), gCounter(0), dutyCycle(100), periodS(1), customCmd(255), STATE(WAIT_START), NUMBER_OF_POINTS(500), currentNode(0), prevTime(QDateTime::currentMSecsSinceEpoch()),filteredCounter(0)
{
    ui->setupUi(this);
    createUI();                                                                           	// Create the UI
    ui->plot->setBackground(QBrush(QColor(48,47,47)));                                    	// Background for the plot area
    setupPlot();                                                                          	// Setup plot area
    ui->stopPlotButton->setEnabled(false);                                                	// Plot button is disabled initially
    ui->sendDevCmd->setEnabled(false);

    ui->plot->setNotAntialiasedElements(QCP::aeAll);                                      	// used for higher performance (see QCustomPlot real time example)
    QFont font;
    font.setStyleStrategy(QFont::NoAntialias);
    ui->plot->xAxis->setTickLabelFont(font);
    ui->plot->yAxis->setTickLabelFont(font);
    ui->plot->yAxis2->setTickLabelFont(font);
    ui->plot->legend->setFont(font);

    ui->plot->yAxis->setAutoTickStep(true);                                              	// User can change tick step with a spin box
    ui->plot->xAxis->setTickLabelColor(QColor(170,170,170));                              	// Tick labels color
    ui->plot->yAxis->setTickLabelColor(QColor(170,170,170));                              	// See QCustomPlot examples / styled demo
    ui->plot->xAxis->grid()->setPen(QPen(QColor(170,170,170), 1, Qt::DotLine));
    ui->plot->yAxis->grid()->setPen(QPen(QColor(170,170,170), 1, Qt::DotLine));
    ui->plot->xAxis->grid()->setSubGridPen(QPen(QColor(80,80,80), 1, Qt::DotLine));
    ui->plot->yAxis->grid()->setSubGridPen(QPen(QColor(80,80,80), 1, Qt::DotLine));
    ui->plot->xAxis->grid()->setSubGridVisible(true);
    ui->plot->yAxis->grid()->setSubGridVisible(true);
    ui->plot->xAxis->setBasePen(QPen(QColor(170,170,170)));
    ui->plot->yAxis->setBasePen(QPen(QColor(170,170,170)));
    ui->plot->xAxis->setTickPen(QPen(QColor(170,170,170)));
    ui->plot->yAxis->setTickPen(QPen(QColor(170,170,170)));
    ui->plot->xAxis->setSubTickPen(QPen(QColor(170,170,170)));
    ui->plot->yAxis->setSubTickPen(QPen(QColor(170,170,170)));
    ui->plot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->plot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->plot->setInteraction(QCP::iRangeDrag, true);
    ui->plot->setInteraction(QCP::iRangeZoom, true);
    ui->plot->setInteraction(QCP::iSelectAxes, true);

    ui->plot->yAxis2->setAutoTickStep(true);                                              	// User can change tick step with a spin box
    ui->plot->yAxis2->setTickLabelColor(QColor(170,170,170));                              	// See QCustomPlot examples / styled demo
    ui->plot->yAxis2->grid()->setPen(QPen(QColor(170,170,170), 1, Qt::DotLine));
    ui->plot->yAxis2->grid()->setSubGridPen(QPen(QColor(80,80,80), 1, Qt::DotLine));
    ui->plot->yAxis2->grid()->setSubGridVisible(true);
    ui->plot->yAxis2->setBasePen(QPen(QColor(170,170,170)));
    ui->plot->yAxis2->setTickPen(QPen(QColor(170,170,170)));
    ui->plot->yAxis2->setSubTickPen(QPen(QColor(170,170,170)));
    ui->plot->yAxis2->setUpperEnding(QCPLineEnding::esBar);
    ui->plot->yAxis2->setVisible(true);
																							// Slot for printing coordinates
    connect(ui->plot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(onMouseMoveInPlot(QMouseEvent*)));
    connect(ui->plot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(onMouseWheel()));
    connect(ui->plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->plot->yAxis2, SLOT(setRange(QCPRange)));

    serialPort = NULL;                                                                    	// Set serial port pointer to NULL initially;
    //connect(&updateTimer, SIGNAL(timeout()), this, SLOT(replot()));                       // Connect update timer to replot slot

    ui->autoscaleButton->setDown(true);
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Destructor */
/******************************************************************************************************************/
MainWindow::~MainWindow()
{
    if(serialPort != NULL) delete serialPort;
    logFile.close();
    logFileFiltered.close();
    delete ui;
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/**Create the GUI */
/******************************************************************************************************************/
void MainWindow::createUI()
{
    for(QSerialPortInfo port : QSerialPortInfo::availablePorts()) {                       // List all available serial ports and populate ports combo box
        ui->comboPort->addItem(port.portName());
    }

    ui->devPeriod->addItems({ "1", "2", "5", "10", "30", "60", "255" });
    ui->devDutyCycle->addItems({ "1", "5", "10", "20", "30", "40", "50", "60","70", "80", "90", "100" });
    ui->devPeriod->setCurrentIndex(0);
    ui->devDutyCycle->setCurrentIndex(11);

    ui->devPeriod->setValidator( new QIntValidator(0, 255, this) );
    ui->devDutyCycle->setValidator( new QIntValidator(0, 255, this) );
    ui->customCommand->setValidator( new QIntValidator(0, 255, this) );

    ui->counterDisplay->setDigitCount(7);
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Enable/disable controls */
/******************************************************************************************************************/
void MainWindow::enableControls(bool enable)
{
    ui->comboPort->setEnabled(enable);
    ui->devPeriod->setEnabled(!enable);
    ui->devDutyCycle->setEnabled(!enable);
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Setup the plot area */
/******************************************************************************************************************/
void MainWindow::setupPlot()
{
    ui->plot->clearItems();                                                              // Remove everything from the plot

    ui->plot->xAxis->setRange(0, NUMBER_OF_POINTS);                                      // Set x axis range for specified number of points
    ui->plot->addGraph(ui->plot->xAxis, ui->plot->yAxis);
    ui->plot->graph(0)->setPen(QPen(Qt::green));
    ui->plot->addGraph(ui->plot->xAxis, ui->plot->yAxis2);
    ui->plot->graph(1)->setPen(QPen(Qt::yellow));

    ui->plot->graph(0)->setName("Dielectric");
    ui->plot->graph(1)->setName("Temperature");


    ui->plot->legend->setVisible(true);
    ui->plot->legend->setBrush(QBrush(QColor(80,80,80,230)));
    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft);

    ui->plot->xAxis->setLabel("Sample");
    ui->plot->yAxis->setLabel("Dielectric Constant");
    ui->plot->yAxis2->setLabel("Temperature");



    ui->plot->xAxis->setLabelColor(QColor(170,170,170));
    ui->plot->yAxis->setLabelColor(QColor(170,170,170));
    ui->plot->yAxis2->setLabelColor(QColor(170,170,170));

    ui->plot->xAxis->setLabelFont(QFont(QFont().family(), 12));
    ui->plot->yAxis->setLabelFont(QFont(QFont().family(), 12));
    ui->plot->yAxis2->setLabelFont(QFont(QFont().family(), 12));
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Open the inside serial port; connect its signals */
/******************************************************************************************************************/
void MainWindow::openPort(QSerialPortInfo portInfo, int baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    serialPort = new QSerialPort(portInfo, 0);                                            // Create a new serial port

    connect(this, SIGNAL(portOpenOK()), this, SLOT(portOpenedSuccess()));                 // Connect port signals to GUI slots
    connect(this, SIGNAL(portOpenFail()), this, SLOT(portOpenedFail()));
    connect(this, SIGNAL(portClosed()), this, SLOT(onPortClosed()));
    connect(this, SIGNAL(newData()), this, SLOT(onNewDataArrived()));
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));

    if(serialPort->open(QIODevice::ReadWrite) ) {
        serialPort->setBaudRate(baudRate);
        serialPort->setParity(parity);
        serialPort->setDataBits(dataBits);
        serialPort->setStopBits(stopBits);
        emit portOpenOK();
    } else {
        emit portOpenedFail();
        qDebug() << serialPort->errorString();
    }

}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Port Combo Box index changed slot; displays info for selected port when combo box is changed */
/******************************************************************************************************************/
void MainWindow::on_comboPort_currentIndexChanged(const QString &arg1)
{
    QSerialPortInfo selectedPort(arg1);                                                   // Dislplay info for selected port
    ui->statusBar->showMessage(selectedPort.description());
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Convert the data type as the index is changed */
/******************************************************************************************************************/
void MainWindow::on_devPeriod_currentIndexChanged(const QString &arg1){
    periodS = arg1.toInt();
}

void MainWindow::on_devDutyCycle_currentIndexChanged(const QString &arg1){
    dutyCycle = arg1.toInt();
}

void MainWindow::on_customCommand_currentIndexChanged(const QString &arg1){
    customCmd = arg1.toInt();
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Connect Button clicked slot; handles connect and disconnect */
/******************************************************************************************************************/
void MainWindow::on_connectButton_clicked()
{
    if(connected) {                                                                       // If application is connected, disconnect
        writeCmd2Device(DISABLE_DEVICE);
        serialPort->close();                                                              // Close serial port
        emit portClosed();                                                                // Notify application
        delete serialPort;                                                                // Delete the pointer
        serialPort = NULL;                                                                // Assign NULL to dangling pointer
        ui->connectButton->setText("Connect");                                            // Change Connect button text, to indicate disconnected
        ui->statusBar->showMessage("Disconnected!");                                      // Show message in status bar
        connected = false;                                                                // Set connected status flag to false
        plotting = false;                                                                 // Not plotting anymore
        ui->stopPlotButton->setEnabled(false);                                            // Take care of controls
        ui->sendDevCmd->setEnabled(false);
        enableControls(true);
        logFile.close();
        logFileFiltered.close();
    } else {                                                                              // If application is not connected, connect
                                                                                          // Get parameters from controls first
        QSerialPortInfo portInfo(ui->comboPort->currentText());                           // Temporary object, needed to create QSerialPort


        int baudRate = 115200;
        QSerialPort::DataBits dataBits = QSerialPort::Data8;
        QSerialPort::Parity parity = QSerialPort::NoParity;
        QSerialPort::StopBits stopBits = QSerialPort::OneStop;

        openPort(portInfo, baudRate, dataBits, parity, stopBits);                         // Open serial port and connect its signals
        writeCmd2Device(ENABLE_DEVICE);
    }
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Slot for port opened successfully */
/******************************************************************************************************************/
void MainWindow::portOpenedSuccess()
{
    //qDebug() << "Port opened signal received!";
    ui->connectButton->setText("Disconnect");                                        	// Change button text
    ui->statusBar->showMessage("Connected!");
    enableControls(false);                                                          	// Disable controls if port is open
    ui->stopPlotButton->setText("Stop Plot");                                             
    ui->stopPlotButton->setEnabled(true);												// Enable button for stopping plot
    ui->sendDevCmd->setEnabled(true);
    ui->saveJPGButton->setEnabled(true);                                             	// Enable button for saving plot
    updateTimer.start(100);                                                         	// Slot is refreshed 100 times per second
    connected = true;                                                                  	// Set flags
    plotting = true;

    openLogFile();
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Open log file, filtered log file logs only the selected node while the other file has all captured packets */
/******************************************************************************************************************/
void MainWindow::openLogFile(){
    QString fileName = QString::number(QDateTime::currentSecsSinceEpoch());
    fileName = "subspyLog_" + fileName + ".txt";
    logFile.open(fileName.toStdString());

    fileName = "filtered_" + fileName;
    logFileFiltered.open(fileName.toStdString());

    logFile << "time; sinkid; type; length; id; epoch; dielectric; temperature; pktSent; retries; lost; rtt; rssi; eeprom\n";
    logFileFiltered << "time; sinkid; type; length; id; epoch; dielectric; temperature; pktSent; retries; lost; rtt; rssi; eeprom\n";
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Slot for fail to open the port */
/******************************************************************************************************************/
void MainWindow::portOpenedFail()
{
    //qDebug() << "Port cannot be open signal received!";
    ui->statusBar->showMessage("Cannot open port!");
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Slot for closing the port */
/******************************************************************************************************************/
void MainWindow::onPortClosed()
{
    //qDebug() << "Port closed signal received!";
    updateTimer.stop();
    connected = false;
    disconnect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    disconnect(this, SIGNAL(portOpenOK()), this, SLOT(portOpenedSuccess()));             // Disconnect port signals to GUI slots
    disconnect(this, SIGNAL(portOpenFail()), this, SLOT(portOpenedFail()));
    disconnect(this, SIGNAL(portClosed()), this, SLOT(onPortClosed()));
    disconnect(this, SIGNAL(newData()), this, SLOT(onNewDataArrived()));
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Stop Plot Button */
/******************************************************************************************************************/
void MainWindow::on_stopPlotButton_clicked()
{
    if(plotting) {                                                                        // Stop plotting
        updateTimer.stop();                                                               // Stop updating plot timer
        plotting = false;
        ui->stopPlotButton->setText("Start Plot");
    } else {                                                                              // Start plotting
        updateTimer.start();                                                              // Start updating plot timer
        plotting = true;
        ui->stopPlotButton->setText("Stop Plot");
    }
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Autoscale button clicked */
/******************************************************************************************************************/
void MainWindow::on_autoscaleButton_clicked()
{
    autoScale = !autoScale;
    ui->autoscaleButton->setDown(autoScale);
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Slot for new data from serial port . Data is comming in QStringList and needs to be parsed */
/******************************************************************************************************************/
void MainWindow::onNewDataArrived()
{
    if(plotting) {
        dataPointNumber++;                                                                      // Increment data number
        filteredCounter++;
        ui->plot->graph(0)->addData(dataPointNumber, upkPld.dielectric);                     	// Add data to Graph 0
        ui->plot->graph(0)->removeDataBefore(dataPointNumber - NUMBER_OF_POINTS);               // Remove data from graph 0

        ui->plot->graph(1)->addData(dataPointNumber, upkPld.temperature);                  		// Add data to Graph 0
        ui->plot->graph(1)->removeDataBefore(dataPointNumber - NUMBER_OF_POINTS);               // Remove data from graph 0

        if(autoScale){
            ui->plot->graph(0)->rescaleAxes();
            ui->plot->graph(1)->rescaleAxes();
        }
        ui->plot->replot();
    }

    qint64 now = QDateTime::currentMSecsSinceEpoch();
    avgVecRate.append(now - prevTime);
    prevTime = now;

	// Append the new readings on the average vectors
    avgVecTmp.append(upkPld.temperature);
    avgVecDie.append(upkPld.dielectric);
    avgVecRssi.append(upkPld.rssi);

	// Average has limited size
    if(avgVecTmp.size() > NUMBER_OF_POINTS){
        avgVecTmp.erase(avgVecTmp.begin());
        avgVecDie.erase(avgVecDie.begin());
    }

    if(avgVecRate.size() > NUMBER_OF_POINTS/5){
        avgVecRate.erase(avgVecRate.begin());
    }

    if(avgVecRssi.size() > NUMBER_OF_POINTS/5){
        avgVecRssi.erase(avgVecRssi.begin());
    }

	// Calculate average of target values
    float avgTmp = std::accumulate(avgVecTmp.begin(), avgVecTmp.end(), 0.0) / avgVecTmp.size();
    float avgDie = std::accumulate(avgVecDie.begin(), avgVecDie.end(), 0.0) / avgVecDie.size();
    float avgRate = std::accumulate(avgVecRate.begin(), avgVecRate.end(), 0.0) / avgVecRate.size();
    float avgRssi = std::accumulate(avgVecRssi.begin(), avgVecRssi.end(), 0.0) / avgVecRssi.size();

	// Clear the indicators
    ui->comboAvgDie->clear();
    ui->comboAvgTmp->clear();
    ui->comboRate->clear();
    ui->comboRSSI->clear();
    ui->comboRTT->clear();
    ui->comboEEPROM->clear();
    ui->comboEPOCH->clear();
    ui->comboPKTLOST->clear();
    ui->comboPKTSENT->clear();
    ui->comboRETRIES->clear();
    ui->comboSINKID->clear();
    ui->comboPKTRX->clear();

	// Set the indicators
    ui->comboAvgDie->addItem(QString::number(avgDie));
    ui->comboAvgTmp->addItem(QString::number(avgTmp));
    ui->comboRate->addItem(QString::number(avgRate));
    ui->comboRSSI->addItem(QString::number(avgRssi));

    ui->comboRTT->addItem(QString::number(upkPld.rtt));
    ui->comboEEPROM->addItem(QString::number(upkPld.memoryPage));
    ui->comboEPOCH->addItem(QString::number(upkPld.epoch));
    ui->comboPKTLOST->addItem(QString::number(upkPld.packetsLost));
    ui->comboPKTSENT->addItem(QString::number(upkPld.packetsSent));
    ui->comboRETRIES->addItem(QString::number(upkPld.sendingRetries));
    ui->comboSINKID->addItem(QString::number(upkPld.sinkId));
    ui->comboPKTRX->addItem(QString::number(filteredCounter));
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Read data from the CDC port */
/******************************************************************************************************************/
void MainWindow::readData(){
    if(serialPort->bytesAvailable()) {                                                    	// If any bytes are available
        QByteArray data = serialPort->readAll();                                   			// Read all data in QByteArray
        int dsize = data.size();
        int msgClusteredPkts;
        int i;
        int offset = 0;
        if((dsize % 24) == 0) {                                                       		// If the byte array has one or more packets
            msgClusteredPkts = dsize / 24;													// Estimates how many packets are clustered together
            for(i=0; i<msgClusteredPkts; i++){												// Process each packet
                gCounter++;
                upkPld.unpack(data.mid(offset, 24));
                if(mappedNodes.indexOf(upkPld.sourceId) == -1){								// If a new node starts transmitting, it has to be included on the Node Id combobox
                    mappedNodes.append(upkPld.sourceId);
                    if(mappedNodes.size() == 1){
                        ui->comboNodes->setCurrentIndex(1);
                        currentNode = upkPld.sourceId;
                    }
                    ui->comboNodes->addItem(QString::number(upkPld.sourceId));
                }

                QString packet;
                packet.sprintf("%d; %d; %d; %d; %d; %d; %d; %d; %d; %d; %d; %d; %d; %d",upkPld.epoch, upkPld.sinkId, upkPld.packetType, upkPld.packetLength,
                               upkPld.sourceId, upkPld.epoch, upkPld.dielectric, upkPld.temperature, upkPld.packetsSent,
                               upkPld.sendingRetries, upkPld.packetsLost, upkPld.rtt, upkPld.rssi, upkPld.memoryPage);

                if(upkPld.sourceId == currentNode){											// If the packet received is from selected node
                    emit newData();                                       					// Emit signal for data received
                    logFileFiltered << (packet + "\n").toStdString();						// Write to filtered log file
                }

                logFile << (packet + "\n").toStdString();									// Write to complete log file
                ui->console->append(packet);
                ui->counterDisplay->display(gCounter);										// Console appends packet
                offset += 24;
            }
        }
        else{																				// If the data buffer has fragments of packets, just display the raw data on the console
            QString dataHEX = QString(data.toHex());
            logFile << "b#" << QString::number(data.size()).toStdString() <<":" << (dataHEX).toStdString() << std::endl;
            ui->console->append(dataHEX);
        }
    }
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* If the Node Id has been changed */
/******************************************************************************************************************/
void MainWindow::on_comboNodes_currentIndexChanged()
{
    currentNode = ui->comboNodes->currentText().toInt();
    emit ui->resetPlotButton->click();
    filteredCounter = 0;
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Save a JPG image of the plot to current EXE directory */
/******************************************************************************************************************/
void MainWindow::on_saveJPGButton_clicked()
{
    ui->plot->saveJpg(QString::number(QDateTime::currentSecsSinceEpoch()) + ".jpg");
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Reset the zoom of the plot to the initial values */
/******************************************************************************************************************/
void MainWindow::on_resetPlotButton_clicked()
{
    dataPointNumber = 0;

    ui->plot->rescaleAxes();
    ui->plot->graph(0)->clearData();
    ui->plot->graph(1)->clearData();
    ui->plot->replot();
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Clear the console log */
/******************************************************************************************************************/
void MainWindow::on_resetMonWindow_clicked(){
    ui->console->clear();
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Send command button has been clicked */
/******************************************************************************************************************/
void MainWindow::on_sendDevCmd_clicked(){
    writeCmd2Device(DEVPASSWD);
    ui->statusBar->showMessage("Command successfully sent!");
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Clear the console log */
/******************************************************************************************************************/
void MainWindow::on_refreshPortsButton_clicked(){
    ui->comboPort->clear();
    for(QSerialPortInfo port : QSerialPortInfo::availablePorts()) {                       // List all available serial ports and populate ports combo box
        ui->comboPort->addItem(port.portName());
    }
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Write command on the wireless adapter */
/******************************************************************************************************************/
void MainWindow::writeCmd2Device(int code){
    QByteArray writeData;
    writeData.append(1,code);
    writeData.append(1,periodS);
    writeData.append(1,dutyCycle);
    writeData.append(1,customCmd);
    qint64 bytesWritten = serialPort->write(writeData);
    serialPort->waitForBytesWritten(5000);

    // TODO: implement appropriate error handling
    if (bytesWritten == -1) {
        // Throw appropriate error
        QCoreApplication::exit(1);
    } else if (bytesWritten != writeData.size()) {
        // Throw appropriate error
        QCoreApplication::exit(1);
    }
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Prints coordinates of mouse pointer in status bar on mouse release */
/******************************************************************************************************************/
void MainWindow::onMouseMoveInPlot(QMouseEvent *event)
{
    int xx = ui->plot->xAxis->pixelToCoord(event->x());
    int yy = ui->plot->yAxis->pixelToCoord(event->y());
    QString coordinates("X: %1 Y: %2");
    coordinates = coordinates.arg(xx).arg(yy);
    ui->statusBar->showMessage(coordinates);
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Mouse zoom control */
/******************************************************************************************************************/
void MainWindow::onMouseWheel()
{
  // if an axis is selected, only allow the direction of that axis to be zoomed
  // if no axis is selected, both directions may be zoomed

  if (ui->plot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->plot->axisRect()->setRangeZoom(ui->plot->xAxis->orientation());
  else if (ui->plot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->plot->axisRect()->setRangeZoom(ui->plot->yAxis->orientation());
  else
    ui->plot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Spin box controls how many data points are collected and displayed */
/******************************************************************************************************************/
void MainWindow::on_spinPoints_valueChanged(int arg1)// Deprecated
{
    NUMBER_OF_POINTS = arg1;
    ui->plot->replot();
}
/******************************************************************************************************************/


/******************************************************************************************************************/
/* Auxiliar function to unpack the byte formatted packet */
/******************************************************************************************************************/
void Payload::unpack(QByteArray data){
    uint8_t *temp = (uint8_t *)data.data();

    sinkId = temp[0];
    packetType = temp[1];
    packetLength = temp[2];
    sourceId = temp[3];
    sendingRetries = temp[14];

    epoch = this->fetch(&temp[4], BYTE4X);
    dielectric = (int16_t)this->fetch(&temp[8], BYTE2X);
    temperature = (int16_t)this->fetch(&temp[10], BYTE2X);
    packetsSent = this->fetch(&temp[12], BYTE2X);
    packetsLost = this->fetch(&temp[15], BYTE2X);
    rssi = (int16_t)this->fetch(&temp[19], BYTE2X);
    rtt = (int16_t)this->fetch(&temp[17], BYTE2X);
    memoryPage = this->fetch(&temp[21], BYTE3X);
}
/******************************************************************************************************************/

/******************************************************************************************************************/
/* Auxiliar function to fetch bytes */
/******************************************************************************************************************/
int Payload::fetch(uint8_t *data, int size){
    int i;
    int auxInt = 0;
    for(i=0; i<size; i++){
        auxInt += data[i];
        if(i < (size -1)){
            auxInt <<= 8;
        }
    }
    return auxInt;
}
/******************************************************************************************************************/

