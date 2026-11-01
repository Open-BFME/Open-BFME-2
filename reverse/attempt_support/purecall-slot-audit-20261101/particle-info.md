# Particle-info false-pure repair

Base: `42ba5fba3d67de6fd90e938e491169eea70fd6d2`.
Seat: `halilkkaya-codex`; all source changes confined to wt_d.

Retail image facts: RVA 0081D358 slot 1 and RVA 0081D348 slot 1 both
contain VA 004B3FD0 (RVA 000B3FD0), the shared one-byte RET. The old
Rva0056224FCtor.cpp object emitted __purecall for both. The first table is
Rva0056224F's; the second belongs to its +0xC subobject in Rva00562366.
The inherited Snapshot header establishes the slot's loadPostProcess name;
no new original-name or class-identity claim is made.

The protected empty override now emits
`?loadPostProcess@Rva0056224F@@MAEXXZ` and both tables reference it. Its
entire body is C3 with no relocations. add_match.py admitted the real C++
override with --icf-owner ?loadPostProcess@BehaviorModule@@MAEXXZ and its
owning source as fold-proof; no pin, linker alias or generated body was added.
The fold adds zero unique retail bytes.

Remaining false-pure entries, all unchanged:

| Table RVA | Slot | Native target RVA | Prerequisite |
| --- | --- | --- | --- |
| 0081D358 | 2 | 003AE26A | Current row is a cdecl int getter in ConstIntGetters4.cpp, held by StarkillerHDX; reconcile the owner and actual Snapshot getter profile. |
| 0081D358 | 3 | 005622A6 | The transfer body belongs to the separate Rva005622A6 placeholder; owner/signature reconciliation is required. |
| 0081D348 | 2 | 003ACAFA | Derived getter has another placeholder owner; actual Snapshot getter profile is required. |
| 0081D348 | 3 | 003ACB00 | Existing adjusted transfer row names Rva0056234A, not this derived view. |

[Per-slot native targets and row lookup](particle-info.tsv) retain the
pre-change targets and actual post-change object relocations. Other concrete
slots are inventoried, not certified by this bounded repair. Existing
BoxEmissionVolumeInfo comments based on a folded destructor do not establish
this class's identity; native slot-2 getter says RenderObjectParticleUpdateModuleInfo.

Verification:

- Initial foreground ./build.sh: all 99,276 rows and 2,253 data rows pass;
  FULL GATE OK.
- ./build.sh Rva0056224FCtor.cpp: 8/8 exact, including the new folded row;
  frozen-file check clean. Existing funclets verify through their parent EH graph.
- link_check.py --prepare-current on the constructor and
  ModuleTemplateCloneSlots.cpp: 13/13 exact, strict reusable receipts.
- Ordinary link_check.py on those two units, index 86db074988 (2026-11-01
  14:31): both LINKS; constructor 480 -> 481, factory 356 -> 356. Before
  this change their current-object total was 836, after 837; no unit loses
  bytes. The extra counted byte is the shared RET, not new unique coverage.
- Commit hook passes. Its TU-ownership shadow reports A1 for the shared
  B3FD0 row in this source (original owner region.cpp); no ownership-debt
  retirement is claimed. Code identity reports zero new findings.
- COFF object SHA256 after strict preparation:
  213fe707223bace2c940f26e6bec32ee2f537acd7a00ff82490fbeddf09e2cc8.

Only the scheduler's next census and maintainer-run game tests can establish
global linking/runtime effects. No runtime test or publication was run here.
