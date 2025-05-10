#include<SoftwareSerial.h>
const byte tx=3,rx=2;
int value;
SoftwareSerial esp8266(rx,tx);
String ssid = "smart" ;
String password = "123456789" ;
String api = "AAWNHUSIFSUH2V8A" ; 
String host = "api.thingspeak.com" ;
String port = "80" ;
void setup()
{
  Serial.begin (9600);
  esp8266.begin(115200);
  Serial.println("IOT Project");
 connectwifi();
}
void loop()
{
    value++;
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
sendcommand("AT+CWJAP=\"" + ssid + "\",\""+ password + "\"" , 20 ,"OK");
}

void senddata()
{
  String getData1 = "GET /update?api_key="+ api ;
  String getData2 = "&field1="+String(value);
  sendcommand("AT+CIPMUX=0",5,"OK");
     sendcommand("AT+CIPSTART=\"TCP\",\""+ host + "\"," + port , 15, "OK");
 sendcommand("AT+CIPSEND=" + String(getData1.length() + getData2.length()+ 2), 7, ">");

  delay(500);

  esp8266.println(getData1+getData2);
  Serial.println(getData1 + getData2);
  delay(3500);

  sendcommand("AT+CIPCLOSE=0", 5, "OK");  
  Serial.println("---------------------------");
}
