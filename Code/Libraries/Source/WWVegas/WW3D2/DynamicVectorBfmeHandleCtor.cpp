// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// DynamicVectorClass<BfmeHandleCX>::DynamicVectorClass(unsigned, const
// BfmeHandleCX *) at retail 0x0016FE00 (46B): the texture-handle vector whose
// vtable is 0x00BD4688 (as installed inline by the MaterialInfo and
// MaterialCollector constructors). Retail-measured shape: forward both
// arguments to the VectorClass base ctor at 0x0016ED80, then store the vtable,
// GrowthStep=10 at +0x14 and ActiveCount=0 at +0x10. Sibling of the ShaderClass
// version at 0x0016FEA0 (meshmdlio.cpp).
//
// The base is declared only; its symbol is pinned in reverse/symbols.csv.

extern "C" const void *const vtbl_00BD4688[];  // ??_7?$DynamicVectorClass@VBfmeHandleCX@@@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD4688=??_7?$DynamicVectorClass@VBfmeHandleCX@@@@6B@")

class BfmeHandleCX;
class TextureClass;

template <class T>
class RefCountPtr;

typedef RefCountPtr<TextureClass> TextureVectorCell;

class TextureVectorBaseCtorShim
{
public:
	__declspec(noinline) TextureVectorBaseCtorShim(int size, TextureVectorCell const *array);
	virtual ~TextureVectorBaseCtorShim();

private:
	TextureVectorCell *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template <class T>
class DynamicVectorClass : public TextureVectorBaseCtorShim
{
public:
	DynamicVectorClass(unsigned int size, T const *array);

private:
	int ActiveCount;
	int GrowthStep;
};

template <class T>
DynamicVectorClass<T>::DynamicVectorClass(unsigned int size, T const *array)
	: TextureVectorBaseCtorShim(size, (TextureVectorCell const *)array)
{
	*(unsigned int *)this = ((unsigned int)vtbl_00BD4688);
	GrowthStep = 10;
	ActiveCount = 0;
}

template DynamicVectorClass<BfmeHandleCX>::DynamicVectorClass(unsigned int, BfmeHandleCX const *);
