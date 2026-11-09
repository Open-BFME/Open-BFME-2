// cl: /DNDEBUG /MD /EHsc /G7 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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

#include <new>

void BFME_DX8_Thread_Lock();
// The unlock half is rowed at 0x00120F50 as BFME_DX8_Thread_Assert (dx8wrapper.cpp).
bool BFME_DX8_Thread_Assert();
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

// REF_PTR_RELEASE, copied from WWLib/refcount.h (NULL spelled 0: identical
// codegen, keeps this TU include-free).
#define REF_PTR_RELEASE(x) { if (x) { x->Release_Ref(); x = 0; } }

// Minimal RefCountClass: vtable slot 0 is Delete_This, NumRefs sits at +0x04.
// Release_Ref inlines to dec/test/Delete_This; the virtual Delete_This call
// itself is never inlined, which is exactly the retail shape. Neither virtual
// is defined here and none is ever ODR-used, so this TU emits no symbols.
#include "../WWLib/RefCountData.h"

#include "FontCharsClass.h"

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

// TEST ONLY P104 (never lands): retail destroys these 8-byte renderer
// elements through 0x00001E13, which releases +4 through its table's slot 2.
// Spelled as EnumParameterClass::_ENUM_VALUE, the reference bound WWSaveLoad's
// real ~_ENUM_VALUE, a StringClass free on +0. This test element does what
// 0x00001E13 does, under a name no other unit uses.
class P104TestSurface
{
public:
	virtual void unused00();
	virtual unsigned long __stdcall addRef();
	virtual unsigned long __stdcall release();
};

struct P104TestRendererElement
{
	~P104TestRendererElement()
	{
		if (m_surface)
			m_surface->release();
	}

	void *m_renderer;
	P104TestSurface *m_surface;
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
	DynamicVectorClass<P104TestRendererElement> m_renderers;
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

// These virtual members use the existing container providers.
template <> bool VectorClassWide<TextureStatisticsStructWide>::Resize(int, const TextureStatisticsStructWide *);
template <> int VectorClassWide<TextureStatisticsStructWide>::ID(const TextureStatisticsStructWide &);
template <> bool VectorClass<Render2DSentenceClass::PendingSurfaceStruct>::operator==(const VectorClass &) const;
template <> bool VectorClass<Render2DSentenceClass::PendingSurfaceStruct>::Resize(int, const Render2DSentenceClass::PendingSurfaceStruct *);
template <> int VectorClass<Render2DSentenceClass::PendingSurfaceStruct>::ID(const Render2DSentenceClass::PendingSurfaceStruct &);
template <> int VectorClass<Render2DSentenceClass::PendingSurfaceStruct>::ID(const Render2DSentenceClass::PendingSurfaceStruct *);

// ??1Render2DSentenceClass@@QAE@XZ
Render2DSentenceClass::~Render2DSentenceClass()
{
	REF_PTR_RELEASE(m_font);
	BFMEDX8DeviceLock lock;
	Render2DSentenceClass::Reset();
	m_renderers.Clear();
}
