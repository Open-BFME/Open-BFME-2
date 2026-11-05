# Four FX draw-info transfer providers

Base: `9210ba89eff7dc2d743c28ff60e6c96c0e5b42f5`. Scope:
`Code/GameEngine/Source/GameClient/FXParticleSystem.cpp`, prerequisite work
for LINK-098 and the DefaultDraw table issue in LINK-006.

## Target evidence

Retail exports identify `DoXfer(Xfer &)` for ButterflyDrawModuleInfo (1160),
DefaultDrawModuleInfo (1163), QuadDrawModuleInfo (1172), and
StreakDrawModuleInfo (1175), all at RVA `00306A9B`, extent 12 bytes.
Their existing native constructors install the tables recorded in
[native.txt](native.txt). Each table has destructor, post-load, name getter,
and transfer slots in that order. The transfer body is
`8b4c2404 e84ae9cfff c20400`: load the argument, call Version1, return.
These are target facts; no external donor names or layouts are asserted.

Each exported member now has a complete C++ body calling the canonical
`Xfer::Version1`. Four `add_match.py --icf-owner` admissions verified the
bytes and call relocation against the existing Xfer.cpp owner. The rows
are explicit `gen-alias` ICF twins with `fold-proof` naming that owner;
they claim no additional address coverage. No pins, alternatenames, data
identities, source moves, or debt retirements were added.

## Verification

- [Final build](build-final.log): 377/377 function checks, the data row,
  17 strings and 10 floats pass. The ledger has 378 rows because of aliases.
- `tools/check_csv.py`: 99,467 function rows pass.
- `tools/find_declared_unmatched.py`: all defined functions matched;
  the five existing unclaimed-definition notes remain.
- [Pin consistency](pins.log): no new or stale findings.
- [EH check](eh.log): no non-exact or missing-object rows.
- [Ordinary link preview](link-final.log), published index `c95fcfcfcd`:
  FXParticleSystem and Xfer retain LINKS, 7,860 -> 7,860 bytes combined.
  T1Base005F3750Ctor remains nonlinking, 0 -> 0 bytes, with the existing
  DefaultDraw vtable COMDAT disagreement. The preview exits 1 for that
  known obstacle. This is no census or real-link improvement claim.

## Remaining prerequisites

The four first-emitter draw-info tables now include the native transfer
slot. Their post-load slot still uses the existing pure `v1` declaration;
the exported empty body at B3FD0 was held by another worker and was not
edited. Reconcile that slot and the other emitting views before retrying
the T1 family. RenderObjectDraw/LifeEvent transfer signatures and their
providers also need reconciliation before removing the private Snapshot
base. The owning header acceptance tool still refuses the private FX
Snapshot view; neither queued Snapshot row is retired by this change.

The MoneyVectorPushBack queue entry also remains: owning acceptance
requires its header include, while the current source no longer uses a
Snapshot view. No unrelated source or queue change was attempted.
