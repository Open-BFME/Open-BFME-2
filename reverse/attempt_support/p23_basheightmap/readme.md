# P23: BaseHeightMapRenderObjClass's real tables, ready except for one claim

**Status.** Closed, 2026-11-08: both installers on the canonical header, and all four compiled tables compared
with retail by slot, with 0 differences outside the three listed below. The prepared texts here are history now.
Receipt `2026-11-08T193111Z-boot_smoke-eaf7942ff6e7` got past the first terrain virtual call, and `blob_rule.py`
passed against landed `2a50ce83ab`. That shows the call returns, not that terrain draws: the run has no screenshots.

**The derived class came after.** BaseHeightMap's tables did not reach the boot stop by themselves: the object the
game calls is the derived `Rva000E3B41` (flat height map, retail's table 0x00BCE788), whose compiled table had 129
slots where retail has 149, so `W3DTerrainLogic::getGroundHeight+0x3F`, `call [edx+0x244]` (slot 145), read past it.
Its four tables now match retail by slot on both installers: 149 (allowed gaps 0, 51, 52, 98), 1, 2 and 4.

Left over, none of it BaseHeightMap's own:

- `RenderObjClass` (`rendobj.h`) disagrees with retail at three inherited slots, for every class
  that compiles its table. Fixing it is a full-gate header edit.
  - Slots 51 and 52: the header returns `const Matrix3D &`, but the ledger rows at 0x0006D06D return by value
    through a hidden pointer (retail's body is 106 bytes). If that row's form is retail's, callers and callee
    disagree on the stack.
  - Slot 98: the header's `Is_Visible` is a bit test; retail's 0x0013B6D0 is 55 bytes, rowed `queryVisible@Rva0013B6D0`.
  - Slot 0: `delete this` against `::delete this`, the known RefCountData.h difference (no behaviour change).
- The header-queue rows for the two units retire once they reach the census: the hook judges each unit alone.
- `~vector<bool>` was pinned to 0x00142D70, the `basic_string` fold. Retail's four unwinds of these members go to
  0x0007FAB3, an identical second body, so it is now rowed there. Other units that name it were rebuilt and pass.

**Landed.** Every BaseHeightMap.h field is typed from retail: +0xD4 and four texture slots
`RefCountPtr<TextureClass>`, `TScorch[500]`, two `vector<bool>`s, eight AsciiStrings.

## Prepared texts (scratch-verified, nothing landed)

| File here | Becomes | Result |
|---|---|---|
| `ctor_adopted.txt` | `BaseHeightMapConstructor.cpp` | 30/30 exact on the canonical header; stores `??_7...6BRefCountClass@@@` and its three siblings |
| `dtor_slots.txt` | `Rva0006D0D7Dtor.cpp` | ~BaseHeightMapRenderObjClass 735/735 bytes; stores the same four tables as the constructor |
| `BaseHeightMap_slots.h.txt` | `BaseHeightMap.h` | slots 2, 3, 133, 139 and 144 below |

## Slots

Retail's table 0x00BC5DB0 against RenderObjClass's 0x00BD2F68. Any slot not listed is inherited
or already named. Today's header spells slots 129-147 `vslotNNN`, and nothing defines those
names, so adopting without this table adds unresolved symbols to a unit that links.

| Slots | Retail body | Fix | Touches BaseHeightMap.cpp | Prepared |
|---|---|---|---|---|
| 2 | 0x000D43D0 `xor eax,eax; ret` | inline `Clone() { return 0; }` | no | yes, byte-equal |
| 3 | 0x004FB350 `push 4; pop eax; ret` | inline `Class_ID() { return CLASSID_TILEMAP; }` | no | yes, byte-equal |
| 139 | 0x0047A69C `ret 4` | inline empty body | no | yes, byte-equal |
| 144 | 0x000D43D0 `xor eax,eax; ret` | inline `return 0` | no | yes, byte-equal |
| 133 | 0x0006933D, rowed `?rva0006933D@Rva0006933D@@QAEHXZ` | `rename.py function --to-class` | no | header and dtor call only; Rva0006933D.cpp's definition still needs preparing |
| 129 | 0x0006692C, `rva0006692C` on the class | `rename.py function --virtual` | yes, tu-skeleton comment | no |
| 131 | 0x0006D6D9, `initHeightData` | `--virtual` | yes, tu-skeleton comment | no |
| 134 | 0x00069CE6, `rva00069CE6` | `--virtual` | yes, tu-skeleton comment | no |
| 143 | 0x0006B804, `rva0006B804` | `--virtual` | yes, tu-skeleton comment | no |
| 130 | 0x00066A9A, `Rva00066A9AHost` | `--to-class` | yes, tu-skeleton comment | no |
| 137 | 0x00068441, `Rva00068441` | `--to-class` | yes, tu-skeleton comment | no |
| 67 | 0x00069AF5, `Rva00069AF5Host`, is Get_Obj_Space_Bounding_Sphere | `--to-class` | yes, the row is there | no |
| 142 | 0x0006820F, `Rva0006820FNullForwarder` | `--to-class` | yes, the row is there | no |

The four `--virtual` dry runs pass retail's slot check (`--max-files 60`; the header reaches 45
sources). `--to-class` requires the installer unit's table to name the new symbol, so the
adoption has to be in the tree first. A partial set cannot land.

## Remaining, in order

1. Claim BaseHeightMap.cpp. Replace the header with the prepared text and make every unit
   declare the slots it names.
2. Adopt the constructor unit (local commit; nothing pushed yet).
3. Run the slot table. Check each caller stays a direct call: spell non-virtual calls
   `BaseHeightMapRenderObjClass::name()`, and let byte-gating catch the rest.
4. Adopt the destructor unit, with these ledger changes:
   - Retract its helper rows `??1SnapC8` (0x0049B47C), `??1RefTex` (0x0017098D) and `??1FreeBuf`
     (0x0007FAB3), and re-row the bodies that remain, under real names or as folds:
     `TScorch`'s destructor; `RefCountPtr<TextureClass>`'s, which is rowed in streakRender.cpp;
     `_Bvector_base<allocator<bool> >`'s destructor.
   - Repoint its `$L` funclets, which the header's new inline members renumber
     (`tools/eh_verify.py` must find the parent's graph EXACT).
5. Run `header_adopt_lane.py accept` for both units; `link_check` every dependent after
   `--fetch-index`.
6. Test-branch receipt: `local_link.py request`, then a boot past the first terrain virtual call.

## Findings to keep

- **The destructor unit's free.** The allocator's inline `deallocate` must call
  `Rva00030830GameFree` (C++ linkage), as the prepared text does. With CRT `free` the two
  `vector<bool>` teardowns lose retail's EH state writes. `/EHs` does not change that.
- **RO0's slot 0.** `??_7BaseHeightMapRenderObjClass@@6BRO0@@@` comes from the destructor unit's
  scaffold view, and only the destructor stores it, so its deleting destructor in slot 0 is live
  only during destruction. The prepared destructor stores the constructor's table.
- **Target facts.** Retail's settings fields +0x37E4/+0x37E8 are floats (copied without FPU
  instructions); slot 0 of 0x00BC5DB0 equals RenderObjClass's, so Delete_This is inherited.

P23 does not depend on object.h's `m_name` or `m_next`.
