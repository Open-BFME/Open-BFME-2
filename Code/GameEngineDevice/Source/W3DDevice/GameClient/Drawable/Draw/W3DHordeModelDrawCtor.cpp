// cl: /DNDEBUG /MD
//
// ??0W3DHordeModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x00078A82,
// 68 bytes. Behavior-side ctor completing the W3DHordeModelDraw file-unit
// (instance factory rowed at 0x64E80 news 0x2F0+ with this ctor as sole raw
// caller; ModuleData proc/factory rowed at 0x793E5/0x64EBB; pool key rowed at
// 0x78B38; name getter rowed at 0x78B7D returning the W3DHordeModelDraw
// literal; ModuleData ctor pinned at 0x789E3).
//
// Shape: frameless single-base ctor over the pinned W3DScriptedModelDraw base
// 0xC0DD8 (factory-evidenced (Thing*;ModuleData*) ctor) with the derived
// vtable plus its two shared member-subobject vtables stored explicitly in
// the body via pointer casts after the member zeros (Defector precedent: no
// virtuals are declared anywhere so no vtable is emitted here; the
// immediates are DIR32-masked in comparison). The three trailing members at
// +0x2E8 are zeroed from the init list, which the compiler emits before the
// body statements, matching retail order. The global counter bump closes the
// body. Zero new pins (base resolves via the existing pin).

extern "C" const unsigned char __identifier("??_7Rva000CA119@@6BRva000CA119_B2@@@")[];
extern "C" const unsigned char __identifier("??_7W3DTankDraw@@6BDrawInterfaceA@@@")[];
// The retail table at RVA 0x007C68F0: 68 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva0078B83@@UAEPAXI@Z")();
void __identifier("?rva000CA132@Rva000CA132@@QAEXXZ")();
void __identifier("?name@Rva00078B7DNamed@@QBEPBDXZ")();
void __identifier("?xfer@W3DHordeModelDraw@@MAEXPAVXfer@@@Z")();
void __identifier("?getModuleNameKey@W3DHordeModelDraw@@UBE?AW4NameKeyType@@XZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?onDrawableBoundToObject@W3DHordeModelDraw@@QAEXXZ")();
void __identifier("?rva000B7C18@W3DScriptedModelDraw@@QAEXXZ")();
void __identifier("?getDebrisDrawInterface@W3DDebrisDraw@@UAEPAVDebrisDrawInterface@@XZ")();
void __identifier("?doDrawModule@W3DModelDraw@@UAEXPBVMatrix3D@@@Z")();
void __identifier("?setShadowsEnabled@W3DModelDraw@@UAEX_N@Z")();
void __identifier("?releaseShadows@W3DModelDraw@@UAEXXZ")();
void __identifier("?allocateShadows@W3DScriptedModelDraw@@UAEXXZ")();
void __identifier("?rva000B90A3@W3DScriptedModelDraw@@QAEXXZ")();
void __identifier("?setHidden@W3DModelDraw@@UAEX_N@Z")();
void __identifier("?get@Rva002035A9ByteField@@QBEEXZ")();
void __identifier("?set@Rva003B23CDByteSlot@@QAEXE@Z")();
void __identifier("?rva000B9DD9@Rva000B9DD9@@QAEXABVAsciiString@@@Z")();
void __identifier("?setTerrainDecal@W3DModelDraw@@UAEXW4TerrainDecalType@@@Z")();
void __identifier("?setTerrainDecalSize@W3DModelDraw@@UAEXMM@Z")();
void __identifier("?setTerrainDecalOpacity@W3DModelDraw@@UAEXM@Z")();
void __identifier("?rva000B508A@Rva000B508A@@QAEXPBVRadiusDecalTemplate@@@Z")();
void __identifier("?rva000B318D@Rva000B318DForwarder@@QAEXH@Z")();
void __identifier("?rva000B3198@Rva000B32EF@@QAEXABUCoord3D@@0@Z")();
void __identifier("?rva000B31B9@Rva000B31B9NullForwarder@@QAEXH@Z")();
void __identifier("?rva000B31CB@Rva000B31CB@@QAEXIH@Z")();
void __identifier("?rva000B3266@Rva000B3266Forwarder@@QAEXXZ")();
void __identifier("?rva000B3271@Rva000B3271@@QAEXPBVRadiusDecalTemplate@@@Z")();
void __identifier("?rva000B32C2@Rva000B32EF@@QAEXPBUCoord3D@@@Z")();
void __identifier("?rva000B32D7@Rva000B32EF@@QAEXM@Z")();
void __identifier("?rva000B32EF@Rva000B32EF@@QAEXPAH@Z")();
void __identifier("?rva000B330C@Rva000B32EF@@QAEXPBUCoord3D@@MPBI@Z")();
void __identifier("?rva000B333D@Rva000B333DForwarder@@QAEXXZ")();
void __identifier("?setFullyObscuredByShroud@W3DModelDraw@@UAEX_N@Z")();
void __identifier("?rva000C7699@Rva000C7699@@QAEXXZ")();
void __identifier("?isVisible@W3DModelDraw@@UBE_NXZ")();
void __identifier("?reactToTransformChange@W3DModelDraw@@UAEXPBVMatrix3D@@PBUCoord3D@@M@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?get@Rva000CA841MovLeaNegSbbField@@QBEHXZ")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?get@Rva00225A98DwordField@@QBEHXZ")();
void __identifier("?rva000B61AB@W3DScriptedModelDraw@@UAEMXZ")();
void __identifier("?GetPortraitImage@Rva000B7029@@UAEPBVImage@@XZ")();
void __identifier("?getButtonImage@W3DScriptedModelDraw@@UAEPBVImage@@XZ")();
void __identifier("?rva000B5FB3@Rva000B5FB3Forwarder@@QAEXH@Z")();
void __identifier("?SetRampMeshOverload@W3DScriptedModelDraw@@UAEXPBDH@Z")();
void __identifier("?rva000B5FD5@W3DScriptedModelDraw@@UAEHXZ")();
void __identifier("?rva000BB4CE@W3DScriptedModelDraw@@QAEXPAVAsciiString@@H@Z")();
void __identifier("?rva000B3A80@W3DScriptedModelDraw@@UAEXXZ")();
void __identifier("?set@Rva00078B2BByteSlot@@QAEXE@Z")();
void __identifier("?set@Rva00078ACEByteSlot@@QAEXE@Z")();
void __identifier("?rva00078AC6@Rva00078AC6Forwarder@@QAEXXZ")();
void __identifier("?rva000B595F@Rva000B595F@@QAEXXZ")();
void __identifier("?rva000B3D39@W3DModelDraw@@UAEXXZ")();
void __identifier("?setModelState@W3DHordeModelDraw@@QAE_NPAUHordeModelState@@_NPAURva000C3886Obj@@@Z")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?rva000791DD@Rva000791DDForwarder@@QAEXXZ")();
void __identifier("?rva000791E5@Rva000791E5Forwarder@@QAEXH@Z")();
}
extern const void *const g_00BC68F0[68] = {
	(const void *)&__identifier("??_GRva0078B83@@UAEPAXI@Z"), // slot 0 0x000791C1
	(const void *)&__identifier("?rva000CA132@Rva000CA132@@QAEXXZ"), // slot 1 0x000CA132
	(const void *)&__identifier("?name@Rva00078B7DNamed@@QBEPBDXZ"), // slot 2 0x00078B7D
	(const void *)&__identifier("?xfer@W3DHordeModelDraw@@MAEXPAVXfer@@@Z"), // slot 3 0x00078BBB
	(const void *)&__identifier("?getModuleNameKey@W3DHordeModelDraw@@UBE?AW4NameKeyType@@XZ"), // slot 4 0x00078B38
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 5 0x000B3FD0
	(const void *)&__identifier("?onDrawableBoundToObject@W3DHordeModelDraw@@QAEXXZ"), // slot 6 0x0007A7DD
	(const void *)&__identifier("?rva000B7C18@W3DScriptedModelDraw@@QAEXXZ"), // slot 7 0x000B7C18
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 8 0x000B3FD0
	(const void *)&__identifier("?getDebrisDrawInterface@W3DDebrisDraw@@UAEPAVDebrisDrawInterface@@XZ"), // slot 9 0x000CF155
	(const void *)&__identifier("?getDebrisDrawInterface@W3DDebrisDraw@@UAEPAVDebrisDrawInterface@@XZ"), // slot 10 0x000CF155
	(const void *)&__identifier("?doDrawModule@W3DModelDraw@@UAEXPBVMatrix3D@@@Z"), // slot 11 0x000C7BC4
	(const void *)&__identifier("?setShadowsEnabled@W3DModelDraw@@UAEX_N@Z"), // slot 12 0x000B2E29
	(const void *)&__identifier("?releaseShadows@W3DModelDraw@@UAEXXZ"), // slot 13 0x000B2E14
	(const void *)&__identifier("?allocateShadows@W3DScriptedModelDraw@@UAEXXZ"), // slot 14 0x000B9B4A
	(const void *)&__identifier("?rva000B90A3@W3DScriptedModelDraw@@QAEXXZ"), // slot 15 0x000B90A3
	(const void *)&__identifier("?setHidden@W3DModelDraw@@UAEX_N@Z"), // slot 16 0x000B6F6D
	(const void *)&__identifier("?get@Rva002035A9ByteField@@QBEEXZ"), // slot 17 0x002035A9
	(const void *)&__identifier("?set@Rva003B23CDByteSlot@@QAEXE@Z"), // slot 18 0x003B23CD
	(const void *)&__identifier("?rva000B9DD9@Rva000B9DD9@@QAEXABVAsciiString@@@Z"), // slot 19 0x000B9DD9
	(const void *)&__identifier("?setTerrainDecal@W3DModelDraw@@UAEXW4TerrainDecalType@@@Z"), // slot 20 0x000B9CE8
	(const void *)&__identifier("?setTerrainDecalSize@W3DModelDraw@@UAEXMM@Z"), // slot 21 0x000B314B
	(const void *)&__identifier("?setTerrainDecalOpacity@W3DModelDraw@@UAEXM@Z"), // slot 22 0x000B316B
	(const void *)&__identifier("?rva000B508A@Rva000B508A@@QAEXPBVRadiusDecalTemplate@@@Z"), // slot 23 0x000B508A
	(const void *)&__identifier("?rva000B318D@Rva000B318DForwarder@@QAEXH@Z"), // slot 24 0x000B318D
	(const void *)&__identifier("?rva000B3198@Rva000B32EF@@QAEXABUCoord3D@@0@Z"), // slot 25 0x000B3198
	(const void *)&__identifier("?rva000B31B9@Rva000B31B9NullForwarder@@QAEXH@Z"), // slot 26 0x000B31B9
	(const void *)&__identifier("?rva000B31CB@Rva000B31CB@@QAEXIH@Z"), // slot 27 0x000B31CB
	(const void *)&__identifier("?rva000B3266@Rva000B3266Forwarder@@QAEXXZ"), // slot 28 0x000B3266
	(const void *)&__identifier("?rva000B3271@Rva000B3271@@QAEXPBVRadiusDecalTemplate@@@Z"), // slot 29 0x000B3271
	(const void *)&__identifier("?rva000B32C2@Rva000B32EF@@QAEXPBUCoord3D@@@Z"), // slot 30 0x000B32C2
	(const void *)&__identifier("?rva000B32D7@Rva000B32EF@@QAEXM@Z"), // slot 31 0x000B32D7
	(const void *)&__identifier("?rva000B32EF@Rva000B32EF@@QAEXPAH@Z"), // slot 32 0x000B32EF
	(const void *)&__identifier("?rva000B330C@Rva000B32EF@@QAEXPBUCoord3D@@MPBI@Z"), // slot 33 0x000B330C
	(const void *)&__identifier("?rva000B333D@Rva000B333DForwarder@@QAEXXZ"), // slot 34 0x000B333D
	(const void *)&__identifier("?setFullyObscuredByShroud@W3DModelDraw@@UAEX_N@Z"), // slot 35 0x000B6FFE
	(const void *)&__identifier("?rva000C7699@Rva000C7699@@QAEXXZ"), // slot 36 0x000C7699
	(const void *)&__identifier("?isVisible@W3DModelDraw@@UBE_NXZ"), // slot 37 0x000B37F0
	(const void *)&__identifier("?reactToTransformChange@W3DModelDraw@@UAEXPBVMatrix3D@@PBUCoord3D@@M@Z"), // slot 38 0x000B7FE8
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 39 0x000B3FD0
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 40 0x0047A699
	(const void *)&__identifier("?get@Rva000CA841MovLeaNegSbbField@@QBEHXZ"), // slot 41 0x000CA841
	(const void *)&__identifier("?get@Rva000CA841MovLeaNegSbbField@@QBEHXZ"), // slot 42 0x000CA841
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 43 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 44 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 45 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 46 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 47 0x000D43D0
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 48 0x000D43D0
	(const void *)&__identifier("?get@Rva00225A98DwordField@@QBEHXZ"), // slot 49 0x00225A98
	(const void *)&__identifier("?rva000B61AB@W3DScriptedModelDraw@@UAEMXZ"), // slot 50 0x000B61AB
	(const void *)&__identifier("?GetPortraitImage@Rva000B7029@@UAEPBVImage@@XZ"), // slot 51 0x000B7029
	(const void *)&__identifier("?getButtonImage@W3DScriptedModelDraw@@UAEPBVImage@@XZ"), // slot 52 0x000B9C8C
	(const void *)&__identifier("?rva000B5FB3@Rva000B5FB3Forwarder@@QAEXH@Z"), // slot 53 0x000B5FB3
	(const void *)&__identifier("?SetRampMeshOverload@W3DScriptedModelDraw@@UAEXPBDH@Z"), // slot 54 0x000B5FBE
	(const void *)&__identifier("?rva000B5FD5@W3DScriptedModelDraw@@UAEHXZ"), // slot 55 0x000B5FD5
	(const void *)&__identifier("?rva000BB4CE@W3DScriptedModelDraw@@QAEXPAVAsciiString@@H@Z"), // slot 56 0x000BB4CE
	(const void *)&__identifier("?rva000B3A80@W3DScriptedModelDraw@@UAEXXZ"), // slot 57 0x000B3A80
	(const void *)&__identifier("?set@Rva00078B2BByteSlot@@QAEXE@Z"), // slot 58 0x00078B2B
	(const void *)&__identifier("?set@Rva00078ACEByteSlot@@QAEXE@Z"), // slot 59 0x00078ACE
	(const void *)&__identifier("?rva00078AC6@Rva00078AC6Forwarder@@QAEXXZ"), // slot 60 0x00078AC6
	(const void *)&__identifier("?rva000B595F@Rva000B595F@@QAEXXZ"), // slot 61 0x000B595F
	(const void *)&__identifier("?rva000B3D39@W3DModelDraw@@UAEXXZ"), // slot 62 0x000B3D39
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 63 0x000B3FD0
	(const void *)&__identifier("?setModelState@W3DHordeModelDraw@@QAE_NPAUHordeModelState@@_NPAURva000C3886Obj@@@Z"), // slot 64 0x0007A847
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 65 0x0047A69C
	(const void *)&__identifier("?rva000791DD@Rva000791DDForwarder@@QAEXXZ"), // slot 66 0x000791DD
	(const void *)&__identifier("?rva000791E5@Rva000791E5Forwarder@@QAEXH@Z"), // slot 67 0x000791E5
};

class Thing;
class ModuleData;

class W3DScriptedModelDraw
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);

private:
	// W3DHordeModelDraw's own first member is at +0x2E8, so this is what
	// sits before it. Only its size is claimed (BFME1 donor has 0x27C of
	// base here; BFME2 retail proves 0x2E8).
	unsigned char m_unmodelled[0x2E8];
};

class W3DHordeModelDraw : public W3DScriptedModelDraw
{
public:
	W3DHordeModelDraw(Thing *thing, const ModuleData *moduleData);

private:
	int m_unmodelled2E8;	// +0x2E8
	int m_unmodelled2EC;	// +0x2EC
	int m_unmodelled2F0;	// +0x2F0
};

// The counter the constructor bumps. Nothing in the image names it; it is
// reached by what this body does to it.
extern int TheW3DHordeModelDrawCount;	// 0x00DE1FB4
// TheW3DHordeModelDrawCount: VA 0xde1fb4 (zero-filled .bss).
int TheW3DHordeModelDrawCount;

// ??0W3DHordeModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0x00078A82
W3DHordeModelDraw::W3DHordeModelDraw(Thing *thing, const ModuleData *moduleData) :
	W3DScriptedModelDraw(thing, moduleData),
	m_unmodelled2E8(0), m_unmodelled2EC(0), m_unmodelled2F0(0)
{
	*(unsigned int *)this = ((unsigned int)g_00BC68F0);
	*(unsigned int *)((char *)this + 0x0C) = ((unsigned int)__identifier("??_7W3DTankDraw@@6BDrawInterfaceA@@@"));
	*(unsigned int *)((char *)this + 0x10) = ((unsigned int)__identifier("??_7Rva000CA119@@6BRva000CA119_B2@@@"));
	++TheW3DHordeModelDrawCount;
}
