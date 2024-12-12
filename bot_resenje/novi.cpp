// dialog.cpp
#include "dialog.h"
#include "ui_dialog.h"

float distanca;
float interval;
float brzina;
float prethodnaDistanca = 0;
unsigned long prethodnoVreme = 0; // vreme poslednjeg merenja
const unsigned long period = 100;  // interval izmedju merenja u milisekundama
unsigned long startTime = 0;
unsigned long endTime = 0;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , timer(new QTimer(this))  // Inicijalizacija timera
{
    ui->setupUi(this);

    wiringPiSetup();  // Inicijalizuje wiringPi biblioteku

    // Povezivanje dugmadi sa slotovima
    connect(ui->startButton, &QPushButton::clicked, this, &Dialog::startMerenje);
    connect(ui->stopButton, &QPushButton::clicked, this, &Dialog::stopMerenje);

    // Povezivanje timera sa funkcijom za merenje
    connect(timer, &QTimer::timeout, this, &Dialog::merenje_brzine);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::startMerenje()
{
    merenjeAktivno = true;
    timer->start(period);  // Pokreni timer
}

void Dialog::stopMerenje()
{
    merenjeAktivno = false;
    timer->stop();  // Zaustavi timer
    ui->label->setText("");  // Prazni labelu
}

void Dialog::merenje_brzine()
{
    if (!merenjeAktivno) {
        return;  // Ako merenje nije aktivno, izlazimo iz funkcije
    }

    // Reset trigPin pre svakog merenja
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    unsigned long maxWait = 30000;  // Maksimalno čekanje u mikrosekundama
    unsigned long start = micros();
    while (digitalRead(echoPin) == LOW) {
        if (micros() - start > maxWait) return;  // Timeout
    }
    startTime = micros();

    start = micros();
    while (digitalRead(echoPin) == HIGH) {
        if (micros() - start > maxWait) return;  // Timeout
    }
    endTime = micros();

    interval = endTime - startTime;
    distanca = (interval * 0.0343) / 2;

    // Računanje brzine
    brzina = (distanca - prethodnaDistanca) / (period / 1000.0);  // period pretvaramo u sekunde
    prethodnaDistanca = distanca;

    // Ažuriranje labela sa izračunatom brzinom
    ui->label->setText(QString::number(brzina));
}
