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

## Protocol ABI check

`tools/check_protocol_abi.py` compares consumer copies of provider-owned
protocol headers against the provider ABI. Comments and whitespace are ignored;
any declaration change fails.

Each manifest entry names the provider header and the consumer copies. A
standalone driver repository does not contain sibling provider checkouts, so
entries also carry `provider_sha256`, the SHA-256 of the normalized provider
header. When the provider file is present the recorded hash is re-verified, so a
provider change without a manifest update fails.

- `tools/protocols.json` is the family-wide manifest. Its paths are relative to
  the `BC250-DXEv3-BIOSMOD` integration checkout, where every driver submodule
  is present; the integrated build runs this check.
- Each consumer driver carries a small repo-root `protocols.json` covering only
  its own vendored copies. Its build runs the checker against that manifest.

Both manifests must be updated in the same change when a provider ABI changes.
