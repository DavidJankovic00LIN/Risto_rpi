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

bool merenjeAktivno = false;  // Ova promenljiva kontroliše da li je merenje aktivno

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    wiringPiSetup();  // Inicijalizuje wiringPi biblioteku

    // Prvo, potrebno je povezati dugmadi sa slotovima za start i stop
    connect(ui->startButton, &QPushButton::clicked, this, &Dialog::startMerenje);
    connect(ui->stopButton, &QPushButton::clicked, this, &Dialog::stopMerenje);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::startMerenje()
{
    merenjeAktivno = true;  // Početak merenja

    // Podesi timer da poziva funkciju za merenje
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dialog::merenje_brzine); // Poziva merenje brzine
    timer->start(period);  // Timer se aktivira svakih 'period' milisekundi
}

void Dialog::stopMerenje()
{
    merenjeAktivno = false;  // Zaustavi merenje
    ui->label->setText("");  // Prazni labelu

    // Ovdje možete zaustaviti timer ako je potrebno
    // Na primer, ako koristite globalni timer, možete ga zaustaviti ovde
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

    unsigned long startTime = 0;
    unsigned long endTime = 0;

    // Čekaj dok echoPin ne postane HIGH
    while (digitalRead(echoPin) == LOW);
    startTime = micros();  // Startuje merenje vremena

    // Čekaj dok echoPin ne postane LOW
    while (digitalRead(echoPin) == HIGH);
    endTime = micros();  // Kraj merenja vremena

    interval = endTime - startTime;
    distanca = (interval * 0.0343) / 2;

    // Računanje brzine
    brzina = (distanca - prethodnaDistanca) / (period / 1000.0);  // period pretvaramo u sekunde
    prethodnaDistanca = distanca;

    // Ažuriranje labela sa izračunatom brzinom
    ui->label->setText(QString::number(brzina));
}

void Dialog::on_startButton_clicked()
{
startMerenje();
}


void Dialog::on_stopButton_clicked()
{
    stopMerenje();
}

