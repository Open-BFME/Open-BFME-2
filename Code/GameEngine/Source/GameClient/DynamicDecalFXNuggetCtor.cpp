// ??0DynamicDecalFXNugget@@QAE@XZ
// cl: /DNDEBUG /MD
//
// ??0DynamicDecalFXNugget@@QAE@XZ 147B @0x1E0429: no-arg ctor called by
// DynamicDecalFXNugget::parse (0x001E149D) for the DynamicDecal FXList
// keyword; class name from BFME1. Member names and offsets from the retail
// FieldParse table 0x00BDCCF0 (DecalName@0x148, Shader@0x14C, Size@0x150,
// Color@0x154, Offset@0x160, OrientToObject@0x168, OpacityStart@0x16C,
// OpacityFadeTimeOne@0x170, OpacityPeak@0x174, OpacityPeakTime@0x178,
// OpacityFadeTimeTwo@0x17C, OpacityEnd@0x180, StartingDelay@0x184,
// Lifetime@0x188) and the BFME1 donor (DynamicDecalFXNuggetConstructor:
// shader ALPHA, size 0, type 13, color/offset/opacity zeros,
// orientToObject true). Base 0x001DFEAA is the shared FXNugget-family
// base (Rva001DFEAABase.h).
//
// Recovered from the banked attempt reverse/attempts/0x001e0429.cpp (score
// 0.98). Two things were already settled by that pass and are kept: the
// _ReadWriteBarrier at the top of the body, which lets cl hoist the
// `xorps xmm0,xmm0` to its retail slot immediately after the base-ctor call,
// and the fact that the `push edi` / `lea ecx,[esi+0x154]` pair is setFromInt's
// own argument push and receiver load rather than a barrier argument pair --
// retail contains no barrier argument pair.
//
// The remaining residue was that this toolchain hoists that call-setup pair
// above the vtable / decalName / nuggetType stores, while retail keeps it
// below. Binding the decalName slot to a pointer local declared BEFORE the
// barrier blocks the hoist: the store through `nameSlot` is no longer a direct
// write cl can sink past the call setup, so the pair settles at retail's +0x14
// and the following three stores emit in order. 147 bytes, exact match.
//
// Spelling matters here and the reason is not obvious, so it is worth
// recording: routing the OTHER three stores through pointers instead (the
// vtable word, m_nuggetType, m_shader) does not reproduce retail -- each leaves
// the same +0x0E first-diff. Only the decalName store, bound through a
// pointer local in scope across the barrier, moves the pair. A
// read-then-write spelling (`const char *nameSlot = m_decalName;`) collapses
// the whole body to 141 bytes.

#include "../../Include/GameClient/Rva001DFEAABase.h"

// The retail table at RVA 0x007DD7A4: 10 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GCursorParticleSystemFXNugget@@UAEPAXI@Z")();
void __identifier("?doFXPos@DynamicDecalFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z")();
void __identifier("?doFXObj@DynamicDecalFXNugget@@UBEXPBVObject@@0@Z")();
void __identifier("?rva001E1709@AttachedModelFXNugget@@UBEXAAVAssetList@@H@Z")();
void __identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z")();
void __identifier("?doFXPos@LaserFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z")();
void __identifier("?doFXObj@LaserFXNugget@@UBEXPBVObject@@0@Z")();
void __identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z")();
}
extern const void *const g_00BDD7A4[10] = {
	(const void *)&__identifier("??_GCursorParticleSystemFXNugget@@UAEPAXI@Z"), // slot 0 0x001E1152
	(const void *)&__identifier("?doFXPos@DynamicDecalFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z"), // slot 1 0x001E0E43
	(const void *)&__identifier("?doFXObj@DynamicDecalFXNugget@@UBEXPBVObject@@0@Z"), // slot 2 0x001E04BC
	(const void *)&__identifier("?rva001E1709@AttachedModelFXNugget@@UBEXAAVAssetList@@H@Z"), // slot 3 0x001E1709
	(const void *)&__identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z"), // slot 4 0x001DFF5D
	(const void *)&__identifier("??_GCursorParticleSystemFXNugget@@UAEPAXI@Z"), // slot 5 0x001E1152
	(const void *)&__identifier("?doFXPos@LaserFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z"), // slot 6 0x001E04FE
	(const void *)&__identifier("?doFXObj@LaserFXNugget@@UBEXPBVObject@@0@Z"), // slot 7 0x001E05F9
	(const void *)&__identifier("?Add_Dependencies_To_List@RenderObjClass@@MAEXAAV?$DynamicVectorClass@VStringClass@@@@_N@Z"), // slot 8 0x0050B238
	(const void *)&__identifier("?rva001DFF5D@Rva001DFEAABase@@UAE_NPAVObject@@0@Z"), // slot 9 0x001DFF5D
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "../../../Libraries/Include/Lib/RGBColor.h"

#include "../../../Libraries/Include/Lib/Coord2D.h"

// The constructor stores retail's table 0x00BDD7A4 itself, so cl installs no vptr.
class __declspec(novtable) DynamicDecalFXNugget : public Rva001DFEAABase
{
public:
	DynamicDecalFXNugget();
private:
	const char *m_decalName; // +0x148
	int m_shader; // +0x14C, ALPHA = 0
	float m_size; // +0x150
	RGBColor m_color; // +0x154
	Coord2D m_offset; // +0x160
	bool m_orientToObject; // +0x168
	int m_opacityStart; // +0x16C
	float m_opacityFadeTimeOne; // +0x170
	int m_opacityPeak; // +0x174
	float m_opacityPeakTime; // +0x178
	float m_opacityFadeTimeTwo; // +0x17C
	int m_opacityEnd; // +0x180
	float m_startingDelay; // +0x184
	float m_lifetime; // +0x188
};

DynamicDecalFXNugget::DynamicDecalFXNugget()
{
	const char **nameSlot = &m_decalName;
	_ReadWriteBarrier();
	*(const void **)this = g_00BDD7A4;
	*nameSlot = 0;
	m_nuggetType = 13;
	m_shader = 0;
	m_size = 0.0f;
	m_color.setFromInt(0);
	Coord2D *offset = &m_offset;
	offset->x = offset->y = 0.0f;
	m_opacityStart = 0;
	m_opacityPeak = 0;
	m_opacityEnd = 0;
	m_orientToObject = true;
	m_opacityFadeTimeOne = 0.0f;
	m_opacityPeakTime = 0.0f;
	m_opacityFadeTimeTwo = 0.0f;
	m_startingDelay = 0.0f;
	m_lifetime = 0.0f;
}