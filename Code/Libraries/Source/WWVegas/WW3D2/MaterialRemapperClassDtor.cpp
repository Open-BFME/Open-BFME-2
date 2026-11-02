// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// platformsdk
// ??1MaterialRemapperClass@@QAE@XZ
// retail 0x0016F170, 169 bytes. Dedicated TU.
//
// BFME2 rewrote only the texture side of the BFME1 MaterialRemapperClass as
// owning references (the vertex-material side stays raw, like BFME1):
// - TextureRemapStruct holds RefCountPtr<TextureClass> handles, so
//   `delete[] TextureRemaps` runs the vector destructor iterator (ehvec at
//   0x629110 over 8-byte elements with the struct dtor at 0x16EBA0), while
//   `delete[] VertexMaterialRemaps` stays a plain array delete.
// - The dtor releases the cached LastDestTex/LastSrcTex through the
//   out-of-line TextureBaseClass::Release_Ref (matched at 0x61ED10); the
//   Src/Dest MaterialInfo releases stay inline (dword add-form decrement
//   plus slot-0 Delete_This under /G7).
// TU-local replicas mangle identically to the real instantiations, so the
// texture element destructor and the Release_Ref calls resolve with no pins.

#include <string.h>
#include <new>
#include <windows.h>

class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

#include "VertexMaterialClass.h"

class MaterialInfoClass
{
public:
	void Release_Ref(void)
	{
		NumRefs--;
		if (NumRefs == 0) {
			Delete_This();
		}
	}
	// LINK: same-body helper under a TU-unique name (thiscall shape identical
	// to Release_Ref, so the inlined bytes match). This TU's Release_Ref copy
	// loses to the first-in-order copy (no retail address); the two named
	// calls below inline this helper instead, which emits only its own unique
	// (trivially kept) copy and no loser. No flags touched.
	void bfme_release_inline(void)
	{
		NumRefs--;
		if (NumRefs == 0) {
			Delete_This();
		}
	}
	virtual void Delete_This();

private:
	int NumRefs;
};

template<class T>
class RefCountPtr
{
public:
	RefCountPtr() : Referent(0) {}
	~RefCountPtr()
	{
		if (Referent) {
			Referent->Release_Ref();
		}
	}

private:
	T *Referent;
};

// ??1TextureRemapStruct@MaterialRemapperClass@@QAE@XZ present-unmatched
class MaterialRemapperClass
{
public:
	~MaterialRemapperClass(void);

private:
	struct VmatRemapStruct
	{
		VertexMaterialClass *Src;
		VertexMaterialClass *Dest;
	};

	struct TextureRemapStruct
	{
		RefCountPtr<TextureClass> Src;
		RefCountPtr<TextureClass> Dest;
	};

	MaterialInfoClass *SrcMatInfo;
	MaterialInfoClass *DestMatInfo;

	int TextureCount;
	TextureRemapStruct *TextureRemaps;
	int VertexMaterialCount;
	VmatRemapStruct *VertexMaterialRemaps;

	VertexMaterialClass *LastSrcVmat;
	VertexMaterialClass *LastDestVmat;
	RefCountPtr<TextureClass> LastSrcTex;
	RefCountPtr<TextureClass> LastDestTex;
};

MaterialRemapperClass::~MaterialRemapperClass(void)
{
	SrcMatInfo->bfme_release_inline();
	DestMatInfo->bfme_release_inline();

	if (TextureRemaps) {
		delete[] TextureRemaps;
	}
	if (VertexMaterialRemaps) {
		delete[] VertexMaterialRemaps;
	}
}
