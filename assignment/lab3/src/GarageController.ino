/*
 * Project GarageController
 * Description:
 * Author:
 * Date:
 */


 #include "GarageHardware.h"

void setup() {
  setupHardware();
}

void loop() {
openFault();
closeFault();
opened();
closed();
timingStart();
timingConfig();
}
