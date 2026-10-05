// ??0Render2DSentenceClass@@QAE@XZ
// partial score=0.95 date=2026-10-05
// cl: /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2
// ??0Render2DSentenceClass@@QAE@XZ 0x00157E80 368B Render2DSentence ctor via rowed vectors + BfmeThing + 1.0 floats
// Evidence: vtable 0x007D3C80 (Render2DSentence Reset only slot, dtor 0x00157C70 restores it); callers W3DDisplay 0x00104EBF (+0x04) and W3DDisplayString 0x00106088 (+0x14/+0xD8, size 0xC4); callees rowed VectorWide 0x00154CD0 + VectorPending 0x00157280 + VectorAddInfo 0x00154DA0 + BfmeThingDC 0x00116600; floats 1.0 via g_Va00BBB8D8; donor render2dsentence.h (BFME1) + Rva00156540 local layout.

extern float g_Va00BBB8D8;

struct BfmeItemDC
{
	void *m_bfmeOps;
};

class BfmeThingDC
{
public:
	BfmeThingDC(BfmeItemDC *item);
private:
	BfmeItemDC *m_bfmeItem;
};

struct TextureStatisticsStructWide
{
	void *tex;
	float f00;
	float f04;
	float f08;
	float f0c;
	float f10;
	float f14;
	float f18;
	float f1c;
};

template<class T>
class VectorClassWide
{
public:
	VectorClassWide(unsigned size, T const *array);
	virtual ~VectorClassWide();
	virtual bool operator==(VectorClassWide const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	char Pad[2];
};

template<class T>
class DynamicVectorClassWide : public VectorClassWide<T>
{
public:
	DynamicVectorClassWide(unsigned size = 0, T const *array = 0) : VectorClassWide<T>(size, array)
	{
		GrowthStep = 10;
		ActiveCount = 0;
	}
protected:
	int ActiveCount;
	int GrowthStep;
};

class MixFileFactoryClass
{
public:
	struct AddInfoStruct
	{
		void *a;
		void *b;
	};
};

template<class T>
class VectorClass
{
public:
	VectorClass(int size, T const *array);
	virtual ~VectorClass();
	virtual bool operator==(VectorClass const &) const;
	virtual bool Resize(int size, T const *array = 0);
	virtual void Clear();
	virtual int ID(T const *ptr);
	virtual int ID(T const &object);
protected:
	T *Vector;
	int VectorMax;
	bool IsValid;
	bool IsAllocated;
	char Pad[2];
};

template<class T>
class DynamicVectorClass : public VectorClass<T>
{
public:
	DynamicVectorClass(unsigned size = 0, T const *array = 0) : VectorClass<T>((int)size, array)
	{
		GrowthStep = 10;
		ActiveCount = 0;
	}
protected:
	int ActiveCount;
	int GrowthStep;
};

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

class Vector2i
{
public:
	Vector2i(int x, int y) : X(x), Y(y) {}
	int X;
	int Y;
};

class Render2DSentenceClass
{
public:
	Render2DSentenceClass();
	virtual void Reset();
	struct PendingSurfaceStruct
	{
		void *pad[7];
	};
private:
	DynamicVectorClassWide<TextureStatisticsStructWide> m_sentenceData;
	DynamicVectorClass<PendingSurfaceStruct> m_pendingSurfaces;
	DynamicVectorClass<MixFileFactoryClass::AddInfoStruct> m_renderers;
	void *m_font;
	Vector2 m_baseLocation;
	Vector2 m_location;
	Vector2 m_cursor;
	Vector2i m_textureOffset;
	int m_textureStartX;
	int m_currTextureSize;
	int m_textureSizeHint;
	BfmeThingDC m_curSurfaceWork;
	bool m_monoSpaced;
	float m_wrapWidth;
	bool m_centered;
	float m_clipLeft;
	float m_clipTop;
	float m_clipRight;
	float m_clipBottom;
	float m_drawLeft;
	float m_drawTop;
	float m_drawRight;
	float m_drawBottom;
	bool m_isClippedEnabled;
	bool m_parseHotKey;
	bool m_useHardWordWrap;
	void *m_lockedPtr;
	float m_fB4;
	float m_fB8;
	float m_fBC;
	float m_fC0;
};

// ??0Render2DSentenceClass@@QAE@XZ present-unmatched
Render2DSentenceClass::Render2DSentenceClass()
	: m_sentenceData(0, 0),
	  m_pendingSurfaces(0, 0),
	  m_renderers(0, 0),
	  m_font(0),
	  m_baseLocation(0.0f, 0.0f),
	  m_location(0.0f, 0.0f),
	  m_cursor(0.0f, 0.0f),
	  m_textureOffset(0, 0),
	  m_textureStartX(0),
	  m_currTextureSize(0),
	  m_textureSizeHint(0),
	  m_curSurfaceWork((BfmeItemDC *)0),
	  m_monoSpaced(false),
	  m_wrapWidth(0.0f),
	  m_centered(false),
	  m_clipLeft(0.0f),
	  m_clipTop(0.0f),
	  m_clipRight(0.0f),
	  m_clipBottom(0.0f),
	  m_drawLeft(0.0f),
	  m_drawTop(0.0f),
	  m_drawRight(0.0f),
	  m_drawBottom(0.0f),
	  m_isClippedEnabled(false),
	  m_parseHotKey(false),
	  m_useHardWordWrap(false),
	  m_lockedPtr(0),
	  m_fB4(g_Va00BBB8D8),
	  m_fB8(g_Va00BBB8D8),
	  m_fBC(0.0f),
	  m_fC0(0.0f)
{
}
