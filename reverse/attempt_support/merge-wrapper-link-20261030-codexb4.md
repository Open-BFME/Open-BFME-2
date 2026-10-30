# Four-byte inplace-merge provider bindings

Inspected revision: `cb60d7fc6f3473b98b5237fa63bf872fb4b6b0eb`.
Claimed RVA: `0x004F8C16`; additional scope:
`Code/GameEngine/Source/Common/Rva004F60AAInit.cpp`.
This repairs LINK-069's emitted helper dependencies while preserving every
ledger symbol and extent. It does not identify the original element type.

## Target facts and implementation

The complete 131-byte wrapper calls the existing 51-byte buffer initializer
at 0x004F77AD, 33-byte destructor at 0x004F77E0, 303-byte unbuffered merge
at 0x004F840B and 279-byte adaptive merge at 0x004F853A. These already have
providers named Rva004F60AA, TreeHintRef00217D4C/Rva004F9185Cmp and
AsciiString/less<AsciiString>, respectively. The original template
instantiation emitted additional temporary-buffer/merge copies and required
undefined element construction, destruction, assignment and comparison.

Keep the wrapper's existing template specialization symbol and implement
the STLport distance/temporary-buffer/dispatch structure in C++. Declare
the existing provider specializations and pass opaque pointer views and
the existing stateless comparator byte. The inline constructor calls the
rowed initializer; its dllimport inline declaration suppresses a non-retail
standalone forwarding COMDAT. The final object defines no Rva004F60AA
constructor and references the four native providers directly. The two
16-byte distance helpers retain their previous names.

The buffer destructor's native four-byte stride determines its end pointer.
Its existing 24-byte destruction provider at 0x005F97BC already uses the
incomplete TreeHintRef00217D4C view. Name that view directly and remove the
old Rva004F77E0Element alias. Its element teardown remains the existing
flags-zero path through 0x004F72ED and 0x005F8FCC. The initializer's
AsciiString fill view is unchanged. These differing views are existing
provider spellings; neither the stride nor the exact call targets establish
an original owning-handle/string identity or additional fields.

STLport 4.5.3 supplies the generic algorithm structure. Target bytes, calls,
stack shape and EH tables establish this specialization's behavior. No
external donor path, matching name or inferred layout is treated as a
recovered BFME 2 declaration.

## Verification and debt

Strict reusable preparation, ordinary builds and frozen-file checks pass.
The explicit seven-source scope is:

- `Code/Libraries/Source/WWVegas/WWLib/StlSweepW4Rva004F8C16.cpp`
- `Code/GameEngine/Source/Common/Rva004F60AAInit.cpp`
- `Code/GameEngine/Source/Common/Rva004F60AAReserve.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/PAUTreeHintRef00217D4CRva004F9565.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/stlport_stable_sort_asciistring_o1.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/StlportVectorEraseRangeFamily.cpp`
- `Code/GameEngine/Source/Common/Rva004F8B89Stub.cpp`

Preparation passes 87/87 rows, one literal and two imports. After the final
inline-declaration change, wrapper preparation again passes 3/3 and the
seven-source EH check reports EXACT 16, zero missing objects or debt.
The wrapper's renumbered compiler unwind label is resolved by the existing
parent-EH verification, without a ledger change.

The published index is `12b9e7a7c0` (2026-10-30 10:11). The final ordinary
preview reports all seven units LINKS. In the order above, authored bytes
are 0 -> 141, 84 -> 84, 66 -> 66, 3,625 -> 3,625, 611 -> 611,
614 -> 614 and 40 -> 40: 5,040 -> 5,181 total. The wrapper's ledger rows
total 149 bytes; its eight-byte unwind is excluded from authored credit.
These are predictions, not new census figures or ownership receipts.

Remove the four obsolete pins for the wrapper's former temporary-buffer
constructor/destructor and merge specializations. The index's touch query
finds only this wrapper using each name; the final object references none
of them. Pin consistency passes with zero new or stale findings and
check_csv passes 99,014 functions, 9,392 pins and 2,239 data rows.
`hatch_counters.py --update` lowers pins 9,396 -> 9,392 and source
alternatename occurrences 2,880 -> 2,879. The same tool expires the old
allow stamp at 0x004D9A8B without changing its count. No new hatch is added.

## Outgoing audit and remaining work

The complete outgoing staged-tree audit uses merge base
`ad0270b997f11742296db65cc49194c004487f37` and source tree
`a1f9553309b95b6f32f48dd6e18c6b14a19b93df`. It is INCONCLUSIVE: the
index is at a different revision and 33 source objects lack current
receipts, first `Code/GameEngine/Source/Common/Rva003A5DA0Write.cpp`.
It covers the already pending queue/STLport/W3DBuffDraw commits too.
No full consumer-selection or loss clearance is claimed. Carry this
wrapper, the retired helper names, buffer destructor and affected consumers
into the next scheduled census/current-receipt audit. Do not run a nightly
or smoke job for this repair. Original element naming remains separate work.

The outgoing batch's only source move remains the previously audited
W3DBuffDraw module-data consolidation; this repair adds no source-path move
or changed path consumer. Its compatibility audit remains applicable.
Raw object snapshots, the seven-source list, EH verdicts, pin touch query
and audit output are scratch under
`build/merge-buffer-cleanup-20261030/`.
