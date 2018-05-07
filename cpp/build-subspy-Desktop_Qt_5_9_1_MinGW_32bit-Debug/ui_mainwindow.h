/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionHow_to_use;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_2;
    QCustomPlot *plot;
    QSpacerItem *horizontalSpacer;
    QTextBrowser *console;
    QVBoxLayout *controlsLayout;
    QGroupBox *PortControlsBox;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPort;
    QComboBox *comboPort;
    QPushButton *refreshPortsButton;
    QPushButton *connectButton;
    QGroupBox *DeviceControls;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *CounterDisplay;
    QLabel *counterDisplayLabel;
    QLCDNumber *counterDisplay;
    QHBoxLayout *Period;
    QLabel *periodLabel;
    QComboBox *devPeriod;
    QHBoxLayout *DutyCycle;
    QLabel *dutyCycleLabel;
    QComboBox *devDutyCycle;
    QHBoxLayout *CustomCommand;
    QLabel *customCommandLabel;
    QComboBox *customCommand;
    QPushButton *sendDevCmd;
    QGroupBox *DeviceStatus;
    QGridLayout *gridLayout_42;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *labelNodes;
    QComboBox *comboNodes;
    QHBoxLayout *avgTmpLayout;
    QLabel *avgTmpLabel;
    QComboBox *comboAvgTmp;
    QHBoxLayout *avgDieLayout;
    QLabel *avgDieLabel;
    QComboBox *comboAvgDie;
    QHBoxLayout *rateLayout;
    QLabel *rateLabel;
    QComboBox *comboRate;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label;
    QComboBox *comboRSSI;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_2;
    QComboBox *comboRTT;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_3;
    QComboBox *comboEPOCH;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_4;
    QComboBox *comboPKTSENT;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_9;
    QComboBox *comboPKTRX;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_5;
    QComboBox *comboPKTLOST;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_6;
    QComboBox *comboRETRIES;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_8;
    QComboBox *comboSINKID;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_7;
    QComboBox *comboEEPROM;
    QSpacerItem *verticalSpacer;
    QGroupBox *PlotControlsBox;
    QGridLayout *gridLayout_2;
    QVBoxLayout *plotControlsLayout;
    QHBoxLayout *horizontalLayout_10;
    QLabel *pointsLabel;
    QSpinBox *spinPoints;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *autoscaleButton;
    QPushButton *resetPlotButton;
    QPushButton *stopPlotButton;
    QPushButton *saveJPGButton;
    QPushButton *resetMonWindow;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(924, 831);
        MainWindow->setMinimumSize(QSize(840, 768));
        actionHow_to_use = new QAction(MainWindow);
        actionHow_to_use->setObjectName(QStringLiteral("actionHow_to_use"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        plot = new QCustomPlot(centralWidget);
        plot->setObjectName(QStringLiteral("plot"));

        verticalLayout_2->addWidget(plot);

        horizontalSpacer = new QSpacerItem(663, 13, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer);

        console = new QTextBrowser(centralWidget);
        console->setObjectName(QStringLiteral("console"));
        console->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(console->sizePolicy().hasHeightForWidth());
        console->setSizePolicy(sizePolicy);
        console->setMaximumSize(QSize(16777215, 200));

        verticalLayout_2->addWidget(console);


        gridLayout_3->addLayout(verticalLayout_2, 0, 2, 1, 1);

        controlsLayout = new QVBoxLayout();
        controlsLayout->setSpacing(5);
        controlsLayout->setObjectName(QStringLiteral("controlsLayout"));
        PortControlsBox = new QGroupBox(centralWidget);
        PortControlsBox->setObjectName(QStringLiteral("PortControlsBox"));
        PortControlsBox->setFlat(false);
        PortControlsBox->setCheckable(false);
        gridLayout = new QGridLayout(PortControlsBox);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(4, 8, 4, 4);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelPort = new QLabel(PortControlsBox);
        labelPort->setObjectName(QStringLiteral("labelPort"));
        labelPort->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(labelPort);

        comboPort = new QComboBox(PortControlsBox);
        comboPort->setObjectName(QStringLiteral("comboPort"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboPort->sizePolicy().hasHeightForWidth());
        comboPort->setSizePolicy(sizePolicy1);
        comboPort->setMinimumSize(QSize(69, 0));
        comboPort->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(comboPort);


        verticalLayout_3->addLayout(horizontalLayout);

        refreshPortsButton = new QPushButton(PortControlsBox);
        refreshPortsButton->setObjectName(QStringLiteral("refreshPortsButton"));

        verticalLayout_3->addWidget(refreshPortsButton);

        connectButton = new QPushButton(PortControlsBox);
        connectButton->setObjectName(QStringLiteral("connectButton"));
        connectButton->setMinimumSize(QSize(0, 0));
        connectButton->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_3->addWidget(connectButton);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        controlsLayout->addWidget(PortControlsBox);

        DeviceControls = new QGroupBox(centralWidget);
        DeviceControls->setObjectName(QStringLiteral("DeviceControls"));
        gridLayout_4 = new QGridLayout(DeviceControls);
        gridLayout_4->setSpacing(3);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(4, 8, 4, 4);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(3);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        CounterDisplay = new QHBoxLayout();
        CounterDisplay->setSpacing(6);
        CounterDisplay->setObjectName(QStringLiteral("CounterDisplay"));
        counterDisplayLabel = new QLabel(DeviceControls);
        counterDisplayLabel->setObjectName(QStringLiteral("counterDisplayLabel"));

        CounterDisplay->addWidget(counterDisplayLabel);

        counterDisplay = new QLCDNumber(DeviceControls);
        counterDisplay->setObjectName(QStringLiteral("counterDisplay"));

        CounterDisplay->addWidget(counterDisplay);


        verticalLayout_5->addLayout(CounterDisplay);

        Period = new QHBoxLayout();
        Period->setSpacing(6);
        Period->setObjectName(QStringLiteral("Period"));
        periodLabel = new QLabel(DeviceControls);
        periodLabel->setObjectName(QStringLiteral("periodLabel"));

        Period->addWidget(periodLabel);

        devPeriod = new QComboBox(DeviceControls);
        devPeriod->setObjectName(QStringLiteral("devPeriod"));
        sizePolicy1.setHeightForWidth(devPeriod->sizePolicy().hasHeightForWidth());
        devPeriod->setSizePolicy(sizePolicy1);
        devPeriod->setEditable(true);

        Period->addWidget(devPeriod);


        verticalLayout_5->addLayout(Period);

        DutyCycle = new QHBoxLayout();
        DutyCycle->setSpacing(6);
        DutyCycle->setObjectName(QStringLiteral("DutyCycle"));
        DutyCycle->setSizeConstraint(QLayout::SetDefaultConstraint);
        dutyCycleLabel = new QLabel(DeviceControls);
        dutyCycleLabel->setObjectName(QStringLiteral("dutyCycleLabel"));

        DutyCycle->addWidget(dutyCycleLabel);

        devDutyCycle = new QComboBox(DeviceControls);
        devDutyCycle->setObjectName(QStringLiteral("devDutyCycle"));
        sizePolicy1.setHeightForWidth(devDutyCycle->sizePolicy().hasHeightForWidth());
        devDutyCycle->setSizePolicy(sizePolicy1);
        devDutyCycle->setEditable(true);

        DutyCycle->addWidget(devDutyCycle);


        verticalLayout_5->addLayout(DutyCycle);

        CustomCommand = new QHBoxLayout();
        CustomCommand->setSpacing(6);
        CustomCommand->setObjectName(QStringLiteral("CustomCommand"));
        customCommandLabel = new QLabel(DeviceControls);
        customCommandLabel->setObjectName(QStringLiteral("customCommandLabel"));

        CustomCommand->addWidget(customCommandLabel);

        customCommand = new QComboBox(DeviceControls);
        customCommand->setObjectName(QStringLiteral("customCommand"));
        sizePolicy1.setHeightForWidth(customCommand->sizePolicy().hasHeightForWidth());
        customCommand->setSizePolicy(sizePolicy1);
        customCommand->setEditable(true);

        CustomCommand->addWidget(customCommand);


        verticalLayout_5->addLayout(CustomCommand);

        sendDevCmd = new QPushButton(DeviceControls);
        sendDevCmd->setObjectName(QStringLiteral("sendDevCmd"));

        verticalLayout_5->addWidget(sendDevCmd);


        gridLayout_4->addLayout(verticalLayout_5, 0, 0, 1, 1);


        controlsLayout->addWidget(DeviceControls);

        DeviceStatus = new QGroupBox(centralWidget);
        DeviceStatus->setObjectName(QStringLiteral("DeviceStatus"));
        DeviceStatus->setFlat(false);
        DeviceStatus->setCheckable(false);
        gridLayout_42 = new QGridLayout(DeviceStatus);
        gridLayout_42->setSpacing(3);
        gridLayout_42->setContentsMargins(11, 11, 11, 11);
        gridLayout_42->setObjectName(QStringLiteral("gridLayout_42"));
        gridLayout_42->setContentsMargins(4, 8, 4, 4);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        labelNodes = new QLabel(DeviceStatus);
        labelNodes->setObjectName(QStringLiteral("labelNodes"));
        labelNodes->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(labelNodes);

        comboNodes = new QComboBox(DeviceStatus);
        comboNodes->setObjectName(QStringLiteral("comboNodes"));
        sizePolicy1.setHeightForWidth(comboNodes->sizePolicy().hasHeightForWidth());
        comboNodes->setSizePolicy(sizePolicy1);
        comboNodes->setMinimumSize(QSize(0, 0));
        comboNodes->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(comboNodes);


        verticalLayout->addLayout(horizontalLayout_6);

        avgTmpLayout = new QHBoxLayout();
        avgTmpLayout->setSpacing(6);
        avgTmpLayout->setObjectName(QStringLiteral("avgTmpLayout"));
        avgTmpLabel = new QLabel(DeviceStatus);
        avgTmpLabel->setObjectName(QStringLiteral("avgTmpLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(avgTmpLabel->sizePolicy().hasHeightForWidth());
        avgTmpLabel->setSizePolicy(sizePolicy2);

        avgTmpLayout->addWidget(avgTmpLabel);

        comboAvgTmp = new QComboBox(DeviceStatus);
        comboAvgTmp->setObjectName(QStringLiteral("comboAvgTmp"));
        comboAvgTmp->setEnabled(true);
        sizePolicy1.setHeightForWidth(comboAvgTmp->sizePolicy().hasHeightForWidth());
        comboAvgTmp->setSizePolicy(sizePolicy1);
        comboAvgTmp->setEditable(true);

        avgTmpLayout->addWidget(comboAvgTmp);


        verticalLayout->addLayout(avgTmpLayout);

        avgDieLayout = new QHBoxLayout();
        avgDieLayout->setSpacing(6);
        avgDieLayout->setObjectName(QStringLiteral("avgDieLayout"));
        avgDieLabel = new QLabel(DeviceStatus);
        avgDieLabel->setObjectName(QStringLiteral("avgDieLabel"));
        avgDieLabel->setMinimumSize(QSize(60, 0));

        avgDieLayout->addWidget(avgDieLabel);

        comboAvgDie = new QComboBox(DeviceStatus);
        comboAvgDie->setObjectName(QStringLiteral("comboAvgDie"));
        comboAvgDie->setEnabled(true);
        sizePolicy1.setHeightForWidth(comboAvgDie->sizePolicy().hasHeightForWidth());
        comboAvgDie->setSizePolicy(sizePolicy1);
        comboAvgDie->setMinimumSize(QSize(0, 0));
        comboAvgDie->setEditable(true);

        avgDieLayout->addWidget(comboAvgDie);


        verticalLayout->addLayout(avgDieLayout);

        rateLayout = new QHBoxLayout();
        rateLayout->setSpacing(6);
        rateLayout->setObjectName(QStringLiteral("rateLayout"));
        rateLabel = new QLabel(DeviceStatus);
        rateLabel->setObjectName(QStringLiteral("rateLabel"));

        rateLayout->addWidget(rateLabel);

        comboRate = new QComboBox(DeviceStatus);
        comboRate->setObjectName(QStringLiteral("comboRate"));
        comboRate->setEnabled(true);
        sizePolicy1.setHeightForWidth(comboRate->sizePolicy().hasHeightForWidth());
        comboRate->setSizePolicy(sizePolicy1);
        comboRate->setEditable(true);

        rateLayout->addWidget(comboRate);


        verticalLayout->addLayout(rateLayout);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QStringLiteral("horizontalLayout_20"));
        label = new QLabel(DeviceStatus);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_20->addWidget(label);

        comboRSSI = new QComboBox(DeviceStatus);
        comboRSSI->setObjectName(QStringLiteral("comboRSSI"));
        sizePolicy1.setHeightForWidth(comboRSSI->sizePolicy().hasHeightForWidth());
        comboRSSI->setSizePolicy(sizePolicy1);
        comboRSSI->setEditable(true);

        horizontalLayout_20->addWidget(comboRSSI);


        verticalLayout->addLayout(horizontalLayout_20);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QStringLiteral("horizontalLayout_19"));
        label_2 = new QLabel(DeviceStatus);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_19->addWidget(label_2);

        comboRTT = new QComboBox(DeviceStatus);
        comboRTT->setObjectName(QStringLiteral("comboRTT"));
        sizePolicy1.setHeightForWidth(comboRTT->sizePolicy().hasHeightForWidth());
        comboRTT->setSizePolicy(sizePolicy1);
        comboRTT->setEditable(true);

        horizontalLayout_19->addWidget(comboRTT);


        verticalLayout->addLayout(horizontalLayout_19);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QStringLiteral("horizontalLayout_18"));
        label_3 = new QLabel(DeviceStatus);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_18->addWidget(label_3);

        comboEPOCH = new QComboBox(DeviceStatus);
        comboEPOCH->setObjectName(QStringLiteral("comboEPOCH"));
        sizePolicy1.setHeightForWidth(comboEPOCH->sizePolicy().hasHeightForWidth());
        comboEPOCH->setSizePolicy(sizePolicy1);
        comboEPOCH->setEditable(true);

        horizontalLayout_18->addWidget(comboEPOCH);


        verticalLayout->addLayout(horizontalLayout_18);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QStringLiteral("horizontalLayout_17"));
        label_4 = new QLabel(DeviceStatus);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_17->addWidget(label_4);

        comboPKTSENT = new QComboBox(DeviceStatus);
        comboPKTSENT->setObjectName(QStringLiteral("comboPKTSENT"));
        sizePolicy1.setHeightForWidth(comboPKTSENT->sizePolicy().hasHeightForWidth());
        comboPKTSENT->setSizePolicy(sizePolicy1);
        comboPKTSENT->setEditable(true);

        horizontalLayout_17->addWidget(comboPKTSENT);


        verticalLayout->addLayout(horizontalLayout_17);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QStringLiteral("horizontalLayout_23"));
        label_9 = new QLabel(DeviceStatus);
        label_9->setObjectName(QStringLiteral("label_9"));

        horizontalLayout_23->addWidget(label_9);

        comboPKTRX = new QComboBox(DeviceStatus);
        comboPKTRX->setObjectName(QStringLiteral("comboPKTRX"));
        sizePolicy1.setHeightForWidth(comboPKTRX->sizePolicy().hasHeightForWidth());
        comboPKTRX->setSizePolicy(sizePolicy1);
        comboPKTRX->setEditable(true);

        horizontalLayout_23->addWidget(comboPKTRX);


        verticalLayout->addLayout(horizontalLayout_23);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QStringLiteral("horizontalLayout_16"));
        label_5 = new QLabel(DeviceStatus);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_16->addWidget(label_5);

        comboPKTLOST = new QComboBox(DeviceStatus);
        comboPKTLOST->setObjectName(QStringLiteral("comboPKTLOST"));
        sizePolicy1.setHeightForWidth(comboPKTLOST->sizePolicy().hasHeightForWidth());
        comboPKTLOST->setSizePolicy(sizePolicy1);
        comboPKTLOST->setEditable(true);

        horizontalLayout_16->addWidget(comboPKTLOST);


        verticalLayout->addLayout(horizontalLayout_16);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_6 = new QLabel(DeviceStatus);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_15->addWidget(label_6);

        comboRETRIES = new QComboBox(DeviceStatus);
        comboRETRIES->setObjectName(QStringLiteral("comboRETRIES"));
        sizePolicy1.setHeightForWidth(comboRETRIES->sizePolicy().hasHeightForWidth());
        comboRETRIES->setSizePolicy(sizePolicy1);
        comboRETRIES->setEditable(true);

        horizontalLayout_15->addWidget(comboRETRIES);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QStringLiteral("horizontalLayout_22"));
        label_8 = new QLabel(DeviceStatus);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_22->addWidget(label_8);

        comboSINKID = new QComboBox(DeviceStatus);
        comboSINKID->setObjectName(QStringLiteral("comboSINKID"));
        sizePolicy1.setHeightForWidth(comboSINKID->sizePolicy().hasHeightForWidth());
        comboSINKID->setSizePolicy(sizePolicy1);
        comboSINKID->setEditable(true);

        horizontalLayout_22->addWidget(comboSINKID);


        verticalLayout->addLayout(horizontalLayout_22);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QStringLiteral("horizontalLayout_21"));
        label_7 = new QLabel(DeviceStatus);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_21->addWidget(label_7);

        comboEEPROM = new QComboBox(DeviceStatus);
        comboEEPROM->setObjectName(QStringLiteral("comboEEPROM"));
        sizePolicy1.setHeightForWidth(comboEEPROM->sizePolicy().hasHeightForWidth());
        comboEEPROM->setSizePolicy(sizePolicy1);
        comboEEPROM->setEditable(true);

        horizontalLayout_21->addWidget(comboEEPROM);


        verticalLayout->addLayout(horizontalLayout_21);


        gridLayout_42->addLayout(verticalLayout, 0, 0, 1, 1);


        controlsLayout->addWidget(DeviceStatus);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        controlsLayout->addItem(verticalSpacer);

        PlotControlsBox = new QGroupBox(centralWidget);
        PlotControlsBox->setObjectName(QStringLiteral("PlotControlsBox"));
        gridLayout_2 = new QGridLayout(PlotControlsBox);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(4, 8, 4, 4);
        plotControlsLayout = new QVBoxLayout();
        plotControlsLayout->setSpacing(3);
        plotControlsLayout->setObjectName(QStringLiteral("plotControlsLayout"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        pointsLabel = new QLabel(PlotControlsBox);
        pointsLabel->setObjectName(QStringLiteral("pointsLabel"));
        pointsLabel->setMinimumSize(QSize(0, 0));
        pointsLabel->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_10->addWidget(pointsLabel);

        spinPoints = new QSpinBox(PlotControlsBox);
        spinPoints->setObjectName(QStringLiteral("spinPoints"));
        spinPoints->setMinimumSize(QSize(69, 0));
        spinPoints->setMaximumSize(QSize(16777215, 16777215));
        spinPoints->setMinimum(10);
        spinPoints->setMaximum(1000);
        spinPoints->setValue(500);

        horizontalLayout_10->addWidget(spinPoints);


        plotControlsLayout->addLayout(horizontalLayout_10);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));

        plotControlsLayout->addLayout(horizontalLayout_8);

        autoscaleButton = new QPushButton(PlotControlsBox);
        autoscaleButton->setObjectName(QStringLiteral("autoscaleButton"));

        plotControlsLayout->addWidget(autoscaleButton);

        resetPlotButton = new QPushButton(PlotControlsBox);
        resetPlotButton->setObjectName(QStringLiteral("resetPlotButton"));

        plotControlsLayout->addWidget(resetPlotButton);

        stopPlotButton = new QPushButton(PlotControlsBox);
        stopPlotButton->setObjectName(QStringLiteral("stopPlotButton"));
        stopPlotButton->setMinimumSize(QSize(0, 0));
        stopPlotButton->setMaximumSize(QSize(16777215, 16777215));

        plotControlsLayout->addWidget(stopPlotButton);

        saveJPGButton = new QPushButton(PlotControlsBox);
        saveJPGButton->setObjectName(QStringLiteral("saveJPGButton"));

        plotControlsLayout->addWidget(saveJPGButton);

        resetMonWindow = new QPushButton(PlotControlsBox);
        resetMonWindow->setObjectName(QStringLiteral("resetMonWindow"));

        plotControlsLayout->addWidget(resetMonWindow);


        gridLayout_2->addLayout(plotControlsLayout, 0, 0, 1, 1);


        controlsLayout->addWidget(PlotControlsBox);


        gridLayout_3->addLayout(controlsLayout, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        comboNodes->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionHow_to_use->setText(QApplication::translate("MainWindow", "How to use ", Q_NULLPTR));
        PortControlsBox->setTitle(QApplication::translate("MainWindow", "DEVICE SELECTION", Q_NULLPTR));
        labelPort->setText(QApplication::translate("MainWindow", "PORT", Q_NULLPTR));
        refreshPortsButton->setText(QApplication::translate("MainWindow", "Refresh", Q_NULLPTR));
        connectButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        DeviceControls->setTitle(QApplication::translate("MainWindow", "DEVICE CONTROLS", Q_NULLPTR));
        counterDisplayLabel->setText(QApplication::translate("MainWindow", "Packet Counter", Q_NULLPTR));
        periodLabel->setText(QApplication::translate("MainWindow", "Period (s)", Q_NULLPTR));
        dutyCycleLabel->setText(QApplication::translate("MainWindow", "Duty Cycle %", Q_NULLPTR));
        customCommandLabel->setText(QApplication::translate("MainWindow", "Custom", Q_NULLPTR));
        sendDevCmd->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        DeviceStatus->setTitle(QApplication::translate("MainWindow", "DEVICE STATUS", Q_NULLPTR));
        labelNodes->setText(QApplication::translate("MainWindow", "Node Id", Q_NULLPTR));
        avgTmpLabel->setText(QApplication::translate("MainWindow", "Avg. Temperature", Q_NULLPTR));
        avgDieLabel->setText(QApplication::translate("MainWindow", "Avg. Dielectric", Q_NULLPTR));
        rateLabel->setText(QApplication::translate("MainWindow", "RX Rate (mS)", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "RSSI", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "RTT", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "EPOCH", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Packets Sent", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Packets Received", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Packets Lost", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Sending Retries", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Sink ID", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "EEPROM Page", Q_NULLPTR));
        PlotControlsBox->setTitle(QApplication::translate("MainWindow", "PLOT CONTROLS", Q_NULLPTR));
        pointsLabel->setText(QApplication::translate("MainWindow", "Buffer Size", Q_NULLPTR));
        autoscaleButton->setText(QApplication::translate("MainWindow", "Auto Scale", Q_NULLPTR));
        resetPlotButton->setText(QApplication::translate("MainWindow", "Reset Plot", Q_NULLPTR));
        stopPlotButton->setText(QApplication::translate("MainWindow", "Stop Plot", Q_NULLPTR));
        saveJPGButton->setText(QApplication::translate("MainWindow", "Save JPG", Q_NULLPTR));
        resetMonWindow->setText(QApplication::translate("MainWindow", "Clear Monitor Window", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
