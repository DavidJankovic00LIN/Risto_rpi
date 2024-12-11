#include <wiringPi.h>
#include <iostream>

#define trigPin 26
#define echoPin 27

float distanca;
float interval;
float brzina;
float prethodnaDistanca = 0;

unsigned long prethodnoVreme = 0; // Vreme poslednjeg merenja
const unsigned long period = 100; // Interval između merenja u milisekundama

int main()
{
    wiringPiSetup();
    
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    while(1) {
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

        std::cout << "Distanca: " << distanca << std::endl;

        if (brzina > 0) {
            std::cout << "Brzina: " << brzina << std::endl;
        } else {
            std::cout << "Brzina: 0" << std::endl;
        }

        delay(period);  // Pauza između merenja
    }

    return 0;
}
