# INIWater consolidation prerequisite (2026-10-28)

Inspected base: b35ccaab0e. Scope: INIWater.cpp and the four clean donors
served by next_work.py --tier consolidate. name_lane.py consolidate --under
Code/GameEngine/Source/Common/INI/ supplied the evidence packet; tu_skeleton
rebuilt its stale TU map in memory. No committed TU-map regeneration.

## Seed declarations

The original seed imported broad donor headers for a single parser. Baseline
merge dry-run accepted nothing: the headers collided with the ctor donor's
_STL allocator/vector, the transparency donor's OVERRIDE, and the destructor's
WaterTransparencySetting(int). The assignment donor failed byte verification.

Replaced those imports with TU-local declarations and retained the parser body.
The 0x7C WaterSetting stride is a target fact, corroborated by the rowed
WaterSettingsArray.cpp initializer (six elements). The parser provenance remains
Open-BFME-1 revision 6d9434269164392c5ba62aaa7c15a86b5b020d76; that donor is
not claimed as a BFME 2 source path or layout proof.

Verification:

- ./build.sh on all five original sources: 16/16 function/EH rows, two data rows,
  string/import references passed. All five preview LINKS (738 bytes) against
  the 2026-10-28 15:58 census index at d92e7e6635.
- Edited seed: ./build.sh, find_declared_unmatched.py, converged data check and
  link_check.py --prepare-current passed. Three function/EH rows remain exact.
- COFF facts before/after: all eleven retained COMDAT names, byte fingerprints
  and sizes match; strong definitions, undefined symbols and weak references
  are unchanged. Only ??_H@YGXPAXIHP6EPAX0@Z@Z (34 bytes, fingerprint
  6246c280fc30) disappeared. The index selects ATL/atl_vector_constructor_iterator
  as its retail owner; INIWater was an unselected identical copy.
- The new supported dry-run accepts Rva00200CB1Assign.cpp,
  Rva00200D38Ctor.cpp and Rva00200E95Dtor.cpp together with the seed: eleven
  rows, one carried data-ledger entry. This is a proposal, not a landed merge.
- Transparency still fails composition because its selected INI view omits
  parseWaterSettingDefinition and getNextToken. Its Overridable/setting views
  also need reconciliation before adding it to the same TU. Four mixed files
  remain outside this mechanical merge; do not split them during composition.

The five sources have no keys in the identity/data debt registers, hatch
baseline, header_queue, ms_header_queue or flag_overrides. No source paths or
ledger owners changed in this prerequisite, so there is no path-consumer audit
or queue transfer yet. No census gain is claimed.

Seed outgoing audit: link_batch_audit.py --base HEAD --tip <staged tree>
--sources-from <seed receipt> returned 2 (inconclusive). The index predates
b35ccaab0e and the affected-consumer check lacks a current receipt for
Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp. This is not a clean
consumer audit; carry it into the next scheduled census. The seed's own strict
current preview remains LINKS, 198 -> 198 bytes. No proven loss was reported.
