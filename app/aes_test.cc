#include "aes.h"
#include "utility/aes/sys_ctrl.h"
#include "utility/ostream.h"

using namespace EPOS;

OStream cout;

/*****************************************************************************/
/*   This example shows how to run AES ECB with polling on EPOSMote III.     */
/*   It uses no peripherals, no I/O signals, and no interrupt handlers.      */
/*****************************************************************************/

typedef struct {
  unsigned char ui8AESKey[16], ui8AESKeyLocation, ui8AESBuf[16],
      ui8AESExpectedOutput[16];
} tAESExample;

bool AESMemCmp(const unsigned char *pui8Src1, const unsigned char *pui8Src2,
               unsigned int ui32Len) {
  const unsigned char *pui8Src1Temp = pui8Src1;
  const unsigned char *pui8Src2Temp = pui8Src2;

  bool valid = true;
  while (ui32Len--) {
    valid &= *pui8Src1Temp++ == *pui8Src2Temp++;
  }
  return valid;
}

// unsigned char AesEcbExample(unsigned char *pui8Key,
//                             unsigned char ui8KeyLocation,
//                             unsigned char *pui8Buf,
//                             unsigned char *pui8ExpectedOutput) {
//   AESLoadKey((unsigned char *)pui8Key, ui8KeyLocation);
//   AESECBStart(pui8Buf, pui8Buf, ui8KeyLocation, true);
//
//   do {
//     ASM_NOP;
//   } while (!(AESECBCheckResult()));
//
//   AESECBGetResult();
//
//   if (AESMemCmp(pui8Buf, pui8ExpectedOutput, 16) == false) {
//     return AES_ECB_TEST_ERROR;
//   }
//
//   return (AES_SUCCESS);
// }

int main(void) {
  unsigned char ui8Status, i;

  // Set the clocking to run directly from the external crystal/oscillator.
  // (no ext 32k osc, no internal osc)
  // SysCtrlClockSet(false, false, SYS_CTRL_SYSDIV_32MHZ);

  // Set IO clock to the same as system clock
  // SysCtrlIOClockSet(SYS_CTRL_SYSDIV_32MHZ);

  // Enable AES peripheral
  SysCtrlPeripheralReset(SYS_CTRL_PERIPH_AES);
  SysCtrlPeripheralEnable(SYS_CTRL_PERIPH_AES);

  tAESExample sAESexample[] = {
      {
          {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
           0x00, 0x00, 0x00, 0x00, 0x00},
          0,
          {0x6c, 0x5f, 0x51, 0x74, 0x53, 0x53, 0x77, 0x5a, 0x5a, 0x5f, 0x57,
           0x58, 0x55, 0x53, 0x06, 0x0f},
          {0x83, 0x78, 0x10, 0x60, 0x0e, 0x13, 0x93, 0x9b, 0x27, 0xe0, 0xd7,
           0xe4, 0x58, 0xf0, 0xa9, 0xd1},
      },
//      {
//          {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//           0x00, 0x00, 0x00, 0x00, 0x00},
//          1,
//          {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
//           0xff, 0xff, 0xff, 0xff, 0xff},
//          {0x3f, 0x5b, 0x8c, 0xc9, 0xea, 0x85, 0x5a, 0x0a, 0xfa, 0x73, 0x47,
//           0xd2, 0x3e, 0x8d, 0x66, 0x4e},
//      },
  };

  AES<16> a{};
  unsigned char msg[16] = {0x00};
  for (i = 0; i < sizeof(sAESexample) / sizeof(sAESexample[0]); i++) {
    a.encrypt(sAESexample[i].ui8AESBuf, sAESexample[i].ui8AESKey, msg);
if (AESMemCmp(sAESexample[i].ui8AESExpectedOutput, msg, 16) == false) {
  cout << "is it the globals again?" << endl;
   }
  }

  return 0;
}
