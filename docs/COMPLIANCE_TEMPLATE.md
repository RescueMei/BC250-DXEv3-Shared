# <Driver> Compliance

Use this checklist for every driver before merge. Do not replace it with prose
in the README.

- [ ] Shared package version/pin recorded.
- [ ] Configuration structs/constants come from the shared package; no local duplicates.
- [ ] Public protocol copies match the provider ABI; drift check passed.
- [ ] Driver-owned variable names/layouts are documented.
- [ ] SMU SRAM allocations match `SMU_MEMORY_MAP.md`; no overlap. (SMU-touching drivers only; omit otherwise.)
- [ ] Depex is correct; public protocol is installed unconditionally.
- [ ] Feature-disabled path performs no feature writes.
- [ ] Missing/malformed config is rejected safely; boot continues.
- [ ] Factory learning still occurs when the feature is disabled (Core/CU).
- [ ] No cross-driver private headers or internal functions.
- [ ] No forced-VID/force-state from SMU tick context. (SMU-touching drivers only.)
- [ ] SMU writes are read-back verified; reserved fields preserved. (SMU-touching drivers only.)
- [ ] Payload is 4-byte aligned, fits its lane, and was injection-tested. (Payload drivers only.)
- [ ] Individual driver build passed.
- [ ] Eight-driver integrated build passed.
- [ ] BC250 deployment reached `DEPLOY_OK` with expected state.
- [ ] Light and heavy workload validation completed, including actual clock and thermal checks.
- [ ] No generated payload headers, build output, secrets, or temporary files staged.
