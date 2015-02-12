#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
SoftwareSerial wifi(3,2);

String SSID = "VeldhofHuis";
String Password = "fonar123";
String IP = "184.106.153.149";
String API = "0MTOHTVRCTL0U8H4";
String httpTemp = "GET /update?key=" + API + "&field1=";

int pinTemp0 = 0;
int pinTemp1 = 1;
int temp0 = 0;
int temp1 = 0;
int count = 30000;

boolean visible = true;
boolean reset = false;

void setup() {                
  pinMode(13, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
  wifi.begin(9600); 
  wifi.listen();

  digitalWrite(13, LOW);
  while (!initialise()) {
    Serial.println("Can't initialize");
  }
  digitalWrite(13, HIGH);
  delay(100);
  lcd.clear();
  lcd.print("Rookgas        ");
  lcd.print((char)223);
  lcd.setCursor(0,1);
  lcd.print("Water          ");
  lcd.print((char)223);
}

void loop() {
  if(reset) {
    while (!initialise()) {
      Serial.println("Can't initialize");
    }
    digitalWrite(13, HIGH);
    delay(100);
    lcd.clear();
    lcd.print("Rookgas        ");
    lcd.print((char)223);
    lcd.setCursor(0,1);
    lcd.print("Water          ");
    lcd.print((char)223);
    reset = false;
  }
  
  temp0 = ((analogRead(pinTemp0)-514)/34.0)*50.0;
  temp1 = analogRead(pinTemp1)-107;
  updateScreen();

  if(count >= 30000) {
    Serial.println("Updating temps...");
    lcd.setCursor(0,0);
    lcd.print("Rookgas!");
    lcd.setCursor(0,1);
    lcd.print("Water!");

    int tries = 0;
    while(!makeConnection()){
      tries++;
      if(tries >= 2) {
        reset = true;
        return;
      }
    }
    tries = 0;
    while(!sendData()){
      tries++;
      if(tries >= 2) {
        reset = true;
        return;
      }
    }
    count = 0;

    lcd.setCursor(0,0);
    lcd.print("Rookgas ");
    lcd.setCursor(0,1);
    lcd.print("Water ");
    updateScreen();
  }

  count += 1000;
  delay(1000);
}

boolean makeConnection() 
{
  while(wifi.available()) {
    wifi.read();
  }
  Serial.print("Making connection...");
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  wifi.println(cmd);
  int count = 0;
  while(!wifi.find("Linked")) {
    if(count >= 2000) {
      Serial.println();
      return false;
    }
    count += 100;
    delay(100);
    Serial.print(".");
  }
  Serial.println(" DONE");
  return true;
}

boolean sendData()
{
  while(wifi.available()) {
    wifi.read();
  }
  String cmdTemp = httpTemp;
  cmdTemp += String(temp0);
  cmdTemp += "&field2=";
  cmdTemp += String(temp1);
  cmdTemp += "\r\n";

  Serial.print("Sending data...");
  //-----Make announcement
  String cmd = "AT+CIPSEND=" + String(cmdTemp.length());
  wifi.println(cmd);
  while(!wifi.find(">")) {
    delay(100);
    Serial.print(".");
  }

  //-----Send data temp
  Serial.print("data...");
  wifi.print(cmdTemp);
  return true;
}

boolean closeConnection()
{
  Serial.print("Closing connection...");
  int count = 0;
  wifi.println("AT+CIPCLOSE");
  while(!wifi.find("Unlink")) {
    if (count >= 1000) {
      Serial.println();
      return false;
    }
    count += 100;
    Serial.print(".");
    delay(100);
  }
  Serial.println(" DONE");
  return true;
}

void updateScreen(){
  //-----Top
  lcd.setCursor(12,0);
  lcd.print("    ");
  lcd.setCursor(12,0);
  lcd.print(String(temp0));
  visible ? lcd.print((char)223) : lcd.print(" ");

  //------Bottom
  lcd.setCursor(12,1);
  lcd.print("    ");
  lcd.setCursor(12,1);
  lcd.print(String(temp1));
  visible ? lcd.print((char)223) : lcd.print(" ");
}

boolean initialise()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("00");

  //----Reset Board----
  Serial.print("Resetting board... ");
  lcd.setCursor(0,1);
  lcd.print("Reset           ");
  wifi.println("AT+RST");
  int count = 0;
  while (!wifi.find("ready")) {
    if(count >= 2000){
      return false;
    }
    count += 100;
    delay(100);
  }
  Serial.println("DONE");
  lcd.setCursor(0,0);
  lcd.print("0000");

  //----Set mode----
  Serial.print("Setting mode... ");
  lcd.setCursor(0,1);
  lcd.print("Setting mode    ");
  wifi.println("AT+CWMODE=1");
  count = 0;
  while (!(wifi.find("no change") || wifi.find("OK"))) {
    if(count >= 1000){
      return false;
    }
    count += 100;
    delay(100);
  }
  Serial.println("DONE");
  lcd.setCursor(0,0);
  lcd.print("000000");

  //----Connect to network-----
  Serial.print("Connecting to network...");
  lcd.setCursor(0,1);
  lcd.print("Connecting      ");

  String cmd = "AT+CWJAP=\"" + SSID + "\",\"" + Password + "\"";
  wifi.println(cmd);

  count = 0;
  while (!wifi.find("OK")) {
    if(count >= 5000){
      return false;
    }
    count += 250;
    delay(250);
    Serial.print(".");
  }
  Serial.println(" DONE");
  lcd.setCursor(0,0);
  lcd.print("0000000000");

  //----One connection-----
  Serial.print("Set for one connections... ");
  lcd.setCursor(0,1);
  lcd.print("Multiple cons   ");
  wifi.println("AT+CIPMUX=0");
  count = 0;
  while (!wifi.find("OK")) {
    if(count >= 1000){
      return false;
    }
    count += 100;
    delay(100);
  }
  Serial.println("DONE");
  lcd.setCursor(0,0);
  lcd.print("0000000000000");
  lcd.clear();
  return true;
}


