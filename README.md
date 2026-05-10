Progetto: Monitoraggio Sensore Real-Time (C++ / Qt)
Descrizione

Questo progetto implementa un'applicazione desktop scritta in C++17 e basata sul framework Qt. L'obiettivo è simulare il campionamento in tempo reale di un sensore hardware, calcolarne la media mobile e gestire avvisi critici.
Il progetto dimostra una forte separazione tra la logica di business (dominio) e il livello di presentazione (UI), sfruttando i paradigmi di programmazione asincrona e le best practice di gestione della memoria del C++ moderno.
Architettura e Pattern
1. Gestione della Memoria (Ibrida)

Il progetto applica rigorosamente due diverse filosofie di gestione del ciclo di vita degli oggetti per evitare memory leak:

    Smart Pointers (C++ Moderno): La logica di business (la classe Sensor) è gestita tramite std::unique_ptr. Il C++ standard è l'unico responsabile dell'allocazione e deallocazione di questi oggetti, garantendo sicurezza ed evitando costrutti legacy come delete.

    Albero degli Oggetti (Qt Parent-Child): Tutti gli elementi della GUI (QWidget, QPushButton, QTimer, QVBoxLayout) sono allocati dinamicamente tramite raw pointers, delegando la loro distruzione al sistema gerarchico di Qt basato sul passaggio del puntatore this (la MainWindow) al costruttore.

2. Architettura Event-Driven (Segnali e Slot)

L'applicazione è interamente non bloccante e guidata dall'Event Loop di Qt.
La comunicazione tra la logica e l'interfaccia avviene esclusivamente tramite il pattern Observer proprietario di Qt (Signals & Slots):

    Un QTimer asincrono con intervallo di 500ms invoca la lettura del sensore.

    Il sensore, una volta elaborato il dato, emette i segnali valueIsReady e averageUpdated.

    La MainWindow intercetta i segnali e aggiorna i thread-safe le QLabel preposte.

3. Costruzione UI via Codice

L'interfaccia utente è generata in modo programmatico direttamente nel costruttore della finestra principale. L'assenza di file XML .ui generati dal Qt Designer garantisce:

    Maggiore leggibilità delle dipendenze dei widget.

    Controllo assoluto sul posizionamento e sulle policy di ridimensionamento tramite i Layout Manager (QVBoxLayout).

    Nessuna dipendenza da codice autogenerato (ui_mainwindow.h).

Gestione degli Eventi Critici (Allarmi)

È stata implementata una logica di sicurezza (State Machine basilare) per la gestione delle anomalie. Se il sensore rileva che la media mobile supera una soglia predefinita, emette un segnale criticalNumberReached.
La MainWindow risponde all'evento sospendendo il timer di campionamento e generando una finestra modale bloccante (QMessageBox::warning), impedendo l'accumulo di segnali non gestiti e richiedendo l'intervento esplicito dell'operatore prima di riprendere le letture.
Requisiti e Compilazione

Il progetto è basato su CMake (o qmake, a seconda della configurazione generata) e richiede l'installazione delle librerie base di Qt (modulo Core e Widgets).

Per compilare il progetto da terminale utilizzando CMake:
Bash

# Creare e spostarsi nella directory di build
mkdir build
cd build

# Generare i file di make
cmake ..

# Compilare l'eseguibile
make

# Eseguire l'applicazione
./<nome_eseguibile>
