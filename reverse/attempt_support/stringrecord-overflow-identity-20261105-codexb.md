# Mutable-copy overflow identity debt

Inspected base: `10a1c86670`. Preview index: `c95fcfcfcd`, census
2026-11-05 05:17. Scope: `stlport_vector_stringrecord_111acf_allocate_copy.cpp`.

## Target facts

`retail_body.disasm` gives these direct call targets (RVAs, subtracting the
image base from its printed operands):

| Body | Call site | Target |
| --- | --- | --- |
| overflow 0x003F6B24, 183 B | 0x003F6B53 | 0x000B40EA |
| | 0x003F6B65 | 0x003F62F5 |
| | 0x003F6B7A | 0x003F62C8 |
| | 0x003F6B92 | 0x003F631B |
| | 0x003F6BB0 | 0x003F62F5 |
| | 0x003F6BBD | 0x003F69A8 |
| repeated mutable copy 0x003F631B, 37 B | 0x003F632E | 0x003F62C8 |
| other repeated copy 0x000AD7A8, 37 B | 0x000AD7BB | 0x000AD77B |

The two repeated-copy helpers have different construction targets; their
common size does not establish an ICF fold. The ledger already names the
0x003F631B helper and 0x003F62C8 construction helper with `EvaMessageInfo`.
The current source already uses that owner for mutable copy and push_back.
This repair extends the same binding to overflow's single and repeated copies.
The opaque Eva declaration copies the existing helper owner's 28-byte storage
view; it makes no new claim about the element's fields or application identity.
The const-copy helpers retain their existing bindings and names.

## Implementation and checks

The specialization follows STLport 4.5.3's non-POD overflow algorithm in the
pinned reference `_vector.h`: allocate, copy prefix, construct inserted values,
copy suffix, clear and replace storage. Only the two insertion calls use the
existing Eva helper identity. No row, pin, alias or source path changes.

- `./build.sh Code/Libraries/Source/WWVegas/WWLib/stlport_vector_stringrecord_111acf_allocate_copy.cpp`:
  16/16 matched, string/float/import checks pass.
- `find_declared_unmatched.py` before and after: all definitions matched.
- Rebuilt stale participating provider `HordeContainRva00475F61.cpp`: 10/10
  matched, including the four renumbered funclet checks.
- `repair_queue.py retire identity` for the repaired source: PASS, all three
  keys removed by the owning tool, zero remaining, no new finding.
- `link_check.py` with the repaired source, `StlSweepW5Rva003F631B.cpp`,
  `EvaMessageVectorAssign.cpp` and `StlVectorRva003F6B24.cpp`: the three
  previously linking units remain LINKS (877, 37 and 208 bytes). Eva assignment
  remains 0 -> 0; its const-copy allocation/copy, destructor and clear selected
  bodies remain blockers. Preview totals stay 1,122 -> 1,122 bytes.

An external declaration for Eva's fill helper made the compiler materialize
an empty tag and changed stack allocation. Letting the existing generic helper
instantiate on the opaque 28-byte view restores exact code generation. The
nonmatching intermediate versions were replaced, not retained in `Code/`.

This closes only this source's registered identity debt. Broader element-family
reconciliation in LINK-002 and LINK-064 remains necessary. No new census or
headline linked-byte gain is claimed.

## Outgoing-batch follow-up

The runner rebased the repair to `dd4f5c4928` before handing it to the fleet
publisher. `link_batch_audit.py` against parent `ef8b2272b2` and the repaired
tip reports INCONCLUSIVE: its index remains `c95fcfcfcd`, older than the
outgoing base, and affected consumers lack strict current receipts. Prepared
this repair source with `link_check.py --prepare-current`; the next audit
requested `0CreateAHeroManager21FE49.cpp`. Prepared that consumer too: 24/24
matched, including STLport folds and 16 renumbered funclets. The next audit
stopped at `Code/GameEngine/Source/Common/AIBaseBuilder.cpp` without a current
receipt. No complete consumer audit or clean batch result is claimed. Carry
this scope into the next census and rerun the batch audit with current affected
consumer receipts; do not count the unchanged four-unit preview as its substitute.

The commit hook passed enforced checks. Its shadow code-identity scan also
reported a divergent unrowed `vector<BfmeStringRecord00111ACF>::_M_fill_insert`
definition. The source's row-reference retirement verdict still found no new
finding and retired all three keys; that narrower result does not settle the
unrowed member's family identity. Include that emitted member in the broader
LINK-002 reconciliation and next consumer audit.
