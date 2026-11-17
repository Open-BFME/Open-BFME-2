# SpecialPower TU: canonical-header and member-view prerequisites

The current `tu_skeleton.py --merge
Code/GameEngine/Source/Common/RTS/SpecialPower.cpp --dry-run` accepts no
donors. No source or ledger change was retained.

The compiler rejects both store donors because the seed's private
`SpecialPowerStore` exposes `m_vec0C`/`m_18`, not the lookup and parser's
`m_specialPowerTemplates`/`m_nextSpecialPowerID`. Their vector element
types also differ: `BfmeE16`, `SpecialPowerTemplate *`, and
`const ModuleData *`. This is not a field-spelling-only repair.

The registered `Common/SpecialPowerStore.h` has method declarations but no
base or storage. `header_adopt_lane.py run --class SpecialPowerStore
--dry-run` reports **0/4** passing, all rejected at field renames.
The existing vtable attempts in `re_attempts.log` additionally identify the
`Rva003B1546`/`SpecialPowerStore` class-fold prerequisite and the constructor
versus destructor/reset vector-provider differences.

The remaining assignment/destructor donors collide with the shared
`StringBase` template. `tu_views.py` also refuses their shared
`Rva003B1101` view: the parser's opaque `char data[0x80]` starts at zero,
whereas the constructor/assignment/destructor views inherit the 0x10-byte
`Overridable`. The destructor's owning member types and the assignment's
scalar views require reconciliation, not removal of duplicate declarations.

Next owning work is a complete store header/class-fold transaction preserving
the constructor and all cleanup providers, followed by one evidenced
`Rva003B1101` member view. Rebuild each changed donor before retrying the
supported merge. Do not copy fields into the opaque canonical header without
covering its consumers, or bypass the merge's rejected-donor verdict.
