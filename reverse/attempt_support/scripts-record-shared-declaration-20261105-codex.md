# Scripts record loader: reuse the measured declaration

Base: `129d3b39c2`. Scope: `Code/GameEngine/Source/Common/Rva003B3536Load.cpp`.

The loader and record copy constructor now include the existing
`GameLogic/ScriptClass.h` declaration instead of repeating a private class.
The fields use that header's neutral offset names. No semantic rename, source
move, ledger repoint, hatch removal or debt retirement is claimed.

Target evidence: the header records the native record copy at 0x003B3507,
loader at 0x003B3536 and Script constructor writes establishing a 16-byte record
with bytes at +0/+1/+8, an int at +4 and AsciiString at +0xC. The former private
view has precisely those fields. Reusing the declaration is a structural
reconciliation; it supplies no donor name for the record.

Verification before and after:

- `./build.sh Code/GameEngine/Source/Common/Rva003B3536Load.cpp`: 4/4 rows exact
  (47-byte copy, 123-byte loader, 8-byte funclet, 10-byte EH handler).
- `find_declared_unmatched.py`: all definitions already matched.
- `eh_verify.py`: one exact EH graph, none inexact or baselined. The build
  resolves the renumbered funclet through its parent's EH data.
- COFF comparison against the saved pre-edit object: the same five external
  definitions and nine undefined externals, including their symbol types.
- `link_check.py`: LINKS, 170 -> 170 bytes, using the 2026-11-05 05:17 census
  index at c95fcfcfcd. This is a prediction, not a new census measurement.

Consolidation handoff: the ScriptEngine evidence planner completed under
`build/consolidation/scriptengine`; it reports the Scripts group as investigation
work, with mixed-source routing, placement and declaration blockers. The broad
`tu_skeleton.py --merge .../Scripts.cpp --dry-run` was interrupted before a
verdict. No merge, file-count reduction, exhaustive conflict list or link gain
is claimed. Other record declarations and the previously documented Scripts
class-view prerequisites still need reconciliation before merging.
