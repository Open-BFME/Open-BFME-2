# LargeGroupAudio: remove the unused competing erase instantiation

Inspected base: `e12e2545d9`, rebased onto `b85e569cee`, 2026-10-26.
Scope: `stlport_asciistring_set_base.cpp` and the six current audio consumers
listed in the storage handoff. The provider file was claimed before editing.

## Cause and bounded repair

Upstream `b8ee7f1d87` added a pair-tree erase instantiation, without adding a
function row. The independently repaired KeyList already calls the existing
rowed AsciiString-tree erase at `0x00056BC3` directly. AddKey uses the native
record-tree insert owner. Source search finds the pair value type only in
these two consumers and the added provider block; current COFF roots and all
COMDAT relocation edges in both consumers contain no pair-tree erase reference.

The added instantiation nevertheless emits a competing pair destructor:
`??1?$pair@$$CBVAsciiString@@URva003D3F90Value@@@_STL@@QAE@XZ`.
Both copies are five bytes, `E9 rel32`, but their relocation targets differ:

| Object | Target |
|---|---|
| Set provider, earlier in link order | `AsciiString::~AsciiString` at `0x0048BA39` |
| AddKey | `StringBase<char>::releaseBuffer` at `0x00036410` |

The native AsciiString destructor is itself a jump to releaseBuffer. AddKey's
exception cleanup `$L5022` references the pair destructor, making the selected
extra indirection relevant even though the added erase has no callers.
The added 59-byte erase has the rowed erase's masked shape, but its relocation
at +36 targets the pair destructor instead of AsciiString's destructor.
It is therefore not established as a byte-and-relocation ICF twin.

A declaration-only specialization of the pair destructor was tried first.
Normal bytes, EH and frozen-file checks passed, but VC7.1 still emitted the
same conflicting copy and the preview remained 6/7. That ineffective trial
was fully removed; no compiler-internal explanation is claimed.

The final change removes only the added 17-line pair-tree block. All fifteen
existing provider rows, the TU's flags and its rowed set erase are preserved.
The earlier unused fold pin remains recorded debt; no pin, alias, ledger row
or baseline is added or retired by this change.

## Verification

Normal `./build.sh` on the provider, AddKey and KeyList passes **20/20 functions**,
two data rows and one string. AddKey's two EH graphs are EXACT. The provider's
frozen-file check passes. `allowed_symbols.py --source` on the same three files
reports 46 references (35 owner, seven fold, two EH, two alias), zero wrong
bindings. Current COFF checks find no pair-value symbol in the provider and
retain AddKey's five-byte destructor with its releaseBuffer relocation.

The ordinary seven-current-object preview against published index `763dc8759f`
changes from **6/7, 10,874 -> 11,065 authored bytes** to
**7/7, 10,874 -> 11,379**. This restores AddKey's 314 bytes in that bounded
comparison, while retaining KeyList and all five other units. This is not a
census increase, complete-image proof or new C++ matched coverage.

Reproduce through normal build, `eh_verify.py`, `allowed_symbols.py --source`,
`find_declared_unmatched.py` and `link_check.py` with the provider plus the six
paths in [the storage handoff](largegroup-keylist-storage-link-20261026.md).
Detailed local receipts are `build/codex-cleanup-20261025/iteration22-unused-erase-*.log`;
the discarded trial is `iteration22-pair-dtor-*.log`, and the complete consumer
reference check is `iteration22-pair-erase-consumers.log`.
