# AptBoolean union proof and remaining provider prerequisites

Inspected revision: `26253212188`. Worktree: `build/r20`; owner:
`codex-01a1071d-root-isolated-r20`. The canonical ROOT checkout was untouched.

The served item is table `??_7AptBoolean@@6B@`, RVA `0x008EA600`, in
`Code/Libraries/Source/Apt/AptValue/AptBoolean.cpp`. Its private view emits four
slots, including a destructor at slot 3. Native has fifteen slots, with the
Boolean overrides at slots 2, 9, 12, 13 and the destructor at 14. The existing
canonical header documents that interface. This change does not repair the table,
adopt the header, retire a queue row or establish a link/runtime pass.

## Compiler-proven union names

The old `tu_views.member()` refused the private anonymous union before field-name
proof. Native VC7.1 layout probing through `header_adopt_lane.compile_text()`
reports a 12-byte class and these overlapping own fields:

| Member | Offset | Width | CodeView type |
| --- | ---: | ---: | --- |
| `m_next` | 8 | 4 | `AptBoolean*` |
| `m_value` | 8 | 1 | `bool` |

`tu_views` now recognizes only simple scalar/pointer anonymous-union alternatives
for header field-name proof. Each retains shared group metadata and the original
union declaration. Complete compiler evidence must contain each source field
exactly once, with known positive widths, bounds and one shared group offset.
Unsupported declarations and partial/ambiguous records refuse. Union alternatives
cannot be discarded as padding or reconciled/rendered as sequential fields.
Inert donors with any literal union token refuse conservatively: no layout
evidence proves whether macros or conditional declarations assert storage. Active
views can exclude parsed function-local unions. Nested, conditional and qualified
inert aggregates are covered by hostile regressions.

The unchanged header field-name proof maps an Apt-shaped fixture's pointer and
Boolean to `field08_next` and `field08`, even when declaration order is reversed.
On the actual merged TU, the proof advances beyond the union and correctly
refuses: `m_value is also a member of Rva006D89D0ByteField; a token rename would
reach it`. No field rename or header rewrite was applied to bypass that collision.

Validation: affected layout/header/union suites and every gate-exploit case:
734 passed, 1 skipped, 51 subtests passed. The new positive regression fails on
the old reader. The unchanged served source passes `./build.sh`: 5/5 code rows,
four string references, including its compiler-owned EH action and handler.
Scratch receipts are `build/root-apt-union-native.json`,
`build/root-apt-union-tests.log` and `build/root-apt-boolean-baseline.log`.

## Recovery handoff

The constructor is owned by `Rva006D8860BoolValue` at `0x006D8860` in
`AptScalarValueConstructors.cpp`. Complete/deleting destructors are owned by
`Rva006D88B0` at `0x006D88B0`/`0x006D8880` in `Rva006DE350Derived.cpp` and
`Rva006D88B0DeletingDtor.cpp`. Pairwise class folding sees a third identity on
the same table. A reviewed atomic identity cohort is needed; do not remove
derived table aliases by hand or create an intermediate identity.

The pooled-delete body at `0x006D8A20` is one method of mixed scalar holder
`Rva006D8670` in `VslotSmallBodiesP.cpp`. Never fold that whole class. The native
address fills both ForceDelete/DeleteThis slots; current `--to-class` requires
one own slot. A separate narrow verifier correction must prove the complete
shared-slot family before that migration. Genuine emitted ICF twins have an
owning admission route; aliases or pins are unnecessary.

The false/return overrides can use real definitions and supported ICF admission
at `0x0073B660` (3 bytes) and `0x0069E440` (1 byte). The existing canonical
protected AptValue destructor supplies `0x006DE350`. Preserve the factory's
inline construction and allocation/free code when preparing the shared-header
cohort, and audit all emitted destructor copies. No provider or source move was
attempted here. The union reader fix alone does not make contract generation
understand unions; the existing AptBoolean contract remains a separate issue.

Pass test remains the next published authoritative real link keeping the native
15-slot table without bridging or refusing it. No measurement was launched.
