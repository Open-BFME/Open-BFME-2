# AnnounceBirthAndDeathBehavior decisions and safe DieModuleInterface prerequisite

Queue5343; baseeeffbe8291; snapshotbfme2-toolchain-20261031a.
Code addresses below are RVAs; tables are VAs. No BehaviorModuleBase or
UpdateModule root adoption is performed. CreateModule has no shared header on
this base, so full requested-class adoption remains a parent prerequisite.

## Nine decisions from native evidence

Factory24C7C7 allocates1Chex and calls ctor485125. Ctor calls CreateModule
4B8CF7 and stores C1C780 then C4A54C at18, C4A61C at0, C4A560 atC,
and C4A550 at10. Parent4B8CF7 independently installs Create tables at0/C/10
and sets bool14 to1. Thus CreateModule extent18, DieModuleInterface extent4
at18 and no new own data. The partial constructor's pointer spellings do not
turn inherited vfptrs into ordinary fields.

| Queued attribute | Hand decision |
| --- | --- |
| inherited@0 | inherited primary vfptr at0, native storeC4A61C and12callable entries. |
| inherited@C | inherited behavior vfptrC, nativeC4A560 and47entries; not opaque data pointer. |
| inherited@10 | inherited Create interface vfptr10, nativeC4A550 and4entries. |
| inherited@18 | Die interface vfptr18, nativeC4A54C one entry, beyond Create extent18. |
| name@4 | existing m_moduleData, not owner Thing*: native announcements obtain Object at complete8; data is4 as in existing Module chain. No original member spelling claimed. |
| field@C | no separate own field; same inherited behavior vfptr. |
| field@10 | no separate own field; same inherited Create vfptr. |
| field@18 | same Die base vfptr, not an independently allocated pointer field. |
| slot0 | primary0=2549A5 deleting-dtor provider; pool-name getter is primary4=485163. Create0=4851AD onCreate; Die0=4851C7 onDie. Competing slot votes mix distinct tables. |

Full native tables attached. Primary12 is
[2549A5,497805,48515D,4851E3,485163,B3FD0,B3FD0,B3FD0,B3FD0,50B238,D43D0,D43D0].
Create4=[4851AD,250A49,B3FD0,98CBC]; Die1=[4851C7]. Behavior47 has
NONNULL getters3=2533D3 (complete+10) and7=45875F (complete+18), rather than
null base defaults. The new Die interface must not be mistaken for a claim
that the Create/behavior parent providers are already reconciled.

## Safe prerequisite established now

Existing DieModule.h already defined DieModuleInterface together with the
behavior root. The exact one-pure-slot declaration is extracted into
GameLogic/Module/DieModuleInterface.h; old DieModule.h includes it and keeps
EVERY DieModule/BehaviorModule root declaration and default body unchanged.
This avoids duplicate class definitions and lets the announcement caller use
the interface without importing or adopting root profiles. All three extra
keys were claimed on this PC as qc-12 before edits: class:DieModuleInterface,
file:.../DieModule.h and file:.../DieModuleInterface.h.

Native pure Die interface tableC1C780 is exactly one pointer, imageVA0043B810
(RVA0003B810 __purecall). No data, bases or virtual destructor. Native onDie
4851C7 has the existing constDamageInfo* typed row and RET4; ZH DieModule.h
independently names that signature as a DONOR fact. The new shared declaration
is byte-for-byte the existing header's declaration, not a transplanted layout.
The announcement source replaces ONLY its private Die interface with the new
header. Its other ancestor and Announce views remain unchanged adoption debt.
The original Announce constructor and its dummy table-address definitions are
untouched; no native table-data verification for those dummies is claimed.

## Virtual-provider and runtime proof beyond row matching

Both served donors initially pass frozen checks and3/3 native code rows.
All direct DieModule.h users and the changed announcement caller (24unique
units total) build148/148 rows before and after extraction. The announcement
caller has the same2 code bodies/relocations and ZERO vtable definitions.
All64 native Announce table entries therefore retain their existing providers
outside that unit; onCreate remains create0 and onDie remains die0.

Across all24units,40 emitted vtables have identical complete data bytes and
relocations, and13 weak bindings retain the same fallback symbol and mode.
The841 function definitions retain their runtime bodies. Some compiler-local
EH labels are renumbered, so string equality of $L/$T names is NOT used as
proof. Baseline objects were rebuilt with official build.sh and retained;
coff_runtime_graph.py compares EVERY non-debug section (including EH tables),
raw-byte hash/size/characteristics, COMDAT selection/association, and every
relocation's resolved section/value or external symbol. Defined external
names and weak fallback modes are also compared. This proves an identical
runtime graph despite local debug/compiler numbering. Debug sections alone
are excluded. Result:24units,3172runtime sections,3062external definitions,
13weak bindings, ZERO changed graphs. Before/after graphs and reader included.
No slot changes target or falls through to a newly inherited base default.

Tools: build.sh, find_declared_unmatched (both changed headers and source all
PASS), header_adopt_lane accept for DieModuleInterface, normal commit hooks.
One NEW donor adoption credit is the Die interface prerequisite in the
announcement caller; NOT a completed AnnounceBirthAndDeathBehavior adoption.
No source deletion, row move, new runtime body, pin, hatch, alias or tools edit.

Remaining blocker class:CreateModule: canonical complete12/47/4-slot parent
profile plus Announce's behavior7 override must preserve2533D3 and45875F.
All nine queued decisions are resolved; undecided attributes are not the stop.
Shared obstacle register was held elsewhere; this README is the proposed
native-ABI and remaining-parent entry for its owner.
