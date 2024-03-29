/*
Training game for using the dewclaw. A5 and A4 are bioamp input pins
*/

#include <Servo.h>

#define FLX1 A5
#define EXT1 A4
#define SWT1 6
#define SWT2 7

#define abs(x) ((x)>0?(x):-(x))

class CircularBuffer {
public:
    CircularBuffer(int size) : size(size), numElements(0), index(0), sum(0), sumOfSquares(0), buffer(new double[size]) {
        for (int i = 0; i < size; i++) {
            buffer[i] = 0;
        }
    }

    void add(double value) {
        if (numElements < size) numElements++;
        sum -= buffer[index];
        sumOfSquares -= buffer[index] * buffer[index];
        buffer[index] = value;
        sum += value;
        sumOfSquares += value * value;
        index = (index + 1) % size;
    }

    double getAverage() { return (sum / numElements); }


    double getStandardDeviation() {
        double average = getAverage();
        //check for divide by zero
        if (numElements == 0) return 0;
        double standardDeviation = sqrt(sumOfSquares / numElements - average * average);
        if (isnan(standardDeviation)) return 0;
        return standardDeviation;
    }

    int getSize() { return size; }

    int getNumElements() { return numElements; }

    void reset() {
        numElements = 0;
        index = 0;
        sum = 0;
        sumOfSquares = 0;
    }


private:
    int size;
    int numElements;
    int index;
    double sum;
    double sumOfSquares;
    double *buffer;
};

double old = 0;
double oldPos = 0;
double pos = 0;
int match = 0;
double goal = 0;
double combined = 0;
//feel free to edit the below scaling factors to fit preferences.
double sc1=16.8;
double sc2=10.4;
double deadzone1=1;
double deadzone2=0.75;
CircularBuffer buffer1(30); // Create a buffer of size 30
CircularBuffer buffer2(30); // Create a buffer of size 30
CircularBuffer buffer3(10); // Create a buffer of size 10

void setup() {

    pinMode(FLX1, INPUT);
    pinMode(EXT1, INPUT);
    pinMode(SWT1, INPUT);
    pinMode(SWT2, INPUT);

    Serial.begin(9600);
}

 //training mode. Combines both signals to mimic flexor/extensor muscle interaction for one DoF.
 //"randomly" generates a number for the goal "position" and counts how long you can hold the position.
 //sets new goal once the previous goal is met.

void loop() {
    buffer1.add(analogRead(FLX1));
    double raw1 = analogRead(FLX1);
    buffer2.add(analogRead(EXT1));
    double raw2 = analogRead(EXT1);

    combined = constrain((old + (abs(raw1 - buffer1.getAverage()) / sc1 - abs(raw2 - buffer2.getAverage()) / sc2)), 0,300);
    if (abs(combined - old) > deadzone1) {
        old = combined;
    }
    buffer3.add(old);
    pos = map(buffer3.getAverage(), 0, 300, 0, 180);
    if (abs(pos - oldPos) > deadzone2) {
        oldPos = pos;
    }
    if (match == 100) {
        goal = millis() % 180;
        match = 0;
    }
    if (abs(goal - pos) < 2) {
        match++;
        if (match > 100)match = 100;
    }
    if (abs(goal - pos) > 5) {
        match--;
        if (match < 0)match = 0;
    }
    
    Serial.println(pos);
    Serial.print(", ");
    Serial.println(goal);
    //Serial.print("%: ");
    //Serial.println(match); uncomment to see match. will mess up the serial graph
}
