# AssaultTransportAIUpdate composition prerequisite

Base: `1184c0c8e20d`. Scope: the existing AssaultTransportAIUpdate.cpp seed
and the approved pool-key donor; this prerequisite moves no source paths.

## Target facts

Native `0x0048F45C` loads ObjectID at argument +0x74 and stores it at
receiver +0x4C. The constructor at `0x0048F5A3` installs the secondary table
`0x00C4CC88` at complete-object +0x3E4; that table selects this method.
The store therefore reaches complete-object +0x430. These placements are
target evidence, not an inference from the donor's field offsets.

## Donor facts and bounded reconstruction

The official Zero Hour AssaultTransportAIUpdate header declares the
AIUpdateInterface and AssaultTransportAIInterface bases, with beginAssault
in the latter. That source is a structural lead, not a BFME 2 header.
The old seed included that broad header stack and collided with the separate
pool-key definition. The replacement is a TU-local partial view using the
native offsets above. It declares only the slots needed by these bodies;
the full AIUpdateInterface contract, primary slot inventory and complete
AssaultTransportAIUpdate layout remain open. No sizeof claim is made.

## Verification

- `find_declared_unmatched.py` passes before and after; `./build.sh` passes
  both existing seed rows, including string/float/import references.
- `class_layouts.py` places the secondary base at 0x3E4 and the target field
  at 0x430. All three retained external COMDAT fingerprints (beginAssault,
  the existing comparison helper, Object::getID) are unchanged; none added.
- The broad headers previously emitted 549 external COMDATs; the narrowed
  seed emits three. Every one of the 546 removed names has another provider
  in the published index. This is provider-presence evidence, not proof of
  every consumer's selected provider.
- Strict two-source preparation passes 5/5 rows, including the pool-key EH
  funclet mapping ($L306 renumbered to $L310). Ordinary preview retains
  2/2 LINKS, 75 + 79 = 154 authored bytes, against the 2026-10-30 10:11
  index at `12b9e7a7c0`.
- The staged outgoing audit is INCONCLUSIVE: the index predates this base,
  and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current
  receipt. Full consumer loss/selection checks remain unverified. Carry the
  removed header providers and their consumers into the next scheduled
  census. No census gain or debt retirement is claimed.
- No seed/pool-key debt keys occur in the gate, code-identity, data-check,
  header, ms-header or hatch registers. The donor does own two static-data
  rows in reverse/data_ledger.csv (0x00A03974 and 0x00A03978); the prerequisite
  leaves them in place. No protected register, shared header, canonical class
  or pin is changed by the prerequisite.

The supported merge probe must be refreshed against this seed. The remaining
donors still require reconciliation of their private views and declarations;
the mixed-source donors require their own supported splits. The prior blocked
merge record is retained as history, not treated as a new matching regression.

## Supported consolidation after a78570e9d7

The refreshed planner under Object/Update (`build/consolidation/assault`) passes
its input/output currency check. Its packet has one destination alternative
for the pool-key method and its two EH rows. Its stale-map evidence is a lead;
the merge tool rebuilds the current map in memory and approves all three rows
for AIUpdate/AssaultTransportAIUpdate.cpp. No regenerated map is committed:
the three existing map rows change their source column only.

`tu_skeleton.py --merge ... --dry-run` now accepts the seed and pool-key donor;
the subsequent supported apply repeats byte/link guards and removes only
AssaultTransportAIUpdatePoolKey.cpp. It transfers the two data-ledger owners,
repoints the three function/map source cells and refreshes the header queues.
No header/ms-header queue changes result. Register totals, static symbols,
addresses and names remain unchanged. The tool's protected-register transfer
trailer accompanies the consolidation commit.

The normal build passes 5/5 rows; the string reference matches; the renumbered
funclet $L410 remains proven at native 0x0078C897 by its parent EH data.
The standalone EH verifier reports the parent graph EXACT. All five external
COMDATs equal the two input objects' union, with no added, removed or changed
fingerprints. Frozen-file and staged TU-ownership checks pass; check_csv
retains 99,015 function rows. The change removes one source file, moving three
rows to their approved TU without claiming new byte-matched or census bytes.

Final strict preparation passes 5/5 rows. After the supported tool deletes
the donor, ordinary preview reports one LINKS unit for 154 authored bytes,
equal to the original paired total. The staged consolidation audit is again
INCONCLUSIVE on the older index and missing current
Common/0CreateAHeroManager21FE49.cpp receipt. The prerequisite's broader
consumer and scheduled-census follow-up therefore remains open; the per-file
75 -> 154 preview change is composition, not new linked coverage.

The outgoing path audit covers the prerequisite and this consolidation, plus
the earlier outgoing BitFlags caller declarations (which move no paths).
Searches of tools, hooks, workflows, sources, configuration/registries and
documentation find no active consumer of the retired basename/path. The
remaining old-path references are the generated provenance comment, historical
attempt evidence, the historical deleted-row explanation and the scheduled
census's link_status row. These remain historical; no active fold proof or
debt key names the retired owner. The directory itself stays in place, so
directory scans and globs continue to apply.

The eight rejected donors retain their own matching sources. Helper, check,
finish and dispatch need member/base reconciliation; the constructor needs its
explicit table stores reconciled with the seed's bases; passenger and command
helpers need consistent Object and AssaultTransportAIUpdate declarations;
xfer needs its declaration and layout integrated. Four mixed-source donors
also remain outside this merge. Their private-view reconciliation and the
complete primary/secondary interface inventory remain subsequent work.
