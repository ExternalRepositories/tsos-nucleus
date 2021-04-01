// By Tsuki Superior
#include "generic/elf.hpp"

ELF_quark::ELF_quark(void)
{
  name = "Executable and Linkable Format";
}

bool ELF_quark::detectsystem(void)
{
  return isvalidexecutable("/nucleus");
}

void ELF_quark::reset(void)
{
}

bool ELF_quark::isvalidexecutable(char *path)
{
  return true;
}

// This needs to give back the address to the first free memory location in the os, that can be used for a primitive heap
uintptr_t ELF_quark::getstartoffreemem(void)
{

#ifdef __PERSONAL_COMPUTER__
  extern uintptr_t _kernelend;
  return _kernelend;
#endif

#ifdef __GAMEBOY_ADVANCED__
  return 0x03000000;
#endif

#ifdef __NSPIRE__
  extern uintptr_t _kernelend;
  return _kernelend;
#endif

#ifdef __RASPBERRY_PI_3__
  extern uintptr_t _kernelend;
  return _kernelend;
#endif

#ifdef __NINTENDO_DUAL_SCREEN__

#endif
  return 0;
}
