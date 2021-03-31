//By Tsuki Superior
#ifndef __TSOS_RPI3_SOUND_DRIVER__
#define __TSOS_RPI3_SOUND_DRIVER__

#include "generic/sound_driver.hpp"

class RPI3_SOUND_driver : public Sound_driver
{
public:
  RPI3_SOUND_driver(void);
  bool detectsystem(void) final;
  void reset(void) final;
  void playtone(uint32_t tone) final;
  void killsound(void) final;
};

#endif