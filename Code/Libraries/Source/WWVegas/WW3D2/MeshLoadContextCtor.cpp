// cl: /Ireference/shims/meshgeom /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// MeshLoadContextClass constructor and destructor, retail 0x0018B5F0 / 0x0018B180.
//
// Dedicated TU (MeshModelReadTexcoords.cpp precedent): meshmdlio.cpp carries
// dozens of unrowed donor defs, so editing it trips the
// find_declared_unmatched gate; the lifetime methods use a TU-local
// class replica here.
//
// Layout evidence, all retail-measured from the 0x18B5F0 body:
// - Six vector members at +0x94..+0x123. The +0xAC one builds through the
//   rowed VectorClass<ShaderClass> base (0x0016FB40, matinfo.cpp) exactly as
//   the headers spell it. The +0x10C one is BFME2-only (ZH upstream
//   GeneralsMD meshmdlio.cpp carries five): TextureVectorBase shim 0x0016ED80
//   with (0, 0) plus vtable 0x00BD4688 with [0x14] = 10 and [0x10] = 0,
//   mirroring matched MaterialCollectorClassCtor.cpp. The matched owning-handle
//   Peek_Texture overload at 0x188700 confirms texture storage at +0x110.
// - AlternateMatDesc opens at +0x124 and spans 0x118 (TempUVArray vtable lands
//   at +0x23C per the matched MeshModelReadTexcoords.cpp TU, whose TU-local
//   replica asserts sizeof(MeshMatDescClass) == 0x118); the ZH header spells
//   0xF4 and this TU never touches MeshMatDesc internals (method calls only),
//   so the delta is a named gap in the reference/shims/meshmatdesclayout
//   spirit.
// - W3DMPO is an empty base (mesh.h documents it), so the replica omits it,
//   exactly like the MeshModelReadTexcoords replica does.

#include "meshgeometry.h"	// the meshgeom shim has to win the include guard before meshmdl.h reaches the reference copy
#include "meshmdl.h"
#include "aabtree.h"
#include "matinfo.h"
#include "vertmaterial.h"
#include "shader.h"
#include "texture.h"
#include "chunkio.h"
#include "w3derr.h"
#include "w3d_file.h"
#include "w3d_util.h"
#include "assetmgr.h"
#include "simplevec.h"
#include "realcrc.h"
#include "dx8wrapper.h"

#include <stdio.h>
void __cdecl operator delete[](void *) throw();

// Retail 0x0018B5F0 constructs the +0x10C member through the rowed
// TextureVectorBase shim (see the evidence comment above). No header defines
// RefCountPtr or the shim, so these TU-local declarations cannot collide with
// covered types.
template <class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent != 0) {
			Referent->Release_Ref();
			Referent = 0;
		}
	}

private:
	T *Referent;
};

typedef RefCountPtr<TextureClass> TextureVectorCell;

class TextureVectorBaseCtorShim
{
public:
	TextureVectorBaseCtorShim(int, TextureVectorCell const *);
	virtual ~TextureVectorBaseCtorShim()
	{
		if (Vector && IsAllocated) {
			delete [] Vector;
			Vector = 0;
		}
		IsAllocated = false;
		VectorMax = 0;
	}
	TextureVectorBaseCtorShim &operator=(const TextureVectorBaseCtorShim &);
private:
	TextureVectorCell *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

class MeshMdlTextureVector : public TextureVectorBaseCtorShim
{
public:
	__forceinline MeshMdlTextureVector()
		: TextureVectorBaseCtorShim(0, 0)
	{
		*(unsigned int *)this = 0x00BD4688;
		GrowthStep = 10;
		ActiveCount = 0;
	}
private:
	int ActiveCount;
	int GrowthStep;
};

class MeshLoadContextClass
{
private:
	MeshLoadContextClass(void);
	~MeshLoadContextClass(void);

	struct LegacyMaterialClass
	{
		LegacyMaterialClass(void) : VertexMaterialIdx(0), ShaderIdx(0), TextureIdx(0) { }
		~LegacyMaterialClass(void) { }
		void Set_Name(const char * name) { Name=name; }
		StringClass Name;
		int VertexMaterialIdx;
		int ShaderIdx;
		int TextureIdx;
	};

	W3dMeshHeader3Struct		Header;
	W3dTexCoordStruct *		TexCoords;
	W3dMaterialInfoStruct	MatInfo;

	uint32						PrelitChunkID;

	int							CurPass;
	int							CurTexStage;

	DynamicVectorClass < LegacyMaterialClass * >		LegacyMaterials;
	DynamicVectorClass < ShaderClass >					Shaders;
	DynamicVectorClass < VertexMaterialClass * >		VertexMaterials;
	DynamicVectorClass < unsigned long >				VertexMaterialCrcs;
	DynamicVectorClass < TextureClass * >				Textures;
	MeshMdlTextureVector							TextureHandles;

	MeshMatDescClass											AlternateMatDesc;
	// Named gap: retail spans the descriptor 0x118, the ZH header 0xF4.
	char															BfmeAlternateMatDescGap[0x24];

	SimpleVecClass<Vector2>									TempUVArray;

	bool															LoadedDIG;
};

MeshLoadContextClass::MeshLoadContextClass(void)
{
	memset(&Header,0,sizeof(Header));
	memset(&MatInfo,0,sizeof(MatInfo));
	PrelitChunkID = 0xffffffff;
	CurPass = 0;
	CurTexStage = 0;
	TexCoords = NULL;
	LoadedDIG = false;
}

// MeshModelClass::Load allocates 0x24C and pairs this cleanup with the constructor.
// Donor cleanup order is preserved; retail adds the owning texture-handle vector.
MeshLoadContextClass::~MeshLoadContextClass(void)
{
	int i;
	if (TexCoords != NULL) {
		delete TexCoords;
		TexCoords = NULL;
	}
	for (i = 0; i < VertexMaterials.Count(); i++) {
		VertexMaterials[i]->Release_Ref();
	}
	for (i = 0; i < LegacyMaterials.Count(); i++) {
		delete LegacyMaterials[i];
	}
}
