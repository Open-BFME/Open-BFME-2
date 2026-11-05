# W3DStreakDraw body consolidation, 2026-11-05

Scope: the reconciliation in `fc9cc163a6` and the following merge of
`Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DStreakDrawBody.cpp`
into its approved `Draw/W3DStreakDraw.cpp` TU. One source file is removed;
no new matched or census-linked coverage is claimed.

The donor's color fields at +0x14/+0x18/+0x1c now use the seed's existing
`m_color[3]` view. Explicit casts of module-data and drawable storage let
the same body compile against the seed's inherited storage types. The
standalone donor retained its three exact rows, 550 bytes, before merging.
No class layout, pin, alias, field offset or compiler flag was changed.

## Verification

- `tu_skeleton.py --merge .../Draw/W3DStreakDraw.cpp --dry-run` accepted
  the seed and reconciled body. The applied merge also passed its census
  link guard, including selected-copy, outside-COMDAT and removed-provider
  checks, against index `c95fcfcfcd` (2026-11-05 05:17).
- `./build.sh .../Draw/W3DStreakDraw.cpp`: 23/23 function rows exact;
  the one data row, eight funclet pins, string/float/import references pass.
- `find_declared_unmatched.py` reports all defined functions matched;
  the existing dead-stripped `_STL::_Construct` marker remains.
- `allowed_symbols.py --source .../Draw/W3DStreakDraw.cpp`: 64 references,
  51 owner / 7 fold / 3 EH / 3 alias, zero wrong bindings.
- `link_check.py .../Draw/W3DStreakDraw.cpp`: LINKS, 903 -> 1,453 bytes.
  The 550-byte difference is the absorbed donor, which independently
  previewed LINKS 550 -> 550. An unreferenced ShaderClass copy has the
  existing register-allocation diagnostic; it is not a linking blocker.
- `check_csv.py` passes; `git diff --cached --check` passes.

These are byte checks and link predictions, not a real-link or new census
measurement. The outgoing batch remains subject to the publisher's link audit.

## Debt and path-consumer audit

Audited the complete source-path change in this batch: the body donor above
is absorbed by the seed; the reconciliation changes no paths.

- `tu_skeleton` repointed the three function rows and only their source
  cells in the committed TU map. TU approvals were not regenerated.
- Its header-lane transfer retained the donor's W3DStreakDraw adoption row,
  original diagnostics and three RVAs under the destination. No header debt
  was retired. The destination's DrawModule, RTS3DScene and W3DStreakDraw
  adoption debts also remain. The owning Microsoft-header refresh produced
  no queue change.
- The first commit-msg check refused the vanished donor's header key because
  the destination already held that class/source key: duplicate destination
  rows do not count as newly added keys in `repair_queue`'s transfer test.
  The commit uses the documented per-key `Debt-Retired` trailer solely to
  account for this vanished source. Both pending adoption rows remain in
  the queue under the destination; this is not a passing adoption verdict.
- Neither donor nor seed has a data-identity, code-identity or flag-override
  baseline key. The hatch refresh produced no register change: the seed's
  three existing optimization regions remain, and no hatch was introduced.
- All three scoped naming provenance source cells followed the donor.
  Searches of active ledgers/registers, tools, hooks, workflows, Code includes,
  shim includes, build.sh and docs found no additional live path consumer.
  Remaining mentions in historical naming votes/approvals, the prior census
  status, a saved consumer inventory and donor-origin comments are historical
  evidence. The BFME1 reference path in the source comment remains a donor
  fact, not a claim about BFME2's original source path.
- No `/alternatename` or other provider was removed by hand. The merge guard
  verified the composed provider set; the identity check verified the current
  unit's bindings. Census confirmation of outside consumers is still pending.

## Remaining composition prerequisites

The merge retained four rejected donors unchanged. Rva000CFF4C and PoolKey
still conflict with the seed's RefCountPtr texture storage; Destructor expects
a Release_Ref member absent from the seed's streak-object view. The separate
module-data constructor still has a different base/vector view. Canonical
header adoption and these layouts need separate byte- and link-verified
reconciliations before another merge. The three mixed-owner sources also
remain outside this move. No new linking failure was observed and no existing
link-obstacle clearance is claimed.
