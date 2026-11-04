# W3DBibBuffer declaration reconciliation and consolidation

Inspected starting revision: `9e35476d77`. Scope: W3DBibBuffer.cpp,
W3DBibBufferConstructor.cpp and W3DBibBufferDtor.cpp in
`Code/GameEngineDevice/Source/W3DDevice/GameClient/`.

The supported consolidation planner reports the existing W3DBibBuffer.cpp
placement for this group, with no alternate destination. Its static report
warns about the stale committed map, declaration differences, compiler flags,
include resolution and the seed's data ledger. The merge tool rebuilds the map
in memory; this work does not publish a regenerated map.

Target facts: the already matched constructor owns two four-byte texture
members at +0x10/+0x14 and constructs 1000 68-byte TBib elements. Its native
EH graph requires counted texture lifetimes. The seed previously included a
raw-pointer member declaration. The native destructor also has two counted
member cleanups, but its private Rva000D402ETextureHolder still differs.
Donor facts: the pinned Zero Hour W3DBibBuffer.h supplies the shared class
shape and existing seed field names, not the target's ownership behavior.

The TU-scoped W3DBibBufferLayout.h retains those declarations and uses the
constructor's existing RefCountPtr<TextureClass> contract. The existing
bfme2_meshmdlio texture shim supplies the out-of-line TextureBaseClass release
already owned at RVA 0x0061ED10. No new pins, aliases or global identities.
The constructor adopts this declaration and the seed's compilation context.

Verification of the declaration prerequisite:

- `./build.sh` on seed and constructor: 22/22 matched; strings, floats and
  import references pass. Funclet label renumbering is resolved by parent EH.
- `eh_verify.py` on both: 3/3 EXACT, no missing objects or baseline debt.
- `find_declared_unmatched.py` on both: all definitions matched.
- `link_check.py` on both: 2/2 link cleanly against the 2026-11-04 07:28
  census index at a62ac1c10b; each retains its 1517/303 census-linked bytes.
  This is a local prediction, not a new census or headline linking gain.

The initial ordinary merge trial accepted neither donor (constructor field
names, destructor bytes). After this separately verified prerequisite the
constructor can be retried. The destructor's distinct member identity remains
out of scope until its rowed folded destructor and EH consumers are reconciled.

## Applied constructor merge

After the declaration prerequisite, the refreshed supported planner passed its
currency check. `tu_skeleton.py --merge` reused its successful dry-run plan,
accepted the seed and constructor (22 rows), and rejected the destructor on
bytes. The merge removes one C++ source and moves seven existing rows into
their approved TU. The committed map changes only those seven source fields;
its approval evidence was not regenerated. No new matched coverage is claimed.

Post-merge verification:

- `./build.sh W3DBibBuffer.cpp`: 22/22 matched; string, float and import checks
  pass. `eh_verify.py`: 3/3 EXACT, no missing objects or baseline debt.
- `find_declared_unmatched.py`, `check_csv.py`, `tu_ownership.py --staged` and
  both working-tree/index whitespace checks pass.
- The merge's census-linked guard retained the seed, constructor and destructor.
  `link_check.py` predicts the combined unit links with all 1820 own bytes,
  equal to the seed's 1517 plus constructor's 303. No new census was run.

The batch path audit covers the two pending prerequisite commits and this
merge, after fetching origin/master at efb5fcbb60. The only absorbed path is
W3DBibBufferConstructor.cpp. Searches across active tools, hooks, workflows,
source/includes, configuration and reverse registers found no remaining active
path consumer. Remaining old-path references are the merge provenance comment,
historical link_status/re_attempts records and attempt-support documents.

The removed constructor has no code/data identity, hatch or header-queue keys.
The merge tool transferred header-queue ownership and refreshed the Microsoft
header queue without changes. The seed's detailAlphaShader data-ledger owner
is retained; no providers, pins, aliases or debt keys were removed. Ledger and
map repointing preserve all seven row identities, including the parent's
already-owned EH funclets. The destructor's independent identity prerequisite
and LINK-090's awaiting-real-link status are unchanged.
