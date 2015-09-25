#include <SPI.h>
#include <HttpClient.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <Servo.h> 

const char kHostname[] = "brewcrew-thefad3.c9.io";

const char kPath[] = "/index.php";

byte mac[] = {  0x90, 0xA2, 0xDA, 0x0F, 0x98, 0xCF  };

const int kNetworkTimeout = 30*1000;
const int kNetworkDelay = 10*1000;

EthernetClient c;
HttpClient http(c);
Servo theArm;


void setup()
{
  theArm.attach(5);
  Serial.begin(9600); 
  while (Ethernet.begin(mac) != 1)
  {
  }  
}

void loop()
{
  currentCount();
  delay(kNetworkDelay);
}

void currentCount(){
  int err =0;
  err = http.get(kHostname, kPath);
  if (err == 0)
  {
    Serial.println("startedRequest ok");
    err = http.responseStatusCode();
    if (err >= 0)
    {
      err = http.skipResponseHeaders();
      if (err >= 0)
      {
        int bodyLen = http.contentLength();
        unsigned long timeoutStart = millis();
        char c;
        while ((http.connected() || http.available()) && ((millis() - timeoutStart) < kNetworkTimeout))
        {
            if (http.available())
            {
                c = http.read();
                if(c == 'y'){
                  Serial.println("Needs Moar Beer");         
                    theArm.write(180);
                    delay(150);
                    theArm.write(90);
                    delay(150);
                    theArm.write(180);
                    delay(30*1000);
                }
                if(c == 'n'){
                  Serial.println("Dont need no bureee");
                }
                timeoutStart = millis();
            }
            else
            {
                delay(kNetworkDelay);
            }
        }
      }
      else
      {
        Serial.print("Failed to skip response headers: ");
        
      }
    }
    else
    {    
      Serial.print("Getting response failed: ");
      
    }
  }
  else
  {
    Serial.print("Connect failed: "); 
  }
  http.stop();
  
}





