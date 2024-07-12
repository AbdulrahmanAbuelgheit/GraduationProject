 #include <SoftwareSerial.h>
 int RX_PIN = 2;
 int TX_PIN = 3;
 SoftwareSerial mySerial(RX_PIN, TX_PIN);
String data = "";
#define T1R 2
#define T1Y 3
#define T1G 4
#define T2R 5
#define T2Y 6
#define T2G 7
#define T3R 8
#define T3Y 9
#define T3G 10
#define T4R 11
#define T4Y 12
#define T4G 13

int Traffic1_CarCount =1;
int Traffic2_CarCount =4 ;
int Traffic3_CarCount =6;
int Traffic4_CarCount =2;

int lastOpen = -1;


void setup() {
  for (int pin = 2; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
  }
  if (Serial) {
     Serial.begin(115200);
   } else {
     mySerial.begin(115200);  // For software serial
   }
}

void loop() {
  if (Serial.available() > 0 || mySerial.available() > 0) {  // Check for incoming data (hardware or software serial)
    
     
     if (Serial) {
       data = Serial.readStringUntil('\n');  // Read data until newline character (hardware serial)
     } else {
       data = mySerial.readStringUntil('\n');  // Read data until newline character (software serial)
     }

        if (data.length() > 0) {
       // Split data into individual integers using spaces as delimiters
       int intVar1 = data.toInt();
       int index1 = data.indexOf(' ');
       int intVar2 = data.substring(index1 + 1).toInt();
       int index2 = data.indexOf(' ', index1 + 1);
       int intVar3 = data.substring(index2 + 1).toInt();
       int intVar4 = data.substring(data.indexOf(' ', index2 + 1) + 1).toInt();
        Traffic1_CarCount=intVar1;
        Traffic2_CarCount=intVar2;
        Traffic3_CarCount=intVar3;
        Traffic4_CarCount=intVar4;
        if(intVar1>0){
          digitalWrite(13, HIGH);
        }
        }}

  int roadToOpen = getRoadToOpen();

  if (roadToOpen != -1) {
    int &carCount = getCarCount(roadToOpen);
    int openTime = min(carCount, 30); // Set open time based on minimum of 30 seconds or car count
    if (openTime > 0) {
      wait(roadToOpen, 1);
      Open(roadToOpen, openTime);
      carCount -= openTime;
      lastOpen = roadToOpen;
     } }
  }


int& getCarCount(int road) {
  switch (road) {
    case 1: return Traffic1_CarCount;
    case 2: return Traffic2_CarCount;
    case 3: return Traffic3_CarCount;
    case 4: return Traffic4_CarCount;
  }
  
  return Traffic1_CarCount;
}

int getRoadToOpen() {
  int road = -1;
  int maxCarCount = -1;

  if (lastOpen != 1 && Traffic1_CarCount > maxCarCount) {
    maxCarCount = Traffic1_CarCount;
    road = 1;
  }
  if (lastOpen != 2 && Traffic2_CarCount > maxCarCount) {
    maxCarCount = Traffic2_CarCount;
    road = 2;
  }
  if (lastOpen != 3 && Traffic3_CarCount > maxCarCount) {
    maxCarCount = Traffic3_CarCount;
    road = 3;
  }
  if (lastOpen != 4 && Traffic4_CarCount > maxCarCount) {
    maxCarCount = Traffic4_CarCount;
    road = 4;
  }

  return road;
}

void wait(int y, int seconds) {
  digitalWrite(T1R, HIGH);
  digitalWrite(T1Y, LOW);
  digitalWrite(T1G, LOW);

  digitalWrite(T2R, HIGH);
  digitalWrite(T2Y, LOW);
  digitalWrite(T2G, LOW);

  digitalWrite(T3R, HIGH);
  digitalWrite(T3Y, LOW);
  digitalWrite(T3G, LOW);

  digitalWrite(T4R, HIGH);
  digitalWrite(T4Y, LOW);
  digitalWrite(T4G, LOW);


  switch (y) {
    case 1:
      digitalWrite(T1Y, HIGH);
      digitalWrite(T1R, LOW);
      break;
    case 2:
      digitalWrite(T2Y, HIGH);
      digitalWrite(T2R, LOW);
      break;
    case 3:
      digitalWrite(T3Y, HIGH);
      digitalWrite(T3R, LOW);
      break;
    case 4:
      digitalWrite(T4Y, HIGH);
      digitalWrite(T4R, LOW);
      break;
  }

  delay(seconds * 1000);
}

void Open(int Set, int seconds) {
  digitalWrite(T1Y, LOW);
  digitalWrite(T2Y, LOW);
  digitalWrite(T3Y, LOW);
  digitalWrite(T4Y, LOW);

  switch (Set) {
    case 1:
      digitalWrite(T1G, HIGH);
      digitalWrite(T1R, LOW);
      break;
    case 2:
      digitalWrite(T2G, HIGH);
      digitalWrite(T2R, LOW);
      break;
    case 3:
      digitalWrite(T3G, HIGH);
      digitalWrite(T3R, LOW);
      break;
    case 4:
      digitalWrite(T4G, HIGH);
      digitalWrite(T4R, LOW);
      break;
  }

  delay(seconds * 1000);

  digitalWrite(T1G, LOW);
  digitalWrite(T2G, LOW);
  digitalWrite(T3G, LOW);
  digitalWrite(T4G, LOW);

  digitalWrite(T1R, HIGH);
  digitalWrite(T2R, HIGH);
  digitalWrite(T3R, HIGH);
  digitalWrite(T4R, HIGH);
}
