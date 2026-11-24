/** @file
  Common BC250 DXEv3 configuration helpers.
**/

#ifndef MEIMEI_CONFIG_LIB_H_
#define MEIMEI_CONFIG_LIB_H_

#include <Uefi.h>
#include <Config/MeiMeiDXEv3Config.h>

extern EFI_GUID  gMeiMeiDXEv3ConfigVarGuid;

extern CONST SMU_SAFE_POINT       mMeiMeiDefaultSafePoints[SMU_SAFE_POINT_COUNT];
extern CONST SMU_GOVERNOR_CONFIG  mMeiMeiDefaultGovernorConfig;
extern CONST ACPI_CONFIG          mMeiMeiDefaultAcpiConfig;
extern CONST SMU_UNLOCK_CONFIG    mMeiMeiDefaultSmuUnlockConfig;
extern CONST SMU_PATCH_CONFIG     mMeiMeiDefaultSmuPatchConfig;
extern CONST CORE_CONFIG          mMeiMeiDefaultCoreConfig;
extern CONST CU_CONFIG            mMeiMeiDefaultCuConfig;

EFI_STATUS
EFIAPI
MeiMeiConfigRead (
  IN  CONST CHAR16  *Name,
  OUT VOID          *Buffer,
  IN  UINTN          ExpectedSize,
  OUT BOOLEAN       *Present
  );

EFI_STATUS
EFIAPI
MeiMeiConfigCreateDefaultIfMissing (
  IN  CONST CHAR16  *Name,
  IN  CONST VOID    *DefaultData,
  IN  UINTN          Size,
  OUT BOOLEAN       *Created
  );

BOOLEAN
EFIAPI
MeiMeiValidateGovernorConfig (
  IN CONST SMU_GOVERNOR_CONFIG  *Config
  );

BOOLEAN
EFIAPI
MeiMeiValidateCuConfig (
  IN CONST CU_CONFIG  *Config
  );

#endif // MEIMEI_CONFIG_LIB_H_
