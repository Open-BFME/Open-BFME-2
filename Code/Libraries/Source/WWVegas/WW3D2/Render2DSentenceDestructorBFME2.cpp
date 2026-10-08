// cl: /DNDEBUG /MD /EHsc /G7
// BFME1 9cbfb551fe20 Render2DSentenceClass_dtor.cpp semantic donor.
// Native157C70..157DCB/347B writes the established sentence vtable (Reset
// in slot0), releases Font+4C, locks the DX8 device around Reset and renderer
// Clear, then destroys texture+B0, surface+7C and vectors+34/+1C/+4.
// The target destructor is nonvirtual: slot0 is Reset, also supported by the
// existing QAE pin and the native W3DDisplayString member cleanup callers.
// Target has no donor locked-pointer/stride fields; texture holder is B0.
// Vector element spelling below is inherited from the existing BFME1 ABI
// views, not independent identification of the target's renderer records.
// Concrete member offsets, sizes (8/1C/24) and teardown are target evidence.

void operator delete[](void *block);

void W3DRadarResetLock();
char bfmeUnlock1179();
class BfmeSentenceDeviceLock { public: BfmeSentenceDeviceLock(){W3DRadarResetLock();} ~BfmeSentenceDeviceLock(){bfmeUnlock1179();} };

// REF_PTR_RELEASE, copied from WWLib/refcount.h (NULL spelled 0: identical
// codegen, keeps this TU include-free).
#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

// Minimal RefCountClass: vtable slot 0 is Delete_This, NumRefs sits at +0x04.
// Release_Ref inlines to dec/test/Delete_This; the virtual Delete_This call
// itself is never inlined, which is exactly the retail shape. Neither virtual
// is defined here and none is ever ODR-used, so this TU emits no symbols.
class RefCountClass
{
public:
	void Release_Ref() { m_refs--; if (m_refs == 0) { Delete_This(); } }
	virtual void Delete_This();

protected:
	virtual ~RefCountClass();

private:
	int m_refs;
};

class FontCharsClass : public RefCountClass
{
public:
	virtual ~FontCharsClass();
};

class W3DRadarResetSurface
{
public:
	~W3DRadarResetSurface();				// retail 0x008FC5B0

private:
	void *m_surface;
};

class TextureClass
{
public:
	void Release_Ref();						// retail 0x009EB7A0 (non-virtual)
};

// +0xB0 texture holder. Retail destroys it inline (new EH state, no null
// store after the Release_Ref call), so the destructor must be visible here.
// Only its shape is proven: a 4-byte holder releasing a TextureClass.
class TextureRefHolder009409F0
{
public:
	~TextureRefHolder009409F0()
	{
		if (m_texture != 0)
		{
			m_texture->Release_Ref();
		}
	}

private:
	TextureClass *m_texture;
};

// Sentence-data element. The 0x0113CE0C vector vtable names the instantiation
// VectorClassWide<TextureStatisticsStructWide>; retail destroys the elements
// through ILT 0x00018FCF, whose body (0x0005DBF0) is a bare tail jump to the
// W3DRadarResetSurface destructor, so the surface wrapper sits at +0x00 and
// the remaining 0x20 bytes hold no further reference-counted members.
struct TextureStatisticsStructWide
{
	~TextureStatisticsStructWide();			// retail ILT 0x00018FCF

	W3DRadarResetSurface m_surface;
	char m_pad[0x20];
};

class EnumParameterClass
{
public:
	// Renderer element. The 0x0113CE24 vector vtable names
	// VectorClass<ENUM_VALUE>, and retail destroys the 8-byte elements
	// through ILT 0x000470F5 (the pinned ??1_ENUM_VALUE dtor).
	struct ENUM_VALUE
	{
		~ENUM_VALUE();						// retail ILT 0x000470F5

		void *m_name;
		int m_value;
	};
};

template<class T>
class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass();
	virtual bool operator==(VectorClass const &other) const
		{ return VectorMax == other.VectorMax; }
	virtual bool Resize(int size, T const *array = 0) { return false; }
	virtual void Clear();
	virtual int ID(T const *ptr) { return 0; }
	virtual int ID(T const &object) { return 0; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
VectorClass<T>::~VectorClass()
{
	VectorClass<T>::Clear();
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
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(int size = 0, T const *array = 0);

	virtual bool Resize(int size, T const *array = 0) { return false; }
	virtual void Clear() { ActiveCount = 0; VectorClass<T>::Clear(); }
	virtual int ID(T const *ptr) { return 0; }
	virtual int ID(T const &object) { return 0; }

protected:
	int ActiveCount;
	int GrowthStep;
};

template<class T>
class VectorClassWide
{
public:
	VectorClassWide(unsigned size, T const *array);
	virtual ~VectorClassWide();
	virtual bool operator==(VectorClassWide const &other) const
		{ return VectorMax == other.VectorMax; }
	virtual bool Resize(int size, T const *array = 0) { return false; }
	virtual void Clear();
	virtual int ID(T const *ptr) { return 0; }
	virtual int ID(T const &object) { return 0; }

protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	bool VectorClassPad[2];
};

template<class T>
VectorClassWide<T>::~VectorClassWide()
{
	VectorClassWide<T>::Clear();
}

template<class T>
void VectorClassWide<T>::Clear()
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
class DynamicVectorClassWide : public VectorClassWide<T>
{
public:
	DynamicVectorClassWide(unsigned size = 0, T const *array = 0);

	virtual bool Resize(int size, T const *array = 0) { return false; }
	virtual void Clear() { ActiveCount = 0; VectorClassWide<T>::Clear(); }
	virtual int ID(T const *ptr) { return 0; }
	virtual int ID(T const &object) { return 0; }

protected:
	int ActiveCount;
	int GrowthStep;
};

class Render2DSentenceClass
{
public:
	struct PendingSurfaceStruct : public W3DRadarResetSurface
	{
		~PendingSurfaceStruct();				// retail 0x0045F5E0

		DynamicVectorClass<int> m_renderers;	// +0x04 (size filler: 0x18)
	};

	Render2DSentenceClass();
	~Render2DSentenceClass();
	virtual void Reset();						// retail 0x0093EA60

	DynamicVectorClassWide<TextureStatisticsStructWide> m_sentenceData;
	DynamicVectorClass<PendingSurfaceStruct> m_pendingSurfaces;
	DynamicVectorClass<EnumParameterClass::ENUM_VALUE> m_renderers;
	FontCharsClass *m_font;						// +0x4C
	float m_baseLocation[2];					// +0x50
	float m_location[2];						// +0x58
	float m_cursor[2];							// +0x60
	int m_textureOffset[2];						// +0x68
	int m_textureStartX;						// +0x70
	int m_currTextureSize;						// +0x74
	int m_textureSizeHint;						// +0x78
	W3DRadarResetSurface m_curSurface;			// +0x7C
	bool m_monoSpaced;							// +0x80
	char m_pad80[3];
	float m_wrapWidth;							// +0x84
	bool m_centered;							// +0x88
	char m_pad88[3];
	int m_clipRect[4];							// +0x8C
	int m_drawExtents[4];						// +0x9C
	bool m_clippingEnabled;						// +0xAC
	bool m_parseHotKey;							// +0xAD
	bool m_hardWordWrap;						// +0xAE
	char m_padAC;
	TextureRefHolder009409F0 m_curTexture;		// +0xB0
	int m_shader;								// +0xB4 (POD tail)
};

// ??1Render2DSentenceClass@@QAE@XZ
Render2DSentenceClass::~Render2DSentenceClass()
{
	REF_PTR_RELEASE(m_font);
	BfmeSentenceDeviceLock lock;
	Render2DSentenceClass::Reset();
	m_renderers.Clear();
}
