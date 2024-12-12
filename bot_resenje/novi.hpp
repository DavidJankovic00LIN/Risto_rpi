// dialog.h
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QObject>  // Za Qt meta objekt sistem
#include <wiringPi.h>
#include <QTimer>  // Za QTimer
#include <QPushButton> // Za dugmadi

#define trigPin 26   // Pin za trig signal
#define echoPin 27   // Pin za echo signal

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT  // Qt signal-slot sistem

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void startMerenje();  // Slot za dugme Start
    void stopMerenje();   // Slot za dugme Stop
    void merenje_brzine(); // Funkcija za merenje brzine

private:
    Ui::Dialog *ui;
    QTimer *timer;  // Timer za merenje

    bool merenjeAktivno = false;  // Status merenja
};

#endif // DIALOG_H