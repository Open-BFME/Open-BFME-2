# SidesListNotifier caller adoption, 2026-11-04

Inspected revision: `e6bbf29402b0`. Published index: census 2026-11-04
02:25, measured revision `5a13f2cd61`. This is header-debt cleanup; no new
census or linking gain is claimed.

## Applied scope

All paths below are under `Code/GameEngine/Source/GameLogic/Map/`.

- `SidesListCopyCtor.cpp` and `SidesListSwap.cpp`: replace the opaque
  16-byte base and private notifier with the existing canonical headers.
- `SidesListNotifierDispatch.cpp`: use the canonical notifier storage and
  records, preserving the unsigned latch and native member-call ABI with
  typed views. The listener identity remains unproved.
- `SidesList_sidesInfo.cpp`: replace the empty notifier view with the
  canonical 16-byte notifier; reduce the following padding by 15 bytes so
  `m_numSides` stays at +0x3C and every later member keeps its retail offset.

`header_adopt_lane.py accept --class SidesListNotifier` passed all four
sources and retired four queue rows. Its owning acceptance for
`Rva00330757Member` passed the copy and swap sources and retired two more.
No header, ledger identity, pin or alias changed.

## Remaining constructor prerequisite

The same canonical include was tried in `SidesListCtor.cpp`, removing its
private base and notifier. The member-pointer `post` overload can compile
with a four-byte callback representation view. However,
`??1SidesList@@UAE@XZ` at RVA `0x0032EC63` (240 bytes) then fails verification:
retail loads the notifier allocation, tests it and conditionally calls
`free` inline; the canonical base instead emits an out-of-line
`Rva00330757Member` destructor call. The parent's unwind action also stops
matching. This is an existing lifetime/codegen dependency, not a missing
body. The entire constructor-file trial was restored; both of its header
queue entries remain.

Before retrying this caller, reconcile canonical base teardown with the
retail inline nullable free and complete parent EH graph. Verify all base
header dependents if changing the shared lifetime declaration. Do not mask
the mismatch with an alias or erase either queue entry.

## Final checks

`./build.sh` on the four changed sources and restored constructor source:
**97/97 matched**, exact parent/funclet verification, string/float/import
checks passed. `find_declared_unmatched.py` passes; the constructor retains
its existing note of 45 matched rows and two unclaimed definitions.

`link_check.py` explicitly reports every source `LINKS` against the index:

| Source | Census-linked bytes before -> after |
| --- | --- |
| SidesListCopyCtor.cpp | 374 -> 374 |
| SidesListSwap.cpp | 359 -> 359 |
| SidesListNotifierDispatch.cpp | 229 -> 229 |
| SidesList_sidesInfo.cpp | 1,714 -> 1,714 |
| SidesListCtor.cpp (restored) | 1,035 -> 1,035 |

Local logs: `build/sideslist-notifier-accept-20261104.log`,
`build/sideslist-notifier-base-accept-20261104.log`,
`build/sideslist-notifier-verified-20261104.log`, and
`build/sideslist-notifier-links-20261104.log`.

## Shadow identity control

The commit hook reported five out-of-register shadow findings: two bindings
to `SidesList::FactionBuildLists` destruction at RVA `0x0032C1C1`, and three
divergent definitions (`Xfer::Version` construction and two nested-vector
deallocation methods). The four original sources from the adoption commit's
parent were rebuilt with `./build.sh` (52/52 exact), then scanned with the
same scoped `code_identity_gate.check` call. Their complete set of findings
is identical to the adopted sources' set. These are pre-existing findings;
no identity baseline entry was added or retired. The adopted sources were
restored and rebuilt after the control.

Local control logs: `build/sideslist-notifier-identity-current-20261104.txt`,
`build/sideslist-notifier-identity-original-20261104.txt`,
`build/sideslist-notifier-original-control-20261104.log`, and
`build/sideslist-notifier-control-restored-20261104.log`.
