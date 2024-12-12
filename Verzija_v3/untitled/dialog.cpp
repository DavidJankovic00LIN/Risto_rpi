#include "dialog.h"
#include "ui_dialog.h"

#define trigPin 26   // Pin za trig signal
#define echoPin 27   // Pin za echo signal

int granica;
int dimenzija;
float distanca;
float interval;
float brzina;
float prethodnaDistanca = 0;
unsigned long prethodnoVreme = 0;
const unsigned long period = 1000;  // Interval u milisekundama za timeout (QTimer)
int flag_start = 0;
QTimer timer;  // Kreiranje timer objekta

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // Postavljanje pinova na početku
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Kreiraj QTimer i poveži signal timeout sa funkcijom merenja brzine
    connect(&timer, &QTimer::timeout, this, &Dialog::merenje_brzine);
}

Dialog::~Dialog()
{
    delete ui;
}

float Dialog::merenje_brzine(){
    digitalWrite(trigPin, LOW);
    delay(50);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    while (digitalRead(echoPin) == LOW);  // Čeka se da echo pin postane HIGH
    long startTime = micros();

    while (digitalRead(echoPin) == HIGH);  // Čeka se da echo pin postane LOW
    interval = micros() - startTime;

    distanca = (interval * 0.0343) / 2 * dimenzija;  // Izračunavanje distance u cm
    brzina = (distanca - prethodnaDistanca) / (period / 1000.0);  // Brzina = promena u distanci / vreme
    prethodnaDistanca = distanca;

    if(brzina>granica){

    ui->label->setText(QString::number(brzina));  // Ispisivanje brzine na UI
    }else{
         ui->label->setText(0);
    }
    return brzina;
}

void Dialog::on_pushButton_clicked()
{
    if (flag_start == 0) {
        flag_start = 1;  // Postavljamo flag_start na 1, merenje je aktivirano
        timer.start(period);  // Pokrećemo timer, koji poziva merenje_brzine svakih 100ms
    }

    ui->radioButton->setDisabled(true);
    ui->radioButton_2->setDisabled(true);
}

void Dialog::on_pushButton_2_clicked()
{
    ui->radioButton->setDisabled(false);
    ui->radioButton_2->setDisabled(false);
    if (flag_start == 1) {
        flag_start = 0;  // Postavljamo flag_start na 0, merenje je zaustavljeno
        timer.stop();  // Zaustavljamo timer
    }
}

void Dialog::on_radioButton_clicked()
{
    dimenzija=1;
    granica=5;
}


void Dialog::on_radioButton_2_clicked()
{
    dimenzija=10;
    granica=50;
}

