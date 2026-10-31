# BodyModuleInterface: native decisions and first caller adoption

Base 0deda1e981. Queue 5795. Snapshot bfme2-toolchain-20261031a.
Target facts below use RVAs; tables are VAs. The new shared header defines
only the interface, never a BehaviorModule or BodyModule root profile.

## Native interface and all eight queued decisions

BodyModule ctor 4BD7FD installs pure interface C5AB68 at this+10, then
BodyModule defaults C5AC18. C5AB68 is 43 copies of __purecall 43B810 followed
by a zero word, in its 176-byte data-ledger extent. Thus this interface has
one vfptr, sizeof4, no bases/data/destructor, and 43 pure slots. The automatic
42-slot contract omits slot42 and is not authoritative. ActiveBody ctor
4BF6A1 installs C5B5B0 at +10. Highlander uses C5B390 at +10; its 43 targets
are identical to ActiveBody except slot0 (4C082B rather than 4BFE07).
Native table bytes and every exact-address ledger provider are attached.

| Queue attribute | Decision and target evidence |
| --- | --- |
| slot18 | ObjectID rva004BF897(), native4BF89721B and its existing matched enum-return row; it conditionally obtains the last attacker. No generic void slot. |
| slot19 | byte-return structural rva0052BAAB() const, target52BAAB7B; folded MOV AL,[ECX+disp]/RET. No original bool getter identity claimed. |
| slot20 | bool getBackCrushed() const, target4BF8B77B and existing matched row. |
| slot21 | setInitialHealth(float,bool), target4C0642319B and its matched typed body. Reject int argument vote. |
| slot31 | BfmeBodyDataPair8 rva004BDC56() by value, target4BDC5623B hidden result pointer and paired words; existing matched row uses struct return. Reject unproved getGrabOffset identity. |
| slot33 | setIndestructible(bool), target4BF18698B and existing typed body. |
| slot39 | rvaSlot39(BodyDamageType), not void*: ActiveBody::rva004BF969 and setDamageState path pass m_curDamageState at virtual+9C. Symbiotic4C121B forwards the same stack word, so its old opaque pointer view is not stronger evidence. |
| slot40 | rvaSlot40(float,bool), not void*: native internalChangeHealth4BF005 and matched caller pass m_currentHealth and delta>0 to virtual+A0. Symbiotic4C123C ignores first arg and reads second byte, hence cannot establish pointer first arg. |

## Remaining slot signatures and provenance

The header lists every slot0..42 explicitly, all pure. Existing matched
providers establish damage/healing0/1, float estimate2 (DamageInfoInput is
class/ref), reapply-state3 (calls interface8 then9), float getters4..7,
state8/9, particles10, TWO-enum veterancy11, armor12/13, BitFlags<21> by-value14,
member-pointer15 and timestamp words16/17. Structural declaration constness
for folded getters is a convention, not a claim of recovered original names.
The ctor's private BitFlags<11> view is not imported over the independently
matched BitFlags<21> return row. Slots22..27 are typed max-health, noarg
4BDB37, two byte setters, float scalar multiply and float scalar getter.
Slot28 is matched AsciiString by-value const return4BE67E;29 is integer chase
4BDC48;30 float chase4BDC4F;32 is TWO-argument internalChangeHealth(float,
DamageInfo*), not ZH's one-argument declaration;34 is a byte getter;35 float
chase4BDC41;36 noarg forwardAndFinish4BDC03. Slot37 has a nonempty provider
in tableC5BB38:4C15F7 is the matched byte setter, RET4; therefore it is not
inferred merely from shared RET4 default47A69C. Slot38 is the existing
Object* bool130B PorcupineFormationBodyModule override4C2127. Slot41 is
4BF893 LEA EAX,[ECX-10]/RET, a complete BodyModule* structural getIface.
Slot42 is101CBE MOVSS from stackfloat to interface+8/RET4, retained under
its existing address identity. No nominal original identity is invented.

ZH pinned input7a8a034afa7d is a donor fact: its BodyModule.h has a DIFFERENT
slot order, three veterancy args, different initial-health and internal-health
signatures. It is not copied as target ABI. BFME1 only forward declarations
were found for this interface; target tables/callers decide this header.

## Safety and scope

HighlanderBodyAttemptDamage.cpp replaces only its five-slot private interface
with this header. Its other private ancestor views are unchanged. Native
attemptDamage remains slot0 and getHealth slot4. ALL TWO externally defined
code bodies (including min helper), their complete section bytes and every
relocation match baseline exactly. Both before and after emit ZERO vtables.
No new/default provider or runtime binding is emitted, no native table datum
is changed, and all 43 actual Highlander table providers remain untouched.
This is the additional virtual-provider check beyond 1/1 exact row bytes.
Header accept PASS. Normal commit hooks are required before bundling.

The other served donor ActiveBodyConstructor.cpp is deliberately untouched:
its baseline COFF already emits a one-entry pure BodyModuleInterface view,
whereas native ActiveBody has43 concrete providers. Its primary/behavior
profiles are incomplete as well (see coff-proof.json baseline tables).
Replacing just that private interface would not prove native provider closure;
43 pure inherited slots must never be counted as the concrete native table.
Remaining prerequisite is a full BodyModule/ActiveBody override/provider
profile, with the BehaviorModule parent getter closure independently proven.
No adoption of BehaviorModuleBase/UpdateModule roots is attempted.

Proposed shared obstacle update (register file claim was held elsewhere):
BodyModuleInterface now has native43-slot header and a verified no-vtable
caller adoption; ctor/dtor consumers still need full native BodyModule and
ActiveBody table providers, not merely byte matching or a pure/default base.
No new census-linked coverage is claimed. No source paths or rows moved.
