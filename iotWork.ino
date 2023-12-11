

#include <ESP8266WiFi.h>  
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>                                            
#include <FirebaseArduino.h>      
                        
 
#define FIREBASE_HOST "footwear-abf3c-default-rtdb.firebaseio.com"     // the project name address from firebase id
#define FIREBASE_AUTH "fZ3DW9P7TQapIDsS3YCaihofrH3hLUVWi8oaaKpD"       // the secret key generated from firebase
#define WIFI_SSID "GouravA51"                                          
#define WIFI_PASSWORD "gourav2004"                                  
 
String fireStatus = "";          // led status received from firebase

int led1 = 5;  
int led2 = 16 ;
int SOL_PIN = D3;               // Define the GPIO pin connected to the solenoid

                                                             
void setup()
{
  Serial.begin(9600);
  delay(1000);    
  pinMode(led1, OUTPUT);   
  pinMode(led2, OUTPUT); 
  pinMode(SOL_PIN, OUTPUT);     
  // s1.attach(0);         
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                              
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   
  Firebase.setString("LED_STATUS", "OFF");               // connect to firebase
                                                         //send initial string of led status
}
 
void loop()
{

  fireStatus = Firebase.getString("LED_STATUS");        // get ld status input from firebase
  if (fireStatus == "ON")
  {                                                     // compare the input of led status received from firebase
    Serial.println("Led Turned ON");                                                        
    digitalWrite(led1, HIGH);  
    digitalWrite(led2, LOW); 
    digitalWrite(SOL_PIN, HIGH); 
    delay(5000);
    Firebase.setString("LED_STATUS", "OFF");

    
                                             // make external led ON
  }
  else if (fireStatus == "OFF")
  {                                          // compare the input of led status received from firebase
    Serial.println("Led Turned OFF");
    digitalWrite(led2, HIGH);  
    digitalWrite(led1, LOW); 
    digitalWrite(SOL_PIN, LOW); 
    // s1.write(0);                          // make external led OFF
  }
  else
  {
    Serial.println("Command Error! Please send ON/OFF");
  }
  
  
  
}
