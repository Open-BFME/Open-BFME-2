# AIAttackState secondary interface, 2026-11-13 (root20)

Banked change: constructor, destructor and the native goal-propagation callback
share Code/GameEngine/Include/GameLogic/AIAttackState.h. Both emitted secondary
tables now have all five native bindings. The primary State table remains
incomplete; neither vtable queue entry is retired here. No new original interface
name, unique code coverage, measured bridge retirement or game-runtime result is
claimed.

## Native secondary contract

The class extent is 0x50 bytes: State at +0, secondary receiver +0x20, nested
machine +0x24, parameters +0x28, team +0x2C, position +0x30, AsciiString +0x3C,
attacking-object byte +0x41, machine kind +0x4C. The destructor's former float[3]
position becomes the constructor-proven trivial Coord3D, preserving lifetimes
and EH. Coord3DInline.h keeps the constructor's native zero stores. A relative
ASCII shim include preserves the callback TU's original compiler flags.

| Slot | Native RVA | Body | Source contract |
|---|---|---|---|
| 0 | 0x000B3FD0 | 1B | Genuine native empty RET; existing notifyFired label |
| 1 | 0x003413FD | 34B | Set goal on parent and optional nested StateMachine |
| 2 | 0x005CB9FA | 5B | true, int argument, RET4 |
| 3 | 0x004A6A40 | 4B | byte at primary +0x41 |
| 4 | 0x003F712F | 4B | address of position at primary +0x30 |

NotifyWeaponFiredInterface is an existing unrecovered label. It has five slots
and no destructor slot. Neutral slot names retain the established byte and
void-pointer carriers; no donor identity is inferred. Slot 4's const_cast
preserves the existing void-pointer return contract.

Owning header adoption removed the constructor/destructor private views. Normal
add_match --icf-owner admitted four exact native providers with fold-proof=
notes, no pins or address aliases. Owning rename --to-class moved the existing
34B BfmeThingFAC callback to AIAttackState without changing its body. This uses
secondary-this -8 for the parent machine and +4 for the nested machine, calling
the established setGoalObject slot. The obsolete notifyFired alternatename is
removed.

## Verification

Final ./build.sh across all three sources passes 11/11 functions; destructor EH
is EXACT. There are no string, float or import references to check. Final objects
are current against source, flags and include dependencies. The adjacent JSON
contains source, header and object fingerprints.

Both 20B secondary COMDATs contain five DIR32 relocations with zero addends and
exact native targets: ten slot instances. Eight emitted whole-body checks (four
helpers in each object) and the separate 34B callback are exact. The remaining
36 external COMDATs retain bytes and relocation identities, including the one
callback name change. Only the two secondary-table COMDATs change; eight exact
inline copies are added. Both original 17-slot primary COMDATs are unchanged.

Scoped link_check at index 0e4b2640a1 reports 3/3 LINKS, 290 to 304 bytes.
The 14 bytes are folded existing code, not unique recovery. This historical-index
preview does not measure current real-link bridge retirement.

Owning hatch_counters --update removes this source's one alternatename ceiling.
It also removes two already-missing HEAD pin ceilings (005AF9EF,005D5095) and
normalizes two already-landed FX export allow stamps without changing their
counts. No symbols.csv edit or pin retirement belongs to this change.

## Remaining primary-table contract

Retail table 0x00813B78 has 19 slots; the current State view emits 17. Missing
loadPostProcess, name, onEnter and trailing methods cannot safely be appended
around conflicting inherited slots. Native slot 9 is the 11B query at 34B167;
slot 15 is the 19B nested-machine query at 34B154. Their old owners use integer
returns/nonconst members, while State declares bool const predicates.

A source-restoring diagnostic proves a bool-const slot 9 override emits the exact
11 bytes. Slot 9 is not an established code-generation blocker. The analogous
bool-const slot 15 diagnostic emits 21 bytes rather than 19: the existing byte
query at 4D7383 introduces extra Boolean normalization. Neither diagnostic
override remains in production.

Native forwarding and the Boolean fallback make a Boolean query contract
plausible; its original declaration is not recovered. Cached BFME1 matches
confirm caller/callee addresses, but their apparent bool name is only a pin
whose source calls an erased address through call0<bool>. That is not type
proof. Zero Hour lacks BFME's added slot and fallback byte. A genuine query and
caller contract diagnostic remains possible, followed by an owning admission
route. No cast, wrapper, private State copy or undefined provider is a repair.

The no-vote respell route refuses unsigned char E to bool _N (type and mangled
length change). To-class preserves return types, and this nonvirtual query is
absent from StateMachine's native table. Folding its private BfmeSub932C owner
also lacks special-member ownership proof. These evidence/admission prerequisites
remain; no false-reject workaround or verifier edit was attempted.

Scratch evidence under build/root-aiattack includes final-build.log,
interface-proof.json, interface-link.log, bool-probe.json, bool-candidate.cpp.txt
and the restored pre-change objects. The source batch is independently bankable;
primary completion and current-image measurement remain outstanding.
