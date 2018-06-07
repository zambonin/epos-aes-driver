// EPOS AES Mediator Common Package

#ifndef __aes_h
#define __aes_h

#include <utility/aes.h>

#ifdef __AES_H
#include __AES_H
#endif

__BEGIN_SYS

template <unsigned int KEY_SIZE> struct AES_Impl {
  typedef typename IF<Traits<Build>::MODEL == Traits<Build>::eMote3,
                      AES_Cortex<KEY_SIZE>, _UTIL::AES<KEY_SIZE>>::Result type;
};

template <unsigned int KEY_SIZE> class AES : public AES_Impl<KEY_SIZE>::type {
public:
  enum Mode {
    ECB,
    CBC,
  };

  AES(const Mode &m = ECB) : AES_Impl<KEY_SIZE>::type(m) {}
};

__END_SYS

#endif
