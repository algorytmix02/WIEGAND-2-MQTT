// Wiegand access control reader
// Repo: https://github.com/nygma2004/RFID_Wiegand_MQTT original
// repo version usine a gaz https://github.com/algorytmix02/WIEGAND-2-MQTT.git
//
// Libraries:
// - Wiegand library: https://github.com/monkeyboard/Wiegand-Protocol-Library-for-Arduino
// - FastLED by Daniel Garcia
// - ArduinoJson: install latest from version 5
// RFID reader: https://fr.aliexpress.com/item/1005002950625296.html?spm=a2g0o.order_list.order_list_main.10.5e0e5e5bDuaGXO&gatewayAdapt=glo2fra

//
// NodeMCU pinout:
//D6: (d0) du lecteur wiegand
//D7: (d1) du lecteur wiegand
//GND: GND du lecteur wiegand ( et gnd de l'alim)
//5V: + du lecteur wiegand (et + de l'alim )
//D5: Contact magnétique 
//D2: Encore libre pour le moment
//D0: relais 1 (ventouse, gâche ou portail) pour les portails on rentre par l'entrée BP de la carte électronique et on cable entre COM et NO
//D1:led clavier
//D3: Buzzer clavier
//A0: Bouton de sortie (uniquement)
//D8: sonnette ou contact magnétique supplémentaire
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <PubSubClient.h>           // MQTT support
#include <Wiegand.h>
#include "globals.h"
#include "settings.h"
#include <ArduinoJson.h>
//int etatCM;
WIEGAND wg;
MDNSResponder mdns;
ESP8266WebServer server(80);
WiFiClient espClient;
PubSubClient mqtt(mqtt_server, 1883, 0, espClient);


void setup() {
  Serial.begin(115200);  
  // default Wiegand Pin 2 and Pin 3 see image on README.md
  // for non UNO board, use wg.begin(pinD0, pinD1) where pinD0 and pinD1 
  // are the pins connected to D0 and D1 of wiegand reader respectively.
  wg.begin(WG_PIN_GREEN,WG_PIN_WHITE); // D6 D7 pins used on NodeMCU
  Serial.println();
  Serial.println("Wiegand RFID reader");

  // Initiate the relay outputs
   pinMode(ANALOGINPUT2, INPUT_PULLUP);
   pinMode(ANALOGINPUT3, INPUT_PULLUP);
  digitalWrite(RELAY1, LOW);
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY2, LOW);
  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY3, HIGH);
  pinMode(RELAY3, OUTPUT);
  digitalWrite(RELAY4, HIGH);
  pinMode(RELAY4, OUTPUT);
  


  // Setting up wifi connection
  Serial.print(F("Connecting to Wifi"));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  seconds = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("+"));
    seconds++;
    {
  if (millis()-lastKey > PINTIMEOUT) {
    if (pin!="") {
      pin="";
      lastKey=millis();
      Serial.println("Pin timeout");
    }
  }
  if(wg.available()) {
    unsigned long wcode = wg.getCode();
    int wtype = wg.getWiegandType();
    Serial.print("Wiegand HEX = ");
    Serial.print(wcode,HEX);
    Serial.print(", DECIMAL = ");
    Serial.print(wcode);
    Serial.print(", Type W");
    Serial.print(wtype); 
 if ((pin == codeclamerde )) 
 { Serial.print (" C'est la merde je deverouille la porte");
       digitalWrite(RELAY1, HIGH);
      Serial.println("Relay1 off"); 
      delay(delaisortie);
      digitalWrite(RELAY1, LOW);
      Serial.println("Relay1 ON"); 
 }
    // RFID card was scanned  
    if ((wtype==26)||(wtype==34)) {
      String msg;
      msg = "{\"code\":";
      msg += wcode;
      msg += ",\"type\": \"rfid\"}";
      if ((wcode==badgemaitre1)||(wcode==badgemaitre2)) {
        
        Serial.print("badgemaitre");
         Serial.print (" badge maitre je deverouille la porte");
       digitalWrite(RELAY1, HIGH);
       digitalWrite(RELAY3, HIGH);
      Serial.println("Relay1 off"); 
      delay(delaisortie);
      digitalWrite(RELAY1, LOW);
      digitalWrite(RELAY3, LOW);
      Serial.println("Relay1 ON");
        
      } 
    }

    // Keypad was used
    if (wtype==8) {
      if (wcode==27) {
        pin+="*";
        lastKey = millis();
        Serial.print(" | PIN = ");
        Serial.print(pin);
      }
      if (wcode==13) {
        lastKey = millis();
        String msg;
        msg = "{\"code\": \"";
        msg += pin;
        msg += "\" ,\"type\": \"pin\"}";
        Serial.print(" | PIN = ");
        Serial.print(pin);
        if (millis()-lastPin > PINLIMIT) {
          pincount++;
          mqtt.publish(topicEvent, msg.c_str());
          Serial.print("  -> MQTT sent");
          pin="";
          lastPin = millis();
        } else {
          mqtt.publish(topicEvent, "{ \"type\": \"pinratelimit\" }");
          Serial.print("  -> RATELIMITED");
          pin="";
        }
      }
      if ((wcode>=0)&&(wcode<=9)) {
        pin+=wcode;
        lastKey = millis();
        Serial.print(" | PIN = ");
        Serial.print(pin);
      }
    }
    Serial.println(); 
  }
}

    if (seconds % 2 == 0) {
         digitalWrite(RELAY2, HIGH);
      Serial.println("led clic"); 
    } else {
         digitalWrite(RELAY2, LOW);
      Serial.println("ledCLAC"); 
    }
      
{
  if (millis()-lastAnalog>ANALOGRATE) {
    int sensorValue = analogRead(ANALOGINPUT);
    bool sensorBool = (sensorValue>500 ? false : true);

    if (lastAnalogState!=sensorBool) {
      if (sensorBool) {
     
     
        
      } else {          digitalWrite(RELAY1, HIGH);
      Serial.println("Porte OUVERTE"); 
      delay(delaisortie);
             digitalWrite(RELAY1, LOW);
      Serial.println("Porte FERMée"); 
      
      }
      lastAnalogState = sensorBool;
      lastAnalog=millis();
     
    }
  }
}
    if (seconds>180) {
      // reboot the ESP if cannot connect to wifi
      ESP.restart();
    }
  }

 digitalWrite(RELAY2, HIGH);
  Serial.println("");
  Serial.print(F("Connected to "));
  Serial.println(ssid);
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());
  Serial.print(F("Signal [RSSI]: "));
  Serial.println(WiFi.RSSI());

  // Set up the MDNS and the HTTP server
  if (mdns.begin("rfidmqtt", WiFi.localIP())) {
    Serial.println(F("MDNS responder started"));
  }  
  server.on("/", [](){                        // Dummy page
    server.send(200, "text/plain", "RFID MQTT");
  });
  server.begin();
  Serial.println(F("HTTP server started"));


  // Set up the MQTT server connection
  if (mqtt_server!="") {
    mqtt.setServer(mqtt_server, 1883);
    mqtt.setCallback(MQTTcallback);
    reconnect();
    
  }
      


}

void loop() {
  handleWiegand();
  handleAnalogInput();
 handleAnalogInput2();
 handleAnalogInput3();
  handleMQTTStatus();
  handlePulseReset();
  // Handle MQTT connection/reconnection
  if (mqtt_server!="") {
    if (!mqtt.connected()) {
      reconnect();
      Serial.println ("coucou");
    }
    mqtt.loop();
    delay(10);
  }
  

  
}

// Check the analog input and post changes to MQTT
void handleAnalogInput() {
  if (millis()-lastAnalog>ANALOGRATE) {
    int sensorValue = analogRead(ANALOGINPUT);
    bool sensorBool = (sensorValue>500 ? false : true);

    if (lastAnalogState!=sensorBool) {
      if (sensorBool) {
        mqtt.publish(topicInput, "1");
               digitalWrite(RELAY1, HIGH);
      Serial.println("Porte OUVERTE"); 
      delay(delaisortie);
             digitalWrite(RELAY1, LOW);
      Serial.println("Porte FERMée"); 
        
      } else {
        mqtt.publish(topicInput, "0");
      }
      lastAnalogState = sensorBool;
      lastAnalog=millis();
      Serial.print("Input: ");
      Serial.print(sensorBool);
      Serial.println("  -> MQTT sent");
    }
  }
  }



void handleAnalogInput2(){
  bool etatCM = (digitalRead(ANALOGINPUT2) == LOW); // Lire l'état actuel du bouton
  
  if (etatCM && !etatCMPrec) {
    // Le bouton est enfoncé pour la première fois
    Serial.println("Portail fermé");
    mqtt.publish(topicInput2, "0");
    // Ajoutez ici le code que vous souhaitez exécuter lorsque le bouton est enfoncé
  } else if (!etatCM && etatCMPrec) {
    // Le bouton est relâché pour la première fois
    Serial.println("Portail Ouvert");
    mqtt.publish(topicInput2, "1");
    // Ajoutez ici le code que vous souhaitez exécuter lorsque le bouton est relâché
  }
  
  etatCMPrec = etatCM; // Mettre à jour l'état précédent du bouton
  
  delay(100); // Ajouter un court délai pour éviter les rebonds
}
void handleAnalogInput3(){
  bool etatsonette = (digitalRead(ANALOGINPUT3) == LOW); // Lire l'état actuel du bouton
  
  if (etatsonette && !etatsonettePrec) {
    // Le bouton est enfoncé pour la première fois
    Serial.println("sonette 0");
    mqtt.publish(topicInput3, "0");
    // Ajoutez ici le code que vous souhaitez exécuter lorsque le bouton est enfoncé
  } else if (!etatsonette && etatsonettePrec) {
    // Le bouton est relâché pour la première fois
    Serial.println("sonette 1");
    mqtt.publish(topicInput3, "1");
    // Ajoutez ici le code que vous souhaitez exécuter lorsque le bouton est relâché
  }
  
  etatsonettePrec = etatsonette; // Mettre à jour l'état précédent du bouton
  
  delay(100); // Ajouter un court délai pour éviter les rebonds
}
// This resets the relay output when it was turned on in pulse mode
void handlePulseReset() {
  if ((pulse1State)&&(millis()-lastPulse1>250)) {
    digitalWrite(RELAY1, HIGH);
    pulse1State = false;
    Serial.println("Relay1 Pulse End");
  }
  if ((pulse2State)&&(millis()-lastPulse2>250)) {
    digitalWrite(RELAY2, HIGH);
    pulse2State = false;
    Serial.println("Relay2 Pulse End");
  }
}



// Check the Wiegand input for new keypresses or scanned RFID tags
void handleWiegand() {
  if (millis()-lastKey > PINTIMEOUT) {
    if (pin!="") {
      pin="";
      lastKey=millis();
      Serial.println("Pin timeout");
    }
  }
  if(wg.available()) {
    unsigned long wcode = wg.getCode();
    int wtype = wg.getWiegandType();
    Serial.print("Wiegand HEX = ");
    Serial.print(wcode,HEX);
    Serial.print(", DECIMAL = ");
    Serial.print(wcode);
    Serial.print(", Type W");
    Serial.print(wtype); 
 if ((pin == codeclamerde )) 
 { Serial.print (" C'est la merde je deverouille la porte");
       digitalWrite(RELAY1, HIGH);
      Serial.println("Relay1 off"); 
      delay(delaisortie);
      digitalWrite(RELAY1, LOW);
      Serial.println("Relay1 ON"); 
 }
    // RFID card was scanned  
    if ((wtype==26)||(wtype==34)) {
      String msg;
      msg = "{\"code\":";
      msg += wcode;
      msg += ",\"type\": \"rfid\"}";
      if (millis()-lastRfid > RFIDLIMIT) {
        rfidcount++;
        mqtt.publish(topicEvent, msg.c_str());
        Serial.print("  -> MQTT sent");
        lastRfid = millis();
      } else {
        mqtt.publish(topicEvent, "{ \"type\": \"rfidratelimit\" }");
        Serial.print("  -> RATELIMITED");
      }
    }

    // Keypad was used
    if (wtype==8) {
      if (wcode==27) {
        pin+="*";
        lastKey = millis();
        Serial.print(" | PIN = ");
        Serial.print(pin);
      }
      if (wcode==13) {
        lastKey = millis();
        String msg;
        msg = "{\"code\": \"";
        msg += pin;
        msg += "\" ,\"type\": \"pin\"}";
        Serial.print(" | PIN = ");
        Serial.print(pin);
        if (millis()-lastPin > PINLIMIT) {
          pincount++;
          mqtt.publish(topicEvent, msg.c_str());
          Serial.print("  -> MQTT sent");
          pin="";
          lastPin = millis();
        } else {
          mqtt.publish(topicEvent, "{ \"type\": \"pinratelimit\" }");
          Serial.print("  -> RATELIMITED");
          pin="";
        }
      }
      if ((wcode>=0)&&(wcode<=9)) {
        pin+=wcode;
        lastKey = millis();
        Serial.print(" | PIN = ");
        Serial.print(pin);
      }
    }
    Serial.println(); 
  }
}

// Send status messge over MQTT
void handleMQTTStatus() {
  if (millis() - lastStatus >= STATUSUPDATEFRQ) {  
    lastStatus = millis();
    String mqttStat;
    mqttStat = "{\"rssi\":";
    mqttStat += WiFi.RSSI();
    mqttStat += ",\"uptime\":";
    mqttStat += millis()/1000/60;
    mqttStat += ",\"rfidcount\":";
    mqttStat += rfidcount;
    mqttStat += ",\"pincount\":";
    mqttStat += pincount;
    mqttStat += "}";
    mqtt.publish(topicStatus, mqttStat.c_str());
    Serial.print(F("Status: "));
    Serial.println(mqttStat);
  }    
}

// MQTT reconnect logic
void reconnect() {

  // Loop until we're reconnected
  while (!mqtt.connected())
  {
     
  digitalWrite(RELAY2, HIGH);
    delay(500);
     digitalWrite(RELAY2, LOW);
    Serial.print("Attempting MQTT connection...");
    
  if (millis()-lastKey > PINTIMEOUT) {
    if (pin!="") {
      pin="";
      lastKey=millis();
      Serial.println("Pin timeout");
    }
  }
  if(wg.available()) {
    unsigned long wcode = wg.getCode();
    int wtype = wg.getWiegandType();
    Serial.print("Wiegand HEX = ");
    Serial.print(wcode,HEX);
    Serial.print(", DECIMAL = ");
    Serial.print(wcode);
    Serial.print(", Type W");
    Serial.print(wtype); 
 
    // RFID card was scanned  
    if ((wtype==26)||(wtype==34)) {
      String msg;
      msg = "{\"code\":";
      msg += wcode;
      msg += ",\"type\": \"rfid\"}";
      if ((wcode==badgemaitre1)||(wcode==badgemaitre2)) {
      Serial.print (" C'est la merde je deverouille la porte");
       digitalWrite(RELAY1, HIGH);
      Serial.println("Relay1 off"); 
      delay(delaisortie);
      digitalWrite(RELAY1, LOW);
      Serial.println("Relay1 ON");  
      } 
    }

    // Keypad was used
    if (wtype==32) {
      if (wcode==27) {
        pin+="*";
        lastKey = millis();
        Serial.print(" | PIN = ");
        Serial.print(pin);
      }
      if (wcode==13) {
        lastKey = millis();
        String msg;
        msg = "{\"code\": \"";
        msg += pin;
        msg += "\" ,\"type\": \"pin\"}";
        Serial.print(" | PIN = ");
        Serial.print(pin);
        if (millis()-lastPin > PINLIMIT) {
          pincount++;
          mqtt.publish(topicEvent, msg.c_str());
          Serial.print("  -> MQTT sent");
          pin="";
          lastPin = millis();
        } else {
          mqtt.publish(topicEvent, "{ \"type\": \"pinratelimit\" }");
          Serial.print("  -> RATELIMITED");
          pin="";
        }
      }
      if ((wcode>=0)&&(wcode<=9)) {
        pin+=wcode;
        lastKey = millis();
        Serial.print(" | PIN = ");
        Serial.print(pin);
      }
      if ((pin == codeclamerde )) 
 { Serial.print (" C'est la merde je deverouille la porte");
       digitalWrite(RELAY1, HIGH);
      Serial.println("Relay1 off"); 
      delay(delaisortie);
      digitalWrite(RELAY1, LOW);
      Serial.println("Relay1 ON"); 
 }
    }
    Serial.println(); 
  }

    // Attempt to connect
    if (mqtt.connect(clientID, mqtt_user, mqtt_password)) {
      Serial.println(F("connected"));
      // ... and resubscribe
      mqtt.subscribe(topicRelay1);
      Serial.print(F("Subscribed to "));
      Serial.println(topicRelay1);
      mqtt.subscribe(topicRelay2);
      Serial.print(F("Subscribed to "));
      Serial.println(topicRelay2);
      mqtt.subscribe(topicRelay3);
      Serial.print(F("Subscribed to "));
      Serial.println(topicRelay3);
      mqtt.subscribe(topicRelay4);
      Serial.print(F("Subscribed to "));
      Serial.println(topicRelay4);
      Serial.print(F("Subscribed to "));
      mqtt.subscribe(topicPulse1);
      Serial.print(F("Subscribed to "));
      Serial.println(topicPulse1);
      mqtt.subscribe(topicPulse2);
      Serial.print(F("Subscribed to "));
      Serial.println(topicPulse2);
    } else {
  
  
      digitalWrite(RELAY2, HIGH);
    delay(500);
     digitalWrite(RELAY2, LOW);
      Serial.print(F("failed, rc="));
      Serial.print(mqtt.state());
      Serial.println(F(" try again in 5 seconds"));
      // Wait 5 seconds before retrying
        digitalWrite(RELAY2, HIGH);
    delay(500);
     digitalWrite(RELAY2, LOW);
      delay(1000);
    
        }
 }
}

// MQTT callback function
void MQTTcallback(char* topic, byte* payload, unsigned int length) {
  // Convert the incoming byte array to a string
  char inData[120];
  Serial.print("array: ");
   for(int i = 0; i<length; i++){
     //Serial.print((char)payload[i]);Serial.print("_");
     inData[i] = (char)payload[i];
   }
   //Serial.println();

  String strTopic = String((char*)topic);
  payload[length] = '\0'; // Null terminator used to terminate the char array
  String message = (char*)payload;

  Serial.print(F("Message arrived on topic: ["));
  Serial.print(strTopic);
  Serial.print(F("], "));
  Serial.println(message);

  if (strTopic==(String)topicRelay1) {
    int newvalue = atoi((char *)payload);
    if (newvalue==0) {
      digitalWrite(RELAY1, HIGH);
      Serial.println("Relay1 off");  
    }
    if (newvalue==1) {
      digitalWrite(RELAY1, LOW);
      Serial.println("Relay1 on");  
    }
  }
  if (strTopic==(String)topicRelay2) {
    int newvalue = atoi((char *)payload);
    if (newvalue==0) {
      digitalWrite(RELAY2, HIGH);
      Serial.println("Relay2 off");  
    }
    if (newvalue==1) {
      digitalWrite(RELAY2, LOW);
      Serial.println("Relay2 on");  
    }
  }
  if (strTopic==(String)topicRelay3) {
    int newvalue = atoi((char *)payload);
    if (newvalue==0) {
      digitalWrite(RELAY3, HIGH);
      Serial.println("Relay3 off");  
    }
    if (newvalue==1) {
      digitalWrite(RELAY3, LOW);
      Serial.println("Relay3 on");  
    }
  }
  if (strTopic==(String)topicRelay4) {
    int newvalue = atoi((char *)payload);
    if (newvalue==0) {
      digitalWrite(RELAY4, HIGH);
      Serial.println("Relay4 off");  
    }
    if (newvalue==1) {
      digitalWrite(RELAY4, LOW);
      Serial.println("Relay4 on");  
    }
  }
  if (strTopic==(String)topicPulse1) {
    int newvalue = atoi((char *)payload);
    if (newvalue==1) {
      digitalWrite(RELAY1, LOW);
      Serial.println("Relay1 Pulse");  
      lastPulse1 = millis();
      pulse1State = true;
    }
  }
  if (strTopic==(String)topicPulse2) {
    int newvalue = atoi((char *)payload);
    if (newvalue==1) {
      digitalWrite(RELAY2, LOW);
      Serial.println("Relay2 Pulse");  
      lastPulse2 = millis();
      pulse2State = true;
    }
  }
 

}
