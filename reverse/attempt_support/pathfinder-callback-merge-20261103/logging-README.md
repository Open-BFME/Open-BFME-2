# AIPathfind stdio debt: native game-helper blocker, zero new header trials

Verdict: standard `<stdio.h>`/FILE* adoption is inapplicable to these five logging calls. Their native target is the game's matched format-and-append helper at RVA2CEC42, not CRT fprintf, an import thunk, or an IAT slot. Main explicitly stopped the planned CRT-configuration experiments after this target check. No new control, header, /MT or _CRTIMP trial was compiled; no macro/compiler configuration is proposed for landing.

## Target instruction facts

The parent is the341-byte row `?rva002F6F90@Rva002F6F90Context@@QAE_NIH@Z` at RVA2F6F90. The parent-supplied frozen normally verified declaration-inputs/seed.obj has five `_fprintf` REL32 relocations. At every corresponding retail instruction the opcode is direct E8 and the signed rel32 resolves to the SAME RVA2CEC42:

| Instruction RVA | Parent relocation offset | Native five instruction bytes | Target RVA |
|---|---:|---|---|
| 0x2f6fb8 | 41 | `e8857cfdff` | 0x2cec42 |
| 0x2f7015 | 134 | `e8287cfdff` | 0x2cec42 |
| 0x2f7066 | 215 | `e8d77bfdff` | 0x2cec42 |
| 0x2f708d | 254 | `e8b07bfdff` | 0x2cec42 |
| 0x2f70d4 | 325 | `e8697bfdff` | 0x2cec42 |

No site calls through a dllimport pointer. The target is in-image code, not an import slot. These per-body facts were established before considering a standard-header replacement, as required by docs/matching.md's Microsoft-header lane.

## Existing owner/signature facts

The narrow function ledger names `_fprintf`, matched108B at RVA2CEC42, owned by `Code/GameEngine/Source/Common/FprintfAppendLine.cpp`; the same owner has its compiler EH handler at RVA7771E9/10B. That current owner source was read in full. It explicitly distinguishes CRT stdio in namespace NativeFormatCrt from its game helper:

- The game helper's current matched declaration/body is `extern "C" void fprintf(FprintfTarget *target, const char *format, ...)`.
- A null format returns; otherwise it formats varargs via the genuine CRT _vsnprintf into a1000-byte local buffer, constructs an AsciiString and appends it through vector<AsciiString>::push_back to the target object's vector at+4.
- The owner's first4-byte target field remains unproved padding. FprintfTarget is the existing reconstruction's view, not a recovered original class name. This packet supplies no invented replacement identity or owner name.

The seed's hand declaration instead says INT return and uses opaque PathfinderLogFile*. Its calls ignore the return value. Their stack/varargs call bytes can therefore match despite that return-type mismatch; equality of bytes would not make FILE* or CRT's return signature an accurate description of the game API. The unresolved cohort is existing game-helper naming/ABI and callers, not standard-header retirement.

## Why the proposed configuration trials were stopped

The earlier root-owned real-stdio /MD negative (`build/core-header-proof/stdio-proof.json`) loses only F6F90. tools/ms_header_audit.py models `_CRTIMP` as a header configuration input and explicitly requires per-body checks for /MD dllimport conflicts. That supported macro model is not evidence that this target is CRT fprintf. Empty _CRTIMP or static-CRT configuration could restore a direct symbol spelling while attaching FILE* to the wrong native API; such a byte-only result would not justify retiring this debt. No header-configuration escape or forced import configuration is proposed.

Since the per-body target proves inapplicability and main canceled further trials, .drectve DEFAULTLIB/import deltas were NOT measured for new configurations. No hypothetical link-impact claim is made. Any separate repair should first establish the existing owner/caller identity and consistent ABI through the guarded naming/ownership workflow, then verify all affected consumers and refresh the owning ms-header queue on its actual verdict. Do not erase fprintf:abi by installing stdio declarations, changing runtime flags or suppressing the finding.

Evidence: native-callees.json contains each original relocation offset/type, native instruction and resolved target. Existing owner/source and ledger facts were read-only; no Code/ledger/Git-index edits, claims, network, normal build/cache write or new compiler trial occurred. Tracked reads stopped.
