#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QObject>  // Dodajte ovo za korišćenje Qt meta objekt sistema
#include <wiringPi.h>
#include <stdio.h>
#include <QTimer>  // Za korišćenje QTimer
#include <QPushButton> // Za dugmadi

#define trigPin 26   // Pin za trig signal
#define echoPin 27   // Pin za echo signal

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT  // Ovaj makro omogućava korišćenje Qt signal-slot sistema

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
  //  void on_pushButton_clicked();  // Slot za dugme (ako želite specifično za dugme u GUI-u)
    void startMerenje();          // Slot za dugme Start
    void stopMerenje();           // Slot za dugme Stop

    void on_startButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::Dialog *ui;

    void merenje_brzine();  // Funkcija za merenje brzine

    bool merenjeAktivno = false;  // Ova promenljiva prati da li je merenje aktivno

};

#endif // DIALOG_H
