#ifdef _SMARTDEBUG
//TODO Change for my use case
  // Hilfsfunktion für WAIT - Makro
  void DebugWait(String txt) {
    // buffer leeren
    char ch;
    while (Serial.available()) ch = Serial.read();
    ch = 0;
  
    Serial.print(txt);
    Serial.println(" >press 'c' to continue..."); 

    // auf 'c' warten
    do {
      if (Serial.available() > 0) ch = Serial.read();
    } while (ch != 'c'); 
    // buffer leeren
    while (Serial.available()) ch = Serial.read();
  }  

  // Initialisierung
  #define DEBUG_INIT(speed) Serial.begin(speed)

  // Textausgabe
  #define DEBUG_PRINT(txt) Serial.print(txt)
  #define DEBUG_PRINTLN(txt) Serial.println(txt)
  #define DEBUG_PRINT_VALUE(txt, val) Serial.print(txt); Serial.print(": "); Serial.print(val)
  #define DEBUG_PRINTLN_VALUE(txt, val) Serial.print(txt); Serial.print(": "); Serial.println(val)
  #define DEBUG_PRINTLN_EMPTY() Serial.println()
  
  // andere Befehle
  #define DEBUG_DELAY(ms) delay(ms)
  #define DEBUG_WAIT(txt, condition) if (condition) DebugWait(txt)
#else
  // Leere Makro - Rümpfe, für den Fall, dass kein Debugging erwünscht ist
  #define DEBUG_INIT(speed)
  #define DEBUG_PRINT(txt)
  #define DEBUG_PRINTLN(txt)
  #define DEBUG_PRINT_VALUE(txt, val)
  #define DEBUG_PRINTLN_VALUE(txt, val)
  #define DEBUG_PRINTLN_EMPTY()
  #define DEBUG_DELAY(ms)
  #define DEBUG_WAIT(txt, condition)
#endif



#ifndef myGENERAL
#define myGENERAL


#ifndef def_FUNC_SoftwareReset
#define def_FUNC_SoftwareReset
//======================================================================================
void FUNC_SoftwareReset()
{ // Restarts program from beginning but does not reset the peripherals and registers
  // digitalWrite(D5_LED_gruen_PIN,LOW);
  // digitalWrite(D4_LED_an_PIN,LOW);
  // asm volatile ("  jmp 0");
  ESP.restart();
}
#endif

//======================================================================================
// void FUNC_PrintVar(char *_VARL_text) { // Prints a given text to serial out
void FUNC_PrintVar(String _VARL_text)
{ // Prints a given text to serial out
#ifdef LogOn
  Serial.println(_VARL_text);
  //  Serial.print("stat1="); Serial.print(starttime1); Serial.print(" stot1="); Serial.print(stoptime1); Serial.print(" sto-sta1="); Serial.print(stosta1); Serial.print(" sta1sto2="); Serial.println(sta1sto2);
  //  Serial.print("stat2="); Serial.print(starttime2); Serial.print(" stot2="); Serial.print(stoptime2); Serial.print(" sto-sta2="); Serial.print(stosta2); Serial.print(" sta2sto3="); Serial.println(sta2sto3);
  //  Serial.print("stat3="); Serial.print(starttime3); Serial.print(" stot3="); Serial.print(stoptime3); Serial.print(" sto-sta3="); Serial.print(stosta3); Serial.print(" sta3sto4="); Serial.println(sta3sto4);
  //  Serial.print("stat4="); Serial.print(starttime4); Serial.print(" stot4="); Serial.print(stoptime4); Serial.print(" sto-sta4="); Serial.println(stosta4);
#endif
}

#endif
