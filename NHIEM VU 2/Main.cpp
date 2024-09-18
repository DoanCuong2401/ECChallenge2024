#include <Leanbot.h>                    // use Leanbot library


void setup() {
  Leanbot.begin();                      // initialize Leanbot
}

void Buzzer() {
  Leanbot.tone(1000, 5000);
}

void EmergencySignal() {
  byte LedRandom = BITMAP(ledA, ledF, ledE, ledD, ledC, ledB);
  LbRGB[LedO] = CRGB::Yellow;
  LbRGB.show();
  while(1) {
    LbRGB.fillColor(CRGB::Red, LedRandom);
    LbDelay(1000);
    LbRGB.show();
  }
}

void Out_of_CO2() {
  LbMotion.runLR(100, 100);
  LbMotion.waitDistanceMm(600);
  LbDelay(1000);
  LbMotion.runLR(-50, 50);
  LbMotion.waitRotationDeg(90);
  LbDelay(1000);
  LbMotion.runLR(100, 100);
  LbMotion.waitDistanceMm(900);
}

void Motion() {
  int line = LbIRLine.read();  
  static int count = 0;       

  if (line == 0b1100) {  
    LbMotion.runLR(-50, 50);   
    LbMotion.waitRotationDeg(90);
    LbMotion.runLR(100, 100);  
  } 
  else if (line == 0b0011) {  
    LbMotion.runLR(50, -50);   
    LbMotion.waitRotationDeg(90);
    LbMotion.runLR(100, 100);  
  } 
  else if (line == 0b0011 && line == 0b1100) { 
    if (count == 0) {  
      LbMotion.runLR(-50, 50);
      LbMotion.waitRotationDeg(90);
      LbMotion.runLR(100, 100);
      count++;
    } else { 
      LbMotion.runLR(100, 100);
    }
  } 
  else {  
    LbMotion.runLR(100, 100);
  }
}

void FireZone() {
  int zone = LBIRLine.read();
  if(zone == 0) {
    LbGripper.open();
    Buzzer();
  } else {
    LbGripper.close();
  }
}


