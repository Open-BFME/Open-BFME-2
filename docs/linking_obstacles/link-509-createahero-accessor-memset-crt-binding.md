### LINK-509: CreateAHero accessor references a retired memset thunk spelling
Status: Repair verified in preview / awaiting real link. Updated: 2026-11-05; inspected revision: f319f63d21.
Affected unit: `Code/GameEngine/Source/Common/Rva00219B9EAccessor.cpp`; real-link blocker `?ji_006291ae@@YAPAXPAXHI@Z`.
Completed: use `<string.h>` and the rowed `_memset` CRT thunk; 91/91 rows exact; remove one redundant alias while the identical link-wide alias remains in another compiled unit.
Remaining / next check: next scheduled real link must confirm both units leave exit_link_blockers.tsv; Rva0051C0E7Ctor.cpp's separate legacy reference was repaired by ce7565b2ca ([current constructor verification](../../reverse/attempt_support/rva0051c0e7-memset-followup-20261105-codex4.md)), and the then-unreferenced `?ji_006291ae@@YAPAXPAXHI@Z` pin was dropped (2026-11-05).
Remaining / next check: next scheduled real link must confirm both units leave exit_link_blockers.tsv; Rva0051C0E7Ctor.cpp's reference went in ce7565b2ca and the then-unreferenced `?ji_006291ae@@YAPAXPAXHI@Z` pin was dropped (2026-11-05).
Remaining / next check: next scheduled real link must confirm removal from exit_link_blockers.tsv; both the accessor and Rva0051C0E7Ctor.cpp now have verified source repairs.
Clearance: accessor and CRT provider LINKS with strict current receipts; census already counted this accessor linked, so no census gain claimed.
[Evidence and verification scope](../../reverse/attempt_support/createahero-memset-crt-20261105-codex3.md).
2026-11-05: the constructor repair already landed in `ce7565b2ca`; current checks retain 7/7 exact rows and a 326/326-byte preview. [Status evidence](../../reverse/attempt_support/memset-constructor-status-20261105-codex5.md).
