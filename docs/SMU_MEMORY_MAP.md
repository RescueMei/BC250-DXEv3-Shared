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
