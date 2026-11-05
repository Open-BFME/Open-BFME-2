# CaveContain canonical base and vtable (2026-11-05)

Inspected source base: `4d0a72b281`. Claim owner: `yasinschroeder-codex`.
Census preview: `c95fcfcfcd`, 2026-11-05 05:17. No new census was run.

## Target facts and source change

The existing constructor row at RVA `0x00466D37` is 25 bytes. Its clear at
`+0x98` and table store of VA `0x00C43F40` match when compiled against
`OpenContainModuleData.h`, with a single derived `int m_caveIndexData`.
This removes the empty private base view, explicit vtable field, padding and
manual table store. The existing HealContain constructor alternatename remains.

The index has exactly one provider for `??_7CaveContainModuleData@@6B@`:
`ContainModuleDeletingDtors.cpp`. Its minimal, unrelated class previously
emitted only the deleting-destructor slot. Giving just its Cave declaration the
same canonical base and trailing field makes both current table copies 124 bytes
with 31 DIR32 relocations, in identical slot order. The other 14 class scaffolds
are unchanged. The tag constructor is still explicitly absent from retail.

Retail's table at RVA `0x00843F40` has the destructor at `0x002576F3`,
ModuleData's interface in slots 1..30, and the OpenContain true override in slot 8
(`0x0050B5C6`). These are target table facts; the inherited method spellings come
from the existing canonical header, not a new donor-name attribution. The original
CaveIndex field-name evidence is the existing parse table at VA `0x00BEEAC8`.

## Verification

- `./build.sh` on the constructor: 1/1 matched, 25 bytes.
- `./build.sh` on the wrapper provider: 15/15 matched, 420 bytes.
- `find_declared_unmatched.py` passes independently for both files; existing
  absent-from-retail anchors remain, with no new unclaimed retail body.
- `link_check.py --prepare-current` on both files passes 16/16 rows and creates
  strict reusable provider receipts without modifying the census/index/status.
- Paired ordinary `link_check.py` reports both LINKS, 445 -> 445 bytes.
- `data_check.py` reports zero findings across both files.

These results preserve the measured sources' scoped preview coverage. They do not
claim measured linking growth, image ownership, complete game linking or a smoke run.
The pre-publication batch audit against HEAD cannot judge uncommitted compiler
inputs; the publishing hook must audit the committed batch. Its older census
baseline and any missing consumer receipts remain census follow-up, not clearance.

## Header queue and remaining work

The initial supported adoption trial rejected all six queued OpenContain consumers:
Cave had C2373 on its explicit vtable declaration; Garrison/Tunnel had an 88-byte
filter field where the canonical handle is four bytes; the base ctor/dtor units
had C2011 in layout discovery; Transport used Rva003623E5Filter rather than the
canonical Rva003623E5Member. No failed automatic source trial was retained.

With the Cave constructor repaired alone, `header_adopt_lane.py accept` refuses a
25 -> 0 preview: its new full table conflicts with the saved one-slot provider.
The paired preview passes after the provider repair, but the retirement hook
checks only the queued constructor and does not overlay the unqueued provider.
The header queue row is deliberately unchanged. Once a published index contains
the corrected provider, run:

```
python3 tools/header_adopt_lane.py accept --class OpenContainModuleData Code/GameEngine/Source/GameLogic/Object/Contain/CaveContainModuleDataCtor.cpp
```

Other five consumers need their own field/layout prerequisite repairs. The
historical ModuleFactory constructor-provider obstruction is no longer the
current Cave failure: the current saved vtable provider is the wrapper unit.
