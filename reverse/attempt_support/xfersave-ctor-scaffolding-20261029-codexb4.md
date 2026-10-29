# XferSave constructor declaration cleanup and link boundary

Base: `b6a65e10bf`. Source: `Code/GameEngine/Source/Common/BfmeConv881O1.cpp`.
Index: `840db2d676` (2026-10-28 20:44), retained by `link_check --fetch-index`.

Removed 139 lines of unused extraction scaffolding after the constructor:
placeholder EOA/EOC/EOD/EOE/EOF/EOG views, callback prototypes, a duplicate
ClientSubsystem virtual-interface view and unrelated audio declarations.
None contributes a definition or a dependency to this object. The constructor,
its base/member declarations and its existing STL specializations are unchanged.
This is source cleanup; no debt, linked-byte, source-file or ownership gain is
claimed.

Verification:

- `./build.sh` passes all four rows, including the two compiler-generated EH
  rows. The local unwind label renumbers and verifies through parent EH data.
- `find_declared_unmatched.py` reports all definitions matched.
- `eh_verify.py` reports one EXACT EH graph, none missing or baselined.
- The census COFF reader compares a saved pre-edit object with the rebuilt
  object: all 66 COMDAT name/digest/size triples, 86 external symbol records,
  ten relocation roots and 65 dependency edge sets are identical.
- Strict `link_check.py --prepare-current` succeeds. Ordinary previews before
  and after both report zero linked bytes and precisely the same two unresolved
  `Gen_t_009d80b0_p12cd` / `Gen_t_009d8120_p12cd` destructors. The index reports
  117 authored bytes; the picker advertises 138 bytes. Neither is a new census.

The staged-tree batch audit is INCONCLUSIVE: index `840db2d676` predates the
outgoing base and affected consumer
`Common/0CreateAHeroManager21FE49.cpp` lacks a current receipt. Carry this
provider/consumer scope into the next normal census; unchanged scoped object
facts do not establish consumer-wide selection.

## Remaining identity repair

The earlier 2026-10-27 obstacle evidence remains relevant. The constructor's
+0x18 map uses a string key and unsigned payload; its +0x2C map uses a pointer
key and integer payload. The current int-key/12-byte opaque mapped declarations
instantiate destructors with no providers. Do not supply empty destructors.

Current source inspection also confirms why a local typedef substitution does
not complete the repair:

- The shared constructor at 0x0060D06A and initializer at 0x0060CF76 still have
  old template identities and pins. Both calls need their real typed identities
  and verified folds.
- The five-byte hash-map destructor at 0x0060D0AE is still
  `Rva0060D0AE` in `GapBodiesSeat10O1.cpp`, forwarding through the existing
  `Rva0060D031Member` destructor. It needs owner replacement, not a second name.
- `System/XferSave.cpp` still defines `Rva0060D031Member` in terms of a
  `hash_map<NameKeyType, FXList>` clear. The clear and node-destruction rows at
  0x0060CFB6 / 0x0060CF5A remain owned by `GameClient/FXList.cpp`. Reconcile that
  provider/type family with the string-keyed native operations before restoring
  actual STL template identities in the constructor's unwind graph.

No retyping, retraction, source move, pin or hatch was attempted. The next useful
step is a coordinated provider/constructor identity repair with current byte,
EH, fold and consumer evidence. Current `add_match.py` requires a separate
reviewable retraction for a real named row; a mere replacement of this template
row is not a placeholder takeover. TU placement must use the fresh approved map
and supported tooling. The current map assigns these constructor rows to
`Common/System/XferSave.cpp`; no consolidation approval is inferred here.

## Reference freshness

Official BFME 1 master was fetched at
`326ef10249d19dd08940fbf18467af2c98a4305a`. The update scope remains claimed by
`yasinschroeder-codexb`; verified pin
`e42b9782fd4cce1f79832a6ed591b0b8fdbbc2fc` is retained. No success stamp written.
