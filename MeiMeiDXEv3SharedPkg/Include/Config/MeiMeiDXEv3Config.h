/** @file
  Canonical MeiMeiDXEv3 configuration ABI.

  All drivers and the menu consume these definitions from the shared package.
  Do not duplicate these layouts in individual driver packages.
**/

#ifndef MEIMEIDXEV3_CONFIG_H_
#define MEIMEIDXEV3_CONFIG_H_

#include <Uefi.h>

extern EFI_GUID  gMeiMeiDXEv3ConfigVarGuid;

#define MEIMEIDXEV3_CONFIG_VAR_GUID \
  { 0x49CC168D, 0xE8B0, 0x4613, { 0xA8, 0x07, 0x16, 0x96, 0x99, 0x86, 0x72, 0x6F } }

#define MEIMEIDXEV3_CONFIG_VAR_ATTRIBUTES \
  (EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE)

#define MEIMEIDXEV3_ACPI_VAR_NAME          L"MeiMeiDXEv3AcpiVar"
#define MEIMEIDXEV3_SMU_UNLOCK_VAR_NAME    L"MeiMeiDXEv3SmuUnlockVar"
#define MEIMEIDXEV3_SMU_PATCH_VAR_NAME     L"MeiMeiDXEv3SmuPatchVar"
#define MEIMEIDXEV3_CORE_VAR_NAME          L"MeiMeiDXEv3CoreVar"
#define MEIMEIDXEV3_GOVERNOR_VAR_NAME      L"MeiMeiDXEv3SmuGovernorVar"
#define MEIMEIDXEV3_CU_VAR_NAME            L"MeiMeiDXEv3CuVar"

#define SMU_GOVERNOR_VAR_NAME              MEIMEIDXEV3_GOVERNOR_VAR_NAME
#define SMU_GOV_CONFIG_VAR_NAME            MEIMEIDXEV3_GOVERNOR_VAR_NAME
#define SMU_GOV_CONFIG_VAR_ATTR            MEIMEIDXEV3_CONFIG_VAR_ATTRIBUTES
#define SMU_GOV_CONFIG_MAX_SIZE            256U

#define MEIMEIDXEV3_ACPI_SCHEMA            1U
#define MEIMEIDXEV3_SMU_UNLOCK_SCHEMA      1U
#define MEIMEIDXEV3_SMU_PATCH_SCHEMA       1U
#define MEIMEIDXEV3_CORE_SCHEMA            1U
#define MEIMEIDXEV3_GOVERNOR_SCHEMA        1U
#define MEIMEIDXEV3_CU_SCHEMA              1U
#define CU_CONFIG_SCHEMA                   MEIMEIDXEV3_CU_SCHEMA

#define CORE_UNLOCK_DISABLED               0U
#define CORE_UNLOCK_ALL_CORES              1U
#define CORE_UNLOCK_CUSTOM                 2U

#define CU_UNLOCK_FACTORY                  0U
#define CU_UNLOCK_ALL                      1U
#define CU_UNLOCK_CUSTOM                   2U

#define SMU_SAFE_POINT_COUNT               15U
#define SMU_GOV_POINT_COUNT                SMU_SAFE_POINT_COUNT

#define MEIMEIDXEV3_DEFAULT_PACKAGE_LIMIT_W 250U
#define MEIMEIDXEV3_DEFAULT_GPU_LIMIT_W     200U

typedef struct {
  UINT8  AcpiPatch;
} ACPI_CONFIG;

typedef struct {
  UINT8  SmuUnlock;
} SMU_UNLOCK_CONFIG;

typedef struct {
  UINT8  SmuReportingPatch;
} SMU_PATCH_CONFIG;

typedef struct {
  UINT8  CoreUnlock;
  UINT8  Core0;
  UINT8  Core1;
  UINT8  Core2;
  UINT8  Core3;
  UINT8  Core4;
  UINT8  Core5;
  UINT8  Core6;
  UINT8  Core7;
} CORE_CONFIG;

typedef struct {
  UINT8   Enable;
  UINT8   Reserved;
  UINT16  Frequency;
  UINT16  Voltage;
} SMU_SAFE_POINT;

typedef struct {
  UINT8           SMUGovernorEnable;
  UINT8           Reserved;
  SMU_SAFE_POINT  GovernorFreqVoltPoints[SMU_SAFE_POINT_COUNT];
  UINT16          PackagePowerLimitW;
  UINT16          GpuPowerLimitW;
} SMU_GOVERNOR_CONFIG;

typedef SMU_SAFE_POINT      SMU_GOV_SAFE_POINT;
typedef SMU_GOVERNOR_CONFIG SMU_GOV_CONFIG;

#define SMU_GOV_CONFIG_LEGACY_SIZE \
  (2U + SMU_SAFE_POINT_COUNT * sizeof (SMU_SAFE_POINT))

typedef struct {
  UINT8  Version;
  UINT8  Mode;
  UINT8  Reserved[2];
  UINT8  Wgp[20];
} CU_CONFIG;

#define MEIMEIDXEV3_CORE_COUNT             8U
#define MEIMEIDXEV3_WGP_COUNT              20U

#endif // MEIMEIDXEV3_CONFIG_H_
