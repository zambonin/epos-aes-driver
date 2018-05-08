// EPOS AES Mediator Common Package

#ifndef __aes_h
#define __aes_h

#include <utility/aes.h>

#ifdef __AES_H
#include __AES_H
#endif

__BEGIN_SYS

template <unsigned int KEY_SIZE> class AES : public AES_Util<KEY_SIZE> {
public:
  enum Mode {
    ECB,
    CBC,
  };

  AES(const Mode &m = ECB) : AES_Util<KEY_SIZE>(m) {}
};

__END_SYS

#endif
