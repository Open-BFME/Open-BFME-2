# XferSave hash helper: remove unused instantiation scaffolding

Inspected base: `92024380d425b3eee9aa67ddc4686e3a68d7e3da`.
Scope: `Code/GameEngine/Source/Common/System/XferBlockWriter_rva009D86E0_Rva0060CB97.cpp`,
the existing 21-byte row at `0x0060CB97`, and read-only composition trials with
`Code/GameEngine/Source/Common/System/XferSave.cpp`.

## Verified cleanup

The helper now instantiates only `_M_bkt_num_key`. Its former whole-class
suppression declarations, unused local max overload, unused allocator inline
bodies and unused C headers are unnecessary: removing 100 lines changes none
of the six external COMDAT fingerprints or six external symbol records.
`link_census.object_symbols` also returns identical definition, reference,
weak-external, alternate-name and include facts before and after.
No provider, pin, alias, ledger row or protected-register key is removed.

Before source SHA-256:
`a983f1a4d406bebd49a9591c3cb03d5d94eeb18e5f808dacda7c9d482ef9be46`.
After source SHA-256:
`a33930959e7ca85bd1ecda0ef5bb2cf3ab0bf97b4d62b6b9c3327c6e6ad42812`.
The identical `json.dumps(link_census.comdat_bodies(object))` lists hash to
`997bc29f7bedc254e0650fc83d6bcd6ebca71185dfb045570886472c5deefa5b`
with SHA-256. The six entries are string npos, string size, string data,
the string-hash function template, the string hash functor and the rowed member.

Checks:

- `./build.sh Code/GameEngine/Source/Common/System/XferBlockWriter_rva009D86E0_Rva0060CB97.cpp`:
  1/1 exact, string/float/import-reference checks pass.
- `find_declared_unmatched.py`: all defined functions already matched, before
  and after the edit.
- `eh_verify.py`: zero EH rows, no missing objects or nonexact graphs.
- `data_check.py`: shadow, zero findings and zero outside the baseline.
- `check_csv.py`: OK, 99,440 function rows, 9,336 symbols and 2,269 data rows.
- Paired ordinary `link_check.py` previews before/after: both units LINKS;
  helper retains 21 bytes, XferSave retains 1,294 bytes, total 1,315 unchanged.
  Published index: census 2026-11-04 07:28, revision `a62ac1c10b`.

## Consolidation boundary and next check

The supported planner was run under `Code/GameEngine/Source/Common/System/`.
The supported merge reconstructs its map from current inputs: 57 approved rows,
six mixed sources, one refused vendored source. The dry run still accepts no
donor, so application was not attempted and no source path moves.

Before cleanup the helper fails composition with C2908: its explicit
`_String_base<char>::_M_deallocate_block` specialization follows an existing
instantiation. Removing only that declaration clears the compile error but
leaves the seed's `0x0060CF76` hashtable constructor nonexact because the donor's
vector-constructor suppression declarations affect the seed. Removing the
remaining unused scaffolding restores all 22 seed rows in the diagnostic
seed/helper composition.

The remaining helper failure is its member's access spelling. The helper
includes `<hash_map>` with `private` defined as `public`; its ledger owner
therefore has `QBEI` in the mangled member name. The seed includes the same
header without that override, so composition emits `ABEI` instead. Reading
the existing scratch object `build/tu_skeleton/f9b346eb00e17579.obj` and checking
the same row with only that name substitution verifies the entire private
21-byte body as exact. This diagnostic changes no ledger. Access/name and
consumer reconciliation is the next prerequisite; do not add another alias or
globally expose the seed's private STL members to force the merge.

Other donors retain their separate class-view, specialization and byte blockers.
`tu_views.py --dry-run` reports incompatible XferSave bases, BfmePositionVector
class keys, the FXList vfptr and Rva0060D031Member fields. They were not edited.
Full dry-run logs and diagnostic compositions remain under the ignored
`build/xfersave-codexb-20261104/` directory. There is no source-file, debt or
census headline gain; this is a verified prerequisite cleanup and handoff.
