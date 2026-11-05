# Horde manager redundant optimization pragmas

Inspected revision: `ec4c30d96a`. Source:
`Code/GameEngine/Source/Common/W3DHordeModelDrawManager.cpp`.

Removed two consecutive sequences of `#pragma optimize("s", off)`,
`#pragma optimize("t", on)`, and `#pragma optimize("", on)`. Each sequence
restored command-line optimization settings before any code followed it.
The second sequence was also the only content left under a self-origin marker;
that empty marker was removed with it. Compiler flags and link aliases remain
unchanged.

Verification: `./build.sh` on the source passed before and after the edit:
72/72 function rows, two data rows, three funclet pins, string references and
floating-point references. `find_declared_unmatched.py` passed before and after.
Using `class_cleanup.runtime_graph` and `same_runtime`, the compiled objects
compare equal across all 225 non-debug sections, their bytes and relocations,
208 external definitions, COMDAT policies and one weak default.
`hatch_counters.py --update` removes the six pragma occurrences from the
register. This changes no source paths or ledger ownership and claims no new
linked bytes or source-file reduction.
