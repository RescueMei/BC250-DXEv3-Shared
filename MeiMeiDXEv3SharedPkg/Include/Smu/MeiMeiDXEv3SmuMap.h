/** @file
  Canonical BC250 DXEv3 SMU SRAM allocation map.

  Every owner must use these constants and stay within its region. The map is
  intentionally conservative: reserve the full span even when the current
  image is smaller.
**/

#ifndef MEIMEIDXEV3_SMU_MAP_H_
#define MEIMEIDXEV3_SMU_MAP_H_

#define MEIMEIDXEV3_SMU_FREE_START        0x0003AE00U
#define MEIMEIDXEV3_SMU_FREE_END          0x00040000U

#define MEIMEIDXEV3_SMU_PATCH_BASE        0x0003AE00U
#define MEIMEIDXEV3_SMU_PATCH_MAX         0x00001200U

#define MEIMEIDXEV3_SMU_CU_PAYLOAD_BASE   0x0003C000U
#define MEIMEIDXEV3_SMU_CU_PAYLOAD_MAX    0x00000400U
#define MEIMEIDXEV3_SMU_CU_STATE_BASE     0x0003C400U
#define MEIMEIDXEV3_SMU_CU_STATE_MAX      0x00000200U

#define MEIMEIDXEV3_SMU_GOV_STATE_BASE    0x0003C600U
#define MEIMEIDXEV3_SMU_GOV_STATE_MAX     0x00000A00U
#define MEIMEIDXEV3_SMU_GOV_PAYLOAD_BASE  0x0003D000U
#define MEIMEIDXEV3_SMU_GOV_PAYLOAD_MAX   0x00001000U

#define MEIMEIDXEV3_SMU_FIRMWARE_START    0x0003E000U

/*
  Firmware cache-maintenance registers.  These are firmware state, not a free
  payload lane: the patch and CU payloads save and restore them around each
  cache publish so injected SRAM writes become visible to the SMU.  They must
  never be used as scratch or payload space.
*/
#define MEIMEIDXEV3_SMU_CACHE_CB_ADDR     0x000184F8U
#define MEIMEIDXEV3_SMU_CACHE_FLAG_ADDR   0x0003FFBCU
#define MEIMEIDXEV3_SMU_CACHE_MASK_ADDR   0x0003FFF0U

#define MEIMEIDXEV3_SMU_REGION_END(base, max) ((base) + (max))

#endif // MEIMEIDXEV3_SMU_MAP_H_
