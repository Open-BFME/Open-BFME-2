// cl: /DNDEBUG /MD /EHsc
// ??0TextureVectorBaseCtorShim@@QAE@HPBV?$RefCountPtr@VTextureClass@@@@@Z
// @ 0x0016ED80 (191B). Ported from Open-BFME-1
// Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorClass_ctor_Thunk.cpp
// (?construct@TextureVectorBaseCtorShim@@QAEXHH@Z at 0x92FBA0, 191B).
// Exception strings and both internal calls are identical in both games.
extern "C" const void *const __identifier("??_7?$VectorClass@VBfmeHandleCX@@@@6B@")[];  // folded vftable 0x00BD4640 (2 classes), by its data-ledger name

#include <new.h>

#include <new>

class TextureClass
{
public:
	void Release_Ref();
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr();
	~RefCountPtr();

private:
	T *Referent;
};

typedef RefCountPtr<TextureClass> TextureVectorCell;

// The compiler-generated RefCountPtr<TextureClass> vector deleting destructor (??_E) takes
// the optimization state of the first function that needs it; retail links the /O1 copy
// (TextureHandleAssignment.cpp emits it). This unemitted anchor makes this unit's copy that body.
static void bfmeTextureCellVddAnchor(TextureVectorCell *textureVectorCell) { delete [] textureVectorCell; }

class TextureVectorBaseCtorShim
{
public:
	__declspec(noinline) TextureVectorBaseCtorShim(int, TextureVectorCell const *);
	virtual ~TextureVectorBaseCtorShim();

private:
	TextureVectorCell *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

// ??0TextureVectorBaseCtorShim@@QAE@HPBV?$RefCountPtr@VTextureClass@@@@@Z
// @ 0x0016ED80 (191B). Ported from Open-BFME-1
// Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorClass_ctor_Thunk.cpp
// (?construct@TextureVectorBaseCtorShim@@QAEXHH@Z at 0x92FBA0, 191B) with the
// BFME2 retail vtable 0x00BD4640 (BFME1 carries 0x0113C5FC).
TextureVectorBaseCtorShim::TextureVectorBaseCtorShim(int size, TextureVectorCell const *array)
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7?$VectorClass@VBfmeHandleCX@@@@6B@"));
	Vector = 0;
	VectorMax = size;
	IsValid = true;
	IsAllocated = false;

	if (size) {
		if (array) {
			Vector = new ((void *)(unsigned char *)array) TextureVectorCell[size];
		} else {
			Vector = new TextureVectorCell[size];
			IsAllocated = true;
		}
	}
}
