#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <memory>
#include "sensor.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void    onNewValueReceived( int );
    void    onNewAverageReceived( int );
    void    onNewCriticalValue( int );
private:
    QPushButton                 *btnStart;
    QPushButton                 *btnStop;
    QLabel                      *lblValue;
    QLabel                      *lblAverage;
    std::unique_ptr<Sensor>     m_sensor;
    QTimer                      *m_timer;
    QMessageBox                 *criticalValueMessage;
};
#endif // MAINWINDOW_H
