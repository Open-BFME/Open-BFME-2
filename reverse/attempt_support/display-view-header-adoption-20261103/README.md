# Display view insertion: canonical-header prerequisite repair

Base: 81d62487b5 (game sources from 678d949f99), 2026-11-03.
Source: Code/GameEngine/Source/Common/BfmeStrVM0Rva0025C134.cpp.
RVA 0x0025C134, 25 bytes; existing name and ledger signature are unchanged.

The selected Display.cpp consolidation still accepts no remaining donor. The
supported GameClient planner and tu_skeleton dry run identify canonical Display
adoption as a prerequisite; tu_views refuses to write registered private Display
and GameWindowManager views. The movie sources also disagree on VideoStreamInterface
slot 5; W3DDisplay and Rva0025C3AA have compatible mechanical union plans.
No merge, class-union application, source-path move or TU-map regeneration landed.

This repair removes the view-insertion donor's private Display definition and
uses existing canonical View.h and Display.h. The legacy Display* argument is
cast to View* at the dispatch; Display::field1C is already a View* in the header.
No header, exported name, parameter signature, pin or alias directive is edited.

Target facts: the complete 25-byte body passes [this+0x1c] to argument vslot 151
(+0x25c), then stores the result to [this+0x1c]. View's table at VA 0x00BF6178
points slot 151 to VA 0x0096DE1F: store the argument at receiver+4 and return the
receiver. The canonical View declaration already names this prependViewToList.
The disassembly is in target.txt. Donor facts, independently: committed BFME1
GameEngine/Source/GameClient/Display.cpp attachView and View.cpp
prependViewToList express this list insertion. Those paths are BFME1 evidence,
not recovered BFME2 original-path proof. No function rename is claimed.

Checks: normal ./build.sh passes 1/1, strict find_declared_unmatched passes,
check_csv passes, and header_adopt_lane.py accept --class Display passes and
retires exactly this source's header_queue.tsv row. A normal control build of
the original source and a rebuilt adopted source have identical single external
code definition, full 25-byte payload, relocations, undefined names, weak routes
and INCLUDE directives (provider-comparison.json). Canonical-header inclusion
also emits seven existing AsciiString aliases from
reference/shims/bfme2_ascii/ascii_string.h; none was authored or removed here.
Explicit link_check preview: LINKS, 25 -> 25 bytes, census 2026-11-03 20:03 at
8661f15284. This preserves the unit's predicted linking bytes; no census or real
link gain is claimed. No protected source-keyed data, identity or hatch entry
names this source.

Remaining consolidation prerequisite: adopt Display.cpp's shared private view
and the remaining movie/constructor donors to the canonical header, preserving
their typed storage, virtual slots and exact code. The insertion donor's old
unknown-argument-class blocker is resolved by the existing View interface and
target dispatch evidence; the ABI spelling remains a separate naming task.
