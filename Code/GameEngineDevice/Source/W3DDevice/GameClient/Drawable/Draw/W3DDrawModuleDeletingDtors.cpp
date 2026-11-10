// cl: /O1 /MD /Ireference/shims/moduledata
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// These minimal declarations emit the wrappers, not complete class layouts.
// No bases, member layout, or destructor implementation are claimed here.
// A dummy tag constructor per class (absent from retail) makes this unit emit
// the vtable and so the wrapper; the wrapper's call resolves to the retail
// destructor (its row or pin). The empty noinline destructors that used to
// stand here were second strong definitions, not retail's, that the link kept
// over the rowed W3DModelDrawModuleData (0x000C8BE0), W3DBoatWakeModelDraw
// (0x000D0B69), W3DTornadoDrawModuleData (0x000D1713) and
// W3DProjectileStreamDraw (0x000D146B) destructors.

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../../../../../GameEngine/Include/GameLogic/Module/DrawModule.h"

// ??_GW3DScriptedModelDraw@@UAEPAXI@Z @0x000C8617 28B: slot 0 of vtable 0x00BCA090; calls ??1 at 0x000C79C9.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x000C1201 uses class-name string "W3DScriptedModelDraw".
class W3DScriptedModelDraw { public: W3DScriptedModelDraw(struct EmitVtableTag *); virtual ~W3DScriptedModelDraw(); };
// ?<W3DScriptedModelDraw::W3DScriptedModelDraw> absent-from-retail
W3DScriptedModelDraw::W3DScriptedModelDraw(struct EmitVtableTag *) {}
void W3DScriptedModelDraw_Delete(W3DScriptedModelDraw *w3DScriptedModelDraw) { delete w3DScriptedModelDraw; }

// ??_GW3DModelDrawModuleData@@UAEPAXI@Z @0x000C8DC3 28B: slot 0 of vtable 0x00BCADE8; calls ??1 at 0x000C8BE0.
// Owner evidence (audited 2026-09-26): retail W3DScriptedModelDraw registration -> shared data factory RVA 0x000648D6 -> ctor RVA 0x000C8EEF; primary vptr store RVA 0x000C8F13; field parser RVA 0x000C9240 agrees with donor W3DModelDraw data.
// Its view derives from the canonical Snapshot base, as the rowed destructor's
// unit (Code/Libraries/Source/WWVegas/WWLib/W3DModelDrawModuleData.cpp) does
// (that destructor restores Snapshot's vtable 0x00BBB554), so both units emit
// one identical vtable COMDAT.
class W3DModelDrawModuleData : public Snapshot { public: W3DModelDrawModuleData(struct EmitVtableTag *); virtual ~W3DModelDrawModuleData(); };
// ?<W3DModelDrawModuleData::W3DModelDrawModuleData> absent-from-retail
W3DModelDrawModuleData::W3DModelDrawModuleData(struct EmitVtableTag *) {}
void W3DModelDrawModuleData_Delete(W3DModelDrawModuleData *w3DModelDrawModuleData) { delete w3DModelDrawModuleData; }

// ??_GW3DSailModelDraw@@UAEPAXI@Z @0x000D08A2 28B: slot 0 of vtable 0x00BCDC60; calls ??1 at 0x000D08BE.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x000D07CB uses class-name string "W3DSailModelDraw".
class W3DSailModelDraw { public: W3DSailModelDraw(struct EmitVtableTag *); virtual ~W3DSailModelDraw(); };
// ?<W3DSailModelDraw::W3DSailModelDraw> absent-from-retail
W3DSailModelDraw::W3DSailModelDraw(struct EmitVtableTag *) {}
void W3DSailModelDraw_Delete(W3DSailModelDraw *w3DSailModelDraw) { delete w3DSailModelDraw; }

// ??_GW3DBoatWakeModelDraw@@UAEPAXI@Z @0x000D0D08 28B: slot 0 of vtable 0x00BCDD70; calls ??1 at 0x000D0B69.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x000D0C93 uses class-name string "W3DBoatWakeModelDraw".
class W3DBoatWakeModelDraw : public DrawModule { public: W3DBoatWakeModelDraw(struct EmitVtableTag *); virtual ~W3DBoatWakeModelDraw(); };
// ?<W3DBoatWakeModelDraw::W3DBoatWakeModelDraw> absent-from-retail
inline W3DBoatWakeModelDraw::W3DBoatWakeModelDraw(struct EmitVtableTag *) : DrawModule(0, 0) {}
void W3DBoatWakeModelDraw_Delete(W3DBoatWakeModelDraw *w3DBoatWakeModelDraw) { w3DBoatWakeModelDraw->W3DBoatWakeModelDraw::W3DBoatWakeModelDraw(0); delete w3DBoatWakeModelDraw; }

// ??_GW3DProjectileStreamDraw@@UAEPAXI@Z @0x000D144F 28B: slot 0 of vtable 0x00BCE010; calls ??1 at 0x000D146B.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x000D140A uses class-name string "W3DProjectileStreamDraw".
class W3DProjectileStreamDraw { public: W3DProjectileStreamDraw(struct EmitVtableTag *); virtual ~W3DProjectileStreamDraw(); };
// ?<W3DProjectileStreamDraw::W3DProjectileStreamDraw> absent-from-retail
W3DProjectileStreamDraw::W3DProjectileStreamDraw(struct EmitVtableTag *) {}
void W3DProjectileStreamDraw_Delete(W3DProjectileStreamDraw *w3DProjectileStreamDraw) { delete w3DProjectileStreamDraw; }

// ??_GW3DTornadoDrawModuleData@@UAEPAXI@Z @0x000D16F7 28B: slot 0 of vtable 0x00BCE198; calls ??1 at 0x000D1713.
// Owner evidence (audited 2026-09-26): retail registration W3DTornadoDraw -> data factory RVA 0x00065171 -> ctor RVA 0x000D16B4; primary vptr store RVA 0x000D16CC.
class W3DTornadoDrawModuleData { public: W3DTornadoDrawModuleData(struct EmitVtableTag *); virtual ~W3DTornadoDrawModuleData(); };
// ?<W3DTornadoDrawModuleData::W3DTornadoDrawModuleData> absent-from-retail
W3DTornadoDrawModuleData::W3DTornadoDrawModuleData(struct EmitVtableTag *) {}
void W3DTornadoDrawModuleData_Delete(W3DTornadoDrawModuleData *w3DTornadoDrawModuleData) { delete w3DTornadoDrawModuleData; }

