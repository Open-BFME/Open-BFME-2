// cl: /DNDEBUG /MD /EHsc
// ??0TextureVectorBaseCtorShim@@QAE@HPBV?$RefCountPtr@VTextureClass@@@@@Z
// @ 0x0016ED80 (191B). Ported from Open-BFME-1
// Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorClass_ctor_Thunk.cpp
// (?construct@TextureVectorBaseCtorShim@@QAEXHH@Z at 0x92FBA0, 191B).
// Exception strings and both internal calls are identical in both games.
extern "C" const void *const vtbl_00BD4640[];  // folded, 2 classes; via ??_7?$VectorClass@VBfmeHandleCX@@@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD4640=??_7?$VectorClass@VBfmeHandleCX@@@@6B@")

#include <new.h>

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *pointer);

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
	*(unsigned int *)this = ((unsigned int)vtbl_00BD4640);
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
