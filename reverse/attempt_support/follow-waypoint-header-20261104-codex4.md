# Follow-waypoint header cleanup, 2026-11-04

Inspected revision: `fb705debe0774f5835a869de303b14588cd50ed9`.
Scope: `Code/GameEngine/Source/GameLogic/AI/AIFollowWaypointPathStateOnEnter.cpp`,
row `?onEnter@AIFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ`,
retail RVA `0x0034ED7B`, extent 649 bytes.

Target facts: disassembling this row with `build.read_target_bytes` and
Capstone shows direct calls at `0x0034EF3F` and `0x0034EF85` to `0x002CEC42`.
The current ledger and `Common/FprintfAppendLine.cpp` identify that destination
as the game's void format-and-append helper, whose receiver has a vector at +4.
It is not CRT's FILE-based fprintf. A trial with stdio.h byte-matched but gave
the receiver and result the wrong source identities; that trial was reverted.
No donor identity or layout is inferred from the call spelling.

Applied: obtain NULL from stddef.h, delete the local macro, and replace the
unused partial FprintfTarget definition with an opaque forward declaration.
Keep the game helper's existing void declaration and bindings. No symbol,
ledger, pin, source path, or debt-register key changes.

Checks: ./build.sh of the source passed 1/1 matched rows (649 bytes), four
string literals, and three float literals. find_declared_unmatched.py found
all defined functions matched before and after. ms_header_audit.py show now
reports one finding (the game helper collision), down from two; its supported
scan --write-queue refresh retains that finding. git diff --check passed.

Remaining prerequisite: establish logger identity across provider and consumers
through the naming lane before changing the misleading fprintf spelling.
This cleanup claims no linked-byte gain or census measurement.
