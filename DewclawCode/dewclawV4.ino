#include <Servo.h>
#include <Adafruit_NeoPixel.h>


#define NEOPIN        3
// input pin Neopixel is attached to
#define SRV1         5
// output pin flexion1 is attached to
#define SRV2         6
// output pin extensor1 is attached to
#define SRV12        12
// output pin flexion2 is attached to
#define SRVE2        11
// output pin extensor2 is attached to
#define VIBE         2
// output pin haptic motor is attached to
#define SCMOD        6
// input pin brightness switch is attached to
#define SC1          7
// input pin scale1 switch is attached to
#define SC2        9
// input pin scale2 switch is attached to
#define NOSRV      8
// input switch to force servo position hold
#define SCALE      A7
// input pin scale potentiometer
#define FLX1       A5
// input pin flexion amp 1
#define EXT1       A4
// input pin extension amp 1
#define FLX2       A2
// input pin flexion amp 2
#define EXT2       A3
// input pin extension amp 2
#define FSC        A1
// input pin of force capacitor
#define NUMPIXELS    10
// number of neopixels in strip
#define SERVO_MAX    2500
#define SERVO_MIN  500
#define abs(x) ((x)>0?(x):-(x))



int   old1;
int   oldVal2;
int   muscle2;
float current1;
int   freq;
int deadband=1;
float scaler1=1;
float scaler2=1;
int brightness;
int rate=1000;
int count=0;

class CircularBuffer {
public:
  CircularBuffer(int size) : size(size), numElements(0), index(0), sum(0), sumOfSquares(0), buffer(new double[size]) {
    for(int i=0; i<size; i++){
      buffer[i]=0;
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

  double get(int index) { return buffer[(this->index + index) % size]; }

  int getSize() { return size; }

  int getNumElements() { return numElements; }

  void print() {
    Serial.print("CircularBuffer: ");
    Serial.print(numElements);
    Serial.print("/");
    Serial.print(size);
    Serial.print(" [");
    for (int i = 0; i < numElements; i++) {
      Serial.print(get(i));
      if (i < numElements - 1) Serial.print(", ");
    }
    Serial.println("]");
  }

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
  double* buffer;
};
double output=0;
double input1[5]={0};
double input2[5]={0};
double old=0;
double in1Max=0;
double in1Min=1000;

double combined=0;
CircularBuffer buffer1(10); // Create a buffer of size 10
CircularBuffer buffer2(10); // Create a buffer of size 10
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIN, NEO_GRB + NEO_KHZ800);
//Servo servo1;

void setup() {
    pinMode(SCALE, INPUT);
    pinMode(EXT1, INPUT);
    pinMode(FLX1, INPUT);
    pinMode(SCMOD, INPUT);
    pinMode(SC1, INPUT);
    pinMode(SC2, INPUT);
    //pinMode(NOSRV, INPUT);
    Serial.begin(9600);
    pixels.begin();
}

void loop()
{
    while (digitalRead(SCMOD) == HIGH) {
        int analogValue = analogRead(SCALE);
        if (!digitalRead(SC1) && digitalRead(SC2)) {
          scaler1 = map(analogValue, 0, 1023, .5, 50);
          Serial.println(scaler1);
        } else if (digitalRead(SC1) && !digitalRead(SC2)) {
          scaler2 = map(analogValue, 0, 1023, .5, 50);
          Serial.println(scaler2);
        } else if (digitalRead(SC1) && digitalRead(SC2)) {
          deadband = map(analogValue, 0, 1023, 0, 10);
        } else if (!digitalRead(SC1) && !digitalRead(SC2)){
          brightness = map(analogValue, 0, 1023, 0, 255);
        }
        setPercentLights(scaler1, scaler2);
        pixels.setBrightness(brightness);
        
    }

  double sum1=0;
  double inavg1=0;
  double sum2=0;
  double inavg2=0;
  double in1=0;
  double in2=0;
  for (int i=0;i<5;i++){
    for(int j=0;j<2;j++){
     in1+=analogRead(EXT1);
     in2+=analogRead(FLX1);
    }
    input1[i]=abs(analogRead(EXT1)-(in1/2));
    input2[i]=abs(analogRead(FLX1)-(in2/2));
    sum1+=input1[i];
    sum2+=input2[i];
    in1=0;
    in2=0;
    }
   inavg1=sum1/5;
   inavg2=sum2/5;
   buffer1.add(analogRead(FLX1));
   buffer2.add(analogRead(EXT1));
   double added=abs(analogRead(FLX1)-buffer1.getAverage())-abs(analogRead(EXT1)-buffer2.getAverage());
   combined=old+added;
   old=combined;
   Serial.println(combined);

}


void setPercentLights(int Scaler1, int Scaler2) {
    float ratio = (float)Scaler1 / (Scaler1 + Scaler2);
    int endPixel = round(ratio * NUMPIXELS);

    for (int i = 0; i < NUMPIXELS; i++) {
        int red, green, blue;
        if (i < endPixel) {
            red = 255 - 5 * i;
            green = 20 + 20 * i;
            blue = 0 + 5 * i;
        } else {
            red = 0 + 5 * (i - endPixel);
            green = 20 + 20 * (i - endPixel);
            blue = 255 - 5 * (i - endPixel);
        }
    
        pixels.setPixelColor(i, pixels.Color(red, green, blue));
    }

    int red = (255 - 5 * endPixel) + (10 * (10 - endPixel));
    int green = 10 * (10 - endPixel);
    int blue = 5 * (10 - endPixel);
    pixels.setPixelColor(endPixel, pixels.Color(red, green, blue));

    pixels.show();
}
