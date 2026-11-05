# Camera header retirement after consolidation

The runner's pre-publication gate refused the outgoing batch at `b4c7ca6fcf`:
`Rva00065E3CMethod.cpp` vanished after its `GenericMultiListClass` header-queue
row was retired, so the final tree could not verify that original source.

Commit `216e38f309` used `header_adopt_lane.py accept` to retire this exact
row after adopting the canonical list header. Commit `d4e0a11f37` then merged
the fragment into `Code/GameEngineDevice/Source/W3DDevice/GameClient/camerashakesystem.cpp`.
All four former rows (0x00065D40, 0x00065E3C, 0x0075E6AB and 0x0075E6B3)
remain matched in that destination. They are live rows, not deletions.

Rechecked on 2026-11-05:

- `find_declared_unmatched.py` on the destination passed.
- `./build.sh` on the destination passed **17/17 rows**, including its EH
  funclets; string, float and import-reference checks passed.
- `header_adopt_lane.py accept --class GenericMultiListClass` on the
  destination returned **PASS**. It already includes the canonical header.

The follow-up commit supplies the rules' exceptional per-key `Debt-Retired`
trailer for the vanished original source. It changes no source, debt register,
live ledger row or verifier, and preserves the published/admitted history.
