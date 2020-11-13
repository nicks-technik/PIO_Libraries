#ifndef myWIFI

#define myWIFI

#include <ESP8266WiFi.h>
// #include <ESP8266mDNS.h>
#include <myGENERAL.h>
// Needed Informations for the WIFI network
// const char* _WIFI_SSID = "SSID";
// const char* _WIFI_Password = "PASSWORD";

/************ Global State (you don't need to change this!) ******************/
// #ifndef WIFIClientSecure
// #define WIFIClientSecure
// WiFiClientSecure for SSL/TLS support
WiFiClientSecure _WiFiClientSecure;
// #endif

uint8_t FUNC_rssiToPercentage(int32_t _VARL_rssi) // Convert the WIFI rssi to a percentage
{
  //@author Marvin Roger - https://github.com/marvinroger/homie-esp8266/blob/ad876b2cd0aaddc7bc30f1c76bfc22cd815730d9/src/Homie/Utils/Helpers.cpp#L12
  uint8_t _VARL_quality;
  if (_VARL_rssi <= -100)
  {
    _VARL_quality = 0;
  }
  else if (_VARL_rssi >= -50)
  {
    _VARL_quality = 100;
  }
  else
  {
    _VARL_quality = 2 * (_VARL_rssi + 100);
  }

  return _VARL_quality;
}

void FUNC_PrintWifiStatus() // Wifi Status Ouput to Serial
{ // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress _VARL_ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(_VARL_ip);

  // print the received signal strength:
  long _VARL_rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI): ");
  Serial.print(_VARL_rssi);
  Serial.print(" dBm %: ");
  Serial.println(FUNC_rssiToPercentage(_VARL_rssi));
}

/************ Setup of the Wifi in the normal Setup-Function **************/
void FUNC_WIFI_Setup()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(_WIFI_SSID, _WIFI_Password);

  // while (WiFi.waitForConnectResult() != WL_CONNECTED)
  byte _VARL_counter = 0; // Counter for repeated WLAN Status reads
  while (WiFi.status() != WL_CONNECTED)
  {

#ifdef LogOn
    Serial.print(".");
    _VARL_counter++;
#endif
    delay(500); // Wait until the WiFi is setup correctly
    if (_VARL_counter == 40)
    {
      Serial.println();
      Serial.println("Connection Failed! Rebooting...");
      delay(10000); // Should never be used
      FUNC_SoftwareReset();
    }
#ifdef myMQTT
    _WiFiClientSecure.setFingerprint(_fingerprint);
#endif
  }

#ifdef LogOn
  FUNC_PrintWifiStatus();
#endif
}

#endif
