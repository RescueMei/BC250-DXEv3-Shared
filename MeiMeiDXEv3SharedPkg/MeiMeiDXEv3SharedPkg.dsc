## @file
#  Build description for the shared package.
##
[Defines]
  PLATFORM_NAME                  = MeiMeiDXEv3SharedPkg
  PLATFORM_GUID                  = 5c5c2b5a-ded5-4dea-a8bf-7d25dc23c523
  PLATFORM_VERSION               = 1.0
  DSC_SPECIFICATION              = 0x0001001A
  OUTPUT_DIRECTORY               = Build/MeiMeiDXEv3SharedPkg
  SUPPORTED_ARCHITECTURES        = X64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

[Packages]
  MdePkg/MdePkg.dec
  MeiMeiDXEv3SharedPkg/MeiMeiDXEv3SharedPkg.dec

[LibraryClasses]
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf

[Components]
