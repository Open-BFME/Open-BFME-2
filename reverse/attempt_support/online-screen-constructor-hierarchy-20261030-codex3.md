# Online screen constructor hierarchy handoff

Inspected at `4dbceb34a4` after rebasing on `ad0270b997`. No source change or
new name is proposed. This is existing-placeholder cleanup, not missing code.

## Target facts

`Rva005BA1FDCtor.cpp` still verifies both 55-byte constructors. Ordinary
`link_check.py` against the 2026-10-30 10:11 index `12b9e7a7c0` reports
seven unresolved virtual functions, zero linking bytes:

- `BaseVirt@AptOnlineCustomMatch`
- `BoxVirt@AptOnlineOpenPlay` and `BoxVirt@Rva005BA28E`
- `M60Virt@Rva005BA1FDM60` and `M60Virt@Rva005BA28EM60`
- `M6CVirt@Rva005BA1FDM6C` and `M6CVirt@Rva005BA28EM6C`

Reading the native constructors and destructors with `retail_body.disasm`
gives these shared stores. Table addresses below are VAs; code addresses are
RVAs.

| Constructor | Destructor | Singleton VA | Table VAs at +0 / +0x60 / +0x6C |
|---|---|---|---|
| 0x005BA1FD | 0x005BA23A | 0x00E06544 | 0x00C73D34 / 0x00C73CD8 / 0x00C73CCC |
| 0x005BA28E | 0x005BA2CB | 0x00E06548 | 0x00C73DCC / 0x00C73D70 / 0x00C73D60 |

Both constructors call the existing `AptOnlineCustomMatch` constructor at
0x005A5BC7 with `(shell, 0)` or `(shell, 1)`. Both destructors tail-call its
destructor at 0x005A0009. The first constructor's comment currently reverses
the arguments; its C++ initializer already has the native order.

The primary tables' first slots point to 0x005BA272 and 0x005BA303. These
are already rowed as the deleting destructors of `Rva005BA23A` and
`Rva005BA2CB` in `OpaqueScalarDeletingDtorsB14.cpp`. Their -0x60 and -0x6C
adjusting thunks are also rowed there (0x005BA262 / 0x005BA26A and
0x005BA2F3 / 0x005BA2FB). The +0x6C tables begin with two copies of
0x0059EF57, then the respective -0x6C thunk. These are secondary bases,
not independent polymorphic member lifetimes.

## Remaining prerequisite

The existing constructor view models +0x60/+0x6C as members and has one
invented virtual slot per table. Its shared `BaseVirt` would need two distinct
deleting-destructor targets, so one shared pin cannot repair the contracts.
The destructor source uses separate one-slot secondary views and existing
alternatenames; the scalar-deleting source has a three-base hierarchy under
opaque class names. A coherent repair needs the inherited native slots and
owner identities across all three emitters, retaining their other consumers.
This inspection proves the native lifetime pairing, not a new canonical name
for the opaque sibling. No table suppression, alias or source trial was applied.

Next: reconcile that source-wide hierarchy and its complete tables before
renaming the existing destructor owners or composing their approved TUs. The
2026-10-26 virtual-table audit in the shared obstacle register remains open.
Both constructor boundaries now have explicit deferred attempt records, so the
picker can prefer untried work. Whole-unit link clearance and census
confirmation remain pending.

## Checks

- `find_declared_unmatched.py`: all defined functions already matched.
- `./build.sh Code/GameEngine/Source/Common/Rva005BA1FDCtor.cpp`: 2/2 exact.
- Ordinary `link_check.py`: U7, 0 -> 0 bytes; no gain claimed.
- No Code, ledger, pin, header or provider change in this handoff.
