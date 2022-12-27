#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs , en , d4 , d5 , d6 , d7);
#define Bt 12

#define Min Thick 0.19
#define Max Thick 0.21

#define pump 8 
#define Time 5
#define sensor A0

#define heater 10

#define motor 8

#define pump 9

double T;

int t_i;

int t;
double R;
int t_total = 0; 
const int Power  =2200;

int Energy = 0;

bool P_status = 0;
bool heater_status = 0;

int bit_array[25];



unsigned long time_now;

int CLOCK_PIN = 5;

int DATA_PIN = 10;

float result1 = 0;

float result2 = 0;
int repeatedcount = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16 ,2);
  pinMode(CLOCK_PIN , INPUT);
  pinMode(DATA_PIN , INPUT);
  pinMode(Bt , INPUT_PULLUP);
  pinMode(pump, OUTPUT);
digitalWrite(pump , 1);
pinMode(heater , OUTPUT);
}
double Temp () {
int v = analogRead (sensor); // Read voltage binary
float Vin = (v/1023.0) *5.0; // Convert to decimal
double R = (50000.0/Vin) -10000.0; // Read the value of the resistor
double T = log ((R+10897049.3)/(12.14*R))/0.03;
return T;
}
void decode() {

int sign = 1;
int i = 0;

float value = 0.0;

float result = 0.0;

bit_array[i] = digitalRead(DATA_PIN);

while (digitalRead(CLOCK_PIN) == 1) {};

for (i=1; i<=24; i++){

while (digitalRead(CLOCK_PIN)==0) {}// Wait until clock returns to Risk

bit_array[i]= digitalRead(DATA_PIN);

while (digitalRead(CLOCK_PIN)== 1) {} // WALE until clock returns to Low
}
for (i=1; i<=20; i++) {
  value = value + (pow(2,i-1) * bit_array[i]);
}

if (bit_array[21] == 1) sign = -1;

if (bit_array[24] == 1) {
  }else{
result = (value*sign) / 100.00 ; 
R = result; 
  }
}

void loop() {
  lcd.clear();
T = Temp ();
Serial.print ((T-32.0) *5.0/9.0);
lcd.print("Temp: ");
lcd.print ((T-32.0) *5.0/9.0);

lcd.setCursor(0,1);
if (T< 195) {
digitalWrite (heater, 1);
Serial.println("on");
lcd.print("Heater is on");
}else{
digitalWrite (heater, 0);
Serial.println(" off");
lcd.print("Heater is off");
}
delay(10);
}

