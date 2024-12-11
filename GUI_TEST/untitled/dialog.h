#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <wiringPi.h>
#include<stdio.h>
#include<QTimer>
#define trigPin 26
#define echoPin 27

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

private:
    Ui::Dialog *ui;

    void merenje_brzine();
};
#endif // DIALOG_H
