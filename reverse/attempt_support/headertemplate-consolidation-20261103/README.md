# HeaderTemplate consolidation, 2026-11-03

Absorb `Code/GameEngine/Source/GameClient/GUI/HeaderTemplateManagerRva00201B05.cpp`
into its approved `HeaderTemplate.cpp` TU with `tu_skeleton.py --merge`.
Source files decrease by one; all 25 code rows and both data rows remain.
The five moved rows are 0x00201B05, 0x00201BD0, 0x00201C34,
0x0076C589 and 0x0076C594. The live TU map approves 22 rows;
three existing inline/COMDAT rows remain carried with the seed.

## Prerequisite and target evidence

The initial composition failed because the seed imported Zero Hour's INI and
SubsystemInterface alongside the donor's current BFME headers. The preceding
commit, `Use current INI declarations in HeaderTemplate`, replaces that import
with the current INI/FieldParse declarations and keeps the existing STL allocator
mode. Its 20 code rows and both data rows passed byte verification independently.
The supported GUI consolidation planner ran before that edit; the subsequent
merge rebuilt its TU map in memory, accepted both inputs and rejected none.
The committed map is intentionally unchanged under the consolidation rule.

This clears the composition/flag-carry blockers recorded in
`../consolidation-headertemplate-blockers-20261026.md`; no external donor path is
being asserted as additional BFME source evidence.

## Verification and bindings

- `./build.sh Code/GameEngine/Source/GameClient/GUI/HeaderTemplate.cpp`:
  25/25 code rows, two data rows, literal references and two STLport constructor
  folds pass. `link_check.py --prepare-current` separately produced a strict
  reusable compiler receipt and reran the ordinary byte gates (log attached).
- `find_declared_unmatched.py`: all defined functions already matched.
- `eh_verify.py`: six EH-bearing rows, EXACT 6, no debt or missing objects.
- `code_identity_gate.py --staged`: 25 rows, zero new findings (shadow).
- `data_check.py` for the destination: zero findings (shadow).
- `check_csv.py`: 99,431 function rows, 9,343 symbols, 2,269 data rows; OK.
- The merge guard accepts both census-linked inputs. It checks selected COMDATs,
  duplicate definitions, relocations and providers lost to outside consumers;
  neither moved definition nor outside binding was refused.
- The bounded source link preview passes against census 8661f15284 from
  2026-11-03 20:03. Its byte delta is composition, not a census coverage gain.
  The optional full current-ledger preview refuses 121 missing unrelated
  provider objects; it provides no current-tree closure proof. A whole-ledger
  refresh was stopped in favor of the bounded check. No census was run or changed.

## Registers, headers and batch path audit

Audit scope: origin/master `c5e87803d677f2ba156cce5564dbb0b0411a0c33`
through parent `ce00385bb2c0969183b25d356ac397c997033bbf` plus this staged
merge. The complete pending range contains only this source-path removal.
Searches covered the old full path and basename across `tools/`, `.githooks/`,
`.github/`, Code includes, documentation and reverse registers. No active tooling
or include consumer names the donor. Remaining mentions are the source provenance
comment, historical attempt/re_log evidence and the measured census link-status
row. The TU map's old current-source column remains until its owning refresh.
No tooling update is needed.

The merge repoints all five function rows and transfers the existing
`-Os -G7` flag-override key without changing totals. No gate, code-identity,
data-check, hatch or pin-consistency baseline key belongs to either source.
The seed retains its two data-ledger globals (0x007E3098 and 0x009FE124).
The header and Microsoft-header queues have no entries for these sources;
`tu_skeleton.refresh_reports` refreshed the affected destination/deletion scope
without a queue delta. Canonical HeaderTemplate/Manager declarations remain in
HeaderTemplateView.h. No shared header, function identity, pin or link-wide alias
was changed. Existing fold proofs retain their current sources and callees.
