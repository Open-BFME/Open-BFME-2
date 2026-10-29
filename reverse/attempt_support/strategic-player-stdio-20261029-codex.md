# Strategic player status CRT declarations

Base: `8f350110e4`, 2026-10-29. Source:
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/StrategicPlayerStatusCallbacks.cpp`.

The Microsoft-header picker served the local sprintf and _snprintf
declarations. Replace both with the toolchain's real `<stdio.h>`. The unit
already uses `/MD`; the header preserves the two imported CRT callees without
local configuration overrides. No function body, shared header, ledger name,
source path or pin changes.

Before and after `./build.sh` pass all seven function rows, four literal
references and two named imports. Declaration checks pass before and after;
there are no EH rows in this source. Ordinary before/after link previews both
report LINKS for 684 authored bytes against the published index at
`840db2d676`, 2026-10-28 20:44. This preserves the scoped preview result and
does not establish a new census result or linking gain.

The first staged-tree batch audit is inconclusive: the index predates the
base and the changed source lacks a strict current receipt. Further strict
preparation passes for this explicit source, preserving all seven rows and
both named imports. The repeated audit then reaches external consumers and
remains inconclusive because
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. Carry that consumer and this provider scope into the next scheduled
census; full consumer closure is unverified.

The Microsoft-header auditor classifies the changed file as clean. Its
remaining `Shell` spelling collision is not a local Microsoft declaration.
The owning `refresh_queue` API removes this source's two-definition entry
while preserving unrelated queue records. No baseline or whitelist changes.
