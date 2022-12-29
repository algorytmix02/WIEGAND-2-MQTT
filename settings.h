#define STATUSUPDATEFRQ 60000 // sending status MQTT in milliseconds
#define PINTIMEOUT 2000       // pin code entry timeout in milliseconds
#define PINLIMIT 2000         // limit how quickly pin codes can be sent
#define RFIDLIMIT 2000        // limit how quickly rfids can be scanned
#define IBUTTONLIMIT 2000     // limit how quickly same ibutton can be scanned
#define BRIGHTNESS  64        // Default LED brightness.
#define ANALOGRATE 250        // Analog input query frequency
#define PULSEDELAY 250        // Length of the pulse output
#define badgemaitre1 7549741 // badge maitre 1 qui sert a ouvrir la porte coute que coute ( voir au dos du badge aprés les 000)
#define badgemaitre2 8406068
#define delaisortie 5000      // ici le delai de sortie aprés avoir relacher ton BP, sauf si pas de wifi ou mqtt c'est l'inverse
const char *codeclamerde="12345";           // Ici tu modifie ton code "c'est la merde" qui deverouille la porte quoi qu'il arrive
const char *ssid = "SSID";                     // Wifi SSID
const char *password = "MDP";              // Wifi password
const char* mqtt_server = "IPMOSQUITTO";               // MQTT server address, leave empty to disable MQTT function
const char* mqtt_user = "jeedom";                          // MQTT user id
const char* mqtt_password = "jeedom";                      // MQTT password
const char* clientID = "rfid2";                     // MQTT client ID
const char* topicStatus = "rfid/status";          // MQTT topic where the device sends updates every 10 seconds
const char* topicEvent = "rfid/event";          // pin code entered, or card scanned
const char* topicRelay1 = "rfid/relay1";          // Relay 1 On/Off
const char* topicRelay2 = "rfid/relay2";          // Relay 2 On/Off
const char* topicRelay3 = "rfid/relay3";          // Relay 3 On/Off
const char* topicRelay4 = "rfid/relay4";          // Relay 4 On/Off
const char* topicPulse1 = "rfid/pulse1";          // Short Pulse on Relay 1
const char* topicPulse2 = "rfid/pulse2";          // Short Pulse on Relay 2
const char* topicLight = "rfid/light";          // change the light
const char* topicInput = "rfid/input";          // input sensor value
