# AITacticSiege shared-header adoption, 2026-11-04

Inspected source revision: `e1d0a5dd7c`. Scope: the approved
`Code/GameEngine/Source/Common/AITacticSiege.cpp` and its clean donor
`Code/GameEngine/Source/Common/Rva005DC87BXfer.cpp`.

## Applied change

The donor includes the registered `AITactic`, `AITacticOffensive` and `AI`
headers instead of declaring private copies. Its record accesses cast the
canonical base's `m_field20` storage to the existing `Rva002C589B` view; the
owner uses `m_field24`, and the pathfinder uses `AI::pathfinder()`.
No shared header, pin, ledger row, source path or hatch changes.

`header_adopt_lane.py accept --class CLASS DONOR` passed for each of the three
classes and retired their three rows from `reverse/header_queue.tsv`.
`./build.sh` passed all four donor rows. Both files together passed all seven
rows; both `find_declared_unmatched.py` checks passed. Final ordinary
`link_check.py` preview against census `a62ac1c10b` (2026-11-04 07:28):

```text
AITacticSiege.cpp: LINKS  LINKED 149 -> 149 bytes
Rva005DC87BXfer.cpp: LINKS  LINKED 495 -> 495 bytes
link_check: 2 of 2 link cleanly; LINKED 644 -> 644 bytes
```

These are preview preservation receipts, not a new census or a linking gain.
An additional transient `--refresh` preview rebuilt/restored 2,478 stale ledger
objects, refreshed 20 already-rebuilt objects, and also preserved both units.

## Reverted constructor trial and consolidation prerequisite

The initial `tu_skeleton.py --merge ... --dry-run` accepted no donor: the
seed's private `AITacticOffensive` lacks `xfer` and does not inherit `AITactic`.
`tu_views.py --dry-run` identifies the canonical base as header-lane work and
also lists `Object`, `AITacticSiege` and `Rva0025BFF8` private-view reconciliation.
The mixed destructor provider `Rva005DC73CDerived.cpp` cannot be absorbed whole.

Replacing only the seed's private base with `AITacticOffensive.h` and changing
its owner accesses to `m_field24` still byte-matched all three seed rows, but
the combined ordinary preview reported:

```text
AITacticSiege.cpp: does not link  LINKED 149 -> 0 bytes
  unresolved  ?v4@AITactic@@UAEIXZ
  unresolved  ?vslot08@AITactic@@UAEXXZ
  comdat      ??_7AITacticSiege@@6B@ (differs from first copy in link order)
Rva005DC87BXfer.cpp: LINKS  LINKED 495 -> 495 bytes
```

That seed change was reverted and its original source rebuilt successfully.
The existing seed header-queue debt remains. No merge or file reduction is
claimed. The base class claim was held by another worker; its header and
providers were not edited.

## Target facts for the next pass

Direct little-endian reads of retail game.dat's vtables (VA addresses below;
entries shown as RVAs), independently of donor source:

| Table VA | Slot RVAs in order |
| --- | --- |
| `0x00C629E4` AITactic | `004EDEE7 0003B810 0003B810 004ECE61 000910FB 004EDA8C 0003B810 0003B810 004EDDAA` |
| `0x00C767DC` AITacticOffensive | `005DC747 0003B810 0003B810 004ECE61 000910FB 004EDA8C 0003B810 0003B810 004EDDAA 0003B810 0047A699` |
| `0x00C76808` AITacticSiege | `005DC886 0003B810 0003B810 004ECE61 000910FB 005DC903 0003B810 0003B810 004EDDAA 0003B810 0050B5C6` |

The ledger already owns `0x004EDDAA` as nonvirtual `AITactic::rva004EDDAA`;
the canonical header declares the virtual slot as `vslot08`. Slot 4 is an
ICF-shared return-one body at `0x000910FB`. These placements do not establish
the original names of either slot. Siege additionally overrides offensive
slot 10 with the shared true body at `0x0050B5C6`, while the canonical
offensive default is false at `0x0047A699`.

Next: reconcile the two base-slot providers without inventing semantic names,
and reconcile the siege constructor, xfer and mixed destructor views to the
same native eleven-slot table (including the slot-10 override). Reverify all
affected consumers before retrying private-view reconciliation and the merge.
