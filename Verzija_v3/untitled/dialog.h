#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QObject>  // Dodajte ovo za korišćenje Qt meta objekt sistema
#include <wiringPi.h>
#include <stdio.h>
#include <QTimer>  // Za korišćenje QTimer
#include <QPushButton> // Za dugmadi



QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::Dialog *ui;

    float merenje_brzine();  // Funkcija za merenje brzine
};
#endif // DIALOG_H
