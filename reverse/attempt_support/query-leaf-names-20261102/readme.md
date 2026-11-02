# Two inferred query names applied through existing agreements

Base `e12978fd83b39565226b43fedb3bdce6cfed084a`; model GPT-6.
Normal `name_lane.py apply` revalidates the existing independent agreements,
claims the two RVAs and source files, and applies both names in one run.
No new voter, class identity, signature, layout, source path or pin is added.

| Existing row | Source | Applied inferred name | Directly observed behavior |
| --- | --- | --- | --- |
| 0x001F4A37, 9 B | Common/GapThunksSeat8.cpp | isEmptyString | Forwards its const StringBase<char> reference to the rowed isEmpty method at 0x00001E2F. |
| 0x000D1A9A, 7 B | Common/GlobalFloatGetters.cpp | getProjectionBias | Returns the existing bfmeProjectionBias float without changing it. |

The getter name follows existing source vocabulary; this pass does not
independently establish the global's original EA name or application role.
Both function names remain inferred and revocable. The tool records their
agreement IDs, basis entries and old-symbol tombstones together with the rows.

The source plans mark the TU map stale and approve no move. Both files pass
the frozen-file check. Normal and strict verification preserve 30/30 functions,
three existing data rows and five float literals across the two sources.
Bounded preview against index984a4cdc4d retains both units: 172->172 and
91->91 bytes, totaling LINKS263->263. No new matched or census bytes.

Receipts: `apply.log`, `strict.log`, `preview.log`.
Broader outgoing consumer selection is not established by that preview.

`isEmptyString: t=3 model=gpt-6 lane=R budget=30m`

`getProjectionBias: t=3 model=gpt-6 lane=R budget=30m`

## Post-rebase publication scope

Rebase onto `30e83c2c6cebf4b0e36440c7d0e0bbe1a6763948` succeeds. Neither
owned source nor AGENTS.md changes. Worktree preparation pins the committed
BFME 1 reference946f3c05a1b1e60448734e874a8f47f8017cfdb9; no upstream
refresh is attempted. CSV checks pass at99,291 functions. Rename check finds
two renames and zero problems; header-dependency check returns0.

At code tip372a09e481377dabfae22b5b0946a086d1b39ba3 the explicit outgoing
audit returns2 INCONCLUSIVE: index984a4cdc4d predates the base and affected
Common/0CreateAHeroManager21FE49.cpp lacks a current receipt. No unowned
consumer was rebuilt to conceal that boundary. Carry both query providers
and their affected consumers into the next scheduled census. No full-image
selection or linking-credit clearance is claimed.

Additional receipts: `range-check.log`, `header-check.log`, `batch-audit.log`.
