# AptAnimation AptCIH adoption: loader scheduling blocker

Date: 2026-11-05. Inspected base: `c1a5a2b848fc382bcfb6d7088dfe1886bd24bd1f`.
Claim owner: `yasinschroeder-codex5`. Model: gpt-6.1.

Target: retire the AptCIH/AptAnimation.cpp header-queue row using the existing
AptCIHClass.h, without changing any shared header. The automatic adopter refuses
an ambiguous `inst` field use; manual adoption replaces the private class with
the canonical include, uses `field4C` at the same +0x4C offset, and retains the
old assertions/callees through TU-local inline helpers. `candidate.patch` banks
the final four-helper trial only; it is not an applied source change.

All seven other ledger rows pass, including the action runner, interval timer,
removeTimerFunctions, and the loader's EH handler/funclets. The only failure is
`?rva006E5050@Rva006E58D0@@QAEXPAX00@Z`, RVA 0x006E5050, extent 2172 bytes.
The compiled body has the correct size and differs only at four byte positions:

- Retail +0xE6: `8b 5c 24 28 8b 6c 24 24` (load constant file into EBX, then base into EBP).
- Candidate +0xE6: `8b 6c 24 24 8b 5c 24 28` (same independent loads in reverse order).

`./build.sh Code/Libraries/Source/Apt/AptAnimation.cpp` was used for every
trial; no manual compiler/cache calls. The variants test the ledger's existing
code-order sensitivity note: static inline helpers; loader before pool methods;
canonical include/helpers after local class declarations; loader before that
late include; and restoring all four original helper call paths. None changes
the observed mismatch:

- `static-build.log`: target 2172 bytes, compiled 2172 bytes; differing offsets: 0xE7, 0xE9, 0xEB, 0xED.
- `loader-first-build.log`: target 2172 bytes, compiled 2172 bytes; differing offsets: 0xE7, 0xE9, 0xEB, 0xED.
- `late-header-build.log`: target 2172 bytes, compiled 2172 bytes; differing offsets: 0xE7, 0xE9, 0xEB, 0xED.
- `isolated-loader-build.log`: target 2172 bytes, compiled 2172 bytes; differing offsets: 0xE7, 0xE9, 0xEB, 0xED.
- `all-helpers-build.log`: target 2172 bytes, compiled 2172 bytes; differing offsets: 0xE7, 0xE9, 0xEB, 0xED.

Hypothesis: changed declaration/inlining inputs alter an MSVC 7.1 scheduling
tie-break. The byte difference proves instruction order, not that hypothesis.
Next useful check: isolate the declaration or original inline helper structure
that controls these two reloads, while keeping canonical class ownership. Do not
repeat the recorded order-only trials without a new hypothesis. No pin, alias,
flag, ledger or shared header change was attempted.

The full source was restored byte-for-byte from the pre-trial copy. A fresh
`./build.sh` then passed **8/8**, including the two funclets located despite
stale compiler labels; `find_declared_unmatched.py` passes. The header queue is
unchanged; no link preview or census gain is claimed. AptMiscObjects.cpp's
separate shared-root prerequisite remains LINK-197; the adopter's existing
slot0 refusal was reproduced without retaining a source change.
