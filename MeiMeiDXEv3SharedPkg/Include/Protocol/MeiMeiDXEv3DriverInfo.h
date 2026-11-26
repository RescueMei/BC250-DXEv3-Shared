/** @file
  Driver identity and version record, installed by every DXEv3 DXE driver.

  The record is published as an EFI_NATIVE_INTERFACE protocol and points at a
  static const structure; there are no methods. A consumer enumerates handles
  with the protocol GUID and reads each record after checking Revision/Size.
**/

#ifndef MEIMEIDXEV3_DRIVER_INFO_H_
#define MEIMEIDXEV3_DRIVER_INFO_H_

#include <Uefi/UefiBaseType.h>

#define MEIMEIDXEV3_DRIVER_INFO_REVISION  1U
#define MEIMEIDXEV3_DRIVER_NAME_MAX       24U

//
// Version is 0xMMmmpp: major, minor, patch.
//
#define MEIMEIDXEV3_MAKE_VERSION(major, minor, patch) \
  ((UINT32) ((((major) & 0xFFU) << 16) | (((minor) & 0xFFU) << 8) | ((patch) & 0xFFU)))

#define MEIMEIDXEV3_DRIVER_CAP_CONFIG     0x00000001U
#define MEIMEIDXEV3_DRIVER_CAP_PAYLOAD    0x00000002U

typedef struct {
  UINT32    Revision;
  UINT32    Size;
  CHAR16    Name[MEIMEIDXEV3_DRIVER_NAME_MAX];
  UINT32    Version;
  EFI_GUID  DriverGuid;
  UINT16    ConfigSchema;
  UINT16    PayloadVersion;
  UINT32    Capabilities;
} MEIMEIDXEV3_DRIVER_INFO;

#endif // MEIMEIDXEV3_DRIVER_INFO_H_
