### LINK-242: ActiveBody-derived vtables need unrowed ActiveBody slot providers
Status: Blocked (naming rules and a rename.py false reject). Updated: 2026-11-04; inspected revision: 49dfd905bf.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/Object/Body/PorcupineFormationBody.cpp`
defines PorcupineFormationBodyModule's constructor, so it emits the class vtables, and their
inherited ActiveBody slots reference three symbols nothing defines:
`?GetSnapshotName@ActiveBody@@UBEPBDXZ` (retail slot 2 of 0x00C5B038 is 0x004BF88D, rowed as the
non-virtual `?name@ActiveBody@@QBEPBDXZ`), `?Rva004BE67E@ActiveBody@@UBE?AVAsciiString@@XZ`
(0x004BE67E is rowed as `?Rva004BE67E@DetachableRiderBody@@UBE?AVAsciiString@@XZ`) and
`?applyDamageScalar@ActiveBody@@UAEXM@Z` (declared in `GameLogic/Module/ActiveBody.h`, no row).
`tu_skeleton.py --merge ... --dry-run` (index 2026-11-04 16:16 at 2f0cb97f52) compiles and
byte-matches all three donors (PorcupineFormationBodyModuleSlots.cpp,
...ModuleRva004C21A9.cpp, ...ModuleSlots_AttemptDamage.cpp) and rejects each only because those
census-linked donors would join an object with these unresolved references. The same gap applies
to any unit that emits an ActiveBody-derived vtable.
Completed: the TU's PorcupineFormationBodyModule and its ModuleData views were reconciled with the
donors (two commits ending at 49dfd905bf); every row still byte-matches.
Remaining / next check: give the three slots their providers without a second name on one address:
rename the 0x004BF88D row to the virtual GetSnapshotName (its existing non-virtual `name()` callers
need a qualified-call spelling), decide whether 0x004BE67E's owner is ActiveBody (the body-interface
table 0x00C5B5B0 is not in `vftable_map.py`'s output), and find applyDamageScalar's address. Then
re-run the dry run; the merge removes three files.
Clearance: pending.
Census confirmation: not claimed.

2026-11-04 (revision c7d8498c81), retail tables read from game.dat:

- Slot 26, `applyDamageScalar`: BodyModule's own body-interface table 0x00C5AC18 (installed by
  ctor 0x004BD7FD) holds 0x004BD77C; its BodyModuleInterface base table 0x00C5AB68 has
  `_purecall` there. ActiveBody 0x00C5B5B0 and PorcupineFormationBodyModule 0x00C5C318 inherit
  the same entry. So the row `?multiply@Rva004BD77CFloatField@@QAEXM@Z` is
  `BodyModule::applyDamageScalar` (Zero Hour's BodyModule inline), and ActiveBody.h's
  `applyDamageScalar` override is phantom. `rename.py function --rva 0x004BD77C --to-class
  BodyModule --new applyDamageScalar` with prepared BodyModuleCtor.cpp, BodyModuleClass.h (the
  override) and ActiveBody.h (the phantom removed) refuses: HighlanderBody, ImmortalBody and
  SymbioticStructuresBody tables hold the address too and their views declare no BodyModule base.
  Recorded as a false reject in `reverse/re_attempts.log` (tooling seat: the relatedness test
  should follow retail's own installer table, or those views must declare their real bases).
- Slot 28, `Rva004BE67E`: BodyModule's 0x00C5AC18 has `_purecall`; ActiveBody's 0x00C5B5B0 holds
  0x004BE67E, as do DetachableRiderBody's and Porcupine's tables. The owner is ActiveBody; the row is
  spelled under DetachableRiderBody. No rename.py mode moves a row between two real classes
  (`--to-class` needs a placeholder class), so this needs a tool mode or a maintainer decision.
- Slot 2, `GetSnapshotName`: ActiveBody's primary table 0x00C5B038 slot 2 is 0x004BF88D, rowed
  `?name@ActiveBody@@QBEPBDXZ` by the BFME_LITERAL_NAME_GETTER macro in
  Common/ModuleNameGetters.cpp. `rename.py` refuses to replace `name` (an unrecorded real name,
  which neither canonical nor inferred evidence may replace), and `--virtual` refuses because
  the macro hides the declaration. Vtable-slot evidence is only a hint under docs/naming.md, so
  this needs a maintainer decision on correcting an unrecorded agent label.

Next check once the three providers exist: `tu_skeleton.py --merge
Code/GameEngine/Source/GameLogic/Object/Body/PorcupineFormationBody.cpp --dry-run` (compile and
bytes already pass for all three donors).

2026-11-13 (revision 196c1cae97), real-link regression from adopting ActiveBody.h in an installer:

- 922e561591 registered a canonical HighlanderBody (`HighlanderBodyClass.h`, over ActiveBody.h) and
  adopted it in HighlanderBody.cpp, which defines the constructor and so emits the class's tables.
  The real link measured at 10efe4859e lists that unit with 35 missing names
  (`reverse/exit_link_blockers.tsv`; the two measures before list only the 2 unowned exports), and
  `link_check.py` on it gives LINKED 241 -> 0 with the same 35.
- An exact revert builds 319/319 over the three units and links 3 of 3 (241 -> 241), but
  `class_gate.py --staged` refuses it as a new private `ActiveBody` copy. Not landed; steps and
  measurements in `reverse/attempt_support/highlanderbody-adoption-revert-class-gate-20261113.md`.
- For the adoption lane until the slots move: a unit that defines a constructor or destructor of an
  ActiveBody subclass must not take ActiveBody.h, directly or through a subclass header. Run
  `link_check.py` on the adopting units; the byte gate passes either way.
