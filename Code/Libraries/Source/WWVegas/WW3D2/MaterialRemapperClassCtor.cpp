// cl: /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// platformsdk
// ??0MaterialRemapperClass@@QAE@PAVMaterialInfoClass@@0@Z
// retail 0x0016EF20, 503 bytes. Dedicated TU.
//
// BFME2 keeps BFME1's MaterialRemapperClass shape but rewrites the texture
// side with owning references (the vertex-material side stays raw):
// - TextureRemapStruct holds RefCountPtr<TextureClass> handles, so its array
//   new goes through the vector constructor iterator (ehvec at 0x629512 with
//   the struct ctor/dtor as DIR32s); the VmatRemapStruct array stays a plain
//   operator new[] (trivial 8-byte elements, no cookie consumer).
// - The texture fill assigns through RefCountPtr temporaries: Peek_Texture
//   returns by value (hidden retptr, pinned at 0x135F35), the inline
//   operator= does Add_Ref-new/Release-old/store, and the temporary dies at
//   the end of each assignment statement (four Release_Ref sites per pass).
// - The vertex-material fill uses an inlined bounds-checked Peek (the dest
//   side guards against its own count, like retail).
// TU-local replicas mangle identically to the real instantiations.

#include <new>
#include <string.h>
#include <windows.h>

class TextureBaseClass
{
public:
	void Release_Ref();

protected:
	void *m_vptr;
	unsigned short m_refs;
};

class TextureClass : public TextureBaseClass
{
public:
	// Preserve inline increments without emitting a competing external copy.
	__declspec(dllimport) __forceinline void Add_Ref(void) { m_refs++; }
};

class VertexMaterialClass;
class MaterialInfoClass;

template<class T>
class RefCountPtr
{
public:
	__declspec(dllimport) __forceinline RefCountPtr() : Referent(0) {}
	// The constructor inlines this assignment; do not emit a competing copy.
	__declspec(dllimport) __forceinline RefCountPtr &operator=(const RefCountPtr &src)
	{
		if (src.Referent) {
			src.Referent->Add_Ref();
		}
		if (Referent) {
			Referent->Release_Ref();
		}
		Referent = src.Referent;
		return *this;
	}
	~RefCountPtr()
	{
		if (Referent) {
			Referent->Release_Ref();
		}
	}

private:
	T *Referent;
};

// ??0TextureRemapStruct@MaterialRemapperClass@@QAE@XZ present-unmatched
#include "MaterialInfoClass.h"

class MaterialRemapperClass
{
public:
	MaterialRemapperClass(MaterialInfoClass *src, MaterialInfoClass *dest);

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

MaterialRemapperClass::MaterialRemapperClass(MaterialInfoClass *src, MaterialInfoClass *dest) :
	TextureCount(0),
	TextureRemaps(NULL),
	VertexMaterialCount(0),
	VertexMaterialRemaps(NULL),
	LastSrcVmat(NULL),
	LastDestVmat(NULL),
	LastSrcTex(),
	LastDestTex()
{
	SrcMatInfo = src;
	SrcMatInfo->Add_Ref();
	DestMatInfo = dest;
	DestMatInfo->Add_Ref();

	if (src->Vertex_Material_Count() > 0) {
		VertexMaterialCount = src->Vertex_Material_Count();
		VertexMaterialRemaps = new VmatRemapStruct[VertexMaterialCount];
		for (int i = 0; i < src->Vertex_Material_Count(); i++) {
			// Retail inlines Peek_Vertex_Material's bounds check here.
			VertexMaterialRemaps[i].Src = i < src->field18 ? src->field0c[i] : NULL;
			VertexMaterialRemaps[i].Dest = i < dest->field18 ? dest->field0c[i] : NULL;
		}
	}

	if (src->Texture_Count() > 0) {
		TextureCount = src->Texture_Count();
		TextureRemaps = new TextureRemapStruct[TextureCount];
		for (int i = 0; i < src->Texture_Count(); i++) {
			TextureRemaps[i].Src = src->Peek_Texture(i);
			TextureRemaps[i].Dest = dest->Peek_Texture(i);
		}
	}
}
