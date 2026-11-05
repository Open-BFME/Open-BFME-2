# OneRingPenaltyUpdate consolidation prerequisites

Inspected base: `6fc1aef413`; worker: `yasinschroeder-codex4`, 2026-11-05.
Link preview index: census 2026-11-05 05:17 at `c95fcfcfcd`.

## Completed scope

`OneRingPenaltyUpdateRva00499D23.cpp` includes the canonical OneRingPenaltyUpdate,
Thing and TerrainLogic headers. The module-data pointer is obtained through
`getModuleData()` and cast to the existing module-data view. Removed the unused
110-slot AI view; actual calls already use AIUpdate's shared header.

Target/codegen facts: the 373-byte retail helper reads TerrainLogic's primary
table slot 6 after Sin and before the Y addition. Its existing four-byte
member-pointer table view preserves that scheduling. Canonical TerrainLogic
has multiple bases, so its member pointers are wider. The call now uses an
explicit single-inheritance receiver for that same table word, with the
existing compile-time four-byte width check. This receiver describes the
witnessed calling ABI, not TerrainLogic's class layout or an original type name.

`./build.sh` verifies the complete 373-byte helper, its string, all five float
literals and imports. The frozen-source check reports every body matched.
Header debt leaves only through `header_adopt_lane.py accept` for each class.
All three acceptance commands passed and retired their three queue rows.
Final current-object link preview: helper 373 -> 373 B and restored seed
765 -> 765 B, both LINKS (1,138 -> 1,138 B total). This is a scoped preview,
not a census update or a real-link measurement.

## Seed attempt reverted; consolidation remains blocked

The initial `tu_skeleton.py --merge .../OneRingPenaltyUpdate.cpp --dry-run`
accepted no donor: the seed's private raw UpdateModule/OneRingPenaltyUpdate
views conflict with canonical donors, and Slot0 still declares rva00499D18
instead of the canonical onDie declaration.

A seed-only trial removed its private UpdateModule/OneRingPenaltyUpdate views
and explicit table-address stores, included OneRingPenaltyUpdate.h, and left
the constructor's field initialization and setWakeFrame call. All 13 ledger
rows byte-matched, including the 113-byte constructor. However, current-object
`link_check.py` predicted 765 -> 0 linked bytes with these four unresolved names:

```
??1OneRingPenaltyUpdate@@UAE@XZ
?GetSnapshotName@OneRingPenaltyUpdate@@MBEPBDXZ
?loadPostProcess@OneRingPenaltyUpdate@@MAEXXZ
?onDie@OneRingPenaltyUpdate@@UAEXPBVDamageInfo@@@Z
```

Existing owners at those addresses are placeholders, not unrowed bodies:

| RVA | Current owner/source |
|---|---|
| 0x00499934 | Rva00499934 destructor, Common/Rva0024A797Grandchildren.cpp |
| 0x00499954 | Rva00499954Named::name, Common/ModuleNameGetters3.cpp |
| 0x00497805 | Rva00497805::loadPostProcess, Update/BattlePlanUpdate.cpp |
| 0x00499D18 | OneRingPenaltyUpdate::rva00499D18(void *), Update/OneRingPenaltyUpdateSlot0.cpp |

The seed trial was restored completely; no linking regression is retained.
Next: reconcile those providers with the canonical declarations, prove their
table identities and byte/link behavior, then retry the seed adoption and TU
composition. No source path was moved and no census figure was changed.
