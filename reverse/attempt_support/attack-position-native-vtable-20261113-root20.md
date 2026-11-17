# AttackPositionHordeStateMachine native table prerequisites

Inspected at `5f3deb924b5`. This is an unlanded diagnostic candidate. Production sources, rows, pins and tables remain unchanged; the owning bridge pass test is pending.

Retail RVA `0x00811CF0` has sixteen entries: `343BAD, B3FD0, 33FC04, 33FB0B, 4D7321, 4D72C5, 4D7A75, 4D770F, 4D7ACD, D43D0, D43D0, 2621B8, 4D7309, 4D7395, 4D750F, 4D73A4`. The following address `0x00811D30` holds the class-name string. The rowed constructor and destructor install the same table. Canonical StateMachine remains the base; no layout change is proposed.

The two installer views inherit StateMachine's name and transfer methods, but native slots 2/3 are subclass overrides. Slot 2 is the existing 6-byte literal getter at `0x0033FC04`, currently rowed as public nonvirtual `name() const` in SubsystemNameGetters4.cpp. The candidate spells protected virtual `GetSnapshotName() const`, matching the base API's constness. Slot 3 is the 21-byte fold at `0x0033FB0B`: `StateMachine::xfer(xfer); xfer->Version1();`. Existing Rva0033FB0B and DozerPrimaryStateMachine rows own that body. The candidate defines the subclass override alongside its existing destructor and declares both overrides in the constructor view.

Before: ordinary `./build.sh` passes 40/40 function rows across the three sources. Diagnostic `tu_skeleton.Verifier` passes 41/41 rows including the proposed transfer twin and respelled getter. Both compiler-emitted tables are 64 bytes, and all 16 slots match native when the two proposed names are provisionally bound to those exact RVAs. Slot 0 uses the compiler's weak vector-to-scalar deleting-destructor default, parsed from COFF. This is a conditional candidate proof, not admission of those bindings. Scratch preparation uses the existing BfmeXfer operand forward declarations; no shared header changed.

Two separate landing prerequisites remain:

1. `rename.py function --to-class AttackPositionHordeStateMachine` refuses the getter because it already belongs to that named class. This route only moves members from a different placeholder class. Ordinary inferred prepared respelling also faces the unresolved prepared-vote transaction fingerprint issue; the earlier parent-hash exception was unsound. No votes or gate exceptions were fabricated here.
2. `tu_ownership.check_ledger` refuses the proposed 21-byte row with A1: second row in Common/AttackPositionHordeStateMachine.cpp, owned by Common/VslotSmallBodiesAM.cpp. `add_match.py --icf-owner` does not exempt the real fold from this guard. Existing Dozer admission is evidence, not a current exemption. No row was written; no gen-alias, pin, whitelist or TU-placement workaround was attempted.

A tooling repair needs its own regression tests and Verifier-Change commit before this candidate is applied. Then use ordinary naming/admission, whole-cohort byte/EH checks, current-object slot checks and the next published real link's bridge verdict.

Latest completed authoritative run 43449493373 at c9d82e95: **38 unresolved, 0 duplicates, no image; 468 initializer bridges and 3,331 vtable bridges / 50,310 slots**. This attempt changes none of those figures.

Evidence: [proof and refusals](attack-position-native-vtable-20261113-root20/proof.json); three complete unlanded proposed source texts in that directory. Independent native reviewer confirmed the table and A1 refusal. t=25min model=gpt-6.1-sol.


## Follow-up at 768d86245d4 (2026-11-17)

No repeated candidate compilation or production edit. `find_declared_unmatched` reports all defined functions already matched. The table remains bridged with the same slot-2/3 provider differences.

The first historical blocker changed: commit `1a526d9f623` admits precisely the same-class getter respell to `?GetSnapshotName@AttackPositionHordeStateMachine@@MBEPBDXZ`. Current `--to-class` additionally requires a committed registered canonical class header, approved slot-2 declaration, and explicit approval base. This class has neither registration nor slot approval. That supported path is separate from the still-closed prepared-source fingerprint checks.

The second blocker did not change: `tu_ownership.py` A1 still rejects a second source row at the transfer fold, and `--icf-owner` provides no exemption. The owning rename also refuses the shared body as a unique class move. Current `tu_map` calls the transfer destination proposed, not approved; it authorizes no move or consolidation. The newer class-fold getter proof does not establish unique ownership of this multi-table body.

A read-only independent tool-history review confirmed these facts. Full table recovery still requires supported transfer-fold admission or independently proven approved consolidation, as well as proper getter approval. Existing conditional byte evidence is retained, not reported as current admission. No source, ledger, header, queue or bridge changed. The obstacle-register file is held by another worker, so this follow-up updates its already-linked handoff instead of editing that worker's file.

Latest completed authoritative run observed is 317 at `e3eaacd49dbcbda37c703f6561e9ca1f3d9aef85`: **11 unresolved, 0 duplicates, no image; 468 initializer bridges and 3,118 vtable bridges / 45,938 slots**. Run 318 is still in progress; neither result supplies a retirement claim here. t=12min model=GPT-6.
