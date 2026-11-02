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
Broader outgoing consumer selection is not established by that preview and
will be checked through the ordinary publication audit.

`isEmptyString: t=3 model=gpt-6 lane=R budget=30m`

`getProjectionBias: t=3 model=gpt-6 lane=R budget=30m`
