### LINK-072: Zero Hour port units for module classes BFME 2 never had

(Formerly a second LINK-063, also headed LINK-045; `reverse/re_attempts.log`
entries citing LINK-063 for a ZH-port rehome trial mean this entry. Every other
LINK-063 reference means the `OrCondition` entry. WWLib `wwfont.cpp`, the same
shape outside the module tree, is recorded under LINK-065.)

**Status: Open (7 units repaired; remaining inline-only units parked). Updated: 2026-10-28.**

- **Evidence / scope:** several `Code/` units are verbatim Zero Hour ports of
  module classes that retail BFME 2 does not contain. Test, per class: game.dat
  (`baselines/bfme2/workshop-vanilla-1.06/files/game.dat`, `strings` ASCII and
  UTF-16) has no module-name string for it (the factory's name table, e.g.
  around `SlavedUpdate`, `BezierProjectileBehavior`, lists every registered
  module), and `reverse/functions.csv` has no row for any of its methods. The
  port's bodies are then all `present-unmatched` nonmatching reconstructions
  whose references are the unit's only link blockers; the unit's few rows are
  generic inlines a masked search placed there.
- **Completed:** MobMemberSlavedUpdate.cpp (01564e4a01, 0 -> 8 B),
  EMPUpdate.cpp (0a575d1548, 0 -> 13 B, also LeafletDropBehavior),
  HackInternetAIUpdate.cpp (e0cbcdaa47, 0 -> 10 B): ZH bodies dropped, the
  rowed inline kept by explicit instantiation (template) or a pointer anchor
  (TU-local const at /O1; extern const at the default -O2, which drops an
  unused TU-local one). 61 present-unmatched hatches removed. All LINK in
  preview.
  StickyBombUpdate.cpp (ac1b73589c, 0 -> 36 B; the two rowed accessors are
  ordinary out-of-line definitions), ParkingPlaceBehavior.cpp (191cb9df0a,
  0 -> 38 B), AnimationSteeringUpdate.cpp (9cae72c749, 0 -> 14 B): same
  test, ZH bodies dropped, template rows emitted by explicit instantiation
  of the single member. Zero Hour's header declares
  `ParkingPlaceBehavior::RunwayInfo` private and cl 7.1 refuses to name it
  in an explicit instantiation (C2248), so that unit declares only the
  element (36 bytes; the byte-exact strides confirm it). 50 more
  present-unmatched hatches (and one `#pragma optimize`) removed. All LINK
  in preview.
- **Remaining / next check:** same test passes for SpectreGunshipUpdate,
  RailedTransportDockUpdate, DeliverPayloadAIUpdate, JetAIUpdate,
  FlightDeckBehavior, DumbProjectileBehavior, HelicopterSlowDeathUpdate and
  HordeUpdate (no
  module-name string), but check each unit's rows first: several carry ZH
  class names on retail bodies (`SpectreGunshipUpdate::setLogicalStatus`,
  `StickyBombUpdate::set/getTargetObject`, `RailedTransportDockUpdate`
  getters, `RunwayInfo` vector helpers), which need an honest name/home
  before the class can go. HelicopterSlowDeathUpdate's only row is the
  virtual inline `SlowDeathBehavior::isDieApplicable` (0x0045D49E): a
  pointer-to-member of a virtual yields a vcall thunk, not the body, so it
  needs another emission route (parked; see the rehome trial below). AIUpdate.cpp's present-unmatched
  `AIUpdateInterface::privateHackInternet` (no "HackInternetAIUpdate" NAMEKEY
  string in game.dat) now leaves `HackInternetAIUpdate::hackInternet`
  unresolved; that unit did not link before either.
- **Non-hatch emission routes for the inline-only units (2026-10-26):**
  - HelicopterSlowDeathUpdate: the row's approved unit (tu_map) is
    `Behavior/SlowDeathBehavior.cpp`, which already emits
    `SlowDeathBehavior::isDieApplicable` through SlowDeathBehavior's vftable
    (its dtor), but with the ZH UpdateModule layout (`[ecx-0x18]/[ecx-0x1C]`
    against retail `[ecx-0x1C]/[ecx-0x20]`). Adding `/Ireference/shims/dockupdate`
    (retail's extra UpdateModule dword) and `/O1` byte-matches it, but moves the
    unit's two masked-search rows `PhysicsBehavior::setExtraBounciness` /
    `setExtraFriction` (0x000EFB3E/0x000EFB5A) from +0x74/+0x78 to +0x78/+0x7C.
    Those rows are displaced COMDATs with no approved home, so they block the
    rehome; settle their identity/home first (re_log db1eba0fb4).
  - JetAIUpdate: `Matrix3D::Matrix3D(bool)` (0x0004C91A) sits inside
    W3DGameClient.cpp's approved cluster but is itself only `proposed` to a
    non-existent `AIUpdate/Matrix3D.cpp`; a ctor cannot be pointer-anchored, and
    `reference/shims/bfme_matrix3d_bool_link` keeps every other consumer inline
    so JetAIUpdate.cpp is its sole emitter. Parked until the address gets an
    approved unit.
  - DumbProjectileBehavior: `UpdateModule::getUpdatePhase` (0x0022C4CB, the
    ICF-shared PUSH 2/POP EAX/RET slot) is a displaced COMDAT with no approved
    unit (3092d4a84c moved it here); `sqr<float>` alone could stay by explicit
    instantiation. Parked with the getUpdatePhase home.
  - Also failing test 4 (other units need the class's symbols):
    DeliverPayloadAIUpdate (ObjectCreationList.cpp's DeliverPayloadNugget uses
    `DeliverPayloadData::getFieldParse` and the AI update), StickyBombUpdate
    (AISpecialPowerPickers.cpp calls the rowed set/getTargetObject).
    SpectreGunshipUpdate's only row `setLogicalStatus` is protected (`IAE`), so
    a file-scope pointer anchor cannot reach it once the ZH callers go.

  unresolved; that unit did not link before either. Why the rest are
  not one-step (K9, 2026-10-26): HordeUpdate (`isTrueHordeMember`),
  DumbProjectileBehavior (`UpdateModule::getUpdatePhase`), FlightDeckBehavior
  (`ExitInterface::getNaturalRallyPoint`) and RailedTransportDockUpdate
  (`getRailedTransportDockUpdateInterface`, `DockUpdate::setDockOpen`) keep
  virtual inlines, the HelicopterSlowDeathUpdate case; JetAIUpdate's only
  row is the inline `Matrix3D(bool)` ctor (0x0004C91A, whose other emitters
  keep it inline by shim), and no pointer can anchor a ctor;
  SpectreGunshipUpdate's `setLogicalStatus` is a protected inline, so a
  namespace-scope pointer anchor is refused; DeliverPayloadAIUpdate (row:
  `WeaponTemplate::getProjectileExhaust`, anchorable) is the `fold-proof=`
  source of the `Locomotor::setUltraAccurate` / `setAllowInvalidPosition`
  fold pins in `reverse/symbols.csv`, which its ZH bodies instantiate, so
  those pins need another proving source (pin admission) before the
  bodies can go. W3DTankTruckDraw.cpp also fails the string test, but
  retail rows its methods under that class in sibling units
  (W3DTankTruckDrawTossEmitters.cpp, ...CreateEmitters.cpp), so it is not
  this case.

- **Checked, not removable as-is (2026-10-26, K5, index d1f046749a, no source change):**
  - `ObjectCreationList.cpp` (1,427 B, 8 blockers): `DeliverPayloadNugget`
    is ZH-only (no `DeliverPayload` string in game.dat; retail's table at
    0x007E07F0 lacks it) and its `parsePayload` is the unit's static
    `INI::scanInt` caller, but its three `vector<Payload>` rows (0x005F8653
    `_M_clear`, 0x005F8752 `_M_insert_overflow`, 0x005F8855 `push_back`,
    no TU approval) are a masked-search misnaming: retail 0x005F8752 calls
    0x004F6A88/0x004F6A52/0x004F6AAE (`Rva004C5DD0Set.cpp`, an 8-byte
    two-ref-counted-pointer element), which is why `_Construct`/`_Destroy<Payload>`
    lose as "not retail's body". Those rows need an honest element type and
    home before the nugget can go. The `setProducer(const Object *)` U
    blocker is the unfinished ZH-spelling pass from 83a5361fc7 (29 files).
    Rechecked 2026-10-30 (census at 12b9e7a7c0, no source change): down to
    two unresolved (`?scanInt@INI@@SAHPBD@Z`, `?setProducer@Object@@QAEXPBV1@@Z`;
    28 caller units and the 0x0028AFD2 row spell `Object *`, so the ZH const
    spelling is this unit's alone) plus the two Payload `_Construct`/`_Destroy`
    losers and two first-copy COMDAT differences
    (`??1RadiusDecalTemplate@@QAE@XZ`, `??_7ObjectCreationNugget@@6B@`).
    The Payload row identity/home is still the first prerequisite.
  - `DieModule.cpp` (13 B): its unrowed ZH `crc`/`xfer`/`loadPostProcess`
    and `DieMuxData::getFieldParse` are the only providers of names that
    linked units reference (DieModule vftables in CreateObjectDie,
    SpecialPowerCompletionDie, FXListDie; `buildFieldParse` in ModuleFactory,
    InstantDeathBehavior, about 2.7 KB linked). Dropping them would lose
    those units; the static `INI::scanIndexList` blocker comes from
    `ObjectStatusMaskType::parseFromINI` in that table.
  - `light.cpp` (6 B): the row `LightPersistFactoryClass::Chunk_ID`
    (0x00615B60, `mov eax,0x10001; ret`) is in no retail vftable, so retail
    has no such factory; the virtual inline cannot be kept emitted without
    the ZH factory instance (same vcall-thunk limit as HelicopterSlowDeath).
  - `HordeUpdate.cpp` (14 B): its row 0x0049001F is pointed to from retail
    .rdata 0x0084D054, inside a run of code pointers (a vftable), so a
    retail class owns it; name/home first.
  - `BridgeScaffoldBehavior.cpp` already links in a current preview (952 B);
    its census `UpdateModule::loadPostProcess` blocker is stale.

**HordeUpdate bounded emission repair (2026-10-28, base `afeacf59f4`,
index `d92e7e6635`):** the sole 14-byte row now emits as an ordinary
out-of-line override using bounded declarations, without the unrelated Zero
Hour implementation. Before/after `./build.sh` is exact 1/1; strict preparation
passes. Nine present-unmatched hatches and their allowances are removed.
Ordinary preview changes U5 -> LINKS, 0 -> 14 authored bytes. No new pin,
anchor, alias, name or source-path move is involved. This clears the emission
obstacle in that unit only; its legacy HordeUpdate identity and approved
LargeGroupBonusUpdate.cpp home still need reconciliation. COFF comparison
removes 688 external definitions and retains the one matched method unchanged;
42 removed names lack another indexed provider but have no other indexed
consumer. The outgoing audit is **UNVERIFIED**: the index predates the base,
and affected `Common/0CreateAHeroManager21FE49.cpp` has no current receipt.
Carry consumer preservation into the next census; no census gain is claimed.
[Target, donor and verification evidence](../../reverse/attempt_support/horde-inline-link-20261028-codex3.md).

**Assigned inline-unit recheck (2026-10-26, inspected `2a45addda1806342ac5c52757f63be902dcd428e`, index `d1f046749a`):** HackInternetAIUpdate.cpp and EMPUpdate.cpp already report LINKS in the initial 26-unit preview and retain that result in the paired current-provider preview. Their ten and thirteen authored bytes are inherited repairs, not new gains from this worker. The other assigned inline-only ZH units retain the emission, identity and approved-home prerequisites above; no anchor, row move, new body or repeated rehome trial was added. Raw evidence: `build/c136-logic/before.log`, `final-cohort-before.log`, `final-cohort-after.log` and `all-assigned-build.log`. These two units are cleared in ordinary-preview scope; census confirmation pending.

- **Census confirmation:** pending for all three units.

  b313329af6 renamed the four numpunct slot rows in place to the real `do_truename` /
  `do_falsename` names (narrow pair in `stlport_narrow_string_range_ctors.cpp`, wide pair in
  `Rva00017B00StringInit.cpp`, which drops `/EHs-c-` so `return <static>;` emits retail's
  return-value flag), still reading the existing address-named storage, and removed the
  unrowed duplicates from `stlport_numpunct_virtuals.cpp`: that unit now LINKS (0 -> 44 B).
  The data-lane rename of the statics was not needed for the link.
  620cbe78fd did the same for 0x00019D90 (slot 4 of `moneypunct<wchar_t,true>` 0x007BC868;
  slots 4-6 of both wide moneypuncts): now `?do_curr_symbol@?$moneypunct@G$00@_STL@@...XZ` in
  `Rva00017B00StringInit.cpp`; its own hatch dropped, the other five retargeted. 6/6 LINK.
  Note: link_check without the edited partners in the set uses stale index objects and
  reports spurious duplicates / unresolveds; check these units together.
  13cb4119f9 named the `_Messages` pair (vftable 0x007BC8D4, `.?AV_Messages@_STL@@`): slot 1
  0x0001A090 is `do_get(..., const wstring&)` and slot 2 0x0001A060 `do_get(..., const string&)`
  (reverse declaration order). They were the BFME 1 donor shells `?bfmeGoDQE` / `?bfmeGoDQD` in
  `BfmeConv760.cpp` / `BfmeConv759.cpp`; both now define the real `return __dfault;` in place.
  Four hatches removed (two `do_get` lines in `stlport_messages_dtors.cpp`, the `bfmeCallDQD` /
  `bfmeCallDQE` copy-ctor aliases in `stlport_{narrow,wide}_string_copy_ctor.cpp`) and the two
  placeholder symbol aliases dropped. 6/6 units still LINK, bytes unchanged.
  After this, every RTTI vftable slot outside `ctype` holds a real STLport name or a known
  fold (`do_close` / `Prepare_LOD`, `do_always_noconv` / `_AptValidate`, `showmanyc` /
  `GetNativeHashVirtual`): `tools/vtable_slots.py` lists no other placeholder. Retail is `/GR-`,
  so no engine, W3D or Apt class has an RTTI vftable; this method does not reach them.
- **Remaining / next check:** (0) `ctype` range virtuals: slots 5/7 of `ctype<char>` (0x007BC3E4)
  hold 0x00016C20 / 0x00016C60 (`do_widen` / `do_narrow` range forms) and slots 1/5/7/9/11 of
  `ctype<wchar_t>` (0x007BBAD0) hold 0x00016D00..0x00016E60 (`do_is` / `do_toupper` /
  `do_tolower` / `do_widen` / `do_narrow` range forms), all rowed as the BFME 1 donor names
  `T2NarrowCtype::*Range` / `T2WideCtype::*Range` in `T2CtypeTableFacets.cpp`. The natural owners
  are `stlport_narrow_ctype_virtuals.cpp` (which already defines the two narrow range forms
  unrowed, with `memcpy` bodies that do not match retail's `if (high != low) memmove`) and
  `stlport_wide_ctype_virtuals.cpp` (single-character forms only; addresses interleave).
  Moving the seven rows there removes ten hatches (five each in `stlport_classic_locale.cpp`
  and `stlport_locale_facet_subclass_dtors.cpp`). Not attempted: `T2CtypeTableFacets.cpp` was
  LOCKED by K6. (1) Give the 12-byte statics their STLport names (`_M_truename` / `_M_falsename`,
  monetary.cpp's file-static empty strings) through the data lane; `data_check` (shadow)
  already flags `g_009DEEF0Static` and siblings as duplicate-def / wrong-name. (2) The nine
  narrow and five wide moneypunct alias hatches (per unit) need alias rows to go.
- **Census confirmation:** awaiting the next census for 437bc30603 and b313329af6.
