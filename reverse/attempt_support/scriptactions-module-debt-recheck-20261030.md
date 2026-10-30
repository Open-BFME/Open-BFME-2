# ScriptActions Module debt recheck

The canonical Module adoption already landed in `702a5efe73`. The three
remaining queue entries were stale; no production source change is needed.

On 2026-10-30, normal `./build.sh` verification passed all seven rows across:

- `ScriptActionsModuleQuery.cpp`: one row, ordinary preview LINKS, 84 bytes.
- `ScriptActions_rva003C30D9.cpp`: three rows, LINKS, 164 bytes.
- `ScriptActions_rva003C3175.cpp`: three rows, LINKS, 132 bytes.

The two latter units retain their compiler funclet/EH bindings; their two
string references also pass. `find_declared_unmatched.py` reports all defined
functions matched. Each source includes the registered Module header and
contains no private Module class. `header_adopt_lane.py accept --class Module`
passes and retires exactly these three keys through the owning register.

The ordinary previews use published index `ccafe54d1d` and preserve all 380
authored bytes. This retires debt; it adds no recovered or measured linked
coverage and does not establish a full-image link result.
