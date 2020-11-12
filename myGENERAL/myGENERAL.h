#define myGENERAL

#ifndef def_FUNC_SoftwareReset
#define def_FUNC_SoftwareReset
//======================================================================================
void FUNC_SoftwareReset() {  // Restarts program from beginning but does not reset the peripherals and registers
  // digitalWrite(D5_LED_gruen_PIN,LOW);
  // digitalWrite(D4_LED_an_PIN,LOW);
  // asm volatile ("  jmp 0");
  ESP.restart();
}
#endif

//======================================================================================
// void FUNC_PrintVar(char *_VARL_text) { // Prints a given text to serial out
void FUNC_PrintVar(String _VARL_text) { // Prints a given text to serial out
#ifdef LogOn
  Serial.println(_VARL_text);
  //  Serial.print("stat1="); Serial.print(starttime1); Serial.print(" stot1="); Serial.print(stoptime1); Serial.print(" sto-sta1="); Serial.print(stosta1); Serial.print(" sta1sto2="); Serial.println(sta1sto2);
  //  Serial.print("stat2="); Serial.print(starttime2); Serial.print(" stot2="); Serial.print(stoptime2); Serial.print(" sto-sta2="); Serial.print(stosta2); Serial.print(" sta2sto3="); Serial.println(sta2sto3);
  //  Serial.print("stat3="); Serial.print(starttime3); Serial.print(" stot3="); Serial.print(stoptime3); Serial.print(" sto-sta3="); Serial.print(stosta3); Serial.print(" sta3sto4="); Serial.println(sta3sto4);
  //  Serial.print("stat4="); Serial.print(starttime4); Serial.print(" stot4="); Serial.print(stoptime4); Serial.print(" sto-sta4="); Serial.println(stosta4);
#endif
}




