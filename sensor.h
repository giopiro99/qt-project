#ifndef SENSOR_H
#define SENSOR_H

#include "qobject.h"
#include <random>

#define MAX_HISTORY_VALUES 15
#define CRITICAL_AVERAGE 70

class Sensor : public QObject
{
    Q_OBJECT
public:
    explicit                            Sensor(QObject *parent = nullptr);
    virtual                             ~Sensor();
    void                                simulateReading();
private:
    std::vector<int>                    historyValues;
    int                                 writeIndex;
    int                                 currentSum;

    std::random_device                  rd;
    std::mt19937                        mt;
    std::uniform_int_distribution<int>  distribution;
signals:
    void                                valueIsReady( int );
    void                                averageUpdated( int );
    void                                criticalNumberReached( int );
};

#endif // SENSOR_H
