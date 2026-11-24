/** @file
  Common BC250 DXEv3 configuration helpers.
**/

#include <Uefi.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MeiMeiConfigLib.h>

CONST SMU_SAFE_POINT mMeiMeiDefaultSafePoints[SMU_SAFE_POINT_COUNT] = {
  { 0, 0,  350,  700 },
  { 1, 0,  500,  700 },
  { 1, 0, 1175,  700 },
  { 1, 0, 1400,  750 },
  { 1, 0, 1600,  800 },
  { 1, 0, 1700,  850 },
  { 1, 0, 1800,  875 },
  { 0, 0, 1850,  900 },
  { 0, 0, 2000,  950 },
  { 0, 0, 2050,  975 },
  { 0, 0, 2100, 1000 },
  { 0, 0, 2125, 1015 },
  { 0, 0, 2150, 1030 },
  { 0, 0, 2200, 1050 },
  { 0, 0,    0,    0 }
};

CONST SMU_GOVERNOR_CONFIG mMeiMeiDefaultGovernorConfig = {
  0, 0,
  {
    { 0, 0,  350,  700 },
    { 1, 0,  500,  700 },
    { 1, 0, 1175,  700 },
    { 1, 0, 1400,  750 },
    { 1, 0, 1600,  800 },
    { 1, 0, 1700,  850 },
    { 1, 0, 1800,  875 },
    { 0, 0, 1850,  900 },
    { 0, 0, 2000,  950 },
    { 0, 0, 2050,  975 },
    { 0, 0, 2100, 1000 },
    { 0, 0, 2125, 1015 },
    { 0, 0, 2150, 1030 },
    { 0, 0, 2200, 1050 },
    { 0, 0,    0,    0 }
  },
  MEIMEIDXEV3_DEFAULT_PACKAGE_LIMIT_W,
  MEIMEIDXEV3_DEFAULT_GPU_LIMIT_W
};

CONST ACPI_CONFIG         mMeiMeiDefaultAcpiConfig      = { 0 };
CONST SMU_UNLOCK_CONFIG   mMeiMeiDefaultSmuUnlockConfig = { 0 };
CONST SMU_PATCH_CONFIG    mMeiMeiDefaultSmuPatchConfig  = { 0 };
CONST CORE_CONFIG         mMeiMeiDefaultCoreConfig      = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
CONST CU_CONFIG           mMeiMeiDefaultCuConfig        = {
  MEIMEIDXEV3_CU_SCHEMA, CU_UNLOCK_FACTORY, { 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

EFI_STATUS
EFIAPI
MeiMeiConfigRead (
  IN  CONST CHAR16  *Name,
  OUT VOID          *Buffer,
  IN  UINTN          ExpectedSize,
  OUT BOOLEAN       *Present
  )
{
  EFI_STATUS  Status;
  UINTN       Size;
  UINT32      Attributes;

  if (Present == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *Present = FALSE;
  Size = ExpectedSize;
  Status = gRT->GetVariable (
                  (CHAR16 *)Name,
                  &gMeiMeiDXEv3ConfigVarGuid,
                  &Attributes,
                  &Size,
                  Buffer
                  );
  if (Status == EFI_NOT_FOUND) {
    return EFI_SUCCESS;
  }
  if (EFI_ERROR (Status)) {
    return Status;
  }
  *Present = TRUE;
  if (Size != ExpectedSize) {
    return EFI_BAD_BUFFER_SIZE;
  }
  if (Attributes != MEIMEIDXEV3_CONFIG_VAR_ATTRIBUTES) {
    return EFI_SECURITY_VIOLATION;
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MeiMeiConfigCreateDefaultIfMissing (
  IN  CONST CHAR16  *Name,
  IN  CONST VOID    *DefaultData,
  IN  UINTN          Size,
  OUT BOOLEAN       *Created
  )
{
  EFI_STATUS  Status;
  UINTN       CurrentSize;
  UINT32      Attributes;

  if (Created == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *Created = FALSE;
  CurrentSize = 0;
  Status = gRT->GetVariable (
                  (CHAR16 *)Name,
                  &gMeiMeiDXEv3ConfigVarGuid,
                  &Attributes,
                  &CurrentSize,
                  NULL
                  );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    return EFI_SUCCESS;
  }
  if (Status != EFI_NOT_FOUND) {
    return Status;
  }
  Status = gRT->SetVariable (
                  (CHAR16 *)Name,
                  &gMeiMeiDXEv3ConfigVarGuid,
                  MEIMEIDXEV3_CONFIG_VAR_ATTRIBUTES,
                  Size,
                  (VOID *)DefaultData
                  );
  if (!EFI_ERROR (Status)) {
    *Created = TRUE;
  }
  return Status;
}

BOOLEAN
EFIAPI
MeiMeiValidateGovernorConfig (
  IN CONST SMU_GOVERNOR_CONFIG  *Config
  )
{
  UINTN  Index;
  UINTN  Enabled;

  if (Config == NULL) {
    return FALSE;
  }
  Enabled = 0;
  for (Index = 0; Index < SMU_SAFE_POINT_COUNT; Index++) {
    if (Config->GovernorFreqVoltPoints[Index].Enable == 0) {
      continue;
    }
    Enabled++;
    if (Config->GovernorFreqVoltPoints[Index].Frequency < 300U ||
        Config->GovernorFreqVoltPoints[Index].Frequency > 3000U ||
        Config->GovernorFreqVoltPoints[Index].Voltage   < 600U ||
        Config->GovernorFreqVoltPoints[Index].Voltage   > 1250U) {
      return FALSE;
    }
  }
  if (Config->SMUGovernorEnable != 0 && Enabled < 2U) {
    return FALSE;
  }
  if (Config->PackagePowerLimitW != 0U &&
      (Config->PackagePowerLimitW < 100U || Config->PackagePowerLimitW > 1000U)) {
    return FALSE;
  }
  if (Config->GpuPowerLimitW != 0U &&
      (Config->GpuPowerLimitW < 50U || Config->GpuPowerLimitW > 1000U)) {
    return FALSE;
  }
  return TRUE;
}

BOOLEAN
EFIAPI
MeiMeiValidateCuConfig (
  IN CONST CU_CONFIG  *Config
  )
{
  UINTN  Bank;
  UINTN  Wgp;
  UINTN  Enabled;

  if (Config == NULL || Config->Version != MEIMEIDXEV3_CU_SCHEMA) {
    return FALSE;
  }
  if (Config->Mode != CU_UNLOCK_FACTORY &&
      Config->Mode != CU_UNLOCK_ALL &&
      Config->Mode != CU_UNLOCK_CUSTOM) {
    return FALSE;
  }
  if (Config->Mode != CU_UNLOCK_CUSTOM) {
    return TRUE;
  }
  for (Bank = 0; Bank < 4U; Bank++) {
    Enabled = 0;
    for (Wgp = 0; Wgp < 5U; Wgp++) {
      if (Config->Wgp[Bank * 5U + Wgp] != 0) {
        Enabled++;
      }
    }
    if (Enabled == 0U) {
      return FALSE;
    }
  }
  return TRUE;
}
