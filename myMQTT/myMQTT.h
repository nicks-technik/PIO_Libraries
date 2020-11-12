#define myMQTT
// Needed in the platformio.ini
// adafruit/Adafruit MQTT Library @ ^2.1.0

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* Adafruit.io Setup *********************************/
// #define _AIO_SERVER      "io.adafruit.com"
// #define _AIO_SERVERPORT  8883                   // 8883 for MQTTS
// #define _AIO_USERNAME    "AIO_User"
// #define _AIO_KEY         "AIO_Key"
// #define _CONST_MQTT_Open_SubFeed_Name "/feeds/test"

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client _VAR_MQTT_Secure_Client(&_VAR_WIFIClientSecure, _AIO_SERVER, _AIO_SERVERPORT, _AIO_USERNAME, _AIO_KEY);

// io.adafruit.com SHA1 fingerprint. Current fingerprint can be verified via:
// # echo | openssl s_client -connect io.adafruit.com:443 |& openssl x509 -fingerprint -noout
//const char* _CONST_Fingerprint = "77 00 54 2D DA E7 D8 03 27 31 23 99 EB 27 DB CB A5 4C 57 18";
static const char* _CONST_Fingerprint PROGMEM = "59 3C 48 0A B1 8B 39 4E 0D 58 50 47 9A 13 55 60 CC A0 1D AF";

const unsigned int _CONST_MQTTIntervall = 60000; // after this time a keepalive of the MQTTS Server was made
unsigned long _VAR_MQTTAn = 0; // Millis, when the last MQTT Keepalive worked.

/****************************** Feeds ***************************************/
// Setup a subscribe feed
Adafruit_MQTT_Subscribe _VAR_MQTT_SubFeed = Adafruit_MQTT_Subscribe(&_VAR_MQTT_Secure_Client, _AIO_USERNAME _CONST_MQTT_SubFeed_Name, MQTT_QOS_1);
// Feedback feed
Adafruit_MQTT_Publish _VAR_MQTT_PublishFeed = Adafruit_MQTT_Publish(&_VAR_MQTT_Secure_Client, _AIO_USERNAME _CONST_MQTT_SubFeed_Name, MQTT_QOS_1);
    
//======================================================================================
void FUNC_MQTT_Connect() { // Function to connect and reconnect as necessary to the MQTT server.
  // Should be called in the loop function and it will take care if connecting.
int8_t _VARL_ret;

  // Stop if already connected.
  if (_VAR_MQTT_Secure_Client.connected()) {
    return;
  }

      #ifdef LogOn
  Serial.print("Connecting to MQTT... ");
      #endif

  uint8_t _VARL_retries = 3;
  while ((_VARL_ret = _VAR_MQTT_Secure_Client.connect()) != 0) { // connect will return 0 for connected
#ifdef LogOn
    Serial.println(_VAR_MQTT_Secure_Client.connectErrorString(_VARL_ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
#endif
    _VAR_MQTT_Secure_Client.disconnect();
    delay(1000);  // wait 1 seconds
    _VARL_retries--;
    if (_VARL_retries == 0) {
      // basically die and wait for WDT to reset me
      FUNC_SoftwareReset();
    }

  }

#ifdef LogOn
  Serial.println("MQTT Connected!");
#endif
}

//======================================================================================
void FUNC_MQTT_Paket() { // Check, that the MQTT Connection is alive and wait for packets
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  FUNC_MQTT_Connect();

  // this is our 'wait for incoming subscription packets and callback em' busy subloop
  // try to spend your time here:
  _VAR_MQTT_Secure_Client.processPackets(10);

}

//======================================================================================
// void FUNC_MQTT_PublishMessage(char *_VARL_MessageText) { // Publish a MQTT Message, with error check
void FUNC_MQTT_PublishMessage(char *_VARL_MessageText) { // Publish a MQTT Message, with error check
  // delay(1200);
  if (! _VAR_MQTT_PublishFeed.publish(_VARL_MessageText)) {
    Serial.println("Failed to Publish" + String(_VARL_MessageText));
    delay(2000); // Should normally never be used
    if (! _VAR_MQTT_PublishFeed.publish(_VARL_MessageText)) {
      Serial.println("Failed2 to Publish " + String(_VARL_MessageText));
    }
    else
    {
      #ifdef LogOn
      Serial.println("OK!2 Published" + String(_VARL_MessageText));
      #endif
    }
  }
  else
  {
      #ifdef LogOn
      Serial.println("OK! Published" + String(_VARL_MessageText));
      #endif
  }
}




