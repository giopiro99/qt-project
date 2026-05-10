#include "sensor.h"

Sensor::Sensor(QObject *parent)
    : QObject{parent}, historyValues(MAX_HISTORY_VALUES, 0), writeIndex(0), currentSum(0), mt(rd()), distribution(0, 100)
{}

Sensor::~Sensor()
{}

void Sensor::simulateReading(){
    //come prima cosa sottraggo dalla somma corrente il valore piu' vecchio
    this->currentSum -= this->historyValues[this->writeIndex];
    //creo il valore
    int value = this->distribution(this->mt);
    //emetto l evento per l handler nell interfaccia grafica
    emit this->valueIsReady(value);
    qDebug("il valore attuale e' %d", value);
    //salvo il valore nel vettore dei vaalori storici
    this->historyValues[this->writeIndex] = value;
    //aggiungo alla somma corrente il valore appena calcolato
    this->currentSum += value;
    qDebug("la somma corrente e' %d", this->currentSum);
    // avanzo l indice in modo circolare in modo da sovrascrivere sempre il valore piu' vecchio
    this->writeIndex = (writeIndex + 1) % MAX_HISTORY_VALUES;
    qDebug("L'indice attuale e' %d", this->writeIndex);
    // calcolo la media
    int average = 0;
    int size = this->historyValues.size();
    if (size > 0){
        average = this->currentSum / size;
        emit this->averageUpdated(average);
        qDebug("La media e' %d", average);
    }

    //se la media supera la soglia critica emetto un segnale di allarme
    if (average > CRITICAL_AVERAGE){
        qDebug("Media critica rilevata");
        emit this->criticalNumberReached(average);
    }
}
