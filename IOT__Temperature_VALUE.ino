#include<SoftwareSerial.h>

const byte tx=3,rx=2;
const int temp_pin=A0;
float temp;
                                          
SoftwareSerial esp8266(rx,tx);

String ssid = "smart" ;
String password = "123456789" ;


String api = "AAWNHUSIFSUH2V8A" ; 
String host = "api.thingspeak.com" ;
String port = "80" ;

void setup()
{
  pinMode(temp_pin,INPUT);
  Serial.begin (9600);
  esp8266.begin(115200);
  Serial.println("IOT Project");
 connectwifi();
}
  
void loop()
{
    temp=analogRead(temp_pin)*0.00488*100;
    senddata();
    delay(50000);
}



void sendcommand(String command, int maxtime, char readreply[]) 
{

boolean found = false;
  
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
 esp8266.println(command);
         while (maxtime--)
         {
            if (esp8266.find(readreply)) 
             {
                 found = true; break;
             }
        }

  if (found)
  {
    Serial.println("OK Done");
  }
 else
  {
    Serial.println("Fail");
  }

}

void connectwifi()
{
sendcommand("AT",5,"OK");
sendcommand("AT+CWMODE=1",5,"OK");
sendcommand("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"" , 20 ,"OK");

}

void senddata()
{
  String getData1 = "GET /update?api_key="+ api ;
  String getData2 = "&field2="+String(temp);
  
 sendcommand("AT+CIPMUX=0",5,"OK");
 sendcommand("AT+CIPSTART=\"TCP\",\""+ host + "\"," + port , 15, "OK");
 sendcommand("AT+CIPSEND=" + String(getData1.length() + getData2.length()+ 2), 7, '>');

  delay(100);

  esp8266.println(getData1+getData2);
  Serial.println(getData1 + getData2);
  delay(2500);
 
  Serial.println("---------------------------");
}
