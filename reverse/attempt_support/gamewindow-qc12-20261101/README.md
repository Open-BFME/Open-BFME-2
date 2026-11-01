# GameWindow: ten native decisions and initial canonical header

Queue5229; base99e7d1af15; snapshotbfme2-toolchain-20261031a.
Target code addresses are RVAs, table addresses VAs. Native bytes attached.
GameWindow ctor3145F0 installsC0BBCC then calls WinInstanceData32225A onthis+30.
It zeroes through214 and sets1F4=1. Apt ctor51268C and its factory2D1E55
independently bound the base: secondary ctor onthis+218, total allocation27C.
Thus GameWindow extent218 and member30..1D7 extent1A8, no guessed donor size.
WinInstanceData ctor storesC0D830, has four string-word initializations188..194,
and final fields19C/1A0/1A4; virtual dtor3222B8 is a matched154-byte owner.
Its table is exactly one deleting-dtor entry. The shared WinInstanceData view
keeps unknown storage opaque and DECLARES its actual out-of-line lifetime
bodies; no trivial-destructor substitute or invented string member is supplied.
Known styleC and eight colors15C..178 come from matched Window color setters.
Copy/assignment are private undeclared bodies so unreconciled copying fails.

## All ten contract decisions resolved by hand

| Attribute | Decision |
| --- | --- |
| slot11 | Absent: exact44-byte C0BBCC datum has11entries0..10. |
| slot12 | Absent, same bound. |
| slot13 | Absent, same bound. |
| slot14 | Absent, same bound. |
| slot15 | Absent, same bound. |
| slot16 | Absent, same bound; one partial view's synthetic extras are rejected. |
| slot2 | Existing structural bfmeGoEHCb(uint,uint,uint), target104E45; matched typed provider and dispatch caller. Not guessed from majority unknown02 vote. |
| slot6 | Existing structural bool vslot6() const, target313913: compare input pointer at1E0 with LeftHUDInput. |
| slot7 | Pure fetchCreateInstance: C0BBCC[7]=imageVA0043B810 (RVA0003B810 __purecall); derived Apt table fills it with510D87. No null/default body invented. |
| slot8 | Existing structural bool vslot8() const, target31393A: input pointer1E0 comparison with GadgetPushButtonInput. isPushButton is only a semantic lead. |

Full native base table11 RVAs:
[314AC4,A0CFF,104E45,9DC05,8FF56,9FD78,313913,3B810,31393A,8FF78,50B5C6].
Slot0 is protected virtual scalar deleting dtor; slots1/2 enum-return input/
system dispatch,3 draw(void*),4 tooltip(WinInstanceData*,uint),5 structural
int-return body,9/10 existing bool predicate declarations. Every provider is
retained as an existing matched owner; headers contain no default bodies.
Native Apt table C659E8 and all its overrides are attached separately.
No source-base identity beyond the proven primary/no-secondary-base-data ABI
is claimed; this initial view follows the current matched no-base class shape.

Fields follow native ctor and callers: anchor4,status8, scalar position/size
C..28,userData2C, WinInstanceData30, inputData1D8, handler1DC, input1E0,
system1E4,draw1E8,tooltip1EC,extra1F0,phase1F4,next1F8,prev1FC,parent200,
child204,layout links208/20C,gadget210,editData214. The host donor incorrectly
calls the1FC pointer next; that is the reverse link relative to native linkWindow
and the owning GameWindow view. Its field must adopt the canonical prev label.
Structural Rva0031468C edit-data identity is retained; its four-string destructor
is an existing matched owner, not a recovered original application type.

## Header choice and first consumer

BFME1 dest is ambiguous between game_window.h and window_layout.h. Existing
Code units also include the donor GameClient/GameWindow.h. New target headers
are explicitly Bfme2GameWindow.h and Bfme2WinInstanceData.h in the official
Code/GameEngine/Include/GameClient folder, avoiding silent donor-header shadowing.
No external donor path is claimed as original BFME2 source. ZH/BFME1 are donor
facts only; target ctor/table/callers establish this view. Extra WinInstanceData
class and both actual header paths were claimed on this PC before editing.
Unused ambiguous GameWindow.h/WinInstanceData.h destination claims were released.

First consumer Disp8CmpBoolGettersFuncPtr.cpp removes its private GameWindow
and adopts the shared11-slot header; its two predicate bodies retain exact
bytes/relocations. All7served baseline units85/85 native rows and frozenPASS
(owner GameWindow.cpp has one pre-existing unclaimed-definition shadow note).
All7compiled object runtime graphs remain EXACT:103nondebug sections,
85external definitions,3weak bindings, no data/provider/default change.
This includes the predicate donor emitting no new vtable; all eleven native
base targets and all derived Apt targets continue to use the same bodies.
Normal hooks/header acceptance are required before first header bundle.

Other donors follow individually. Destructor and constructor consumers must
preserve the WinInstanceData lifetime and ALL emitted virtual providers.
processDestroyList's scalar deleting-dtor flag0/returned-pointer ABI must be
proved rather than changing it to a generic delete. No BehaviorModuleBase or
UpdateModule root adoption is attempted. Shared obstacle register is held
elsewhere; this README is its proposed native-ABI/remaining-consumer entry.

Host donor: canonical status8/phase1F4 and reverse-link1FC names; same185B draw traversal and all runtime providers, no table emission.
