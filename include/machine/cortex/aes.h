// EPOS ARM Cortex AES Mediator Declarations

#ifndef __cortex_aes_h
#define __cortex_aes_h

#include <cpu.h>

__BEGIN_SYS

/*
 * TODO
 * - implement with interruptions
 * - extend key size to 192 and 256 bits
 * - add other modes (CBC-MAC, CCM, CTR, GCM)
 */
class AES_Cortex {
private:
  // AES base address according to the memory map (SWRU319C, pp. 156)
  enum {
    AES_BASE_ADDRESS = 0x4008B000,
  };

  // AES register offsets
  enum {
    AES_DMAC_CH0_CTRL = 0x000,          // Channel 0 control
    AES_DMAC_CH0_EXTADDR = 0x004,       // Channel 0 external address
    AES_DMAC_CH0_DMALENGTH = 0x00C,     // Channel 0 DMA length
    AES_DMAC_STATUS = 0x018,            // DMAC status
    AES_DMAC_SWRES = 0x01C,             // DMAC software reset
    AES_DMAC_CH1_CTRL = 0x020,          // Channel 1 control
    AES_DMAC_CH1_EXTADDR = 0x024,       // Channel 1 external address
    AES_DMAC_CH1_DMALENGTH = 0x02C,     // Channel 1 DMA length
    AES_DMAC_MST_RUNPARAMS = 0x078,     // DMAC master run-time parameters
    AES_DMAC_PERSR = 0x07C,             // DMAC port error raw status
    AES_DMAC_OPTIONS = 0x0F8,           // DMAC options
    AES_DMAC_VERSION = 0x0FC,           // DMAC version
    AES_KEY_STORE_WRITE_AREA = 0x400,   // Key store write area
    AES_KEY_STORE_WRITTEN_AREA = 0x404, // Key store written area
    AES_KEY_STORE_SIZE = 0x408,         // Key store size
    AES_KEY_STORE_READ_AREA = 0x40C,    // Key store read area
    AES_AES_KEY2_0 = 0x500,             // AES_KEY2_0 / AES_GHASH_H_IN_0
    AES_AES_KEY2_1 = 0x504,             // AES_KEY2_1 / AES_GHASH_H_IN_1
    AES_AES_KEY2_2 = 0x508,             // AES_KEY2_2 / AES_GHASH_H_IN_2
    AES_AES_KEY2_3 = 0x50C,             // AES_KEY2_3 / AES_GHASH_H_IN_3
    AES_AES_KEY3_0 = 0x510,             // AES_KEY3_0 / AES_KEY2_4
    AES_AES_KEY3_1 = 0x514,             // AES_KEY3_1 / AES_KEY2_5
    AES_AES_KEY3_2 = 0x518,             // AES_KEY3_2 / AES_KEY2_6
    AES_AES_KEY3_3 = 0x51C,             // AES_KEY3_3 / AES_KEY2_7
    AES_AES_IV_0 = 0x540,               // AES initialization vector
    AES_AES_IV_1 = 0x544,               // AES initialization vector
    AES_AES_IV_2 = 0x548,               // AES initialization vector
    AES_AES_IV_3 = 0x54C,               // AES initialization vector
    AES_AES_CTRL = 0x550,          // AES input/output buffer control and mode
    AES_AES_C_LENGTH_0 = 0x554,    // AES crypto length (LSW)
    AES_AES_C_LENGTH_1 = 0x558,    // AES crypto length (MSW)
    AES_AES_AUTH_LENGTH = 0x55C,   // Authentication length
    AES_AES_DATA_IN_OUT_0 = 0x560, // Data input/output
    AES_AES_DATA_IN_OUT_1 = 0x564, // Data input/output
    AES_AES_DATA_IN_OUT_2 = 0x568, // Data input/output
    AES_AES_DATA_IN_OUT_3 = 0x56C, // Data input/output
    AES_AES_TAG_OUT_0 = 0x570,     // TAG
    AES_AES_TAG_OUT_1 = 0x574,     // TAG
    AES_AES_TAG_OUT_2 = 0x578,     // TAG
    AES_AES_TAG_OUT_3 = 0x57C,     // TAG
    AES_HASH_DATA_IN_0 = 0x600,    // HASH data input
    AES_HASH_DATA_IN_1 = 0x604,    // HASH data input
    AES_HASH_DATA_IN_2 = 0x608,    // HASH data input
    AES_HASH_DATA_IN_3 = 0x60C,    // HASH data input
    AES_HASH_DATA_IN_4 = 0x610,    // HASH data input
    AES_HASH_DATA_IN_5 = 0x614,    // HASH data input
    AES_HASH_DATA_IN_6 = 0x618,    // HASH data input
    AES_HASH_DATA_IN_7 = 0x61C,    // HASH data input
    AES_HASH_DATA_IN_8 = 0x620,    // HASH data input
    AES_HASH_DATA_IN_9 = 0x624,    // HASH data input
    AES_HASH_DATA_IN_10 = 0x628,   // HASH data input
    AES_HASH_DATA_IN_11 = 0x62C,   // HASH data input
    AES_HASH_DATA_IN_12 = 0x630,   // HASH data input
    AES_HASH_DATA_IN_13 = 0x634,   // HASH data input
    AES_HASH_DATA_IN_14 = 0x638,   // HASH data input
    AES_HASH_DATA_IN_15 = 0x63C,   // HASH data input
    AES_HASH_IO_BUF_CTRL = 0x640,  // Input/output buffer control and status
    AES_HASH_MODE_IN = 0x644,      // Hash mode
    AES_HASH_LENGTH_IN_L = 0x648,  // Hash length
    AES_HASH_LENGTH_IN_H = 0x64C,  // Hash length
    AES_HASH_DIGEST_A = 0x650,     // Hash digest
    AES_HASH_DIGEST_B = 0x654,     // Hash digest
    AES_HASH_DIGEST_C = 0x658,     // Hash digest
    AES_HASH_DIGEST_D = 0x65C,     // Hash digest
    AES_HASH_DIGEST_E = 0x660,     // Hash digest
    AES_HASH_DIGEST_F = 0x664,     // Hash digest
    AES_HASH_DIGEST_G = 0x668,     // Hash digest
    AES_HASH_DIGEST_H = 0x66C,     // Hash digest
    AES_CTRL_ALG_SEL = 0x700,      // Algorithm select
    AES_CTRL_PROT_EN = 0x704,      // Master PROT privileged access enable
    AES_CTRL_SW_RESET = 0x740,     // Software reset
    AES_CTRL_INT_CFG = 0x780,      // Interrupt configuration
    AES_CTRL_INT_EN = 0x784,       // Interrupt enable
    AES_CTRL_INT_CLR = 0x788,      // Interrupt clear
    AES_CTRL_INT_SET = 0x78C,      // Interrupt set
    AES_CTRL_INT_STAT = 0x790,     // Interrupt status
    AES_CTRL_OPTIONS = 0x7F8,      // Options
    AES_CTRL_VERSION = 0x7FC,      // Version
  };

  // Bit fields for the AES_DMAC_CH0_CTRL register
  enum {
    AES_DMAC_CH0_CTRL_PRIO = 0x00000002, // Channel priority 0: Low 1: High
    AES_DMAC_CH0_CTRL_EN = 0x00000001,   // Channel enable
  };

  // Bit fields for the AES_DMAC_CH0_DMALENGTH register
  enum {
    AES_DMAC_CH0_DMALENGTH_DMALEN =
        0x0000FFFF, // Channel DMA length in bytes mask
  };

  // Bit fields for the AES_DMAC_STATUS register
  enum {
    AES_DMAC_STATUS_PORT_ERR = 0x00020000, // AHB port transfer errors
    AES_DMAC_STATUS_CH1_ACT =
        0x00000002, // Channel 1 active (DMA transfer on-going)
    AES_DMAC_STATUS_CH0_ACT =
        0x00000001, // Channel 0 active (DMA transfer on-going)
  };

  // Bit fields for the AES_DMAC_SWRES register
  enum {
    AES_DMAC_SWRES_SWRES = 0x00000001, // Software reset enable
  };

  // Bit fields for the AES_DMAC_CH1_CTRL register
  enum {
    AES_DMAC_CH1_CTRL_PRIO = 0x00000002, // Channel priority 0: Low 1: High
    AES_DMAC_CH1_CTRL_EN = 0x00000001,   // Channel enable
  };

  // Bit fields for the AES_DMAC_CH1_DMALENGTH register
  enum {
    AES_DMAC_CH1_DMALENGTH_DMALEN =
        0x0000FFFF, // Channel DMA length in bytes mask
  };

  // Bit fields for the AES_DMAC_MST_RUNPARAMS register
  enum {
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_BURST_SIZE =
        0x0000F000, // Maximum burst size mask
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_IDLE_EN =
        0x00000800, // Idle insertion between bursts
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_INCR_EN =
        0x00000400, // Fixed-length burst or single transfers
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_LOCK_EN = 0x00000200, // Locked transfers
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_BIGEND =
        0x00000100, // Big endian AHB master
  };

  // Bit fields for the AES_DMAC_PERSR register
  enum {
    AES_DMAC_PERSR_PORT1_AHB_ERROR = 0x00001000, // AHB bus error
    AES_DMAC_PERSR_PORT1_CHANNEL = 0x00000200, // Last serviced channel (0 or 1)
  };

  // Bit fields for the AES_DMAC_OPTIONS register
  enum {
    AES_DMAC_OPTIONS_NR_OF_CHANNELS =
        0x00000F00,                            // Number of channels implemented
    AES_DMAC_OPTIONS_NR_OF_PORTS = 0x00000007, // Number of ports implemented
  };

  // Bit fields for the AES_DMAC_VERSION register
  enum {
    AES_DMAC_VERSION_HW_MAJOR_VERSION = 0x0F000000, // Major version number mask
    AES_DMAC_VERSION_HW_MINOR_VERSION = 0x00F00000, // Minor version number mask
    AES_DMAC_VERSION_HW_PATCH_LEVEL = 0x000F0000,   // Patch level mask
    AES_DMAC_VERSION_EIP_NUMBER_COMPL =
        0x0000FF00,                           // EIP_NUMBER 1's complement mask
    AES_DMAC_VERSION_EIP_NUMBER = 0x000000FF, // DMAC EIP-number mask
  };

  // Bit fields for the AES_KEY_STORE_WRITE_AREA register
  enum {
    AES_KEY_STORE_WRITE_AREA_RAM_AREA7 =
        0x00000080, // Select RAM area 7 to be written
    AES_KEY_STORE_WRITE_AREA_RAM_AREA6 =
        0x00000040, // Select RAM area 6 to be written
    AES_KEY_STORE_WRITE_AREA_RAM_AREA5 =
        0x00000020, // Select RAM area 5 to be written
    AES_KEY_STORE_WRITE_AREA_RAM_AREA4 =
        0x00000010, // Select RAM area 4 to be written
    AES_KEY_STORE_WRITE_AREA_RAM_AREA3 =
        0x00000008, // Select RAM area 3 to be written
    AES_KEY_STORE_WRITE_AREA_RAM_AREA2 =
        0x00000004, // Select RAM area 2 to be written
    AES_KEY_STORE_WRITE_AREA_RAM_AREA1 =
        0x00000002, // Select RAM area 1 to be written
    AES_KEY_STORE_WRITE_AREA_RAM_AREA0 =
        0x00000001, // Select RAM area 0 to be written
  };

  // Bit fields for the AES_KEY_STORE_WRITTEN_AREA register
  enum {
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN7 =
        0x00000080, // Reset or check validity of RAM area 7
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN6 =
        0x00000040, // Reset or check validity of RAM area 6
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN5 =
        0x00000020, // Reset or check validity of RAM area 5
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN4 =
        0x00000010, // Reset or check validity of RAM area 4
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN3 =
        0x00000008, // Reset or check validity of RAM area 3
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN2 =
        0x00000004, // Reset or check validity of RAM area 2
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN1 =
        0x00000002, // Reset or check validity of RAM area 1
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN0 =
        0x00000001, // Reset or check validity of RAM area 0
  };

  // Bit fields for the AES_KEY_STORE_SIZE register
  enum {
    AES_KEY_STORE_SIZE_KEY_SIZE = 0x00000003, // Define key size
  };

  // Bit fields for the AES_KEY_STORE_READ_AREA register
  enum {
    AES_KEY_STORE_READ_AREA_BUSY = 0x80000000,     // Key store operation busy
    AES_KEY_STORE_READ_AREA_RAM_AREA = 0x0000000F, // Key store RAM area select
  };

  // Bit fields for the AES_AES_CTRL register
  enum {
    AES_AES_CTRL_CONTEXT_READY =
        0x80000000, // Context data registers can be overwritten
    AES_AES_CTRL_SAVED_CONTEXT_READY =
        0x40000000, // AES auth. TAG and/or IV block(s) available
    AES_AES_CTRL_SAVE_CONTEXT =
        0x20000000, // Auth. TAG or result IV needs to be stored
    AES_AES_CTRL_CCM_M = 0x01C00000,        // CCM auth. field length
    AES_AES_CTRL_CCM_L = 0x00380000,        // CCM length field width
    AES_AES_CTRL_CCM = 0x00040000,          // AES-CCM mode
    AES_AES_CTRL_GCM = 0x00030000,          // AES-GCM mode
    AES_AES_CTRL_CBC_MAC = 0x00008000,      // AES-CBC MAC mode
    AES_AES_CTRL_CTR_WIDTH = 0x00000180,    // CTR counter width mask
    AES_AES_CTRL_CTR = 0x00000040,          // AES-CTR mode
    AES_AES_CTRL_CBC = 0x00000020,          // AES-CBC mode
    AES_AES_CTRL_KEY_SIZE = 0x00000018,     // Key size
    AES_AES_CTRL_DIRECTION = 0x00000004,    // Encrypt
    AES_AES_CTRL_INPUT_READY = 0x00000002,  // AES input buffer empty
    AES_AES_CTRL_OUTPUT_READY = 0x00000001, // AES output block available
  };

  // Bit fields for the AES_HASH_IO_BUF_CTRL register
  enum {
    AES_HASH_IO_BUF_CTRL_PAD_DMA_MESSAGE =
        0x0000007f, // Hash engine message padding required
    AES_HASH_IO_BUF_CTRL_GET_DIGEST =
        0x00000040, // Hash engine digest requested
    AES_HASH_IO_BUF_CTRL_PAD_MESSAGE =
        0x00000020, // Last message data in HASH_DATA_IN, apply hash padding
    AES_HASH_IO_BUF_CTRL_RFD_IN =
        0x00000004, // Hash engine input buffer can accept new data
    AES_HASH_IO_BUF_CTRL_DATA_IN_AV =
        0x00000002, // Start processing HASH_DATA_IN data
    AES_HASH_IO_BUF_CTRL_OUTPUT_FULL =
        0x00000001, // Output buffer registers available
  };

  // Bit fields for the AES_HASH_MODE_IN register
  enum {
    AES_HASH_MODE_IN_SHA256_MODE = 0x00000008, // Hash mode
    AES_HASH_MODE_IN_NEW_HASH = 0x00000001,    // New hash session
  };

  // Bit fields for the AES_CTRL_ALG_SEL register
  enum {
    AES_CTRL_ALG_SEL_TAG = 0x80000000,  // DMA operation includes TAG
    AES_CTRL_ALG_SEL_HASH = 0x00000004, // Select hash engine as DMA destination
    AES_CTRL_ALG_SEL_AES =
        0x00000002, // Select AES engine as DMA source/destination
    AES_CTRL_ALG_SEL_KEYSTORE =
        0x00000001, // Select key store as DMA destination
  };

  // Bit fields for the AES_CTRL_PROT_EN register
  enum {
    AES_CTRL_PROT_EN_PROT_EN =
        0x00000001, // m_h_prot[1] asserted for DMA reads towards key store
  };

  // Bit fields for the AES_CTRL_SW_RESET register
  enum {
    AES_CTRL_SW_RESET_SW_RESET =
        0x00000001, // Reset master control and key store
  };

  // Bit fields for the AES_CTRL_INT_CFG register
  enum {
    AES_CTRL_INT_CFG_LEVEL = 0x00000001, // Level interrupt type
  };

  // Bit fields for the AES_CTRL_INT_EN register
  enum {
    AES_CTRL_INT_EN_DMA_IN_DONE =
        0x00000002, // DMA input done interrupt enabled
    AES_CTRL_INT_EN_RESULT_AV =
        0x00000001, // Result available interrupt enabled
  };

  // Bit fields for the AES_CTRL_INT_CLR register
  enum {
    AES_CTRL_INT_CLR_DMA_BUS_ERR = 0x80000000, // Clear DMA bus error status
    AES_CTRL_INT_CLR_KEY_ST_WR_ERR =
        0x40000000, // Clear key store write error status
    AES_CTRL_INT_CLR_KEY_ST_RD_ERR =
        0x20000000, // Clear key store read error status
    AES_CTRL_INT_CLR_DMA_IN_DONE = 0x00000002, // Clear DMA in done interrupt
    AES_CTRL_INT_CLR_RESULT_AV = 0x00000001, // Clear result available interrupt
  };

  // Bit fields for the AES_CTRL_INT_SET register
  enum {
    AES_CTRL_INT_SET_DMA_IN_DONE = 0x00000002, // Set DMA data in done interrupt
    AES_CTRL_INT_SET_RESULT_AV = 0x00000001,   // Set result available interrupt
  };

  // Bit fields for the AES_CTRL_INT_STAT register
  enum {
    AES_CTRL_INT_STAT_DMA_BUS_ERR = 0x80000000,   // DMA bus error detected
    AES_CTRL_INT_STAT_KEY_ST_WR_ERR = 0x40000000, // Write error detected
    AES_CTRL_INT_STAT_KEY_ST_RD_ERR = 0x20000000, // Read error detected
    AES_CTRL_INT_STAT_DMA_IN_DONE =
        0x00000002, // DMA data in done interrupt status
    AES_CTRL_INT_STAT_RESULT_AV =
        0x00000001, // Result available interrupt status
  };

  // Bit fields for the AES_CTRL_OPTIONS register
  enum {
    AES_CTRL_OPTIONS_TYPE = 0xFF000000,         // Device type mask
    AES_CTRL_OPTIONS_AHBINTERFACE = 0x00010000, // AHB interface available
    AES_CTRL_OPTIONS_SHA_256 = 0x00000100, // The HASH core supports SHA-256
    AES_CTRL_OPTIONS_AES_CCM =
        0x00000080, // AES-CCM available as single operation
    AES_CTRL_OPTIONS_AES_GCM =
        0x00000040, // AES-GCM available as single operation
    AES_CTRL_OPTIONS_AES_256 = 0x00000020,  // AES core supports 256-bit keys
    AES_CTRL_OPTIONS_AES_128 = 0x00000010,  // AES core supports 128-bit keys
    AES_CTRL_OPTIONS_HASH = 0x00000004,     // HASH Core available
    AES_CTRL_OPTIONS_AES = 0x00000002,      // AES core available
    AES_CTRL_OPTIONS_KEYSTORE = 0x00000001, // Key store available
  };

  // Bit fields for the AES_CTRL_VERSION register
  enum {
    AES_CTRL_VERSION_MAJOR_VERSION = 0x0F000000, // Major version number mask
    AES_CTRL_VERSION_MINOR_VERSION = 0x00F00000, // Minor version number mask
    AES_CTRL_VERSION_PATCH_LEVEL = 0x000F0000,   // Patch level mask
    AES_CTRL_VERSION_EIP_NUMBER_COMPL =
        0x0000FF00,                           // EIP_NUMBER 1's complement mask
    AES_CTRL_VERSION_EIP_NUMBER = 0x000000FF, // EIP-120t EIP-number mask
  };

  // AES and SHA256 module return codes
  enum {
    AES_SUCCESS = 0,
    SHA256_SUCCESS = 0,
    AES_KEYSTORE_READ_ERROR = 1,
    AES_KEYSTORE_WRITE_ERROR = 2,
    AES_DMA_BUS_ERROR = 3,
    CCM_AUTHENTICATION_FAILED = 4,
    SHA2_ERROR = 5,
    SHA256_INVALID_PARAM = 6,
    SHA256_TEST_ERROR = 7,
    AES_ECB_TEST_ERROR = 8,
    AES_NULL_ERROR = 9,
    SHA256_NULL_ERROR = 9,
    AES_CCM_TEST_ERROR = 10,
  };

  // Various size constants
  enum {
    KEY_SIZE_BYTES = 0x10,
    KEY_STORE_SIZE_BITS = 0x03,
    KEY_STORE_SIZE_RES = 0x00,
    KEY_STORE_SIZE_128 = 0x01,
    KEY_STORE_SIZE_192 = 0x02,
    KEY_STORE_SIZE_256 = 0x03,
  };

  // Key store valid key locations. For key sizes of 192 and 256 bits,
  // only areas 0, 2, 4 and 6 are valid.
  enum {
    KEY_AREA_0,
    KEY_AREA_1,
    KEY_AREA_2,
    KEY_AREA_3,
    KEY_AREA_4,
    KEY_AREA_5,
    KEY_AREA_6,
    KEY_AREA_7,
  };

public:
  enum Mode {
    ECB,
    CBC = AES_AES_CTRL_CBC,
  };

private:
  typedef CPU::Reg32 Reg32;

  static volatile Reg32 &aes_reg(unsigned int offset) {
    return *(reinterpret_cast<volatile Reg32 *>(AES_BASE_ADDRESS + offset));
  }

  // second parameter must be one of KEY_AREA_n values
  unsigned char aes_load_keys(const unsigned char *key,
                              unsigned char key_location);

  // configure mode according to AES_AES_CTRL register
  // note that the message length is bound by AES_DMAC_CHx_DMALENGTH[15:0]
  unsigned char aes_start(const unsigned char *in, unsigned char *out,
                          const unsigned short msg_len, const unsigned char *iv,
                          unsigned char key_location, unsigned char mode);

  // if result is available or error occurs returns true, else returns false
  unsigned char aes_check_result();

  // this must be called strictly after aes_start
  unsigned char aes_get_result();

  // wrapper method for the above routines, debug these return codes if needed
  unsigned char crypt(const unsigned char *key, const unsigned char *in,
                      unsigned char *out, const unsigned short msg_len,
                      const unsigned char *iv, unsigned char loc,
                      unsigned char direction) {
    unsigned char code = aes_load_keys(key, loc);
    code |= aes_start(in, out, msg_len, iv, loc, _mode | direction);

    while (!(aes_check_result()))
      ;
    code |= aes_get_result();

    return code;
  }

  Mode _mode;

public:
  AES(const Mode &m = ECB) : _mode(m) { assert((m == ECB) || (m == CBC)); }

  Mode mode() { return _mode; }

  // ECB is automatically selected if AES_AES_CTRL[28:5] are all zeroes
  // one needs only to enable the direction bit (AES_AES_CTRL[2])
  void encrypt(const unsigned char *in, const unsigned char *key,
               unsigned char *out, const unsigned char *iv = 0,
               const unsigned short msg_len = 16,
               unsigned char key_location = KEY_AREA_0) {
    crypt(key, in, out, msg_len, iv, key_location, AES_AES_CTRL_DIRECTION);
  }

  void decrypt(const unsigned char *in, const unsigned char *key,
               unsigned char *out, const unsigned char *iv = 0,
               const unsigned short msg_len = 16,
               unsigned char key_location = KEY_AREA_0) {
    crypt(key, in, out, msg_len, iv, key_location, 0);
  }
};

template <unsigned int KEY_SIZE>
unsigned char AES<KEY_SIZE>::aes_load_keys(const unsigned char *key,
                                           unsigned char key_location) {
  static unsigned int aligned_key[4];
  unsigned char i, *key_ptr = (unsigned char *)aligned_key;

  // key address needs to be 4 byte aligned
  for (i = 0; i < KEY_SIZE_BYTES; ++i) {
    key_ptr[i] = key[i];
  }

  // workaround for AES registers not retained after PM2
  aes_reg(AES_CTRL_INT_CFG) = AES_CTRL_INT_CFG_LEVEL;
  aes_reg(AES_CTRL_INT_EN) =
      (AES_CTRL_INT_EN_DMA_IN_DONE | AES_CTRL_INT_EN_RESULT_AV);

  // configure master control module
  // enable the DMA path to the key store
  aes_reg(AES_CTRL_ALG_SEL) = AES_CTRL_ALG_SEL_KEYSTORE;

  // clear any outstanding events
  aes_reg(AES_CTRL_INT_CLR) |=
      (AES_CTRL_INT_CLR_DMA_IN_DONE | AES_CTRL_INT_CLR_RESULT_AV);

  // configure key store module (areas, size)
  // writing to this register resets AES_KEY_STORE_WRITTEN_AREA
  aes_reg(AES_KEY_STORE_SIZE) = KEY_STORE_SIZE_128;

  // enable key areas to write
  aes_reg(AES_KEY_STORE_WRITE_AREA) = (0x00000001 << key_location);

  // configure DMAC
  // enable DMA channel 0
  aes_reg(AES_DMAC_CH0_CTRL) |= 0x000000001;

  // base address of the key in external memory
  aes_reg(AES_DMAC_CH0_EXTADDR) = (unsigned int)key_ptr;

  // total key length in bytes
  // writing to this register starts the transfer if the channel is enabled
  aes_reg(AES_DMAC_CH0_DMALENGTH) = KEY_SIZE_BYTES;

  // wait for operation to complete
  while (!(aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_RESULT_AV))
    ;

  // check for absence of errors
  if ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_DMA_BUS_ERR)) {
    // error on the AHB master interface during a DMA operation
    aes_reg(AES_CTRL_INT_CLR) |= AES_CTRL_INT_CLR_DMA_BUS_ERR;
    aes_reg(AES_CTRL_ALG_SEL) = 0x00000000;
    return AES_DMA_BUS_ERROR;
  }

  if ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_WR_ERR)) {
    // DMA operation does not cover a full area
    // or more areas are written than expected
    aes_reg(AES_CTRL_INT_CLR) |= AES_CTRL_INT_CLR_KEY_ST_WR_ERR;
    aes_reg(AES_CTRL_ALG_SEL) = 0x00000000;
    return AES_KEYSTORE_WRITE_ERROR;
  }

  // acknowledge the interrupt
  aes_reg(AES_CTRL_INT_CLR) |=
      (AES_CTRL_INT_CLR_DMA_IN_DONE | AES_CTRL_INT_CLR_RESULT_AV);

  // disable master control / DMA clock
  aes_reg(AES_CTRL_ALG_SEL) = 0x00000000;

  // check status, if error return error code
  if ((aes_reg(AES_KEY_STORE_WRITTEN_AREA) & 0x7) != 0x1) {
    return AES_KEYSTORE_WRITE_ERROR;
  }

  for (i = 0; i < KEY_SIZE_BYTES; ++i) {
    key_ptr[i] = 0;
  }

  return AES_SUCCESS;
}

template <unsigned int KEY_SIZE>
unsigned char
AES<KEY_SIZE>::aes_start(const unsigned char *in, unsigned char *out,
                         const unsigned short msg_len, const unsigned char *iv,
                         unsigned char key_location, unsigned char mode) {
  // workaround for AES registers not retained after PM2
  aes_reg(AES_CTRL_INT_CFG) = AES_CTRL_INT_CFG_LEVEL;
  aes_reg(AES_CTRL_INT_EN) =
      (AES_CTRL_INT_EN_DMA_IN_DONE | AES_CTRL_INT_EN_RESULT_AV);

  // configure the master control module
  // enable the DMA path to the AES engine
  aes_reg(AES_CTRL_ALG_SEL) = AES_CTRL_ALG_SEL_AES;

  // clear any outstanding events
  aes_reg(AES_CTRL_INT_CLR) |=
      (AES_CTRL_INT_CLR_DMA_IN_DONE | AES_CTRL_INT_CLR_RESULT_AV);

  aes_reg(AES_KEY_STORE_READ_AREA) = key_location;

  // wait until key is loaded to the AES module
  while (aes_reg(AES_KEY_STORE_READ_AREA) & AES_KEY_STORE_READ_AREA_BUSY)
    ;

  // check for key store read error
  if ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_RD_ERR)) {
    // key location selected on the key store is not available
    aes_reg(AES_CTRL_INT_CLR) |= AES_CTRL_INT_CLR_KEY_ST_RD_ERR;
    return AES_KEYSTORE_READ_ERROR;
  }

  // write initialization vector
  if (iv != 0) {
    aes_reg(AES_AES_IV_0) = ((const unsigned int *)iv)[0];
    aes_reg(AES_AES_IV_1) = ((const unsigned int *)iv)[1];
    aes_reg(AES_AES_IV_2) = ((const unsigned int *)iv)[2];
    aes_reg(AES_AES_IV_3) = ((const unsigned int *)iv)[3];
  }

  // program mode of operation
  aes_reg(AES_AES_CTRL) = mode;

  // write length of the message (lo)
  aes_reg(AES_AES_C_LENGTH_0) = msg_len;

  // write length of the message (hi)
  aes_reg(AES_AES_C_LENGTH_1) = 0;

  if (msg_len != 0) {
    // enable DMA channel 0
    aes_reg(AES_DMAC_CH0_CTRL) = AES_DMAC_CH0_CTRL_EN;

    // base address of the input data in external memory
    aes_reg(AES_DMAC_CH0_EXTADDR) = (unsigned int)in;

    // input data length in bytes, equal to the message
    // writing to this register starts the transfer if the channel is enabled
    aes_reg(AES_DMAC_CH0_DMALENGTH) = msg_len;

    // enable DMA channel 1
    aes_reg(AES_DMAC_CH1_CTRL) = AES_DMAC_CH1_CTRL_EN;

    // base address of the output data buffer
    aes_reg(AES_DMAC_CH1_EXTADDR) = (unsigned int)out;

    // output data length in bytes, equal to the result
    // writing to this register starts the transfer if the channel is enabled
    aes_reg(AES_DMAC_CH1_DMALENGTH) = msg_len;
  }

  return AES_SUCCESS;
}

template <unsigned int KEY_SIZE>
unsigned char AES<KEY_SIZE>::aes_check_result() {
  return ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_RESULT_AV) ||
          (aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_DMA_BUS_ERR) ||
          (aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_WR_ERR) ||
          (aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_RD_ERR));
}

template <unsigned int KEY_SIZE> unsigned char AES<KEY_SIZE>::aes_get_result() {
  unsigned char errors = aes_reg(AES_CTRL_INT_STAT);

  // clear errors
  aes_reg(AES_CTRL_INT_CLR) =
      (AES_CTRL_INT_CLR_DMA_BUS_ERR | AES_CTRL_INT_CLR_KEY_ST_WR_ERR |
       AES_CTRL_INT_CLR_KEY_ST_RD_ERR);

  // disable master control/DMA clock
  aes_reg(AES_CTRL_ALG_SEL) = 0x00000000;

  // check for absence of errors
  if (errors & AES_CTRL_INT_STAT_DMA_BUS_ERR) {
    return AES_DMA_BUS_ERROR;
  }

  if (errors & AES_CTRL_INT_STAT_KEY_ST_WR_ERR) {
    return AES_KEYSTORE_WRITE_ERROR;
  }

  if (errors & AES_CTRL_INT_STAT_KEY_ST_RD_ERR) {
    return AES_KEYSTORE_READ_ERROR;
  }

  // acknowledge the interrupt
  aes_reg(AES_CTRL_INT_CLR) |=
      (AES_CTRL_INT_CLR_DMA_IN_DONE | AES_CTRL_INT_CLR_RESULT_AV);

  return AES_SUCCESS;
}

__END_SYS

#endif
