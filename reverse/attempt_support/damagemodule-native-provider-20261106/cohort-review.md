# DamageModule registered fold: minimum scope and blockers

2026-11-06; inspected current HEAD `6d19e6b1f0`. Read live AGENTS.md,
`reverse/attempt_support/damagemodule-dtor-identity-20261105-lk33.md`, relevant
LINK-006/LINK-181/LINK-514 handoffs, current sources and canonical headers.
No builds, claims, tracked edits, network or workers. Root owns private proofs.

## What changed since the handoff

The unrelated 2CD7B row in EvacuateDamageCtorModuleFactoryBody.cpp is now
correctly `INIMacroTable::~INIMacroTable()`, with the genuine typed hash/set
members. It no longer requires the false implicit EvacuateDamage destructor.
The old private DamageModule still has no destructor declaration, so it still
emits its wrong implicit destructor reaching PB_DeepBase. Declaration-only
suppression of that implicit body is now a plausible separate prerequisite;
it does not by itself provide the correct named DamageModule destructor.

Current rename.py supports a registered NEW with every spelling/object
consumer supplied as prepared source, adopting its canonical header and
spelling OLD nowhere. The historical tooling refusal is no longer the
blocking implementation gap. Native identity proof remains as recorded:
DamageModule ctor4B9704, destructor4B96CC, deleting destructor4B973B, and the
three native subobject tables. The destructor's Behavior tables are teardown
stores, not proof of another DamageModule class.

## Exact current OLD-token source cohort

The following **eight tracked sources** have an actual OLD type/mangled-token
use and belong in the registered-destination prepared fold scope, subject to
the tool's current object-consumer closure:

| Source (relative to Code/GameEngine/Source/) | Required preparation |
| --- | --- |
| Common/Rva0049B47CThreeVptrDerived.cpp | Replace only the OLD Damage family view with canonical DamageModuleClass.h; define inline BehaviorModule::~BehaviorModule() and DamageModule::~DamageModule(); remove OLD_B2/OLD anchor where unused; preserve the other unrelated opaque families. |
| Common/Rva004B96CCDerived.cpp | Reshape the three children onto canonical DamageModule and preserve their actual full native table providers; see blockers below. Remove obsolete dummy B2 alias machinery only when the real providers replace it. |
| Common/TailJumpWrappers5B.cpp | Use canonical DamageModule as the existing novtable CallHelpOnDamage base; retain the genuine 5-byte tail-call destructor. |
| Common/TailJumpWrappers5B_~Rva002563CE.cpp | Remove its unused OLD/CallHelp declaration leftovers or adopt the same canonical base; no new destructor body. |
| Common/W3DAptComponentView3D.cpp | Same declaration-only cleanup; its unrelated rows remain intact. |
| GameLogic/Object/Behavior/TransitionDamageFXDtor.cpp | Remove private OLD/primary/dummy interface projections; adopt canonical base while retaining +D4 member destruction, full actual child tables and protected destructor signature. |
| GameLogic/Object/Damage/EvacuateDamage.cpp | Remove OLD class/typedef and fake interfaces, include canonical header, retain the real protected4BAEC8 destructor and native list/member offsets; preserve actual child table overrides. |
| GameLogic/Object/Die/HordeTransportContainDamageCtor.cpp | Already includes canonical base; update the OLD-bearing explicit table reference to the actual emitted canonical-view table spelling. Derive that spelling from the compiler/provider; a text substitution to `6BDamageModule@@@` is not proof. Audit all three stored table names. |

Literal `rg Rva004B96CC` also finds BoneFXDamage.cpp, ReflectDamage.cpp and
HordeTransportContainDamage.cpp. Their hits are only the longer residual
filename `Rva004B96CCDerived.cpp` in comments, not the OLD class token. They
are not additional prepared OLD-token sources solely for that reason. They
remain important co-definers/callback owners and become actual preparation
scope if a coupled child reconciliation needs them.

Two additional sources form the immediate practical dependency boundary,
though they do not spell OLD: DamageModuleCtor.cpp must use the canonical
header/body so the native own-table identity and actual vtables are emitted;
EvacuateDamageCtorModuleFactoryBody.cpp must stop emitting the wrong implicit
DamageModule destructor after the INIMacro row fix. Thus eight is the
syntactic fold minimum, **not evidence that an eight-file atomic repair is
already viable**.

## Child reshaping cannot discard native callbacks

Canonical DamageModule is 0x14 bytes: BehaviorModule +0..F, then its three-slot
DamageModuleInterface at +10. Replacing the old 0xC primary shell by canonical
DamageModule **and retaining MiBase1/B2 as extra bases** moves/duplicates
subobjects. The children should have one canonical DamageModule base, with
their real overrides in the inherited slots, not another pair of fake bases.
Callback virtuals belong to the secondary interface; adding new unrelated
primary slots or spreading novtable to suppress emission is no repair.

Native +10 callback tables, read directly from retail (code RVAs):

| Child/table VA | Native three callbacks |
| --- | --- |
| BoneFXDamage / C597E8 | 47A69C,47A69C,4B985E |
| ReflectDamage / C59CB0 | 4BABFA,47A69C,D1407 |
| EvacuateDamage / C59E20 | **4BAFE5**,47A69C,D1407 |
| HordeTransportContainDamage / C59E64 | 4BB176,47A69C,D1407 |

Concrete source/name prerequisites:

* **BoneFXDamage:** an existing full canonical-base declaration is already in
  BoneFXDamage.cpp, with real pool-key, onObjectCreated, snapshot/xfer/load
  overrides and all three callbacks. The destructor unit can use that actual
  declaration/provider vocabulary; it must not keep the old first-B2-slot
  alias to FXParticleSystem::DoXfer. Merely adopting the canonical base with
  no child overrides would replace native callbacks by purecall entries.
* **Rva004BAB36:** its rowed destructor/deleting destructor belong to the
  ReflectDamage table, but the real callback is ReflectDamage::onDamage.
  Declaring Rva004BAB36::onDamage creates a different provider. With no new
  aliases/wrappers/body copies allowed, establish/apply the supported child
  class-fold into ReflectDamage (or equivalent genuine existing-class
  reconciliation) and adopt its full target profile. ReflectDamage.cpp's
  current constructor still uses a private dummy DamageModule view, so its
  table/profile is not already canonical just because the name is readable.
* **Rva004BB0CC:** likewise needs the HordeTransportContainDamage identity
  reconciliation to reuse the actual callback provider. Its current callback
  name is `rva004BB176`, not canonical interface `onDamage`; a supported
  identifier reconciliation is required for it to override that slot. Its
  manual ctor table references must follow the real emitted table names.
* **EvacuateDamage:** the current actual onDamage row at4BAF55 is mangled
  `?onDamage@EvacuateDamage@@UAEXPAUDamageInfo@@@Z` (struct DamageInfo), while
  the canonical interface declares class DamageInfo (`PAV`). This requires
  genuine class-key/signature reconciliation of the existing provider; a
  canonical declaration alone creates a different unresolved symbol. Also,
  the native interface slot names **4BAFE5 rather than4BAF55**. Its exact
  provider/adjustment relation was not investigated in this bounded pass;
  preserve that native target, not merely the familiar function name.
* **TransitionDamageFX:** its dtor file has only the lifetime/member shell;
  adopting the full base makes unimplemented interface callbacks pure.
  Its other source still has a private placeholder interface profile. Its
  real primary/secondary override declarations and providers must be
  reconciled before calling the new emitted child tables correct.

Existing novtable CallHelpOnDamage is different: its known tail-only body
deliberately emits no child tables. Retain that existing behavior and qualify
its actual base call; do not generalize it to the other emitting children.

## Real scalar deleting destructor: bounded conclusion

The current row4B973B/28 belongs to the Common definer. Its old new/delete
anchor works only because the fake OLD type is concrete. Canonical DamageModule
is genuinely abstract. Do not instantiate it, introduce a fake concrete child,
write a scratch emitter, add aliases, or substitute a pointer-delete anchor:
that only dispatches virtually and is not proof of emission of this body's
real scalar deleting destructor.

The canonical constructor's actual class-vtable emission is a legitimate
known mechanism that requires the scalar/vector deleting-destructor family;
the prior handoff already observed its `??_E` slot spelling. A weak `??_E` to
`??_G` binding can be normal compiler machinery, but check actual emitted
definitions/bindings and exact28 bytes; a spelling in a table is not enough.
**This read-only pass has not proved that the canonical destructor definer
itself naturally emits the rowed G after removing the abstract anchor.**
Root's private canonical-definer probe is the correct deciding test. If G is
absent there, record that concrete emission blocker rather than force it.
The committed TU map currently leaves4B96CC/4B9704/4B973B unassigned, so
hand-repointing G to the constructor file is not a supported fallback. No
source move or new emitter workaround is proposed.

## Publication boundary

Use prepared registered-NEW fold support to adopt the real canonical header,
not a new private DamageModule copy. The fold can own row/notes/body-owner/
tombstone/pin cleanup (including the redundant named dtor pin). Its complete
scope is the prepared text plus current object consumers. Existing inherited
callback providers and all selected COMDAT implementations remain part of
the actual repair, even where a 25-byte child destructor still matches.
The minimum currently demonstrated outcome is a precise prerequisite cohort
and blockers, not a proven complete atomic patch.
