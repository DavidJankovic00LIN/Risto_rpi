#include "dialog.h"
#include "ui_dialog.h"

float distanca;
float interval;
float brzina;
float prethodnaDistanca=0;
unsigned long prethodnoVreme=0;// vreme poslednjeg merenja
const unsigned long period=100;// interval izmedju merenja u milisekundama;
unsigned long startTime=0;
unsigned long endTime=0;

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    wiringPiSetup();

    QTimer *timer = new QTimer(this);
       connect(timer, &QTimer::timeout, this, &Dialog::merenje_brzine); // Poziva merenje brzine
       timer->start(period);  // Timer će se aktivirati na svakih 'period' milisekundi
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::merenje_brzine()
{
    // Reset trigPin pre svakog merenja
           digitalWrite(trigPin, LOW);
           delayMicroseconds(2);
           digitalWrite(trigPin, HIGH);
           delayMicroseconds(10);
           digitalWrite(trigPin, LOW);

           // Ručno merenje pulsa
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
           brzina = (distanca - prethodnaDistanca) / (period / 1000.0); // period pretvaramo u sekunde
           prethodnaDistanca = distanca;

           delay(period);

           ui->label->setText(QString::number(brzina));

}




void Dialog::on_pushButton_clicked()
{

    merenje_brzine();

}

