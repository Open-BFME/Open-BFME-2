# WWMath processor-profile follow-up, 2026-11-04

Revision inspected: e14a51cef5. No source, compiler override, ledger, placement
approval or provider change is retained. No source-file or linking gain is claimed.

The current supported merge dry run still accepts no donor and rejects
`WWLib/wwmath.cpp` with `bytes`; both original units are census-linked.
`WWMathInit.cpp` remains mixed and outside this attempted merge.

The new hypothesis was that older processor tuning could select the native
`xor eax,eax; inc eax` true return while retaining the random helper's frameless
stack scratch. The attached [probe](probe.py) uses `tu_skeleton.Verifier` with
explicit flags and its private scratch objects, never manual compilation into
`build/match`. [Results](probe.log):

| Explicit profile | Exact rows | Remaining failure |
| --- | --- | --- |
| O2 / G5 / SSE / MD | 7/8 | areApproxEqual |
| O2 / G6 / SSE / MD | 7/8 | areApproxEqual |
| O1 / G5 / SSE / MD / Ot | 7/8 | areApproxEqual |

All three preserve `Random_Float` and the six wrappers. A standalone
`FLAG_DEFAULTS=off ./build.sh Code/Libraries/Source/WWVegas/WWMath/wwmath.cpp`
under O2/G6/SSE/MD/Oi also confirms the existing 42-byte/44-byte boundary:
retail's true branch is `33 c0 40 c3`, while this profile emits
`b8 01 00 00 00 c3`. The two preceding conditional branch distances grow
accordingly.

An initial ordinary build with those flags written in `// cl:` passed 7/7,
but that was not a processor-profile test: tool-owned region defaults replace
managed flags unless explicitly disabled or admitted as an override. That
result must not be taken as evidence for G6. No override admission was attempted.

After restoring the original source, ordinary `./build.sh` on both files passes
8/8 rows, one float reference and one import reference.
`find_declared_unmatched.py` reports all definitions matched. The next step
remains the common-profile C++ reconstruction described in the
[existing handoff](../wwmath-common-profile-20261103/README.md). The obstacle's
status and next step did not change, so its register entry is left unchanged.
