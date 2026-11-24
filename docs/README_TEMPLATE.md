# Driver README template

Every driver README uses this shape. Facts that belong to the shared contract are
linked, never copied: the SMU map, the configuration structs, the variable names,
and the protocol ABI have one owner each.

Rules:

- No branch names, merge state, or "current work" notes. Those belong in git.
- Do not repeat the SMU SRAM table or the configuration struct definitions.
  Link `BC250-DXEv3-Shared/docs/SMU_MEMORY_MAP.md` and the shared config header.
- List the driver's own Depex and the protocols it produces and consumes.
- State the fail-closed behavior: what happens when the variable is missing,
  undersized, malformed, wrong-attribute, or disabled.
- Validation must be dated and must distinguish the configured ceiling from the
  actual clock. Link `COMPLIANCE.md` instead of repeating the checklist.
- Code examples use the shared macros and validate attributes; do not teach
  local GUID literals or local struct copies.

---

# <Driver name>

<One paragraph: what it does, which problem it solves, and which firmware it
targets.>

> **Firmware warning:** <only for drivers that write SMU SRAM or AVFS state:
> a bad write can require a cold power cycle; test with a recovery path.>

## At a glance

| Item | Value |
| --- | --- |
| Package / module | `<Pkg>/<Module>.inf` -> `<Artifact>.efi` |
| Depex | `<GUID list>` |
| Produces | `<protocol(s), or "no protocol">` |
| Consumes | `<protocols, variables, shared package>` |
| Configuration | `<VariableName>`, `<N>` bytes |
| SMU SRAM | `<lane from the shared map, or "none">` |
| Compliance | [COMPLIANCE.md](COMPLIANCE.md) |

## Dependencies

<What must run or exist first, and why. Name the Depex GUIDs and the shared
package. Do not describe dispatch order without the Depex that enforces it.>

## How it works

<The mechanism, with the existing ASCII diagram. This is the part worth keeping
detailed: registers, hook sites, payload behavior, learning flow.>

## Configuration

<Link the shared header:
`BC250-DXEv3-Shared/MeiMeiDXEv3SharedPkg/Include/Config/MeiMeiDXEv3Config.h`.
Inline only records this driver owns (learning records, baseline records).
Describe validation: size, schema, attribute, range, and the disabled path.>

## Protocols

<For each protocol produced: GUID symbol, header, methods, and the exact
EFI_NOT_FOUND / error semantics. For consumed protocols, show one short lookup
snippet using the shared headers. Omit this section only if the driver neither
produces nor consumes a protocol.>

## SMU SRAM placement

<One line with this driver's lane from the canonical map, then:
See [SMU_MEMORY_MAP.md](https://github.com/RescueMei/BC250-DXEv3-Shared/blob/main/docs/SMU_MEMORY_MAP.md).
Mention any `STATIC_ASSERT`s that pin the lane and that images are 4-byte
aligned. Never paste the whole family table.>

## Build

<Pre-build hooks, container build, host fallback, output artifacts.>

## Validation

<Dated integrated result: deployment result, configured ceiling, actual clock,
voltage, power, temperature, ring/C2P counters, reachability. Then link
COMPLIANCE.md for the checklist.>

## Credits

<Only when the driver is based on someone else's work.>
