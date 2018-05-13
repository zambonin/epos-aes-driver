// EPOS ARM Cortex AES Mediator Declarations

#ifndef __cortex_aes_h
#define __cortex_aes_h

#include <aes.h>
#include <system/config.h>

#ifndef __mmod_emote3__

__BEGIN_SYS

template <unsigned int KEY_SIZE>
class AES : public AES_Common::AES<KEY_SIZE> {};

__END_SYS

#else

#include <cpu.h>

__BEGIN_SYS

template <unsigned int KEY_SIZE> class AES : public AES_Common::AES<KEY_SIZE> {
public:
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
    AES_DMAC_CH0_CTRL_PRIO = 0x00000002,
    AES_DMAC_CH0_CTRL_PRIO_M = 0x00000002,
    AES_DMAC_CH0_CTRL_PRIO_S = 1,
    AES_DMAC_CH0_CTRL_EN = 0x00000001,
    AES_DMAC_CH0_CTRL_EN_M = 0x00000001,
    AES_DMAC_CH0_CTRL_EN_S = 0,
  };

  // Bit fields for the AES_DMAC_CH0_EXTADDR register
  enum {
    AES_DMAC_CH0_EXTADDR_ADDR_M = 0xFFFFFFFF,
    AES_DMAC_CH0_EXTADDR_ADDR_S = 0,
  };

  // Bit fields for the AES_DMAC_CH0_DMALENGTH register
  enum {
    AES_DMAC_CH0_DMALENGTH_DMALEN_M = 0x0000FFFF,
    AES_DMAC_CH0_DMALENGTH_DMALEN_S = 0,
  };

  // Bit fields for the AES_DMAC_STATUS register
  enum {
    AES_DMAC_STATUS_PORT_ERR = 0x00020000,
    AES_DMAC_STATUS_PORT_ERR_M = 0x00020000,
    AES_DMAC_STATUS_PORT_ERR_S = 17,
    AES_DMAC_STATUS_CH1_ACT = 0x00000002,
    AES_DMAC_STATUS_CH1_ACT_M = 0x00000002,
    AES_DMAC_STATUS_CH1_ACT_S = 1,
    AES_DMAC_STATUS_CH0_ACT = 0x00000001,
    AES_DMAC_STATUS_CH0_ACT_M = 0x00000001,
    AES_DMAC_STATUS_CH0_ACT_S = 0,
  };

  // Bit fields for the AES_DMAC_SWRES register
  enum {
    AES_DMAC_SWRES_SWRES = 0x00000001,
    AES_DMAC_SWRES_SWRES_M = 0x00000001,
    AES_DMAC_SWRES_SWRES_S = 0,
  };

  // Bit fields for the AES_DMAC_CH1_CTRL register
  enum {
    AES_DMAC_CH1_CTRL_PRIO = 0x00000002,
    AES_DMAC_CH1_CTRL_PRIO_M = 0x00000002,
    AES_DMAC_CH1_CTRL_PRIO_S = 1,
    AES_DMAC_CH1_CTRL_EN = 0x00000001,
    AES_DMAC_CH1_CTRL_EN_M = 0x00000001,
    AES_DMAC_CH1_CTRL_EN_S = 0,
  };

  // Bit fields for the AES_DMAC_CH1_EXTADDR register
  enum {
    AES_DMAC_CH1_EXTADDR_ADDR_M = 0xFFFFFFFF,
    AES_DMAC_CH1_EXTADDR_ADDR_S = 0,
  };

  // Bit fields for the AES_DMAC_CH1_DMALENGTH register
  enum {
    AES_DMAC_CH1_DMALENGTH_DMALEN_M = 0x0000FFFF,
    AES_DMAC_CH1_DMALENGTH_DMALEN_S = 0,
  };

  // Bit fields for the AES_DMAC_MST_RUNPARAMS register
  enum {
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_BURST_SIZE_M = 0x0000F000,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_BURST_SIZE_S = 12,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_IDLE_EN = 0x00000800,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_IDLE_EN_M = 0x00000800,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_IDLE_EN_S = 11,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_INCR_EN = 0x00000400,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_INCR_EN_M = 0x00000400,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_INCR_EN_S = 10,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_LOCK_EN = 0x00000200,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_LOCK_EN_M = 0x00000200,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_LOCK_EN_S = 9,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_BIGEND = 0x00000100,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_BIGEND_M = 0x00000100,
    AES_DMAC_MST_RUNPARAMS_AHB_MST1_BIGEND_S = 8,
  };

  // Bit fields for the AES_DMAC_PERSR register
  enum {
    AES_DMAC_PERSR_PORT1_AHB_ERROR = 0x00001000,
    AES_DMAC_PERSR_PORT1_AHB_ERROR_M = 0x00001000,
    AES_DMAC_PERSR_PORT1_AHB_ERROR_S = 12,
    AES_DMAC_PERSR_PORT1_CHANNEL = 0x00000200,
    AES_DMAC_PERSR_PORT1_CHANNEL_M = 0x00000200,
    AES_DMAC_PERSR_PORT1_CHANNEL_S = 9,
  };

  // Bit fields for the AES_DMAC_OPTIONS register
  enum {
    AES_DMAC_OPTIONS_NR_OF_CHANNELS_M = 0x00000F00,
    AES_DMAC_OPTIONS_NR_OF_CHANNELS_S = 8,
    AES_DMAC_OPTIONS_NR_OF_PORTS_M = 0x00000007,
    AES_DMAC_OPTIONS_NR_OF_PORTS_S = 0,
  };

  // Bit fields for the AES_DMAC_VERSION register
  enum {
    AES_DMAC_VERSION_HW_MAJOR_VERSION_M = 0x0F000000,
    AES_DMAC_VERSION_HW_MAJOR_VERSION_S = 24,
    AES_DMAC_VERSION_HW_MINOR_VERSION_M = 0x00F00000,
    AES_DMAC_VERSION_HW_MINOR_VERSION_S = 20,
    AES_DMAC_VERSION_HW_PATCH_LEVEL_M = 0x000F0000,
    AES_DMAC_VERSION_HW_PATCH_LEVEL_S = 16,
    AES_DMAC_VERSION_EIP_NUMBER_COMPL_M = 0x0000FF00,
    AES_DMAC_VERSION_EIP_NUMBER_COMPL_S = 8,
    AES_DMAC_VERSION_EIP_NUMBER_M = 0x000000FF,
    AES_DMAC_VERSION_EIP_NUMBER_S = 0,
  };

  // Bit fields for the AES_KEY_STORE_WRITE_AREA register
  enum {
    AES_KEY_STORE_WRITE_AREA_RAM_AREA7 = 0x00000080,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA7_M = 0x00000080,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA7_S = 7,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA6 = 0x00000040,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA6_M = 0x00000040,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA6_S = 6,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA5 = 0x00000020,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA5_M = 0x00000020,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA5_S = 5,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA4 = 0x00000010,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA4_M = 0x00000010,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA4_S = 4,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA3 = 0x00000008,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA3_M = 0x00000008,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA3_S = 3,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA2 = 0x00000004,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA2_M = 0x00000004,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA2_S = 2,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA1 = 0x00000002,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA1_M = 0x00000002,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA1_S = 1,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA0 = 0x00000001,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA0_M = 0x00000001,
    AES_KEY_STORE_WRITE_AREA_RAM_AREA0_S = 0,
  };

  // Bit fields for the AES_KEY_STORE_WRITTEN_AREA register
  enum {
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN7 = 0x00000080,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN7_M = 0x00000080,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN7_S = 7,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN6 = 0x00000040,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN6_M = 0x00000040,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN6_S = 6,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN5 = 0x00000020,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN5_M = 0x00000020,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN5_S = 5,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN4 = 0x00000010,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN4_M = 0x00000010,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN4_S = 4,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN3 = 0x00000008,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN3_M = 0x00000008,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN3_S = 3,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN2 = 0x00000004,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN2_M = 0x00000004,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN2_S = 2,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN1 = 0x00000002,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN1_M = 0x00000002,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN1_S = 1,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN0 = 0x00000001,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN0_M = 0x00000001,
    AES_KEY_STORE_WRITTEN_AREA_RAM_AREA_WRITTEN0_S = 0,
  };

  // Bit fields for the AES_KEY_STORE_SIZE register
  enum {
    AES_KEY_STORE_SIZE_KEY_SIZE_M = 0x00000003,
    AES_KEY_STORE_SIZE_KEY_SIZE_S = 0,
  };

  // Bit fields for the AES_KEY_STORE_READ_AREA register
  enum {
    AES_KEY_STORE_READ_AREA_BUSY = 0x80000000,
    AES_KEY_STORE_READ_AREA_BUSY_M = 0x80000000,
    AES_KEY_STORE_READ_AREA_BUSY_S = 31,
    AES_KEY_STORE_READ_AREA_RAM_AREA_M = 0x0000000F,
    AES_KEY_STORE_READ_AREA_RAM_AREA_S = 0,
  };

  // Bit fields for the AES_AES_KEY2_0 register
  enum {
    AES_AES_KEY2_0_AES_KEY2_M = 0xFFFFFFFF,
    AES_AES_KEY2_0_AES_KEY2_S = 0,
  };

  // Bit fields for the AES_AES_KEY2_1 register
  enum {
    AES_AES_KEY2_1_AES_KEY2_M = 0xFFFFFFFF,
    AES_AES_KEY2_1_AES_KEY2_S = 0,
  };

  // Bit fields for the AES_AES_KEY2_2 register
  enum {
    AES_AES_KEY2_2_AES_KEY2_M = 0xFFFFFFFF,
    AES_AES_KEY2_2_AES_KEY2_S = 0,
  };

  // Bit fields for the AES_AES_KEY2_3 register
  enum {
    AES_AES_KEY2_3_AES_KEY2_M = 0xFFFFFFFF,
    AES_AES_KEY2_3_AES_KEY2_S = 0,
  };

  // Bit fields for the AES_AES_KEY3_0 register
  enum {
    AES_AES_KEY3_0_AES_KEY2_M = 0xFFFFFFFF,
    AES_AES_KEY3_0_AES_KEY2_S = 0,
  };

  // Bit fields for the AES_AES_KEY3_1 register
  enum {
    AES_AES_KEY3_1_AES_KEY2_M = 0xFFFFFFFF,
    AES_AES_KEY3_1_AES_KEY2_S = 0,
  };

  // Bit fields for the AES_AES_KEY3_2 register
  enum {
    AES_AES_KEY3_2_AES_KEY2_M = 0xFFFFFFFF,
    AES_AES_KEY3_2_AES_KEY2_S = 0,
  };

  // Bit fields for the AES_AES_KEY3_3 register
  enum {
    AES_AES_KEY3_3_AES_KEY2_M = 0xFFFFFFFF,
    AES_AES_KEY3_3_AES_KEY2_S = 0,
  };

  // Bit fields for the AES_AES_IV_0 register
  enum {
    AES_AES_IV_0_AES_IV_M = 0xFFFFFFFF,
    AES_AES_IV_0_AES_IV_S = 0,
  };

  // Bit fields for the AES_AES_IV_1 register
  enum {
    AES_AES_IV_1_AES_IV_M = 0xFFFFFFFF,
    AES_AES_IV_1_AES_IV_S = 0,
  };

  // Bit fields for the AES_AES_IV_2 register
  enum {
    AES_AES_IV_2_AES_IV_M = 0xFFFFFFFF,
    AES_AES_IV_2_AES_IV_S = 0,
  };

  // Bit fields for the AES_AES_IV_3 register
  enum {
    AES_AES_IV_3_AES_IV_M = 0xFFFFFFFF,
    AES_AES_IV_3_AES_IV_S = 0,
  };

  // Bit fields for the AES_AES_CTRL register
  enum {
    AES_AES_CTRL_CONTEXT_READY = 0x80000000,
    AES_AES_CTRL_CONTEXT_READY_M = 0x80000000,
    AES_AES_CTRL_CONTEXT_READY_S = 31,
    AES_AES_CTRL_SAVED_CONTEXT_READY = 0x40000000,
    AES_AES_CTRL_SAVED_CONTEXT_READY_M = 0x40000000,
    AES_AES_CTRL_SAVED_CONTEXT_READY_S = 30,
    AES_AES_CTRL_SAVE_CONTEXT = 0x20000000,
    AES_AES_CTRL_SAVE_CONTEXT_M = 0x20000000,
    AES_AES_CTRL_SAVE_CONTEXT_S = 29,
    AES_AES_CTRL_CCM_M_M = 0x01C00000,
    AES_AES_CTRL_CCM_M_S = 22,
    AES_AES_CTRL_CCM_L_M = 0x00380000,
    AES_AES_CTRL_CCM_L_S = 19,
    AES_AES_CTRL_CCM = 0x00040000,
    AES_AES_CTRL_CCM_M = 0x00040000,
    AES_AES_CTRL_CCM_S = 18,
    AES_AES_CTRL_GCM_M = 0x00030000,
    AES_AES_CTRL_GCM_S = 16,
    AES_AES_CTRL_CBC_MAC = 0x00008000,
    AES_AES_CTRL_CBC_MAC_M = 0x00008000,
    AES_AES_CTRL_CBC_MAC_S = 15,
    AES_AES_CTRL_CTR_WIDTH_M = 0x00000180,
    AES_AES_CTRL_CTR_WIDTH_S = 7,
    AES_AES_CTRL_CTR = 0x00000040,
    AES_AES_CTRL_CTR_M = 0x00000040,
    AES_AES_CTRL_CTR_S = 6,
    AES_AES_CTRL_CBC = 0x00000020,
    AES_AES_CTRL_CBC_M = 0x00000020,
    AES_AES_CTRL_CBC_S = 5,
    AES_AES_CTRL_KEY_SIZE_M = 0x00000018,
    AES_AES_CTRL_KEY_SIZE_S = 3,
    AES_AES_CTRL_DIRECTION = 0x00000004,
    AES_AES_CTRL_DIRECTION_M = 0x00000004,
    AES_AES_CTRL_DIRECTION_S = 2,
    AES_AES_CTRL_INPUT_READY = 0x00000002,
    AES_AES_CTRL_INPUT_READY_M = 0x00000002,
    AES_AES_CTRL_INPUT_READY_S = 1,
    AES_AES_CTRL_OUTPUT_READY = 0x00000001,
    AES_AES_CTRL_OUTPUT_READY_M = 0x00000001,
    AES_AES_CTRL_OUTPUT_READY_S = 0,
  };

  // Bit fields for the AES_AES_C_LENGTH_0 register
  enum {
    AES_AES_C_LENGTH_0_C_LENGTH_M = 0xFFFFFFFF,
    AES_AES_C_LENGTH_0_C_LENGTH_S = 0,
  };

  // Bit fields for the AES_AES_C_LENGTH_1 register
  enum {
    AES_AES_C_LENGTH_1_C_LENGTH_M = 0xFFFFFFFF,
    AES_AES_C_LENGTH_1_C_LENGTH_S = 0,
  };

  // Bit fields for the AES_AES_AUTH_LENGTH register
  enum {
    AES_AES_AUTH_LENGTH_AUTH_LENGTH_M = 0xFFFFFFFF,
    AES_AES_AUTH_LENGTH_AUTH_LENGTH_S = 0,
  };

  // Bit fields for the AES_AES_DATA_IN_OUT_0 register
  enum {
    AES_AES_DATA_IN_OUT_0_AES_DATA_IN_OUT_M = 0xFFFFFFFF,
    AES_AES_DATA_IN_OUT_0_AES_DATA_IN_OUT_S = 0,
  };

  // Bit fields for the AES_AES_DATA_IN_OUT_1 register
  enum {
    AES_AES_DATA_IN_OUT_1_AES_DATA_IN_OUT_M = 0xFFFFFFFF,
    AES_AES_DATA_IN_OUT_1_AES_DATA_IN_OUT_S = 0,
  };

  // Bit fields for the AES_AES_DATA_IN_OUT_2 register
  enum {
    AES_AES_DATA_IN_OUT_2_AES_DATA_IN_OUT_M = 0xFFFFFFFF,
    AES_AES_DATA_IN_OUT_2_AES_DATA_IN_OUT_S = 0,
  };

  // Bit fields for the AES_AES_DATA_IN_OUT_3 register
  enum {
    AES_AES_DATA_IN_OUT_3_AES_DATA_IN_OUT_M = 0xFFFFFFFF,
    AES_AES_DATA_IN_OUT_3_AES_DATA_IN_OUT_S = 0,
  };

  // Bit fields for the AES_AES_TAG_OUT_0 register
  enum {
    AES_AES_TAG_OUT_0_AES_TAG_M = 0xFFFFFFFF,
    AES_AES_TAG_OUT_0_AES_TAG_S = 0,
  };

  // Bit fields for the AES_AES_TAG_OUT_1 register
  enum {
    AES_AES_TAG_OUT_1_AES_TAG_M = 0xFFFFFFFF,
    AES_AES_TAG_OUT_1_AES_TAG_S = 0,
  };

  // Bit fields for the AES_AES_TAG_OUT_2 register
  enum {
    AES_AES_TAG_OUT_2_AES_TAG_M = 0xFFFFFFFF,
    AES_AES_TAG_OUT_2_AES_TAG_S = 0,
  };

  // Bit fields for the AES_AES_TAG_OUT_3 register
  enum {
    AES_AES_TAG_OUT_3_AES_TAG_M = 0xFFFFFFFF,
    AES_AES_TAG_OUT_3_AES_TAG_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_0 register
  enum {
    AES_HASH_DATA_IN_0_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_0_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_1 register
  enum {
    AES_HASH_DATA_IN_1_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_1_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_2 register
  enum {
    AES_HASH_DATA_IN_2_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_2_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_3 register
  enum {
    AES_HASH_DATA_IN_3_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_3_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_4 register
  enum {
    AES_HASH_DATA_IN_4_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_4_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_5 register
  enum {
    AES_HASH_DATA_IN_5_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_5_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_6 register
  enum {
    AES_HASH_DATA_IN_6_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_6_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_7 register
  enum {
    AES_HASH_DATA_IN_7_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_7_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_8 register
  enum {
    AES_HASH_DATA_IN_8_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_8_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_9 register
  enum {
    AES_HASH_DATA_IN_9_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_9_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_10 register
  enum {
    AES_HASH_DATA_IN_10_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_10_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_11 register
  enum {
    AES_HASH_DATA_IN_11_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_11_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_12 register
  enum {
    AES_HASH_DATA_IN_12_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_12_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_13 register
  enum {
    AES_HASH_DATA_IN_13_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_13_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_14 register
  enum {
    AES_HASH_DATA_IN_14_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_14_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DATA_IN_15 register
  enum {
    AES_HASH_DATA_IN_15_HASH_DATA_IN_M = 0xFFFFFFFF,
    AES_HASH_DATA_IN_15_HASH_DATA_IN_S = 0,
  };

  // Bit fields for the AES_HASH_IO_BUF_CTRL register
  enum {
    AES_HASH_IO_BUF_CTRL_PAD_DMA_MESSAGE = 0x00000080,
    AES_HASH_IO_BUF_CTRL_PAD_DMA_MESSAGE_M = 0x00000080,
    AES_HASH_IO_BUF_CTRL_PAD_DMA_MESSAGE_S = 7,
    AES_HASH_IO_BUF_CTRL_GET_DIGEST = 0x00000040,
    AES_HASH_IO_BUF_CTRL_GET_DIGEST_M = 0x00000040,
    AES_HASH_IO_BUF_CTRL_GET_DIGEST_S = 6,
    AES_HASH_IO_BUF_CTRL_PAD_MESSAGE = 0x00000020,
    AES_HASH_IO_BUF_CTRL_PAD_MESSAGE_M = 0x00000020,
    AES_HASH_IO_BUF_CTRL_PAD_MESSAGE_S = 5,
    AES_HASH_IO_BUF_CTRL_RFD_IN = 0x00000004,
    AES_HASH_IO_BUF_CTRL_RFD_IN_M = 0x00000004,
    AES_HASH_IO_BUF_CTRL_RFD_IN_S = 2,
    AES_HASH_IO_BUF_CTRL_DATA_IN_AV = 0x00000002,
    AES_HASH_IO_BUF_CTRL_DATA_IN_AV_M = 0x00000002,
    AES_HASH_IO_BUF_CTRL_DATA_IN_AV_S = 1,
    AES_HASH_IO_BUF_CTRL_OUTPUT_FULL = 0x00000001,
    AES_HASH_IO_BUF_CTRL_OUTPUT_FULL_M = 0x00000001,
    AES_HASH_IO_BUF_CTRL_OUTPUT_FULL_S = 0,
  };

  // Bit fields for the AES_HASH_MODE_IN register
  enum {
    AES_HASH_MODE_IN_SHA256_MODE = 0x00000008,
    AES_HASH_MODE_IN_SHA256_MODE_M = 0x00000008,
    AES_HASH_MODE_IN_SHA256_MODE_S = 3,
    AES_HASH_MODE_IN_NEW_HASH = 0x00000001,
    AES_HASH_MODE_IN_NEW_HASH_M = 0x00000001,
    AES_HASH_MODE_IN_NEW_HASH_S = 0,
  };

  // Bit fields for the AES_HASH_LENGTH_IN_L register
  enum {
    AES_HASH_LENGTH_IN_L_LENGTH_IN_M = 0xFFFFFFFF,
    AES_HASH_LENGTH_IN_L_LENGTH_IN_S = 0,
  };

  // Bit fields for the AES_HASH_LENGTH_IN_H register
  enum {
    AES_HASH_LENGTH_IN_H_LENGTH_IN_M = 0xFFFFFFFF,
    AES_HASH_LENGTH_IN_H_LENGTH_IN_S = 0,
  };

  // Bit fields for the AES_HASH_DIGEST_A register
  enum {
    AES_HASH_DIGEST_A_HASH_DIGEST_M = 0xFFFFFFFF,
    AES_HASH_DIGEST_A_HASH_DIGEST_S = 0,
  };

  // Bit fields for the AES_HASH_DIGEST_B register
  enum {
    AES_HASH_DIGEST_B_HASH_DIGEST_M = 0xFFFFFFFF,
    AES_HASH_DIGEST_B_HASH_DIGEST_S = 0,
  };

  // Bit fields for the AES_HASH_DIGEST_C register
  enum {
    AES_HASH_DIGEST_C_HASH_DIGEST_M = 0xFFFFFFFF,
    AES_HASH_DIGEST_C_HASH_DIGEST_S = 0,
  };

  // Bit fields for the AES_HASH_DIGEST_D register
  enum {
    AES_HASH_DIGEST_D_HASH_DIGEST_M = 0xFFFFFFFF,
    AES_HASH_DIGEST_D_HASH_DIGEST_S = 0,
  };

  // Bit fields for the AES_HASH_DIGEST_E register
  enum {
    AES_HASH_DIGEST_E_HASH_DIGEST_M = 0xFFFFFFFF,
    AES_HASH_DIGEST_E_HASH_DIGEST_S = 0,
  };

  // Bit fields for the AES_HASH_DIGEST_F register
  enum {
    AES_HASH_DIGEST_F_HASH_DIGEST_M = 0xFFFFFFFF,
    AES_HASH_DIGEST_F_HASH_DIGEST_S = 0,
  };

  // Bit fields for the AES_HASH_DIGEST_G register
  enum {
    AES_HASH_DIGEST_G_HASH_DIGEST_M = 0xFFFFFFFF,
    AES_HASH_DIGEST_G_HASH_DIGEST_S = 0,
  };

  // Bit fields for the AES_HASH_DIGEST_H register
  enum {
    AES_HASH_DIGEST_H_HASH_DIGEST_M = 0xFFFFFFFF,
    AES_HASH_DIGEST_H_HASH_DIGEST_S = 0,
  };

  // Bit fields for the AES_CTRL_ALG_SEL register
  enum {
    AES_CTRL_ALG_SEL_TAG = 0x80000000,
    AES_CTRL_ALG_SEL_TAG_M = 0x80000000,
    AES_CTRL_ALG_SEL_TAG_S = 31,
    AES_CTRL_ALG_SEL_HASH = 0x00000004,
    AES_CTRL_ALG_SEL_HASH_M = 0x00000004,
    AES_CTRL_ALG_SEL_HASH_S = 2,
    AES_CTRL_ALG_SEL_AES = 0x00000002,
    AES_CTRL_ALG_SEL_AES_M = 0x00000002,
    AES_CTRL_ALG_SEL_AES_S = 1,
    AES_CTRL_ALG_SEL_KEYSTORE = 0x00000001,
    AES_CTRL_ALG_SEL_KEYSTORE_M = 0x00000001,
    AES_CTRL_ALG_SEL_KEYSTORE_S = 0,
  };

  // Bit fields for the AES_CTRL_PROT_EN register
  enum {
    AES_CTRL_PROT_EN_PROT_EN = 0x00000001,
    AES_CTRL_PROT_EN_PROT_EN_M = 0x00000001,
    AES_CTRL_PROT_EN_PROT_EN_S = 0,
  };

  // Bit fields for the AES_CTRL_SW_RESET register
  enum {
    AES_CTRL_SW_RESET_SW_RESET = 0x00000001,
    AES_CTRL_SW_RESET_SW_RESET_M = 0x00000001,
    AES_CTRL_SW_RESET_SW_RESET_S = 0,
  };

  // Bit fields for the AES_CTRL_INT_CFG register
  enum {
    AES_CTRL_INT_CFG_LEVEL = 0x00000001,
    AES_CTRL_INT_CFG_LEVEL_M = 0x00000001,
    AES_CTRL_INT_CFG_LEVEL_S = 0,
  };

  // Bit fields for the AES_CTRL_INT_EN register
  enum {
    AES_CTRL_INT_EN_DMA_IN_DONE = 0x00000002,
    AES_CTRL_INT_EN_DMA_IN_DONE_M = 0x00000002,
    AES_CTRL_INT_EN_DMA_IN_DONE_S = 1,
    AES_CTRL_INT_EN_RESULT_AV = 0x00000001,
    AES_CTRL_INT_EN_RESULT_AV_M = 0x00000001,
    AES_CTRL_INT_EN_RESULT_AV_S = 0,
  };

  // Bit fields for the AES_CTRL_INT_CLR register
  enum {
    AES_CTRL_INT_CLR_DMA_BUS_ERR = 0x80000000,
    AES_CTRL_INT_CLR_DMA_BUS_ERR_M = 0x80000000,
    AES_CTRL_INT_CLR_DMA_BUS_ERR_S = 31,
    AES_CTRL_INT_CLR_KEY_ST_WR_ERR = 0x40000000,
    AES_CTRL_INT_CLR_KEY_ST_WR_ERR_M = 0x40000000,
    AES_CTRL_INT_CLR_KEY_ST_WR_ERR_S = 30,
    AES_CTRL_INT_CLR_KEY_ST_RD_ERR = 0x20000000,
    AES_CTRL_INT_CLR_KEY_ST_RD_ERR_M = 0x20000000,
    AES_CTRL_INT_CLR_KEY_ST_RD_ERR_S = 29,
    AES_CTRL_INT_CLR_DMA_IN_DONE = 0x00000002,
    AES_CTRL_INT_CLR_DMA_IN_DONE_M = 0x00000002,
    AES_CTRL_INT_CLR_DMA_IN_DONE_S = 1,
    AES_CTRL_INT_CLR_RESULT_AV = 0x00000001,
    AES_CTRL_INT_CLR_RESULT_AV_M = 0x00000001,
    AES_CTRL_INT_CLR_RESULT_AV_S = 0,
  };

  // Bit fields for the AES_CTRL_INT_SET register
  enum {
    AES_CTRL_INT_SET_DMA_IN_DONE = 0x00000002,
    AES_CTRL_INT_SET_DMA_IN_DONE_M = 0x00000002,
    AES_CTRL_INT_SET_DMA_IN_DONE_S = 1,
    AES_CTRL_INT_SET_RESULT_AV = 0x00000001,
    AES_CTRL_INT_SET_RESULT_AV_M = 0x00000001,
    AES_CTRL_INT_SET_RESULT_AV_S = 0,
  };

  // Bit fields for the AES_CTRL_INT_STAT register
  enum {
    AES_CTRL_INT_STAT_DMA_BUS_ERR = 0x80000000,
    AES_CTRL_INT_STAT_DMA_BUS_ERR_M = 0x80000000,
    AES_CTRL_INT_STAT_DMA_BUS_ERR_S = 31,
    AES_CTRL_INT_STAT_KEY_ST_WR_ERR = 0x40000000,
    AES_CTRL_INT_STAT_KEY_ST_WR_ERR_M = 0x40000000,
    AES_CTRL_INT_STAT_KEY_ST_WR_ERR_S = 30,
    AES_CTRL_INT_STAT_KEY_ST_RD_ERR = 0x20000000,
    AES_CTRL_INT_STAT_KEY_ST_RD_ERR_M = 0x20000000,
    AES_CTRL_INT_STAT_KEY_ST_RD_ERR_S = 29,
    AES_CTRL_INT_STAT_DMA_IN_DONE = 0x00000002,
    AES_CTRL_INT_STAT_DMA_IN_DONE_M = 0x00000002,
    AES_CTRL_INT_STAT_DMA_IN_DONE_S = 1,
    AES_CTRL_INT_STAT_RESULT_AV = 0x00000001,
    AES_CTRL_INT_STAT_RESULT_AV_M = 0x00000001,
    AES_CTRL_INT_STAT_RESULT_AV_S = 0,
  };

  // Bit fields for the AES_CTRL_OPTIONS register
  enum {
    AES_CTRL_OPTIONS_TYPE_M = 0xFF000000,
    AES_CTRL_OPTIONS_TYPE_S = 24,
    AES_CTRL_OPTIONS_AHBINTERFACE = 0x00010000,
    AES_CTRL_OPTIONS_AHBINTERFACE_M = 0x00010000,
    AES_CTRL_OPTIONS_AHBINTERFACE_S = 16,
    AES_CTRL_OPTIONS_SHA_256 = 0x00000100,
    AES_CTRL_OPTIONS_SHA_256_M = 0x00000100,
    AES_CTRL_OPTIONS_SHA_256_S = 8,
    AES_CTRL_OPTIONS_AES_CCM = 0x00000080,
    AES_CTRL_OPTIONS_AES_CCM_M = 0x00000080,
    AES_CTRL_OPTIONS_AES_CCM_S = 7,
    AES_CTRL_OPTIONS_AES_GCM = 0x00000040,
    AES_CTRL_OPTIONS_AES_GCM_M = 0x00000040,
    AES_CTRL_OPTIONS_AES_GCM_S = 6,
    AES_CTRL_OPTIONS_AES_256 = 0x00000020,
    AES_CTRL_OPTIONS_AES_256_M = 0x00000020,
    AES_CTRL_OPTIONS_AES_256_S = 5,
    AES_CTRL_OPTIONS_AES_128 = 0x00000010,
    AES_CTRL_OPTIONS_AES_128_M = 0x00000010,
    AES_CTRL_OPTIONS_AES_128_S = 4,
    AES_CTRL_OPTIONS_HASH = 0x00000004,
    AES_CTRL_OPTIONS_HASH_M = 0x00000004,
    AES_CTRL_OPTIONS_HASH_S = 2,
    AES_CTRL_OPTIONS_AES = 0x00000002,
    AES_CTRL_OPTIONS_AES_M = 0x00000002,
    AES_CTRL_OPTIONS_AES_S = 1,
    AES_CTRL_OPTIONS_KEYSTORE = 0x00000001,
    AES_CTRL_OPTIONS_KEYSTORE_M = 0x00000001,
    AES_CTRL_OPTIONS_KEYSTORE_S = 0,
  };

  // Bit fields for the AES_CTRL_VERSION register
  enum {
    AES_CTRL_VERSION_MAJOR_VERSION_M = 0x0F000000,
    AES_CTRL_VERSION_MAJOR_VERSION_S = 24,
    AES_CTRL_VERSION_MINOR_VERSION_M = 0x00F00000,
    AES_CTRL_VERSION_MINOR_VERSION_S = 20,
    AES_CTRL_VERSION_PATCH_LEVEL_M = 0x000F0000,
    AES_CTRL_VERSION_PATCH_LEVEL_S = 16,
    AES_CTRL_VERSION_EIP_NUMBER_COMPL_M = 0x0000FF00,
    AES_CTRL_VERSION_EIP_NUMBER_COMPL_S = 8,
    AES_CTRL_VERSION_EIP_NUMBER_M = 0x000000FF,
    AES_CTRL_VERSION_EIP_NUMBER_S = 0,
  };

  // AES module operations
  enum AES_Operation {
    AES_NONE,
    AES_KEYL0AD,
    AES_ECB,
    AES_CCM,
    AES_SHA256,
    AES_RNG
  };

  // AES and SHA256 module return codes
  enum AES_Return_Code {
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

  // Valid key locations. For key sizes of 192 and 256 bits,
  // only areas 0, 2, 4 and 6 are valid.
  enum {
    KEY_AREA_0,
    KEY_AREA_1,
    KEY_AREA_2,
    KEY_AREA_3,
    KEY_AREA_4,
    KEY_AREA_5,
    KEY_AREA_6,
    KEY_AREA_7
  };

  enum {
    KEY_STORE_SIZE_BITS = 0x03UL,
    KEY_STORE_SIZE_NA = 0x00UL,
    KEY_STORE_SIZE_128 = 0x01UL,
    KEY_STORE_SIZE_192 = 0x02UL,
    KEY_STORE_SIZE_256 = 0x03UL,
  };

  static const unsigned int keyLength = 16;          // length of key in bytes

  volatile AES_Operation currentOp;

  typedef CPU::Reg32 Reg32;

  static volatile Reg32 &aes_reg(unsigned int offset) {
    return *(reinterpret_cast<volatile Reg32 *>(AES_BASE_ADDRESS + offset));
  }

  AES_Return_Code aes_load_keys(const unsigned char *key,
                                unsigned char keyLoc) {
    OStream cout;

    static unsigned int ui32temp[4];
    unsigned char *pui8temp = (unsigned char *)ui32temp;
    unsigned char i;

    currentOp = AES_KEYL0AD;
    // The key address needs to be 4 byte aligned
    for (i = 0; i < keyLength; i++) {
      pui8temp[i] = key[i];
    }

    // workaround for AES registers not retained after PM2
    cout << hex << "AES_CTRL_INT_CFG " << aes_reg(AES_CTRL_INT_CFG);
    aes_reg(AES_CTRL_INT_CFG) |= AES_CTRL_INT_CFG_LEVEL;
    cout << hex << " -> " << aes_reg(AES_CTRL_INT_CFG) << endl;
    cout << hex << "AES_CTRL_INT_EN " << aes_reg(AES_CTRL_INT_EN);
    aes_reg(AES_CTRL_INT_EN) |=
        (AES_CTRL_INT_EN_DMA_IN_DONE | AES_CTRL_INT_EN_RESULT_AV);
    cout << hex << " -> " << aes_reg(AES_CTRL_INT_EN) << endl;

    // configure master control module
    cout << hex << "AES_CTRL_INT_SEL " << aes_reg(AES_CTRL_ALG_SEL);
    aes_reg(AES_CTRL_ALG_SEL) &= (~AES_CTRL_ALG_SEL_KEYSTORE);
    aes_reg(AES_CTRL_ALG_SEL) |= AES_CTRL_ALG_SEL_KEYSTORE;
    cout << hex << " -> " << aes_reg(AES_CTRL_ALG_SEL) << endl;

    // clear any outstanding events
    cout << hex << "AES_CTRL_INT_CLR " << aes_reg(AES_CTRL_INT_CLR);
    aes_reg(AES_CTRL_INT_CLR) |=
        (AES_CTRL_INT_CLR_DMA_IN_DONE | AES_CTRL_INT_CLR_RESULT_AV);
    cout << hex << " -> " << aes_reg(AES_CTRL_INT_CLR) << endl;

    // configure key store module (area, size)
    cout << hex << "AES_KEY_STORE_SIZE " << aes_reg(AES_KEY_STORE_SIZE);
    aes_reg(AES_KEY_STORE_SIZE) &= KEY_STORE_SIZE_BITS;

    // 128-bit key size
    aes_reg(AES_KEY_STORE_SIZE) |= KEY_STORE_SIZE_128;
    cout << hex << " -> " << aes_reg(AES_KEY_STORE_SIZE) << endl;

    // enable keys to write (e.g. Key 0)
    cout << hex << "AES_KEY_STORE_WRITE_AREA " << aes_reg(AES_KEY_STORE_WRITE_AREA);
    aes_reg(AES_KEY_STORE_WRITE_AREA) = (0x00000001 << keyLoc);
    cout << hex << " -> " << aes_reg(AES_KEY_STORE_WRITE_AREA) << endl;

    // configure DMAC
    // enable DMA channel 0
    cout << hex << "AES_DMAC_CH0_CTRL " << aes_reg(AES_DMAC_CH0_CTRL);
    aes_reg(AES_DMAC_CH0_CTRL) |= 0x000000001;
    cout << hex << " -> " << aes_reg(AES_DMAC_CH0_CTRL) << endl;

    // base address of the key in ext. memory
  cout << hex << "AES_DMAC_CH0_EXTADDR " << aes_reg(AES_DMAC_CH0_EXTADDR);
    aes_reg(AES_DMAC_CH0_EXTADDR) = (unsigned int)pui8temp;
  cout << hex << " -> " << aes_reg(AES_DMAC_CH0_EXTADDR) << endl;

    // total key length in bytes (e.g. 16 for 1 x 128-bit key)
    cout << hex << "AES_DMAC_CH0_DMALENGTH " << aes_reg(AES_DMAC_CH0_DMALENGTH);
    aes_reg(AES_DMAC_CH0_DMALENGTH) = 0x10;
    cout << hex << " -> " << aes_reg(AES_DMAC_CH0_DMALENGTH) << endl;

    // wait for operation completed
    while ((!(aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_RESULT_AV)))
      ;

    cout << hex << "AES_CTRL_INT_STAT " << aes_reg(AES_CTRL_INT_STAT) << endl;
    // check for absence of errors in DMA and key store
    if ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_DMA_BUS_ERR)) {
      aes_reg(AES_CTRL_INT_CLR) |= AES_CTRL_INT_CLR_DMA_BUS_ERR;
      return (AES_DMA_BUS_ERROR);
    }
    if ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_WR_ERR)) {
      aes_reg(AES_CTRL_INT_CLR) |= AES_CTRL_INT_CLR_KEY_ST_WR_ERR;
      return (AES_KEYSTORE_WRITE_ERROR);
    }

    // acknowledge the interrupt
    cout << hex << "AES_CTRL_INT_CLR " << aes_reg(AES_CTRL_INT_CLR);
    aes_reg(AES_CTRL_INT_CLR) |=
        (AES_CTRL_INT_CLR_DMA_IN_DONE | AES_CTRL_INT_CLR_RESULT_AV);
    cout << hex << " -> " << aes_reg(AES_CTRL_INT_CLR) << endl;

    // disable master control/DMA clock
    cout << hex << "AES_CTRL_ALG_SEL " << aes_reg(AES_CTRL_ALG_SEL);
    aes_reg(AES_CTRL_ALG_SEL) = 0x00000000;
    cout << hex << " -> " << aes_reg(AES_CTRL_ALG_SEL) << endl;

    cout << hex << "AES_KEY_STORE_WRITTEN_AREA " << aes_reg(AES_KEY_STORE_WRITTEN_AREA) << endl;
    // check status, if error return error code
    if ((aes_reg(AES_KEY_STORE_WRITTEN_AREA) & 0x7) != 0x1) {
      currentOp = AES_NONE;
      return (AES_KEYSTORE_WRITE_ERROR);
    }

    for (i = 0; i < keyLength; i++) {
      pui8temp[i] = 0;
    }

    currentOp = AES_NONE;
    return (AES_SUCCESS);
  }

  AES_Return_Code aes_ecb_start(const unsigned char *in, unsigned char *out,
                                unsigned char keyLoc, bool encrypt) {
    currentOp = AES_ECB;
    OStream cout;
    cout << hex << "AES_CTRL_INT_CFG " << aes_reg(AES_CTRL_INT_CFG);
    aes_reg(AES_CTRL_INT_CFG) = AES_CTRL_INT_CFG_LEVEL;
    cout << hex << " -> " << aes_reg(AES_CTRL_INT_CFG) << endl;
    cout << hex << "AES_CTRL_INT_EN " << aes_reg(AES_CTRL_INT_EN);
    aes_reg(AES_CTRL_INT_EN) = AES_CTRL_INT_EN_RESULT_AV;
    cout << hex << " -> " << aes_reg(AES_CTRL_INT_EN) << endl;

    // configure the master control module
    // enable the DMA path to the AES engine
    cout << hex << "AES_CTRL_ALG_SEL " << aes_reg(AES_CTRL_ALG_SEL);
    aes_reg(AES_CTRL_ALG_SEL) = AES_CTRL_ALG_SEL_AES;
    cout << hex << " -> " << aes_reg(AES_CTRL_ALG_SEL) << endl;
    // clear any outstanding events
    cout << hex << "AES_CTRL_INT_CLR " << aes_reg(AES_CTRL_INT_CLR);
    aes_reg(AES_CTRL_INT_CLR) |=
        (AES_CTRL_INT_CLR_DMA_IN_DONE | AES_CTRL_INT_CLR_RESULT_AV);
    cout << hex << " -> " << aes_reg(AES_CTRL_INT_CLR) << endl;

    cout << hex << "AES_KEY_STORE_READ_AREA " << aes_reg(AES_KEY_STORE_READ_AREA);
    aes_reg(AES_KEY_STORE_READ_AREA) = keyLoc;
    cout << hex << " -> " << aes_reg(AES_KEY_STORE_READ_AREA) << endl;

    // wait until key is loaded to the AES module
    while ((aes_reg(AES_KEY_STORE_READ_AREA) & AES_KEY_STORE_READ_AREA_BUSY))
      ;

    // check for Key Store read error
    cout << hex << "AES_CTRL_INT_STAT " << aes_reg(AES_CTRL_INT_STAT);
    if ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_RD_ERR)) {
      // Clear Key Store Read error
      aes_reg(AES_CTRL_INT_CLR) |= AES_CTRL_INT_CLR_KEY_ST_RD_ERR;
      return (AES_KEYSTORE_READ_ERROR);
    }
    cout << hex << " -> " << aes_reg(AES_CTRL_INT_STAT) << endl;

    // configure AES engine
    // program AES-ECB-128 encryption and no IV
    cout << hex << "AES_AES_CTRL " << aes_reg(AES_AES_CTRL);
    if (encrypt) {
      aes_reg(AES_AES_CTRL) = 0x0000000C;
    } else {
      aes_reg(AES_AES_CTRL) = 0x00000008;
    }
    cout << hex << " -> " << aes_reg(AES_AES_CTRL) << endl;

    // write length of the message (lo)
    cout << hex << "AES_AES_C_LENGTH_0 " << aes_reg(AES_AES_C_LENGTH_0);
    aes_reg(AES_AES_C_LENGTH_0) = keyLength;
    cout << hex << " -> " << aes_reg(AES_AES_C_LENGTH_0) << endl;
    // write length of the message (hi)
    aes_reg(AES_AES_C_LENGTH_1) = 0;

    // configure DMAC
    // enable DMA channel 0
    cout << hex << "AES_DMAC_CH0_CTRL " << aes_reg(AES_DMAC_CH0_CTRL);
    aes_reg(AES_DMAC_CH0_CTRL) = AES_DMAC_CH0_CTRL_EN;
    cout << hex << " -> " << aes_reg(AES_DMAC_CH0_CTRL) << endl;

    // base address of the input data in ext. memory
    cout << hex << "AES_DMAC_CH0_EXTADDR " << aes_reg(AES_DMAC_CH0_EXTADDR);
    aes_reg(AES_DMAC_CH0_EXTADDR) = (unsigned int)in;
    cout << hex << " -> " << aes_reg(AES_DMAC_CH0_EXTADDR) << endl;

    // input data length in bytes, equal to the message
    cout << hex << "AES_DMAC_CH0_DMALENGTH " << aes_reg(AES_DMAC_CH0_DMALENGTH);
    aes_reg(AES_DMAC_CH0_DMALENGTH) = keyLength;
    cout << hex << " -> " << aes_reg(AES_DMAC_CH0_DMALENGTH) << endl;

    // length (may be non-block size aligned)
    cout << hex << "AES_DMAC_CH1_CTRL " << aes_reg(AES_DMAC_CH1_CTRL);
    aes_reg(AES_DMAC_CH1_CTRL) = AES_DMAC_CH1_CTRL_EN; // enable DMA channel 1
    cout << hex << " -> " << aes_reg(AES_DMAC_CH1_CTRL) << endl;

    // base address of the output data buffer
    cout << hex << "AES_DMAC_CH1_EXTADDR " << aes_reg(AES_DMAC_CH1_EXTADDR);
    aes_reg(AES_DMAC_CH1_EXTADDR) = (unsigned int)out;
    cout << hex << " -> " << aes_reg(AES_DMAC_CH1_EXTADDR) << endl;

    // output data length in bytes, equal to the result
    cout << hex << "AES_DMAC_CH1_DMALENGTH " << aes_reg(AES_DMAC_CH1_DMALENGTH);
    aes_reg(AES_DMAC_CH1_DMALENGTH) = keyLength;
    cout << hex << " -> " << aes_reg(AES_DMAC_CH1_DMALENGTH) << endl;

    return (AES_SUCCESS);
  }

  unsigned char aes_ecb_check_result() {
    return (((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_RESULT_AV)) ||
            ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_DMA_BUS_ERR)) ||
            ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_WR_ERR)) ||
            ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_RD_ERR)));
  }

  AES_Return_Code aes_ecb_get_result() {
    OStream cout;
    // check for errors
    if ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_DMA_BUS_ERR)) {
      // clear the DMA error bit
      aes_reg(AES_CTRL_INT_CLR) |= AES_CTRL_INT_CLR_DMA_BUS_ERR;
      return (AES_DMA_BUS_ERROR);
    }
    if ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_WR_ERR)) {
      // clear the Key Store Write error bit
      aes_reg(AES_CTRL_INT_CLR) |= AES_CTRL_INT_CLR_KEY_ST_WR_ERR;
      return (AES_KEYSTORE_WRITE_ERROR);
    }
    if ((aes_reg(AES_CTRL_INT_STAT) & AES_CTRL_INT_STAT_KEY_ST_RD_ERR)) {
      // clear the Key Store Read error bit
      aes_reg(AES_CTRL_INT_CLR) |= AES_CTRL_INT_CLR_KEY_ST_RD_ERR;
      return (AES_KEYSTORE_READ_ERROR);
    }

    // clear DMA done and result available bits
    cout << hex << "AES_CTRL_INT_CLR " << aes_reg(AES_CTRL_INT_CLR);
    aes_reg(AES_CTRL_INT_CLR) |=
        (AES_CTRL_INT_CLR_DMA_IN_DONE | AES_CTRL_INT_CLR_RESULT_AV);
    cout << hex << " -> " << aes_reg(AES_CTRL_INT_CLR) << endl;

    // result has already been copied to the output buffer by DMA
    cout << hex << "AES_CTRL_ALG_SEL " << aes_reg(AES_CTRL_ALG_SEL);
    aes_reg(AES_CTRL_ALG_SEL) = 0x00000000; // disable master control/DMA clock
    cout << hex << " -> " << aes_reg(AES_CTRL_ALG_SEL) << endl;
    cout << hex << "AES_AES_CTRL " << aes_reg(AES_AES_CTRL);
    aes_reg(AES_AES_CTRL) = 0x00000000;     // clear mode
    cout << hex << " -> " << aes_reg(AES_AES_CTRL) << endl;
    currentOp = AES_NONE;
    return (AES_SUCCESS);
  }

  AES_Return_Code crypt(const unsigned char *key, unsigned char loc,
                        const unsigned char *in, unsigned char *out,
                        bool mode) {
    OStream cout;
    unsigned char code = AES_SUCCESS;
    code |= aes_load_keys(key, loc);
    cout << hex << "load keys " << code << endl;
    code |= aes_ecb_start(in, out, loc, mode);
    cout << hex << "ecb start " << code << endl;
    while (!(aes_ecb_check_result()))
      ;
    code |= aes_ecb_get_result();
    cout << hex << "get result " << code << endl;
    return (AES_Return_Code)code;
  }

  void encrypt(const unsigned char *in, const unsigned char *key,
               unsigned char *out, unsigned char keyLocation = KEY_AREA_0) {
    crypt(key, keyLocation, in, out, true);
  }

  void decrypt(const unsigned char *in, const unsigned char *key,
               unsigned char *out, unsigned char keyLocation = KEY_AREA_0) {
    crypt(key, keyLocation, in, out, false);
  }
};

// class AES_ECB : private AES {
//   public:
//     AES_ECB() {}
//
//   private:
//     static const unsigned int msgLength = 16;
// };
//
// class AES_CBC_MAC : private AES {
//   public:
//     AES_CBC_MAC() {}
// };

__END_SYS

#endif

#endif
