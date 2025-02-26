//ovde sam dodao dodatne uslove kako bih osigurao da ne meri premalu brzinu ako ne meri lepo distancu

#include<wiringPi.h>
#include<stdio.h>

#define trigPin 26;
#define echoPin 27;

float distanca;
float interval;

float brzina;
float prethodnaDistanca = 0;
float predjen_put

unsigned long prethodnoVreme = 0; // Vreme poslednjeg merenja
const unsigned long period = 100; // Interval između merenja u milisekundama

int main()
{
    wiringPiSetup();
    
    pinMode (trigPin, OUTPUT);
    pinMode (echoPin, INPUT);

    while(1){
        digitalWrite(trigPin,LOW);
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        interval=pulseIn(echoPin, HIGH);
        distanca=(interval*.0343)/2;

        predjen_put=distanca - prethodnaDistanca;
        brzina= predjen_put / (period/1000.0); // period pretvaramo u sekunde
        prethodnaDistanca=distanca;

        cout<< "Distanca : "<< Distanca <<endl;

        if(brzina > 0 && predjen_put>1){
            cout<< "Brzina : "<< Brzina <<endl;
        }else{
            cout<< "Brzina : 0 "<< endl;
        }

    }

    return 0;
}