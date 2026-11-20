// Native BCF4A0..BCF4AC is the complete three-slot WaterTracksObj table:
// empty Render, sphere getter, box getter. The following word is zero before
// the source-path literal at BCF4B0. ZH W3DWaterTracks.h corroborates the slot
// roles; all three addresses below are existing byte-verified body owners.
// Keep the existing neutral table name used by the constructor and reset.
extern "C" void __identifier("?rva000B3FD0@Rva000B3FD0@@QAEXXZ")();
extern "C" void __identifier("?Get_Obj_Space_Bounding_Sphere@WaterTracksObj@@UBEXAAVSphereClass@@@Z")();
extern "C" void __identifier("?Get_Obj_Space_Bounding_Box@WaterTracksObj@@UBEXAAURegion3D@@@Z")();
typedef void (*BfmeWaterTrackSlot)();
extern "C" BfmeWaterTrackSlot const bfmeVftSH[3] = {
	__identifier("?rva000B3FD0@Rva000B3FD0@@QAEXXZ"),
	__identifier("?Get_Obj_Space_Bounding_Sphere@WaterTracksObj@@UBEXAAVSphereClass@@@Z"),
	__identifier("?Get_Obj_Space_Bounding_Box@WaterTracksObj@@UBEXAAURegion3D@@@Z")
};

class TextureBaseClass
{
public:
	void Release_Ref();	// 0x0061ED10
};

class BfmeThingSH
{
public:
	void bfmeResetSH();
	const void *m_bfmeVft;
	TextureBaseClass *m_bfmeSub;
};

void BfmeThingSH::bfmeResetSH()
{
	m_bfmeVft = bfmeVftSH;
	TextureBaseClass *sub = m_bfmeSub;
	if (sub != 0)
		sub->Release_Ref();
}
