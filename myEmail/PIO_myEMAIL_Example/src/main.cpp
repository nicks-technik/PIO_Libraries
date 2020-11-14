#define LogOn

#include <Arduino.h>

#include "secure.h"
const char *_VAR_Fingerprint = "289509731da223e5218031c38108dc5d014e829b"; // For smtp.gmail.com
// WiFiClientSecure _WiFiClientSecure;

#include <myGENERAL.h>
#include <myWIFI.h>
#include <myEmail.h>

void setup()
{
  // put your setup code here, to run once:
#ifdef LogOn
  Serial.begin(115200);
  // delay(10);
  Serial.println("Booting");
#endif

  // Setup the WIFI
  FUNC_WIFI_Setup();

  // Send an email
  if (!FUNC_sendEmail(_VAR_EmailText))
  {
#ifdef LogOn
    FUNC_PrintVar("Problem sending Mail");
#endif
  }

#ifdef LogOn
  FUNC_PrintVar("End of Setup");
#endif
}

void loop()
{
}
