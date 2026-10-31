# LivingWorldScoreKeeper shared header, qc-12

Base17a107fc54, queue5350. The complete existing matched declaration and its
four unshared observer definitions move verbatim from the 75-row constructor/
destructor owner into Common/LivingWorldScoreKeeper.h. Existing shared Building,
Region, Player and Logic observer definitions are included, not copied. Nested
PerTurnStats is forward-declared for its separately owned methods. No field
application type or original name is newly claimed. The complete storage and
lifetime helpers retain their existing explicitly structural types.

Hand decisions superseding all seven queued base attributes:
Snapshot at0; Phase4; Building8; AutoResolveC; RTS10; Region14; Player18;
Logic1C; BuildingNuggetSpawnArmy20; every base occupies4 bytes. Native ctor
4EEADE initially installs those base tables and then the final tables at the
same offsets. Native dtor4EED02 independently repeats final tables and restores
the bases at teardown. The automatic contract's RVA-derived base identities
are rejected; same-address empty callbacks do not identify a semantic class.
Existing native registration calls in the constructor distinguish each observer
role. Names are existing reconstruction spellings, with provenance retained in
source; this extraction does not establish fresh original-source recovery.
Own storage begins24; last booleanF8 plus ABI alignment gives complete sizeFC.
The existing owner has a compile-time sizeFC assertion; full ctor/dtor bodies
and all owned EH funclets remain exact after extraction.

Virtual closure: all nine final vtables and all29 slots have byte-identical
COFF data and relocation provider names before/after. Every slot is compared
with a bounded table in the retail image (C62A60 through C62AD4). Named bodies
have exact existing ledger ownership at the native address, or their complete
relocation-free empty body equals native RET4/8/C. Primary slot0 keeps the
compiler's weak SEARCH_LIBRARY E->G fallback to the same rowed scalar deleting
dtor4EF28F; complete scalar dtor bytes and relocations are unchanged as well.
No override is dropped and no slot gains a new base default. Detailed29-slot
proof is in vtable-comparison.json. No private module-root adoption is involved.

The header refuses an already-included incompatible Snapshot profile rather
than silently appending virtual slots. It requires the existing const name
getter, lower-case post-load/xfer surface and complete lifetime profile.

Initial verification: build.sh75/75 rows exact before and after; header accept
PASS for the full owner against the published census (prediction only, no census
or full-image LINKED claim). Normal commit hooks are required too. No hatches,
pins, aliases, ledger edits, or tools changes. Header acceptance is used for any
queue retirement. Shared obstacle register is held by another worker; this
README contains the proposed entry and scope. BFME1 pinned input remains
7a8a034afa7d; no external donor fact establishes target offsets here.

First served consumer Rva004EE15BFwd.cpp passes adoption and accept. It only
defines PerTurnStats::xfer and emits no LivingWorldScoreKeeper vtable.
Added STLport and canonical Snapshot include context; method stays exact.
All four header-hook shadow definition findings have identical complete bytes
and relocations in the original and adopted owner (shadow-comparison.txt).

Second served consumer Rva004EE5D2Erase.cpp: its eight original fake data
members are replaced with casts to the native observer base subobjects. A
standard derived-to-base pointer conversion preserves the native null adjustment
without an extra conditional. m_player and m_F8 are the actual shared members.
Both complete owned bodies including relocation names equal their original
objects; 2/2 code and2/2 data rows pass. Header accept PASS. No scorekeeper
vtable is emitted here. No extent or compiler optimization switch changed.
