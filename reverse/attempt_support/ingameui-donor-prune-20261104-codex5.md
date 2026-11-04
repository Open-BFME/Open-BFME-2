# InGameUI donor cleanup before consolidation (2026-11-04)

Scope: `Code/GameEngine/Source/GameClient/InGameUI.cpp`, selected by
`next_work.py --claim` for TU consolidation. Starting commit: `4ee23edebd`.

The supported consolidation planner and `tu_skeleton.py --merge ... --dry-run`
found no safe merge. Most rejected donors had incompatible flags or lost byte
matches. Several small candidates passed bytes but the link guard refused the
host's differing `MemoryPoolObject::deleteInstance` and `BitFlags<116>` copies;
some also displaced the selected `Drawable::isSelected` copy. No files or rows
were moved. This is a prerequisite cleanup, not a completed consolidation.

Removed the unverified Zero Hour definitions of `InGameUI::removeNamedTimer`
and `InGameUI::clearFloatingText`, with their two `present-unmatched` markers.
Neither decorated name has a row or pin, another index participant, or a runtime
reference in the original host. This establishes unused donor definitions under
these spellings, not the identity or absence of corresponding retail behavior.
No alias, pin, declaration, matched body or ledger row changed.

## Provider checks

The accompanying [object audit](ingameui-donor-prune-20261104-codex5.json)
compares the saved original object with the rebuilt host. The cached link index
is dated 2026-11-04 07:28 at `a62ac1c10b`, from census 05:53 at `5a13f2cd61`.
Its ten other touching objects were present and inspected. A separate literal
symbol scan of all 25,275 `.obj` files under `build/match/` found twelve other
candidate objects; their runtime references and definitions were parsed too.
Debug references were excluded using `link_census.object_references`.

- 36 external definitions disappeared, including the two donor roots and their
  helper closure. No retained host code references any removed definition.
- The removed pair destructor and `MemoryPoolObject::deleteInstance` have
  outside runtime users, all with other compiled providers. The latter keeps
  the `Player.cpp` and `WeaponSet.cpp` providers; the host's differing copy is
  gone. No removed sole provider has an outside runtime consumer.
- Every retained external COMDAT has the same byte-and-relocation digest.
  Local EH-table symbol renumbering does not change these normalized digests.
- The two placeholder-marker entries alone are retired from the hatch register.
  Unrelated pre-existing address-global counter drift is left unchanged.

## Verification and next step

`./build.sh Code/GameEngine/Source/GameClient/InGameUI.cpp`: both code rows
(55 bytes total) and both data rows remain exact. `find_declared_unmatched.py`
passes: 41 unclaimed definitions, down from 43, covered by existing markers.

`link_check.py` before cleanup reported two blocking COMDAT differences; after
cleanup it reports only `BitFlags<116>::BitFlags()`. Both previews report
LINKED 0 -> 0 bytes. These are predictions, not a new census or real-link result.
`Drawable::isSelected` remains an unreferenced diagnostic in the host preview,
but was a selected-provider loss during attempted donor merges.

Next: reconcile or remove the unverified emitter of the `BitFlags<116>` default
constructor with the same provider checks; then address `Drawable::isSelected`
before retrying the guarded merge. Do not interpret a byte-only donor merge as
permission to lose linking consumers.
