# Player CRT declaration cleanup, 2026-10-29

Base: `656dc5717d13f333beece8a9625e342cf57499c3`.
Source: `Code/GameEngine/Source/Common/RTS/PlayerInitFromDict.cpp`.

Remove only the local memcmp prototype. The existing ascii_string.h includes
string.h, so the real CRT declaration is already visible. The header queue's
own refresh API reduces this source from three copied declarations to two.
No include, compiler option, class, pin or ledger identity changes.

The supported build preserves all 31 matched rows, one data row, six string
literals and one empty-string reference; frozen-file checking passes. All
four EH graphs are EXACT. Before/after objects have identical 52 COMDAT
fingerprints and 157 external symbol entries. Strict link preparation passes;
ordinary previews retain LINKS and 4,707 authored bytes against census index
85f6b7f40c (2026-10-29 15:08 UTC). These previews are not census measurements.

The remaining free/memset deletions are blocked. Removing both, replacing the
three declarations with stdlib.h/string.h before or after the STL headers,
removing free alongside memcmp, and removing memset alongside memcmp all
change Player::initFromDict (0x002AFCDF, extent 2,762 bytes). The failed parent
grows two instruction bytes with register/scheduling changes: at +0x440 the
retail sequence begins 6a 00 b9 f4 d9 db 00, while one candidate begins
bb 00 b9 f4 d9 6a 00 8b cb. Branch differences begin at +0x220. The failed
variants also lose an unambiguous $L10490 binding (for example $L10513 and
$L10512 match equally). No failed source is retained. These reproduce the
existing declaration-sensitive blocker recorded on 2026-10-28; they are not
lost coverage or a false reject. The memcmp-only variant passes independently.

Local evidence: build/codexb4-player-{before,final,strict}.log,
build/codexb4-player-link-{before,final}.log and before/final-facts.json.
The final scoped batch audit exits 2: index 85f6b7f40c predates the base,
and affected consumer Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry both sources into the next scheduled census; consumer closure
remains unverified. Keep free and memset queued until a source-level
explanation preserves the parent bytes and independent EH identity. The
Coord3D member-growth obstacle remains open. No census gain is claimed.
