# Read-only BW filter object investigation, 2026-11-01

No Code, ledger, claims, build receipts, commits or remote state changed.

## Target facts

`native.json` comes from retail game.dat through build.read_target_bytes. The two globals have eight-byte candidate extents: DB5B54={BCF364,0} and DB5B5C={BCF380,0}. Native constructors FBA4A and FC59D each zero +4 and install the corresponding table (13 bytes each). Both constructors already have rows in Common/RvaSmallVtableCtors.cpp under neutral class identities. Their current emitted one-destructor tables are deliberately incomplete native-table models and cannot own these globals safely.

Both native tables contain seven slots. BW: init FB9D4, shutdown FC903, prerender FBA0F, postrender FBA57, setup 5CB9FA, set FBC67, reset FC8B4. DOT3: init FBA20, shutdown 910FB, prerender FBA0F, postrender FC04C, setup 5CB9FA, set FC34F, reset FD551. Both tables are followed by proven boundaries (next table at BCF380; string bytes at BCF39C). The data ledger's128-byte first-table extent and52-byte global interval are inferred overestimates, not object boundaries.

Native absolute references to each object are its already-rowed init registration and a pointer-list element at DB4364/DB4368. Vtable address references are each object's initialized first word and the corresponding13-byte ctor operand. A full .text raw E8/E9 target scan finds no direct branch to either ctor; this is a limited scan, not proof of total ctor unreachability or original initialization syntax.

## Separate donor facts

The committed BFME1 reference includes the pristine Zero Hour header at inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DShaderManager.h. It declares a seven-slot W3DFilterInterface (no virtual destructor), ScreenBWFilter with one DWORD shader handle, and ScreenBWFilterDOT3 deriving ScreenBWFilter without additional fields. The recovered BFME1 W3DShaderManager.cpp defines both globals. This corroborates8-byte shape and names; it does not prove BFME2 source ownership. BFME2 postRender has a fourth stack argument absent from the donor signature, so copying the header verbatim is incorrect.

## Existing providers and prerequisites

Only init and BW set currently use the ScreenBWFilter identities. The other slots are real matched bodies with inconsistent neutral owners:

- shutdownFC903: BfmeThingDF::bfmeDropDF; trivial DOT3 shutdown910FB is an ICF shared four-byte return-one owner.
- prerenderFBA0F: Rva000FBA0F::rva000FBA0F, nonvirtual typed view.
- BW postrenderFBA57: Rva000FBA4A::rva000FBA57, four-word ABI.
- DOT3 postrenderFC04C and setFC34F: Rva000FC34FFilter.
- resetFC8B4: Rva000FC63DFilter, shared with a different native table at BCF3C8.
- DOT3 resetFD551: Rva000FBA4ASecondary.
- setup5CB9FA: shared ICF true-return body with ret4.

A safe global recovery therefore needs native identity/class-view reconciliation and proper ICF membership evidence, not fabricated7-slot arrays, aliases or extra pins. Preserve already-owned providers and use the naming application/review machinery where shared names need approval. The ctor rows must also be reconciled; otherwise the same vtable identity remains inconsistently emitted by an unrelated one-destructor view. Strict data checking must prove the emitted8-byte objects and all fourteen table relocations before ownership admission. No simple independent global-only change is established by this investigation.
