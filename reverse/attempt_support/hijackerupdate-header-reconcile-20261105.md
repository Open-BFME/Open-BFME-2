# HijackerUpdate declaration environment reconciliation

Inspected revision: `fb4a477fdd` (2026-11-05).

The original six-row TU's Zero Hour header environment conflicts with the
canonical declarations used by its approved donors. Current baseline dry-run
accepted no donors: Xfer and SubsystemInterface are redefined; the ctor and
update donor views also disagree with the seed's class environment.

Replace those broad includes with the canonical UpdateModule, Coord3D and
GameLogic lookup headers and a TU-local HijackerUpdate declaration. The target
ID and flag offsets are constrained by the existing matched methods (+0x20,
+0x30/+0x31), and UpdateModule's canonical contract establishes the 0x20 base.
The local Object prefix only exposes the already-used ID at +0x74. Existing
function bodies, source ownership, pins and aliases are retained. Zero Hour
continues to supply method/field spellings; no new BFME2 path or identity is
asserted. The opaque ctor vtable model is not adopted into this declaration.

Checks:

- Original and result `./build.sh HijackerUpdate.cpp`: all six rows exact;
  literal, float and import checks pass.
- `find_declared_unmatched.py`: all definitions matched, with the same two
  absent-from-retail emission anchors.
- `link_check.py --prepare-current HijackerUpdate.cpp`: strict reusable receipt
  accepted after a retry when concurrent scratch composition invalidated the
  first preparation snapshot.
- Current-object `link_check.py` for seed, Xfer, PoolKey, Ctor and Update:
  all five link, 672/672 own bytes, against the published 2026-11-05 05:17
  census at `c95fcfcfcd`. This is a prediction, not a new census.
- Merge dry-run now accepts Xfer and PoolKey (two removable donors, ten total
  resulting rows), passing its current-object link guard. Ctor still requires
  replacing its opaque vptr stores; Update still needs class/interface
  reconciliation. Neither donor was edited. Header-queue rows for those two
  residuals remain owned by their original paths.

The next action is the supported tu_skeleton merge of the two accepted donors,
then byte/EH/link and path-consumer verification. No debt retirement is claimed.
