# BC250-DXEv3-Shared

Shared EDK2 package for the BC250 DXEv3 driver family.

Contents:

- canonical configuration ABI and defaults
- canonical SMU SRAM allocation map
- shared HII question IDs
- `MeiMeiConfigLib` read/default/validation helpers
- compliance checklist template and protocol ABI check

Consumers add this repository as a submodule and include
`MeiMeiDXEv3SharedPkg/MeiMeiDXEv3SharedPkg.dec` in their build.
