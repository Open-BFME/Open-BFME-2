// ?Rva0020E354Cast@@YG_NPAVRenderObjClass@@ABVVector3@@1@Z
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0020E354Cast@@YG_NPAVRenderObjClass@@ABVVector3@@1@Z, retail 0x0020E354, 32 bytes.
// Stdcall wrapper that loads the 0x00DFEF18 singleton and invokes the
// __thiscall cast body at 0x002BF198 with out 0 collisionType 1 checkHidden 1.
// Caller 0x0020F9C5 sets ecx (a member call); the loaded singleton is the
// callee's unused hidden this, which is why retail emits
// `mov ecx, [0x00DFEF18]` where a free call would emit `mov eax, ...`.
class RenderObjClass;
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class Rva00DFEF18Host
{
public:
	bool Cast(RenderObjClass *obj, const Vector3 &start, const Vector3 &dir, Vector3 *out, int collisionType, bool checkHidden);
};

// The rowed body at 0x002BF198 is the same function under a free __stdcall
// alias; both conventions callee-clean the six stack args, so the link is
// ABI-safe and the hidden this is unused.
#pragma comment(linker, "/alternatename:?Cast@Rva00DFEF18Host@@QAE_NPAVRenderObjClass@@ABVVector3@@1PAV3@H_N@Z=?Rva002BF198Cast@@YG_NPAVRenderObjClass@@ABVVector3@@1PAV2@H_N@Z")

extern Rva00DFEF18Host *g_00DFEF18;

bool __stdcall Rva0020E354Cast(RenderObjClass *obj, const Vector3 &start, const Vector3 &dir)
{
	return g_00DFEF18->Cast(obj, start, dir, 0, 1, 1);
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00DFEF18@@3PAVRva00DFEF18Host@@A=?g_00DFEF18@@3PAVRva002D3627Host@@A")
