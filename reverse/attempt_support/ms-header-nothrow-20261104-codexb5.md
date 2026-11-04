# Microsoft-header audit: preserve the nothrow contract

2026-11-04, based on 43da10658b; model gpt-6.

## Reproduction and scope

`ms_header_audit.py show` classified LivingWorldPlayer.cpp:86's
`extern "C" __declspec(nothrow) memset` as `same` / `drop-in candidate`
against VC7 string.h:102. The declaration parser discarded the attribute.
The existing `reverse/re_attempts.log` entries for this source (the header
trial and the subsequent false-reject report) establish why that advice is
unsafe: removing the redeclaration adds an EH-state store in both
Rva002E2AAE constructors and orphans a funclet under this unit's /EHs.
Those earlier failures were not repeated. No game source was edited here.

The audit now carries the nothrow bit from parsed attributes through the
function signature comparison. Different contracts are ABI conflicts,
with an unwind-cleanup explanation. Equal contracts remain candidates.
The index version changes from 15 to 16 so existing header caches cannot
hide attributes omitted by the old parser. This does not retire debt.

## Checks

- The new regression initially failed with the original parser's missing
  `nothrow` field. It now covers both directions of the contract difference,
  equal-contract controls, and declarations versus identical inline bodies.
- The analyzer and gate-exploit suites: 138 passed, 1 skipped, 2 deselected.
  The skip is the existing explicitly open audit escape. The two excluded
  tests are `test_extra_root_arguments` and
  `test_included_project_headers_are_inspected`: the full run failed those
  two, and running them against HEAD's untouched analyzer reproduced both
  failures on this Linux runner (Windows drive path handling and include
  closure classification respectively).
- LivingWorldPlayer.cpp's unchanged source passed `./build.sh`: 85/85 code
  rows and its data row, including 48 parent-verified funclets.
  `find_declared_unmatched.py` and `check_csv.py` pass.
- A rebuilt real Microsoft-header index changes this source's queue entry
  from `drop-in candidate` / `memset:same` to `conflicting` / `memset:abi`.
  The reported difference is `__declspec(nothrow) True vs False; may change
  unwind cleanup`. Other queue rows are preserved; no register key retires.

Detailed local logs: `build/ms-header-nothrow-tests.log` and
`build/livingworldplayer-nothrow-audit.log`.
