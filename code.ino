#include<LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
#include <SoftwareSerial.h>
SoftwareSerial gps(3, 4); // RX, TX

const int SW=A0;   ////////////////L1

int SWalert=1;         // variable for reading the pushbutton status

int i=0;
int  gps_status=0;
float latitude=0; 
float logitude=0;                       
String gpsString="";
char *test="$GPRMC";
////////////////////////////////////////////////////////////////
int BUZZ1 = 7; //Connect LED 1 To Pin #A4 ////////motor
int BUZZ2 = 6; //Connect LED 2 To Pin #7 ///////buzzer
/////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void initModule(String cmd, char *res, int t)
{
while(1)
{
Serial.println(cmd);
delay(100);
while(Serial.available()>0)
{
if(Serial.find(res))
{
Serial.println(res);
delay(t);
return;
}
else
{
Serial.println("Error");
}
}
delay(t);
}
}
////////////////////////////////////////////////////////////////////////////////////
void setup()
{
lcd.begin(16, 2);
Serial.begin(9600);
gps.begin(9600);

pinMode(BUZZ1, OUTPUT); 
pinMode(BUZZ2, OUTPUT); 

digitalWrite(BUZZ1,LOW);
digitalWrite(BUZZ2,LOW);
lcd.begin(16,2);
lcd.setCursor(0,0);


lcd.clear();
lcd.print("Arduino Based");
lcd.setCursor(0,1);
lcd.print("Women Safety");
delay (5000);


lcd.clear();


lcd.setCursor(0,1);
lcd.print("security system");
delay (5000);
lcd.clear();


lcd.clear();
lcd.setCursor(0,0);
lcd.print("GPS MODEM &");
lcd.setCursor(0,1);
lcd.print("GSM MODEM ");
delay (5000);
lcd.clear();
lcd.print("Waiting For GPS");
lcd.setCursor(0,1);
lcd.print(" Signal    ");
get_gps();
show_coordinate();
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("GPS is OK");
delay(1000);
lcd.clear();
lcd.print("Initializing");
lcd.setCursor(0,1);
lcd.print("GSM MODEM");
delay(1000);
initModule("AT","OK",1000);
initModule("ATE1","OK",1000);
initModule("AT+CPIN?","READY",1000);  
initModule("AT+CMGF=1","OK",1000);     
initModule("AT+CNMI=2,2,0,0,0","OK",1000);  
lcd.clear();
lcd.print("Initialized");
lcd.setCursor(0,1);
lcd.print("Successfully");
delay(2000);
lcd.clear(); 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{st:
SWalert = digitalRead(SW);
if (SWalert == LOW)
{  lcd.setCursor(0,0);
lcd.print("WOMEN IN       ");
lcd.setCursor(0,1);
lcd.print("TROUBLE        ");
digitalWrite(BUZZ1,HIGH);
digitalWrite(BUZZ2,HIGH);
delay(2000);lcd.clear();lcd.print("Sending SMS ");delay(2000);Send();delay(2000);goto st;
}
else
{
  lcd.setCursor(0,0);
lcd.print("WOMEN IS        ");
lcd.setCursor(0,1);
lcd.print("SAFE           ");
digitalWrite(BUZZ1,LOW);
digitalWrite(BUZZ2,LOW);
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
////////////////////////////////////////////////////////////////////////
void gpsEvent()
{
gpsString="";
while(1)
{
while (gps.available()>0)  //Serial incoming data from GPS
{
char inChar = (char)gps.read();
gpsString+= inChar;  //store incoming data from GPS to temparary string str[]
i++;
if (i < 7)                      
{
if(gpsString[i-1] != test[i-1])  //check for right string
{
i=0;
gpsString="";
}
}
if(inChar=='\r')
{
if(i>65)
{
gps_status=1;
break;
}
else
{
i=0;
}
}
}
if(gps_status)
break;
}
}
///////////////////////////////////////////////////////////////////
void get_gps()
{
lcd.clear();
lcd.print("Getting GPS Data");
lcd.setCursor(0,1);
lcd.print("Please Wait.....");
gps_status=0;
int x=0;
while(gps_status==0)
{
gpsEvent();
int str_lenth=i;
coordinate2dec();
i=0;x=0;
str_lenth=0;
}
}
////////////////////////////////////////////////////////////////////////////
void show_coordinate()
{
lcd.clear();
lcd.print("Lat:");
lcd.print(latitude);
lcd.setCursor(0,1);
lcd.print("Log:");
lcd.print(logitude);
delay(2000);
lcd.clear();
}
///////////////////////////////////////////////////////////////////////////////////////////
//$GPRMC,053508.00,A,1725.64574,N,07835.11697,E,0.041,,121217,,,D*79
void coordinate2dec()
{
String lat_degree="";
for(i=19;i<=20;i++)         
lat_degree+=gpsString[i];
String lat_minut="";
for(i=21;i<=27;i++)         
lat_minut+=gpsString[i];
String log_degree="";
for(i=32;i<=34;i++)
log_degree+=gpsString[i];
String log_minut="";
for(i=35;i<=41;i++)
log_minut+=gpsString[i];
float minut= lat_minut.toFloat();
minut=minut/60;
float degree=lat_degree.toFloat();
latitude=degree+minut;
minut= log_minut.toFloat();
minut=minut/60;
degree=log_degree.toFloat();
logitude=degree+minut;
}
///////////////////////////////////////////////////////////////////////////////
void init_sms1()
{
Serial.println("AT+CMGF=1");delay(400);
Serial.println("AT+CMGS=\"9553539747\"");   // use your 10 digit cell no. here

delay(400);
}

void init_sms2()
{
Serial.println("AT+CMGF=1");delay(400);
Serial.println("AT+CMGS=\"9912267784\"");   // use your 10 digit cell no. here

delay(400);
}


void init_sms3()
{
Serial.println("AT+CMGF=1");delay(400);
Serial.println("AT+CMGS=\"8500697316\"");   // use your 10 digit cell no. here

delay(400);
}



void init_sms4()
{
Serial.println("AT+CMGF=1");delay(400);
Serial.println("AT+CMGS=\"9912391116\"");   // use your 10 digit cell no. here

delay(400);
}

void init_sms5()
{
Serial.println("AT+CMGF=1");delay(400);
Serial.println("AT+CMGS=\"6281146492\"");   // use your 10 digit cell no. here

delay(400);
}

/////////////////////////////////////////////////////////////////////////////
void send_data(String message)
{ Serial.print(message);delay(200);}
///////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void lcd_status()
{lcd.clear();lcd.print("Message Sent");  delay(3000); lcd.clear(); return;}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Send()
{ 
init_sms1();
Serial.println("Women in Trouble");delay(500);
Serial.println("Location Place");delay(500);
Serial.print("Latitude:");Serial.print(latitude,6);send_data(",N\n");
Serial.print("Longitude:");Serial.print(logitude,6);send_data(",E\n");
Serial.println("Plz Rescue ");
Serial.print("https://www.google.com/maps/place/");
Serial.print(latitude,6);Serial.print(",");Serial.print(logitude,6);Serial.write(26);delay(2000);
delay(2000);
lcd_status();

init_sms2();
Serial.println("Women in Trouble");delay(500);
Serial.println("Location Place");delay(500);
Serial.print("Latitude:");Serial.print(latitude,6);send_data(",N\n");
Serial.print("Longitude:");Serial.print(logitude,6);send_data(",E\n");
Serial.println("Plz Rescue ");
Serial.print("https://www.google.com/maps/place/");
Serial.print(latitude,6);Serial.print(",");Serial.print(logitude,6);Serial.write(26);delay(2000);
delay(2000);
lcd_status();

init_sms3();
Serial.println("Women in Trouble");delay(500);
Serial.println("Location Place");delay(500);
Serial.print("Latitude:");Serial.print(latitude,6);send_data(",N\n");
Serial.print("Longitude:");Serial.print(logitude,6);send_data(",E\n");
Serial.println("Plz Rescue ");
Serial.print("https://www.google.com/maps/place/");
Serial.print(latitude,6);Serial.print(",");Serial.print(logitude,6);Serial.write(26);delay(2000);

delay(2000);
lcd_status();

init_sms4();
Serial.println("Women in Trouble");delay(500);
Serial.println("Location Place");delay(500);
Serial.print("Latitude:");Serial.print(latitude,6);send_data(",N\n");
Serial.print("Longitude:");Serial.print(logitude,6);send_data(",E\n");
Serial.println("Plz Rescue ");
Serial.print("https://www.google.com/maps/place/");
Serial.print(latitude,6);Serial.print(",");Serial.print(logitude,6);Serial.write(26);delay(2000);

delay(2000);
lcd_status();


init_sms5();
Serial.println("Women in Trouble");delay(500);
Serial.println("Location Place");delay(500);
Serial.print("Latitude:");Serial.print(latitude,6);send_data(",N\n");
Serial.print("Longitude:");Serial.print(logitude,6);send_data(",E\n");
Serial.println("Plz Rescue ");
Serial.print("https://www.google.com/maps/place/");
Serial.print(latitude,6);Serial.print(",");Serial.print(logitude,6);Serial.write(26);delay(2000);

delay(2000);
lcd_status();


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


