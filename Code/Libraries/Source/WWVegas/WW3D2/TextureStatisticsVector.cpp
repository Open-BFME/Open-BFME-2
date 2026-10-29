// cl: /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep

// The retail BFME statistics implementation uses DynamicVectorClass here,
// while the later Zero Hour source uses SimpleDynVecClass.  Keep the template
// declarations local so the original out-of-line VectorClass constructor call
// is preserved by the compiler.

#include <new.h>

#include <new>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass : public TextureBaseClass
{
};

inline void TextureBaseClass::Add_Ref()
{
	++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
}

template<class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ref_ptr.h
class RefCountPtr
{
public:
	__declspec(dllimport) __forceinline RefCountPtr() : Referent(0) {}
	RefCountPtr(RefCountPtr const &other) : Referent(other.Referent)
	{
		if (Referent != 0)
			Referent->Add_Ref();
	}
	// BFME's destructor does NOT null the pointer: ~TextureStatisticsStruct at
	// 0x00118800 is twelve bytes -- `mov ecx,[ecx] / test ecx,ecx / jz / jmp
	// Release_Ref` -- a tail jump with no store after it.  Nulling costs the
	// tail call and ten bytes.
	~RefCountPtr()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
		}
	}
	// Inlined at every use here (retail's /G7 family); the out-of-line copy,
	// built without /G7, is RefCountPtrTextureAssign.cpp's row (0x000424D0).
	__declspec(dllimport) __forceinline RefCountPtr const &operator=(RefCountPtr const &other)
	{
		if (other.Referent != 0)
			other.Referent->Add_Ref();
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = other.Referent;
		return *this;
	}
	void Clear()
	{
		if (Referent != 0)
		{
			Referent->Release_Ref();
			Referent = 0;
		}
	}
	bool operator==(RefCountPtr const &other) const { return Referent == other.Referent; }
	bool operator!=(RefCountPtr const &other) const { return Referent != other.Referent; }

private:
	T *Referent;
};

struct TextureStatisticsStruct
{
	RefCountPtr<TextureClass> tex;
	int usage_count;
	int change_count;

	bool operator==(TextureStatisticsStruct const &other) const
	{
		return tex == other.tex;
	}
	bool operator!=(TextureStatisticsStruct const &other) const
	{
		return tex != other.tex;
	}
};

template<class T>
class VectorClass
{
public:
	VectorClass(unsigned size, T const *array);
	VectorClass(VectorClass const &);
	virtual ~VectorClass();
	VectorClass &operator=(VectorClass const &);
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
	int Length() const { return VectorMax; }
	T &operator[](int index) { return Vector[index]; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(unsigned size = 0, T const *array = 0);
	virtual ~DynamicVectorClass();
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
	bool Add(T const &object);

protected:
	int ActiveCount;
	int GrowthStep;
};

template<class T>
VectorClass<T>::VectorClass(unsigned size, T const *array)
	: Vector(0), VectorMax(size), IsValid(true), IsAllocated(false)
{
	if (size)
	{
		if (array)
		{
			Vector = new ((void *)array) T[size];
		}
		else
		{
			Vector = new T[size];
			IsAllocated = true;
		}
	}
}

// VectorClass<T>::Resize is defined in TextureStatisticsVectorResize.cpp,
// which builds retail's /G7 body (0x00129990); this unit only calls it, so
// it emits no second (non-/G7) copy for the link to choose.

template<class T>
VectorClass<T>::~VectorClass()
{
	VectorClass<T>::Clear();
}

// DynamicVectorClass adds nothing to destroy: its destructor is the inlined
// ~VectorClass, which /OPT:ICF folded onto 0x0012A4D0 (the DynamicVectorClass
// vftable 0x00BD14EC's ??_G at 0x0012A620 calls it there).
template<class T>
DynamicVectorClass<T>::~DynamicVectorClass()
{
}

template<class T>
void VectorClass<T>::Clear()
{
	if (Vector != 0 && IsAllocated)
	{
		delete [] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

template<class T>
void DynamicVectorClass<T>::Clear()
{
	ActiveCount = 0;
	VectorClass<T>::Clear();
}

template<class T>
bool DynamicVectorClass<T>::Resize(int newsize, T const *array)
{
	if (VectorClass<T>::Resize(newsize, array))
	{
		if (this->Length() < ActiveCount)
			ActiveCount = this->Length();
		return true;
	}
	return false;
}

template<class T>
bool DynamicVectorClass<T>::Add(T const &object)
{
	if (ActiveCount >= this->Length())
	{
		if ((this->IsAllocated || !this->VectorMax) && GrowthStep > 0)
		{
			if (!Resize(this->Length() + GrowthStep))
				return false;
		}
		else
		{
			return false;
		}
	}
	(*this)[ActiveCount++] = object;
	return true;
}

template<class T>
DynamicVectorClass<T>::DynamicVectorClass(unsigned size, T const *array)
	: VectorClass<T>(size, array)
{
	GrowthStep = 10;
	ActiveCount = 0;
}

template DynamicVectorClass<TextureStatisticsStruct>::DynamicVectorClass(
	unsigned, TextureStatisticsStruct const *);
template VectorClass<TextureStatisticsStruct>::VectorClass(
	unsigned, TextureStatisticsStruct const *);
template bool VectorClass<TextureStatisticsStruct>::Resize(
	int, TextureStatisticsStruct const *);
template void DynamicVectorClass<TextureStatisticsStruct>::Clear();
template bool DynamicVectorClass<TextureStatisticsStruct>::Add(
	TextureStatisticsStruct const &);
template VectorClass<TextureStatisticsStruct>::~VectorClass();

extern "C" { int texture_memory; }
extern "C" int texture_count;
extern "C" { int lightmap_texture_memory; }
extern "C" { int lightmap_texture_count; }
extern "C" { int procedural_texture_memory; }
extern "C" { int procedural_texture_count; }
extern "C" { int record_count; }
extern "C" { int texture_change_count; }
// Defined in DebugStatisticsRecordTexture.cpp (retail statistics.cpp's one pair).
extern RefCountPtr<TextureClass> latest_texture;
extern DynamicVectorClass<TextureStatisticsStruct> texture_statistics;

void Record_Texture_Begin()
{
	texture_memory = 0;
	texture_count = 0;
	lightmap_texture_memory = 0;
	lightmap_texture_count = 0;
	procedural_texture_memory = 0;
	procedural_texture_count = 0;
	record_count = 0;
	texture_change_count = 0;
	latest_texture.Clear();
	texture_statistics.Resize(0);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??4CursorTextureSlot@@QAEXABVBFME2ParticleTextureHandle@@@Z=??4?$RefCountPtr@VTextureClass@@@@QAEABV0@ABV0@@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??4BfmeMapPictureTexture@@QAEAAV0@ABV0@@Z=??4?$RefCountPtr@VTextureClass@@@@QAEABV0@ABV0@@Z")
#pragma comment(linker, "/alternatename:??4?$RefCountPtr@VHierarchyPrototype@@@@QAEABV0@ABV0@@Z=??4?$RefCountPtr@VTextureClass@@@@QAEABV0@ABV0@@Z")
