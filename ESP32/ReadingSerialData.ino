#define GREEN 13
#define RED 5
#define BLUE 14


void setup() {
  Serial.begin(115200); 
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  
  ledcAttachPin(GREEN, 1);
  ledcAttachPin(RED, 0);
  ledcAttachPin(BLUE, 2);
  Serial.setTimeout(300);
}
String str,temp;
void loop() {
  
  
  if(Serial.available())
  {
    str=Serial.readString(); // R225
    Serial.println(str);
    for(int i =0; i<str.length();i=i+4){
    switch (str[i]){
      case 'R':
              Serial.println("RED led");
              temp=str.substring(i+1,i+4);
              Serial.println("temp str =" + temp);
              ledcWrite(0,temp.toInt());
              break;  
      case 'G':
              Serial.println("GREEN led");
              temp=str.substring(i+1,i+4);
              Serial.println("temp str =" + temp);
              ledcWrite(1,temp.toInt());
              break;   
       case 'B':
              Serial.println("BLUE led");
              temp=str.substring(i+1,i+4);
              Serial.println("temp str =" + temp);
              ledcWrite(2,temp.toInt());
              break; 
        default:
              Serial.println("Invalid Input {ex. R255B255G255}");            
    }}
  }
}
