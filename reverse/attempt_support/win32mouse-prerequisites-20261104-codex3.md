# Win32 mouse consolidation prerequisites, 2026-11-04

Inspected revision: `68f4e2294d`. Claims: the approved Win32Mouse TU,
Win32DIMouse.cpp and Win32Mouse_reset.cpp; owner `yasinschroeder-codex3`.

## Target facts and retained changes

The current-input planner surveyed four sources and found three files in the
Win32Mouse group. Its committed map was stale; tu_skeleton rebuilt approval in
memory (17 approved rows, two mixed sources left untouched). No map is committed.

Win32DIMouse.cpp defines only the 60-byte Win32Mouse::setPosition row at
0x00041AD4. Its legacy donor Mouse declaration is 0x4E14 bytes; canonical target
Mouse is 0x5010. The body only calls Mouse::setPosition and the two Windows
imports, so it needs no DirectInput, Display, Debug or WinMain header. It now
uses the canonical target Mouse header and an explicit ApplicationHWnd extern.
Its original donor provenance and copyright remain in the source.

Win32Mouse.cpp replaces its private StringBase template/AsciiString typedef with
the shared BFME2 string header. Retail's cursor-resource body calls the
out-of-line StringBase::isEmpty predicate, so that call retains an explicit
StringBase view instead of expanding AsciiString::isEmpty. Both files keep
runtime/optimization settings and need only the runner sweep include root.
No alias, pin, code/data row, data owner or debt key is added or removed.

## Verification

- Baseline build: 15/15 rows across the seed and both potential donors; one data row.
- Final scoped build and strict `link_check.py --prepare-current`: 14/14 native/EH
  rows across the two edited files; one 1792-byte cursorResources data row.
  String, float and named-import gates pass. Both strict reusable receipts pass.
- `find_declared_unmatched.py` passes for both edited sources.
- `link_check.py --new-variants` exits 0 for both edited files.
- Local link prediction against census 2026-11-04 20:47 at `f12552d0a7`:
  Win32Mouse.cpp 1095 -> 1095, Win32DIMouse.cpp 60 -> 60 authored linked bytes.
  This preserves the prediction; it is not a new census or full-game link proof.
- `check_csv.py` and `git diff --check` pass.

## Reverted trials and remaining prerequisites

Initial native merge trial accepted no donors: duplicate StringBase declarations
blocked the init donor; the position donor's broad Debug include caused C1001.
The native Win32Mouse view rewrite reverted because the position donor's legacy
Mouse base produced size 0x5E28 instead of 0x6024 and different vslots.

An explicit canonical Mouse adoption in the seed removes the private Mouse view
and accesses the cursor records through canonical field0C. It byte-matches all
13 seed rows and the data row, but the link guard predicts 1095 -> 0 linked bytes
because these canonical virtual names have no providers in the inspected index:

```
?getRedrawMode@Mouse@@UAE?AW4RedrawMode@1@XZ
?reset@Mouse@@UAEXXZ
?setRedrawMode@Mouse@@UAEXW4RedrawMode@1@@Z
?vslot14@Mouse@@UAEXXZ
?vslot18@Mouse@@UBEXPAI0@Z
?vslot23@Mouse@@UAEXHH@Z
?vslot24@Mouse@@UAEXHHHH@Z
?vslot25@Mouse@@UAEXH@Z
?vslot28@Mouse@@UAEXEPAE@Z
```

That adoption was reverted. No matching-provider claim or regression is made;
canonical declarations exposing placeholder identities are cleanup prerequisites.
Resolve the providers through the naming/identity lane before adopting Mouse in
the seed, then reconcile Win32Mouse method declarations through tu_views.
The GameClient header queue row is also retained.

The final native merge dry run still accepts zero donors: canonical Mouse from
either donor supersedes the seed's private cursor storage (`m_cursorInfo` then
fails to compile). A separate trial after seed adoption also exposed the missing
Win32Mouse::setPosition declaration in the seed. No files or ledger paths move,
no consolidation credit is claimed and all failed reconstructions were reverted.

Existing local/parameter names in the inspected complete bodies were retained;
no naming batch or unrelated scope was introduced. No source-path compatibility
audit is needed for this batch because no path changes. The push hook remains
responsible for the outgoing provider/consumer audit; no runtime claim is made.
