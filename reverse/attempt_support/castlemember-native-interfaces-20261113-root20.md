# CastleMemberBehavior native interface prerequisite

No source changes were attempted or banked. The original claimed producer and
the Object.cpp area changed by the pull pass 115/115 function rows and one data
row. The native table inventory is preserved in the adjacent JSON file.

The constructor at395B66 calls BehaviorModule253330 and constructs the extra
interface at+10. The12-slot primary,47-slot BehaviorModule interface and native
getDamage conversion at2533D3 establish the existing DamageModuleInterface
contract. getUpdate remains null. The transferred fields14/18 are ObjectIDs.
The constructor's base work is inlined; an out-of-line DamageModule lifecycle
call would not reproduce its bytes. The destructor restores BehaviorModule's
tables and calls the Snapshot cleanup.

Primary81A22C has the deleting dtor395BAF,loadPostProcess58B03E,getter3957C0,
xfer3957C6,key3959B5, four empty slots, the empty two-argument callback50B238
and two zero getters. Interface81A170 differs from BehaviorModule only at slot4
(getDamage2533D3) and45(mapLoadPostProcess399165). Interface81A160 has three
positive pointers:39922D,47A69C,397BD9. The next zero is alignment.

Remaining supported-admission prerequisites:

- Shared BehaviorModuleInterface slot45 is currently slot45(int); the native
  callback is mapLoadPostProcess(const Dict*). A new derived method with that
  name would not override the current canonical declaration.
- Getter3957C0 is currently the nonvirtual name() row in the shared getter TU.
- Callback39922D currently uses a CastleBehavior/RvaArg view; native reads one
  damage pointer and returns RET4 from the+10 receiver. Callback397BD9 is
  currently onStateChanged(int,int,int); native consumes three words and RET12.
  The existing shared damage interface supplies the intended typed contract;
  this observation is not a claim of original source spelling.
- The empty CastleMemberBehavior onHealing callback has no admitted symbol.
  Another cross-TU ICF row would encounter the ownership A1 restriction.

The producer cohort includes CastleMemberBehavior.cpp and its constructor TU;
its getter and two callback owner TUs also need coherent reconciliation.
Existing DamageModule loadPostProcess/getDamage and BehaviorModule destructor
providers are already admitted. No new aliases, pins, hidden definitions or
ownership-rule exceptions were added. No bridge retirement is claimed.
