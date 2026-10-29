# Lua debugger header cleanup and TU evidence boundary

Inspected base: `4b3df77c0e06d03d5e74c171b8f1182d813f5e5d`.
Preview index: `85f6b7f40c`, 2026-10-29 15:08.

## Verified cleanup

Replace the local sprintf declaration in Rva00333BCALog.cpp with stdio.h,
and the local strcmp/strncmp declarations in Rva00333CD1Console.cpp with
string.h. Configure `_CRTIMP` locally as dllimport: these units do not use
/MD, but retail calls sprintf and strncmp through the IAT. The toolchain's
x86 string.h declares strcmp without `_CRTIMP`, retaining its direct call.
Including the headers without this configuration changes the call instructions
and fails byte verification; that intermediate trial was corrected.

Both complete rows (263 and 369 bytes), 21 literals and six named imports
verify. Frozen-source and Microsoft-header checks pass. The owning scanner's
scoped refresh removes exactly these two queue entries, retaining unrelated
records. Comparing the pre-edit and final objects through the census COFF
reader preserves all 23 COMDAT digests/sizes and all 35 external symbol
records (name, value, defined/undefined status and storage class).
Strict current preparation passes for both providers. Ordinary preview
retains LINKS, 262 + 368 = 630 authored bytes, before and after the edit.
These are scoped cleanup checks, with no census gain claimed.

The staged-tree batch audit is INCONCLUSIVE (exit 2): index 85f6b7f40c
predates the outgoing base and affected consumer
Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp lacks a current
receipt. Carry both providers and this consumer into the next scheduled
census; the scoped preview does not establish consumer-wide selection.

## Selected TU-evidence task

The default picker claimed the five-source run 0x00333B02..0x00333E42:
Rva00333B02Set.cpp, BfmeLogMsg574.cpp, Rva00333BCALog.cpp,
Rva00333CD1Console.cpp and luaB_debug.cpp. No row was moved or renamed.
The original five-file scope verifies all eight function/cleanup rows and
one data row. All definitions are matched. A current in-memory map for
Rva00333B02Set.cpp still reports three code rows with no assignment;
tu_evidence.py --source yields only its CSV header, with no layout proposal.

Target facts: the run's nearby map proposals name LuaScriptEngine.cpp below
and LuaDrawableState.cpp above; neither supplies a bracket for these rows.
The debugger strings at data RVAs 0x0080DE7C..0x0080E010 are referenced by
the traceback and console bodies, but do not name a source file. The
consolidation planner finds no approved destination for either body or the
logger. WorldBuilder leads for the logger and traceback are placeholders;
the console lead is PIN_ONLY, not an independently asserted name.

Donor facts: BFME 1 e42b9782 has similar console logic in reconstructed
LuaScriptEngine.cpp, a small io_debug wrapper in Libraries/Source/Lua,
and the same entry message in ObjectSpy.cpp. The local Zero Hour
ScriptEngine directory has no LuaScriptEngine.cpp. Those donor source
placements and shared strings do not prove a BFME 2 TU or function name.

Remaining prerequisite: a target file reference, independently proven name
with an eligible definition, or a valid retail-layout bracket. Do not place
the run from address proximity or the reconstructed BFME 1 path alone.
The supported planning report under build/consolidation is scratch, predates
the header edits, and must be regenerated before reuse. No regenerated TU
map is committed and no TU-approval/source-file reduction is claimed.

## Reference freshness

Fetched official BFME 1 master at fbfea42889700c5141ff601c2d2134b50ec84448.
The update scope remains held by yasinschroeder-codexb (about 3.3 hours left
at the check). Retain the verified e42b9782 input pin and preserve that
worker's scope. No submodule input changed and no successful freshness
stamp was written.
