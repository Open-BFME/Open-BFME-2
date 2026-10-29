# Consumer receipt preparation refused: Eva and thread

2026-10-29, source cleanup rebased as55e00edf5a3 on385303a9af9.
The earlier normal push gate passed41/41 rows across5 sources,4 data
rows,4 EXACT EH graphs and26 DIR32 symbols. Its loss/selection audit was
inconclusive on Eva.cpp and thread.cpp; both cached objects were ordinary
current but lacked strict include-search inventories (76 and42 headers).

The supported bounded command was run exactly on those two consumers:

    python3 tools/link_check.py --prepare-current Code/GameEngine/Source/GameClient/Eva.cpp Code/Libraries/Source/WWVegas/WWLib/thread.cpp

Actual exit1, after23 seconds. Both sources report:

    (macro or parent-traversing include has unknown search roots)

The preparation therefore refuses Eva's strict reusable receipt before its
normal byte-gate phase. It wrote ordinary compiler objects only; no source,
ledger ownership, pin, compiler setting or verifier was changed by this
attempt. Do not call these newly compiled objects strict-current, do not
forge an inventory, mark a fresh-census exception or weaken the check.
The existing35B input body and duplicate cleanup remain backed by the
prior157/157 six-source verification, two data tables and6/6 preview.

Publication context: the original push had finished its code gates and
waited on another landing window. While waiting, origin/master advanced;
merge-base --is-ancestor origin/master HEAD returned1. After its multi-GB
fetch/index-pack finished, only that obsolete own push subtree was
terminated; no foreign process or live index-pack was signalled. The
unchanged wrapper recorded actual exit241. The same source commit was
rebased normally, without replaying admission or the mapped verdict.
The cleanup is still local, not published. This is no new matched-byte or
census-linked-byte gain.

Stop condition: the contributor instruction says to stop and report a gate
refusal, including in untouched sources. No include rewrite or gate edit
was attempted here. The next legitimate prerequisite is a separately
claimed, byte-verified repair of each consumer's include declarations or
another supported maintainer proof of those exact compiler inputs. Preserve
all current row bodies and include resolution; re-run strict preparation
and the normal affected-consumer audit after that repair. A header spelling
change alone is not proof of identical lookup.

Model GPT-6; t=1 for the bounded receipt attempt; lane=R; budget=30m.
Body/source cleanup time is separately recorded as5 minutes. Claims are
released because this publication attempt is blocked.
