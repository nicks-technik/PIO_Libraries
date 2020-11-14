/* 
Needed informations that this Library is working
WIFI Variables
Fingerprint
// const char* _GMailServer = "smtp.gmail.com";
// const char* _mailUser = "expressifmail@gmail.com";
// const char* _mailPassword = "expres8266";
// const String _To = "To: <thorsten.hornick+test@gmail.com>";
// const String _From = "From: <expressifmail@gmail.com>";
// String _VAR_EmailText ="Subject: Your Arduino\r\n" + 
    "This email was sent securely via an encrypted mail link.\n" +
    "In the last hour there was: 8 activities detected. Please check all is well.\n" +
    "This email will NOT be repeated for this hour.\n" +
    "This email was sent from an unmonitored email account - please do not reply.\n" +
    "Love and kisses from Dougle and Benny. They wrote this sketch.\n";


 */
#ifndef myEMAIL
#define myEMAIL

#include <base64.h>

// Check response from SMTP server
byte FUNC_response()
{
  // Wait for a response for up to X seconds
  int loopCount = 0;
  while (! _WiFiClientSecure.available())
  {
    delay(1);
    loopCount++;
    // if nothing received for 10 seconds, timeout
    if (loopCount > 10000)
    {
      _WiFiClientSecure.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }

  byte _VARL_respCode = _WiFiClientSecure.peek(); // Take a snapshot of the response code
  while (_WiFiClientSecure.available())
  {

#ifdef LogOn
 Serial.write(_WiFiClientSecure.read());
#endif

  }

  if (_VARL_respCode >= '4')
  {
#ifdef LogOn
    // Serial.print("Failed in eRcv with response: ");
    // Serial.print(_VARL_respCode);
    FUNC_PrintVar("Failed in eRcv with response: ");
    FUNC_PrintVar(String(_VARL_respCode));
    #endif
    return 0;
  }
  return 1;
}

byte FUNC_sendEmail(String _VARL_EmailText)
{
  _WiFiClientSecure.setFingerprint(_VAR_Fingerprint); // not available in axTLS::WiFiClientSecure 4.2.2
  // if (!response())
  //   return 0;
  // port 465=SSL 567=TLS; 587 not available with library 4.2.2
  // this all needs Google security downgrading:
  // https://myaccount.google.com/lesssecureapps?utm_source=google-account&utm_medium=web

  /*
 * Gmail exposes port 465 for SMTP over SSL and port 587 for SMTP with STARTTLS.
 * The difference between these two is that SMTP over SSL first establishes a secure 
 * SSL/TLS connection and conducts SMTP over that connection, and SMTP with STARTTLS 
 * starts with unencrypted SMTP and then switches to SSL/TLS. 
 * See https://stackoverflow.com/questions/17281669/using-smtp-gmail-and-starttls
 */
  Serial.println("Attempting to connect to GMAIL server");
  _WiFiClientSecure.setInsecure();

  if (_WiFiClientSecure.connect("smtp.gmail.com", 465) == 1)
  {
    Serial.println(F("Connected"));
  }
  else
  {
    Serial.print(F("Connection failed:"));
    return 0;
  }
  if (!FUNC_response())
    return 0;

  Serial.println(F("Sending Extended Hello"));
  _WiFiClientSecure.println("EHLO gmail.com");
  if (!FUNC_response())
    return 0;

  // We're not using port 567 in this demo
  //Serial.println(F("STARTTLS"));
  //if (!FUNC_response())
  //  return 0;
  //Serial.println(F("Sending EHLO"));
  //_WiFiClientSecure.println("EHLO gmail.com");
  //if (!FUNC_response())
  //  return 0;

  Serial.println(F("Sending auth login"));
  _WiFiClientSecure.println("auth login");
  if (!FUNC_response())
    return 0;

  Serial.println(F("Sending User"));
  // Change to your base64, ASCII encoded user
  _WiFiClientSecure.println(base64::encode(_mailUser));
  if (!FUNC_response())
    return 0;

  Serial.println(F("Sending Password"));
  // change to your base64, ASCII encoded password
  _WiFiClientSecure.println(base64::encode(_mailPassword));
  if (!FUNC_response())
    return 0;

  Serial.println(F("Sending From"));
  // your email address (sender) - MUST include angle brackets
  // _WiFiClientSecure.println(F("MAIL FROM: <arduinitepower@gmail.com>"));
  _WiFiClientSecure.println("MAIL " + _From);
  if (!FUNC_response())
    return 0;

  // change to recipient address - MUST include angle brackets
  Serial.println(F("Sending To"));
  // _WiFiClientSecure.println(F("RCPT To: <ralph@gmail.com>"));
  _WiFiClientSecure.println("RCPT " + _To);
  // Repeat above line for EACH recipient
  if (!FUNC_response())
    return 0;

  Serial.println(F("Sending DATA"));
  _WiFiClientSecure.println(F("DATA"));
  if (!FUNC_response())
    return 0;

  Serial.println(F("Sending email"));
  // recipient address (include option display name if you want)
  // _WiFiClientSecure.println(F("To: Home Alone Group<totally@made.up>"));
  _WiFiClientSecure.println(_To);

  // change to your address
  // _WiFiClientSecure.println(F("From: test@gmail.com"));
  // _WiFiClientSecure.println(_From);
  _WiFiClientSecure.println(_VAR_EmailText);

  // IMPORTANT you must send a complete line containing just a "." to end the conversation
  // So the PREVIOUS line to this one must be a prinln not just a print
  _WiFiClientSecure.println(F("."));
  if (!FUNC_response())
    return 0;

  Serial.println(F("Sending QUIT"));
  _WiFiClientSecure.println(F("QUIT"));
  if (!FUNC_response())
    return 0;

  _WiFiClientSecure.stop();
  Serial.println(F("Disconnected Client"));
  return 1;
}

#endif
