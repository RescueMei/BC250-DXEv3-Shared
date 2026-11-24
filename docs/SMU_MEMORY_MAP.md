# BC250 DXEv3 SMU SRAM Map

This is the canonical allocation map. Every driver that owns SMU SRAM must use
these constants and stay inside its reserved span. Reserving the full span is
intentional; do not shrink a span without checking every consumer.

| Base | Max size | End | Owner |
| --- | --- | --- | --- |
| `0x3AE00` | `0x1200` | `0x3C000` | SMU Patch payload |
| `0x3C000` | `0x0400` | `0x3C400` | CU Unlock payload |
| `0x3C400` | `0x0200` | `0x3C600` | CU Unlock save/stack/state |
| `0x3C600` | `0x0A00` | `0x3D000` | SMU Governor state |
| `0x3D000` | `0x1000` | `0x3E000` | SMU Governor payload |
| `0x3E000` | — | — | SMU firmware; do not use |

All payload images must be 4-byte aligned. The injector copies full dwords;
an unaligned image is truncated and can wedge the SMU.

Regions not listed here are not available. A new allocation requires a shared
map change, overlap check, and validation on the BC250.

## Firmware cache-maintenance registers

These are firmware state, not allocations. SMU Patch and CU Unlock use the
SMU's own cache-publish path so injected SRAM writes become visible, and they
save/restore these values around every publish. Never use them as scratch or
payload space.

| Address | Use |
| --- | --- |
| `0x184F8` | cache helper entry (call target) |
| `0x3FFBC` | cache publish flag |
| `0x3FFF0` | cache publish mask |

The map header exposes them as `MEIMEIDXEV3_SMU_CACHE_CB_ADDR`,
`MEIMEIDXEV3_SMU_CACHE_FLAG_ADDR`, and `MEIMEIDXEV3_SMU_CACHE_MASK_ADDR`.
