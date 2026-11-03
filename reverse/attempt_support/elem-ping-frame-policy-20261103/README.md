# Elem005DB98E consolidation: incompatible frame policies

Inspected revision: 678d949f99. The supported Common consolidation planner was
run before the attempt. Its PortNegotiationSchema investigation packet reports
compiler-settings-disagree and routing blockers; it does not approve placement.
The current TU map instead approves the two rows below for the provisional
Code/GameEngine/Source/Common/Elem005DB98E.cpp TU. No real retail file name is
claimed.

- Seed: RVA 0x005DB885, 95 bytes, rva005DB885(int), /MD /DNDEBUG /Oy-.
- Donor: RVA 0x005DB8F7, 49 bytes, rva005DB8F7(float,float,float),
  Code/GameEngine/Source/Common/Rva005DB8F7Set.cpp, /MD /DNDEBUG.

`tu_views.py ... --dry-run` finds a compatible union of the private class
methods and the same fields. `tu_skeleton.py --merge ... --dry-run` accepts
no donor: the setter fails bytes under the seed flags. Its guard identifies
both units as census-linked. GapBodiesSeat1C.cpp and Elem005DB98EFalloff.cpp
remain mixed donors and were not edited.

Target facts, read directly from the retail PE at the ledger RVAs:
0x005DB885 starts push ebp; mov ebp,esp; push esi; push edi. Its timestamp
argument is read/written at [ebp+8]. 0x005DB8F7 instead starts movss
xmm0,[esp+4]; push esi; mov esi,ecx and reads later arguments at [esp+0xc]
and [esp+0x10]. These are different function frame policies, not a class-layout
conflict. The ledger uses RVAs; disassemble PE.get_data(rva, size).

A controlled normal `./build.sh` trial removed only /Oy- from the seed's cl
line. The smoothing function failed: compiled prologue push esi; push edi and
timestamp accesses at [esp+0xc], versus retail's frame above. The source was
restored immediately; no nonmatching attempt remains in Code/.

Verification after restoration: ./build.sh for the seed passes 1/1 rows,
two compiler floats and one named import; the unedited setter passes 1/1 rows
and one named import. find_declared_unmatched for both reports all definitions
matched. No rows, pins, aliases, hatches, registers or source paths changed.

Next step: a source/code-generation recovery that reproduces the smoothing
function's frame under a shared TU policy, supported by target evidence, or an
approved compiler-policy mechanism. Repeating class reconciliation or the same
merge without resolving frame policy cannot fix this failure. No link or census
gain is claimed.
