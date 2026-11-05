# DrawableModule::GetSnapshotName: real-link name and its to-class plan (2026-11-05, halilkkaya-lk29)

Base `b4c9b2d8a8`. No source or ledger change here: the row's file is claimed by
another worker (below). This records the cause, the evidence and a byte-verified
preparation for whoever lands it.

## Symptom

The real links since `50ff761bcd` report one unresolved name in
`W3DScriptedModelDrawDestructor.cpp`: `?GetSnapshotName@DrawableModule@@MBEPBDXZ`.
It is absent at `173e734df9`.

## Cause

`f3fbb9188c` ("Adopt canonical headers in 20 units", 2026-11-04) replaced the unit's
private `DrawableModule` view (a virtual destructor only) with the canonical
`Code/GameEngine/Include/Common/DrawableModule.h`. That header declares slot 2 as
`virtual const char *GetSnapshotName() const` (protected), so the unit's
`??_7DrawModule`/`??_7W3DScriptedModelDraw` tables now name it. Nothing defines that
symbol. `Module.cpp` (Zero Hour port) defines DrawableModule's `crc`, `xfer` and
`loadPostProcess` as present-unmatched bodies, which is why only slot 2 is missing.
Our own `4420cb9508` touched the unit before `173e734df9`, which still linked this
name, so it did not cause it. The header adoption is correct debt retirement. The
missing piece is the provider.

## Target facts (game.dat 1.06)

- 0x00252B84 (6 B, `mov eax, offset "DrawableModule"; ret`) is slot 2 of three
  tables: 0x00C07E54 (DrawableModule; installed by its constructor 0x00306B19),
  0x00BEFE48 (deleting dtor 0x00254C2F, class `Rva00252B68`) and 0x00C170A4
  (deleting dtor 0x003630E6, class `Rva00362EC7`).
- `Rva00252B68Ctor.cpp` and `Rva00362EC7Ctor.cpp` both declare `: public DrawableModule`
  and call the DrawableModule constructor 0x00306B19. These are the derived tables
  `rename.py function --to-class` accepts.
- The row is `?name@Rva00252B84Named@@QBEPBDXZ` in
  `Code/GameEngine/Source/Common/SubsystemNameGetters.cpp`, written as
  `BFME_LITERAL_NAME_GETTER(Rva00252B84Named, "DrawableModule")` (line 107).

## Plan

    python3 tools/rename.py function --rva 0x00252B84 --to-class DrawableModule \
        --new '?GetSnapshotName@DrawableModule@@MBEPBDXZ' \
        --prepared Code/GameEngine/Source/Common/SubsystemNameGetters.cpp=<getter as DrawableModule::GetSnapshotName> \
        --prepared Code/GameEngine/Source/GameLogic/Object/Create/DrawableModuleCtor.cpp=<diff below> --dry-run

- SubsystemNameGetters.cpp: include `Common/DrawableModule.h` and replace the macro line
  with `const char *DrawableModule::GetSnapshotName() const { return "DrawableModule"; }`.
  Not tried: the file is held.
- DrawableModuleCtor.cpp is the installer unit, so its compiled vftable must name the
  new symbol. Its private view gives slots 1-3 `__purecall`. The prepared change below
  replaces the `Module.h` include and the private class with the canonical header. It
  must come before any `Snapshot.h`, so that `BFME_SNAPSHOT_NAME_SLOT` is set.

```
-#include "../../../../Include/Common/Module.h"
-
-class DrawableModule : public Module
-{
-public:
-	DrawableModule(Thing *thing, const ModuleData *moduleData);
-protected:
-	virtual ~DrawableModule();
-public:
-	virtual void onCapture(Player *oldOwner, Player *newOwner) {}
-	virtual void onDisabledEdge(Bool nowDisabled) {}
-
-private:
-	Drawable *m_drawable; // +4
-};
+#include "../../../../Include/Common/DrawableModule.h"
```

## Trial result (scratch, reverted)

- `./build.sh DrawableModuleCtor.cpp`: 1/1 (the 108-byte constructor 0x00306B19 is unchanged).
- `??_7DrawableModule@@6B@` (11 slots) becomes: `??_EDrawableModule@@MAEPAXI@Z`,
  `?loadPostProcess@DrawableModule@@MAEXXZ`, `?GetSnapshotName@DrawableModule@@MBEPBDXZ`,
  `?xfer@DrawableModule@@MAEXPAVXfer@@@Z`, `__purecall`, the four `Module` inline slots, and
  `?vslot09@`/`?vslot10@DrawableModule@@UAEPAXXZ`. That is retail 0x00C07E54's order.
- `link_check DrawableModuleCtor.cpp`: LINKS 108 -> not linking, with the single unresolved name
  `?GetSnapshotName@DrawableModule@@MBEPBDXZ`. The rename provides it in the same commit, so
  the preparation can never land on its own.

## Before landing

Run link_check A/B over DrawableModuleCtor.cpp, SubsystemNameGetters.cpp (263 B),
W3DScriptedModelDrawDestructor.cpp, Rva00252B68Ctor.cpp, Rva00362EC7Ctor.cpp and the
RadarMarkerClientUpdate units of LINK-254. Compare every `??_7DrawableModule` copy
against the pre-edit objects: the derived-class units still emit private-view copies.
