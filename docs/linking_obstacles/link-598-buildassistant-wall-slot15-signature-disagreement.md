### LINK-598: BuildAssistant wall caller and canonical slot 15 disagree

Status: Blocked. Updated: 2026-11-05; inspected revision: `bfd57880db`.
`AIBuildableWallSegment::build` (`0x00596D99`) passes `Coord3D *` as the
second argument of BuildAssistant slot 15; `BuildAssistantClass.h` declares
`const ThingTemplate *`. Direct adoption fails C2664. The caller was restored
and its eleven rows reverified; reconcile the native parameter contract before
retrying, without casting away the disagreement. Four other BuildAssistant
units adopted the header and retired four queue rows with identical runtime
object graphs; their preview preserves 12,967 bytes. Census confirmation and
the remaining five queue items are still open.
[Cohort verification and remaining prerequisites](../../reverse/attempt_support/buildassistant-header-cohort-20261105-codex4.md).
