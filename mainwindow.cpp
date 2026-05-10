#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    this->btnStart = new QPushButton("Start btn", this);
    this->btnStop = new QPushButton("End btn", this);
    this->lblValue = new QLabel(this);
    this->lblAverage = new QLabel(this);

    layout->addWidget(btnStart);
    layout->addWidget(btnStop);
    layout->addWidget(lblValue);
    layout->addWidget(lblAverage);

    setCentralWidget(centralWidget);

    m_sensor = std::make_unique<Sensor>();
    m_timer = new QTimer(this);

    connect(btnStart, &QPushButton::clicked, [this](){
        m_timer->start(500);
    });

    connect(btnStop, &QPushButton::clicked, [this](){
        m_timer->stop();
    });

    connect(m_timer, &QTimer::timeout, m_sensor.get(), &Sensor::simulateReading);
    connect(m_sensor.get(), &Sensor::valueIsReady, this, &MainWindow::onNewValueReceived);
    connect(m_sensor.get(), &Sensor::averageUpdated, this, &MainWindow::onNewAverageReceived);
    connect(m_sensor.get(), &Sensor::criticalNumberReached, this, &MainWindow::onNewCriticalValue);
}

MainWindow::~MainWindow()
{}

void    MainWindow::onNewValueReceived( int value ){
    lblValue->setText(QString::number(value));
}

void    MainWindow::onNewAverageReceived( int average ){
    lblAverage->setText(QString::number(average));
}

void    MainWindow::onNewCriticalValue( int criticalValue){
    m_timer->stop();

    QMessageBox::warning(this, "allarme", "Attenzione, media sopra il valore critico");

    m_timer->start(500);
}
