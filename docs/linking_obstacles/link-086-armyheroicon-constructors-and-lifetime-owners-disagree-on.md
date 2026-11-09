### LINK-086: ArmyHeroIcon constructors and lifetime owners disagree on class and virtual signatures

Status: Blocked on class and table reconciliation. Updated: 2026-10-26; inspected revision: `2a45addda1806342ac5c52757f63be902dcd428e`.

**2026-11-08 current constructor and vbtable boundary:** Rva005E39F3Ctor.cpp
now reports LINKS, 289->289 authored bytes against index f4727bbd09; all six
code rows and two EH graphs pass. The picker's first no-retail-slots refusal
is the ??_8 virtual-base table at 0x00877C94. Its compiled and retail offsets
are exactly (0,36), with no relocations. data_ledger intentionally gives
vbtables kind=vtable, and the positive-slot bridge selector incorrectly
includes them. A false reject is banked before any tooling edit; no source,
ledger or queue is changed. The two eight-slot ??_7 tables and the wider
class/thunk ownership scope remain pending the next real link.
[Exact offset data and repair boundary](../../reverse/attempt_support/army-icon-vbtable-selector-20261108/README.md).

**2026-10-29 constructor preview (`9df8832b7d`):** The current object
retains 0 of 130 authored bytes against index `840db2d676`, with ten
unresolved references. These include the real ArmyHeroIcon destructor, the
anonymous details portion's destructor and four slots, and four base slots.
The frozen-file check passes for all six matched rows. No source trial was
retained; the existing eight-slot and lifetime-owner reconciliation remains
the next prerequisite. [Current evidence](../../reverse/attempt_support/army-hero-constructor-link-20261029.md).
No census clearance or linking gain is claimed.

**2026-10-28 current lifetime-unit check (`2b9f5c4d64`):**
[The bounded prerequisite check](../../reverse/attempt_support/icon-diamond-link-20261028-codex.md)
confirms all nine unresolved virtual-slot names in `Rva005F422CDtor.cpp`
against published index `73061d9452`; its ordinary preview retains zero of
473 authored nonpadding bytes. The frozen-file check passes. No source trial
or identity change was retained: the hero factory's class and hidden-result
type still differ from the lifetime view, and the existing details-slot
owners need the same full-table reconciliation. This confirms the existing
prerequisite, with no new missing body or census clearance claimed.

Evidence / affected units: `LivingWorld/InGameUI/ArmyHeroIconCtor.cpp` remains U10 and `Rva005E39F3Ctor.cpp` remains U7 against index `d1f046749a`, with current `Rva005F4179Dtor.cpp`, `Rva005F422CDtor.cpp`, `StrategicInGameUIArmyHeroIcon.cpp` and `StrategicInGameUIArmyUnitIcon.cpp`. Native tables 0x00879448, 0x00879468, 0x00877C50 and 0x00877C74 each have eight slots. The 40-byte hero destructor at 0x005F422C and 44-byte details destructor at 0x005E3A76 are already rowed under those address-derived class names. The real hero clip factory at 0x005F43B4 returns `HeroClipReference` from `AptMovieClipFrame *`; the second constructor unit declares a void return from `ArmyHeroIconMovieClip *`. Its slot-3 return type also differs from the rowed `TreeHintRef00217D4C` result.

Completed: diagnosis only; all 12 assigned rows pass the byte gate. The full table-slot/owner evidence and provider previews are in `build/c136-gui-w2/native-tables.log`, `native-all.log`, `final-all-with-providers.log` and `build/link-report.md`. The anonymous `HeroDetailsPortion` emission requires the same details owner, rather than another local implementation.

Remaining / next check: reconcile the destructor owner to `StrategicInGameUI::ArmyHeroIcon` and share the full eight-slot ABI across its lifetime, constructor and derived details views. Base slot 3 reaches the existing 18-byte empty-help row 0x001524CA; slot 4 reaches 0x005F41AF; slots 6 and 7 reach 0x005F3FF4 and 0x005F3F6B. Details slots 1, 5, 6 and 7 reach the already rowed forwarders 0x005E3D84, 0x005E5237, 0x005E4663 and 0x005E3ECB. Preserve hidden-result signatures and vtordisp thunks. Replacing real member calls with these placeholder names or changing ledger identities was unavailable in this seat, so no partial table trial was retained.

Clearance: pending. Census confirmation: not claimed.

2026-11-04: related ArmyMemberIconMovieClip header cohort adopted in three units (three queue rows retired, 43 rows exact, preview retains 1,207 linked bytes); its constructor unit still needs base-vptr emission reconciliation and was restored. Broader lifetime/table obstacle unchanged. [Evidence and next prerequisite](../../reverse/attempt_support/army-member-header-adoption-20261104/README.md).

**2026-11-08, seat LeonardBuhl: the vbtable false reject is repaired in the tool.**
`tools/vtable_bridge.is_table_row` no longer admits a data-ledger row whose every name is a `??_8` virtual-base
table; a row that also binds a `??_7`, a legacy `_vtbl_` name or any other name stays a table. On the current ledger
this drops exactly the 34 vbtable-only rows (3,843 -> 3,809 table rows; no mixed `??_7`/`??_8` row exists). Two
regression tests cover the selector boundary and an end-to-end bridge run where an offset table `(0, 36)` sits beside a
strong `_vtbl_` owner: the vbtable is neither refused nor queued, and the strong owner's refusal survives. Bridge,
exit_link, link_batch_audit and gate-exploit suites pass (416 tests). Clearance: none claimed until the next real link's
`vtable_bridge_queue.tsv` lists no `no-retail-slots` row (34 at `4a3033f245`). The `??_7` tables in the same units remain
separate bridge work.

**2026-11-09, real link `f1c6a663f4`:** the queue has no `no-retail-slots` row, so the ??_8 refusals at 0x00877C94 and
0x00879488 are **cleared**. The eight-slot ??_7 tables remain separate work.
