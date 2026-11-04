# AutoPickUpUpdate vector consolidation, 2026-11-04

Preparation: `72421c5dfa` replaces the declaration-only STLport vector view
with the real template, using the donor's allocation/exception policy and
unit-local unsigned `max`. `tu_views.py` reconciled `AutoPickUpEatObjectEntry`
in the two inputs; both inputs passed their ordinary byte gates before merging.

The refreshed `name_lane.py consolidate --under
Code/GameEngine/Source/GameLogic/Object/Update/` report separates the retail
path string at RVA `0x0084F0A0` from donor and structural hints. The merge
uses the current in-memory TU map's approved assignments, not those hints.
`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/AutoPickUpUpdate.cpp`
accepted the existing TU and
`Code/Libraries/Source/WWVegas/WWLib/stlport_vector_autopickup_eat_entry.cpp`.
It moved two rows (RVA `0x0049639F`, 193 bytes; `0x004964BB`, 52 bytes),
repointed their function/TU-map source fields and the `_M_clear` fold proof,
and removed one source file. The destination now owns 31 rows.

Verification:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/AutoPickUpUpdate.cpp`:
  31/31 matched; 11 string literals, two float literals and one import verified.
- `find_declared_unmatched.py`: all defined functions already matched.
- `eh_verify.py`: four EH graphs, all EXACT. Converged `data_check.py`:
  11 addresses, no second names or unjudged rows. `check_csv.py` and staged
  `tu_ownership.py` pass.
- Comparing the saved, verified pre-merge objects with the merged object:
  all 149 COMDAT names, normalized digests and sizes are identical to the
  input union. All 121 external code providers, 28 external data providers,
  two static data names and seven weak-external routes remain. External
  provider needs after subtracting locally supplied definitions stay at 52,
  with no additions or removals.
- `link_check.py` predicts LINKS for the merged TU (2,318 bytes), module-data
  constructor (159 bytes) and destructor (146 bytes), totaling 2,623 bytes.
  The vector donor's 245 bytes are inherited by the main TU; this is no
  increase in total linked coverage and no census gain is claimed.
- `link_check.py --prepare-current` then byte-verified the main TU with a
  strict reusable receipt, without changing census/index/status.
- The outgoing-tree `link_batch_audit.py` remains INCONCLUSIVE: its index
  is at `40fe1783d7`, older than the outgoing base, and affected consumer
  `Code/GameEngine/Source/Common/AIBaseBuilder.cpp` lacks a current receipt.
  Carry this TU, its absorbed vector donor and that consumer into the next
  scheduled census; the broader consumer scope is not verified here.
- Staged code identity remains shadow: five findings (the existing
  `destroyRange` binding, divergent Object getters and duplicate displacement
  getters). The preparation's separate overflow-binding finding disappears
  when its real provider is in this TU; no register key is retired.

Path/debt audit covers the single donor absorption on top of preparation
`72421c5dfa`, with outgoing base `4e46d6eedb03a66ee0d98e4c03df86498b52788a`.
Combined old-path/basename searches cover tracked sources, tools, hooks,
workflows, build/configuration files and documentation. The remaining old
path is the TU's historical provenance comment and `reverse/link_status.csv`,
which is census output and is re-keyed by the next census. There is no active
hard-coded consumer or removed directory. The source's two data-ledger keys
already belong to the surviving TU. The removed donor has no data/identity
baseline, header/ms-header queue, hatch, gate-baseline, EH-baseline,
pin-consistency or deleted-row key to transfer or retire. The merge tool
refreshed its owning header/ms-header reports without a queue change.

Remaining scope: automatic composition still rejects both module-data inputs
at the `AutoPickUpUpdate` module-data getter declaration (C2143/C2501).
Their private module-data/filter/vector views need reconciliation in a
separate verified preparation; the destructor's `novtable` class policy and
the filter destructor's byte-array versus integer member remain relevant.
Mixed shared sources and generated funclets are still separate owners.
