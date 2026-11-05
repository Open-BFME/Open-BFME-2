# HighlanderBody.cpp: absorb HighlanderBodyAttemptDamage.cpp (2026-11-05)

Prerequisite `ca541063aa` declares `attemptDamage` on the TU's local
ActiveBody/HighlanderBody views (body-interface table 0x00C5B390 slot 0 =
0x004C082B; ActiveBody's override 0x004BFE07).

Dry-run findings before the merge:
- with the donor's canonical `ActiveBody.h` spelling the merged object would
  not link: unresolved `?GetSnapshotName@ActiveBody@@UBEPBDXZ`,
  `?Rva004BE67E@ActiveBody@@UBE?AVAsciiString@@XZ`,
  `?applyDamageScalar@ActiveBody@@UAEXM@Z` (LINK-242 phantom override).
  The donor therefore takes the TU's view. class_gate refuses that private
  view in a standalone commit, so it lands only inside the merge, which
  deletes the donor.
- the donor's extern `??$bfmeMin@M@@YAABMABM0@Z` COMDAT
  (`reverse/dup_defs_baseline.tsv`: divergent), carried to the TU's earlier link
  place, "breaks another unit's copy". The helper is now `static`, so its copy
  is unit-local; attemptDamage still byte-matches.

Verification: `tu_skeleton --merge --dry-run` accepted both files, rejected
none; `./build.sh HighlanderBody.cpp` 7/7 matched (EH EXACT funclet $L310,
1 string, 1 float literal); `find_declared_unmatched` clean;
`link_check --new-variants` clean. Mixed satellite ConstIntGetters2.cpp
(0x004C07AB) stays. HighlanderBodyFriendNew.cpp (0x00251439) belongs to
another TU.

Path consumers: only `reverse/link_status.csv` (census output) and historical
attempt evidence name the old path; no tool, hook, include or registry key
(data, identity, header, gate baseline) does, so no debt key transfers.
