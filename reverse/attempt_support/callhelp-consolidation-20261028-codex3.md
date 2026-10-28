# CallHelpOnDamage bounded composition, 2026-10-28

Applied at base `9306e815c8`. Destination:
`Code/GameEngine/Source/GameLogic/Object/Die/CallHelpOnDamage.cpp`.

The scoped `name_lane.py consolidate` packet under the Die subsystem was
reviewed and its currency check passed before applying. It provides no
original-path proof for this filename. The current in-memory TU map approves
the provisional grouping: 23 rows, seven whole-file donors, three mixed files.
The committed map was stale; only nine existing source cells are repointed,
with no map regeneration or approval change.

Both supported dry run and apply accept Rva004bb3a7Finish.cpp,
CallHelpOnDamageModuleDataParse.cpp and CallHelpOnDamagePoolKey.cpp. These
three sources become one TU: two fewer source files, preserving nine rows
(298 bytes). The merge guard accepts the census-linked inputs and their
composition. No rejected donor is edited.

`tu_views.py --dry-run` explains the remaining prerequisites: the ModuleData
constructor uses UpdateModuleData, while the destructor uses ModuleData plus
padding. The behavior constructor, key getter, deleting-destructor scaffold
and transfer fragment also use different base clauses. The supported merge
rejects the destructor/constructor/transfer combinations at compilation and
the deleting-destructor scaffold on bytes. Reconcile bases, declarations and
virtual slots in separately verified prerequisites before another merge.
ConstIntGetters4.cpp, TailJumpWrappers5B.cpp and CallHelpOnDamageOnDamage.cpp
remain mixed sources; no split is attempted here.

## Verification

- All original donors and the destination pass find_declared_unmatched.
- `./build.sh` verifies 9/9 code rows, the 96-byte parser table, one string
  reference and one compiler float literal. The three renamed compiler labels
  retain their retail positions through exact parent EH data.
- `eh_verify.py` reports both EH graphs EXACT, with no missing objects.
- Scoped data checking has zero findings; enforced converged checking has
  zero second names and zero unjudged rows across its 11 addresses.
- Staged code identity checks nine rows and reports zero new findings.
  Staged TU ownership and class gates pass. The Microsoft-header audit is
  clean with /MD enabled. CSV integrity and whitespace checks pass.
- Comparing the saved donor objects with the merged object preserves all
  13 external COMDAT byte-and-symbolic-relocation digests, one strong
  definition, 23 undefined externals and one weak binding. No external binding
  or selected-copy content changes are introduced by composition.

The data ledger transfers three owner records: the parser table and the
cached key/guard. The matched data register transfers the table's source only;
names, addresses, extents and initializers stay intact. No affected code/data
identity baseline, gate/hatch register, flag override, header/MS-header queue,
symbol fold proof, body-owner or doxygen entry needs transfer or retirement.
The merge tool refreshes header reports. No debt retirement or hatch growth
is claimed.

## Path-consumer and link audit

The outgoing batch from origin/master through the staged merge contains only
these three absorbed source paths. A combined search of paths and basenames
finds no active tool, hook, workflow, include, build/configuration or registry
consumer needing repair. Core code/data owners and TU-map source cells follow
the destination. Remaining old-path mentions are source provenance comments,
the destructor's explanation of the former constructor location, historical
link_status census rows and the older module-poolkey attempt handoff. They are
retained as evidence. The local-static symbol's PoolKey spelling is an identity,
not a path reference.

Ordinary preview cannot score the destination: it is absent from index
`d92e7e6635`. Bounded `link_check.py --prepare-current` verifies the new TU
and produces a strict reusable receipt without changing census/index/status.
The staged-tree `link_batch_audit.py` against base `9306e815c8`
is INCONCLUSIVE: that index predates the base, and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry the three retired providers, the destination and this consumer
into the next scheduled census. The bounded merge guard and preserved object
facts do not establish full consumer coverage or a new census-linked result.

`progress.py` reports SOURCE FILES -2 and BYTE-MATCHED 100%, with zero byte
coverage change. Census LINKED/LINKING remain unchanged. No ownership or
runtime gain is claimed.
