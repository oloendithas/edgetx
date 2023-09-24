#include "crsf.h"

static CRSF::Servo crsfTrainer;

void crsfTrainerPauseCheck() {
#if !defined(SIMU)
# if defined(AUX_SERIAL) || defined(AUX2_SERIAL)
    if (hasSerialMode(UART_MODE_CRSF_TRAINER) >= 0) {
        crsfTrainer.tick1ms();
        processCrsfInput();    
    }
# endif
#endif    
}

void processCrsfInput() {
#if !defined(SIMU)
  uint8_t rxchar;

  while (sbusAuxGetByte(&rxchar)) {
      crsfTrainer.process(rxchar, [&](){
          crsfTrainer.convert(trainerInput);
          trainerInputValidityTimer = TRAINER_IN_VALID_TIMEOUT;
      });
  }
#endif
}
