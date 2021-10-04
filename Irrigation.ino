// Loading required Libraries

#include<LiquidCrystal.h>



// Declaration of Global Variables

#define echo 9
#define trigger 10
#define tank_pump 4
#define watering_pump 13
#define moisture_sensor A0

long duration; //Ultrsonic
int distance;
int distance_percent;

int moisture_value; //Soil Sensor
int moist_percent;

String t_status; //Tank Status
String w_status; //Water pump status




LiquidCrystal lcd(12, 11, 8, 7, 6, 5); //LCD Pins

//Declaration of Global Variable Ends


//Setup program Starts
void setup () {

  Serial.begin(9600); //baud rate

  pinMode(echo, INPUT);    // setup for ultrasonic sensor
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, LOW); //Initial Condition

  pinMode(moisture_sensor, INPUT);   // Setup for Moisture Sensor

  pinMode(watering_pump, OUTPUT);   // Setup for relay
  pinMode(tank_pump, OUTPUT);

  digitalWrite(watering_pump, LOW); //Initial Condition
  digitalWrite(tank_pump, LOW);

  lcd.begin(20, 4); //LCD Setup
  lcd.setCursor(0, 1);
  lcd.print(" IRRIGATION PROJECT"    );
  lcd.setCursor(0, 2);
  lcd.print(" Rishubh kumar ");
  lcd.setCursor(0, 3);
  lcd.print("      WELCOME");
  delay(2000);
  lcd.clear();
}

//Setup program Ends

void loop() {


  //Program for Ultrasonic Sensor

  digitalWrite(trigger, LOW); //Sending
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH); //Receiving
  distance = duration * 0.017;
  distance_percent = map( distance, 0, 1023, 0, 100);

  //Program for Ultrasonic Sensor Ends


  moisture_value = analogRead(moisture_sensor);
  moist_percent = map(moisture_value, 0, 1023, 0, 100); //Map(value,fromlow,fromHigh,toLOW,toHIGH)

  int val = digitalRead(2); // read input value
  if (val == HIGH) // check if the input is HIGH
  {
    Serial.println("Alert! Alert!! Alert!!!");
  }

  condition(); //Main Logic For Code

}


void condition() {



  if (distance_percent > 65 && moist_percent < 85) // 1st Condition
  {

    t_status = String(" OFF");
    w_status = String("  ON");
    LCD_1(w_status, t_status);
    digitalWrite(tank_pump, LOW);
    digitalWrite(watering_pump, HIGH);
    delay(1000);

  }

  else if (distance_percent < 65 && moist_percent > 85) //2nd Condition
  {

    w_status = String(" OFF");
    t_status = ("  ON");
    LCD_1(w_status, t_status);
    digitalWrite(tank_pump, HIGH);
    digitalWrite(watering_pump, LOW);
    delay(1000);

  }

  else if (distance_percent > 65 && moist_percent > 85)
  {

    w_status = String(" OFF");
    t_status = String( " OFF");
    LCD_1(w_status, t_status);
    digitalWrite(tank_pump, LOW);
    digitalWrite(watering_pump, LOW);
    delay(1000);

  }

  else if (distance_percent < 65 && moist_percent < 85)
  {
    t_status = "   ON";
    w_status = "   ON";
    LCD_1(w_status, t_status);
    digitalWrite(tank_pump, HIGH);
    digitalWrite(watering_pump, HIGH);
    delay(1000);

  }
}



void LCD_1(String w_statu, String t_statu)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TANK LEVEL=  ");
  lcd.print(distance_percent);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("MOIST CONTENT= ");
  lcd.print(moist_percent);
  lcd.print("%");
  lcd.setCursor(0, 2);
  lcd.print("W-PUMP STATUS  ");
  lcd.print(w_statu);
  lcd.setCursor(0, 3);
  lcd.print("T-PUMP STATUS  ");
  lcd.print(t_statu);

  // For Serial Communication

  Serial.println("TANK LEVEL=  ");
  Serial.print(distance_percent);
  Serial.println("MOIST CONTENT= ");
  Serial.print(moist_percent);
  Serial.println("W-PUMP STATUS  ");
  Serial.print(w_statu);
  Serial.println("T-PUMP STATUS  ");
  Serial.print(t_statu);
}
