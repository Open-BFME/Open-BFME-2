// cl: /DNDEBUG /MD /EHsc
// ??0MaterialCollectorClass@@QAE@XZ @ 0x00170240 (163B). Ported from Open-BFME-1
// Code/Libraries/Source/WWVegas/WW3D2/MaterialCollectorClass_ctor_Thunk.cpp
// with BFME2 retail immediates (mismatch dump): shader-vector vtable
// 0x00BD46A0, material-vector vtable 0x00BD4658, texture-vector vtable
// 0x00BD4688; ShaderValue constant 0x0010441B is identical in both.
// The shader-vector base is the already-matched
// ??0?$VectorClass@VShaderClass@@@@QAE@HPBVShaderClass@@@Z at 0x0016FB40
// (matinfo.cpp), called here through a real VectorClass<ShaderClass> base so
// no pin is needed. The texture-vector base
// (??0TextureVectorBaseCtorShim@@QAE@HPBV?$RefCountPtr@VTextureClass@@@@@Z)
// lives at 0x0016ED80 (ghidra FUN_0056ed80, 191B, same size as BFME1's 191B
// construct); declared only here and pinned, defined in its own TU next.
#include <new>

extern "C" const void *__identifier("??_7?$DynamicVectorClass@VBfmeHandleCX@@@@6B@")[];

class ShaderClass;

template <class T>
class VectorClass
{
public:
	VectorClass(int size, const T *array);
	virtual ~VectorClass();
	virtual bool operator==(const VectorClass &) const;
	virtual bool Resize(int, const T *);
	virtual void Clear();
	virtual int ID(const T *);
	virtual int ID(const T &);

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

// The destructor and Clear are inline in WW vector.h. This unit emits
// VectorClass<VertexMaterialClass *>'s vtable (the inline constructor below
// installs it), so its ??_G inlines both, as retail's 0x0016FF30 (rowed in
// matinfo.cpp) does.
template <class T>
VectorClass<T>::~VectorClass()
{
	VectorClass<T>::Clear();
}

template <class T>
void VectorClass<T>::Clear()
{
	if (Vector && IsAllocated)
	{
		delete[] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

class TextureClass
{
public:
	void Release_Ref();
};

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
	virtual ~TextureVectorBaseCtorShim();
};

template <class T> class DynamicVectorClass;

// Native shader member at +0 is DynamicVectorClass<ShaderClass> (vtable
// BD46A0). Its unwind calls the existing virtual destructor at 16F960.
// The native six-slot vector interface also supplies its vtable entries.
template <>
class DynamicVectorClass<ShaderClass>
	: public VectorClass<ShaderClass>
{
public:
	__forceinline DynamicVectorClass()
		: VectorClass<ShaderClass>(0, 0)
	{
		*(unsigned int *)((unsigned char *)this + 0x14) = 10;
		*(unsigned int *)((unsigned char *)this + 0x10) = 0;
	}
	virtual ~DynamicVectorClass();
	virtual bool Resize(int, const ShaderClass *);
	virtual void Clear();
	virtual int ID(const ShaderClass *);
	virtual int ID(const ShaderClass &);

private:
	unsigned char m_data[8];
};
typedef char ShaderVectorSize[sizeof(DynamicVectorClass<ShaderClass>) == 0x18 ? 1 : -1];

// Native vertex-material member at +0x18 is DynamicVectorClass<
// VertexMaterialClass *> (vtable BD4658): retail expands both its base and its
// own constructor inline. Its unwind calls the virtual destructor at 16F580.
class VertexMaterialClass;

template <>
__forceinline VectorClass<VertexMaterialClass *>::VectorClass(int, VertexMaterialClass *const *)
{
	unsigned char *self = (unsigned char *)this;
	*(unsigned int *)(self + 4) = 0;
	*(unsigned int *)(self + 8) = 0;
	*(unsigned char *)(self + 0x0c) = 1;
	*(unsigned char *)(self + 0x0d) = 0;
}

template <>
class DynamicVectorClass<VertexMaterialClass *>
	: public VectorClass<VertexMaterialClass *>
{
public:
	__forceinline DynamicVectorClass()
		: VectorClass<VertexMaterialClass *>(0, 0)
	{
		*(unsigned int *)((unsigned char *)this + 0x14) = 10;
		*(unsigned int *)((unsigned char *)this + 0x10) = 0;
	}
	virtual ~DynamicVectorClass();
	virtual bool Resize(int, VertexMaterialClass *const *);
	virtual void Clear();
	virtual int ID(VertexMaterialClass *const *);
	virtual int ID(VertexMaterialClass *const &);

private:
	unsigned char m_data[8];
};

class TextureVector
	: public TextureVectorBaseCtorShim
{
public:
	__forceinline TextureVector()
		: TextureVectorBaseCtorShim(0, 0)
	{
		*(unsigned int *)((unsigned char *)this + 0x10) = 0;
		*(unsigned int *)this = ((unsigned int)__identifier("??_7?$DynamicVectorClass@VBfmeHandleCX@@@@6B@"));
		*(unsigned int *)((unsigned char *)this + 0x14) = 10;
	}
	~TextureVector();

private:
	unsigned char m_data[8];
	// Retail proves TextureVector is 0x18 bytes (next member LastShader sits
	// at +0x48 = 3*0x18): base 0x10 + m_data 8 fills it. If the compiler
	// sizes the base smaller here, this pad restores the retail offsets.
	unsigned char m_pad[0x0C];
};

class ShaderValue
{
public:
	__forceinline ShaderValue()
	{
		*(volatile unsigned int *)&m_value = 0x0010441b;
	}

	__forceinline ShaderValue &operator=(unsigned int value)
	{
		m_value = value;
		return *this;
	}

private:
	unsigned int m_value;
};

class MaterialCollectorClass
{
public:
	MaterialCollectorClass();

private:
	DynamicVectorClass<ShaderClass> m_shaders;
	DynamicVectorClass<VertexMaterialClass *> m_materials;
	TextureVector m_textures;
	ShaderValue LastShader;
	void *LastMaterial;
	void *LastTexture;
};

// ??0MaterialCollectorClass@@QAE@XZ
MaterialCollectorClass::MaterialCollectorClass()
{
	LastTexture = 0;
	LastMaterial = 0;
	LastShader = 0xffffffff;
}
