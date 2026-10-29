// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// stlport46
// platformsdk
// Small bodies from .text gaps no Ghidra function covers (thirty-first
// batch; see GapBodiesGE01.cpp). Each begins after its neighbour's padding or
// ret and ends in its own ret. Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings, private statics reached through a friend view.

#include <math.h>
#include <windows.h>

// --- 0x00072882 (16B): RefCountClass's inline constructor (vtable 0x00BC650C,
// one reference); 0x000728B6 (16B): a class deriving from it (vtable
// 0x00BC6514), the base's vtable store folded away.
// Match donor refcount.h and the existing consumer declarations: Delete_This
// is slot zero, followed by the protected destructor. Keep the constructor
// inline so byte-identical consumer copies remain interchangeable COMDATs;
// leave Delete_This to its existing providers rather than emitting a helper.
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
private:
	int NumRefs;
};

class Rva000728B6 : public RefCountClass
{
public:
	Rva000728B6();
	virtual ~Rva000728B6() {}
};

Rva000728B6::Rva000728B6()
{
}

// --- 0x000752D5 (12B): CPUDetectClass::TotalPhysicalMemory.
class Rva000752D5;

class CPUDetectClass
{
	friend class Rva000752D5;
	static unsigned __int64 TotalPhysicalMemory;
};

class Rva000752D5
{
public:
	static unsigned __int64 rva000752D5();
};

unsigned __int64 Rva000752D5::rva000752D5()
{
	return CPUDetectClass::TotalPhysicalMemory;
}

// --- 0x000752E1 / 0x000852B3 (17B each): float exp / acos through the
// msvcr71 thunks.

float rva000752E1(float x)
{
	return (float)exp(x);
}

float rva000852B3(float x)
{
	return (float)acos(x);
}

// --- 0x00078930 (17B): address of the i-th 0x1C-byte record at +0x110.
struct GapRecord1C
{
	char m_bytes[0x1C];
};

class Rva00078930
{
public:
	GapRecord1C *rva00078930(int i);
private:
	char m_pad00[0x110];
	GapRecord1C m_records[1];								// +0x110
};

GapRecord1C *Rva00078930::rva00078930(int i)
{
	return &m_records[i];
}

// --- 0x0007B275 (10B): WW3D::IsCurrentlyRenderingShadowMap store.
class Rva0007B275;

class WW3D
{
	friend class Rva0007B275;
	static bool IsCurrentlyRenderingShadowMap;
};

class Rva0007B275
{
public:
	static void rva0007B275(bool on);
};

void Rva0007B275::rva0007B275(bool on)
{
	WW3D::IsCurrentlyRenderingShadowMap = on;
}

// --- 0x0007B27F (30B): 1024, 1000.0f, 0.0f.
class Rva0007B27F
{
public:
	Rva0007B27F();
private:
	int m_count;
	float m_range;
	float m_zero;
};

Rva0007B27F::Rva0007B27F() : m_count(0x400), m_range(1000.0f), m_zero(0.0f)
{
}

// --- 0x0007B342 / 0x0007B367 (37B each): componentwise min / max with
// another float pair.
class Rva0007B342
{
public:
	void rva0007B342(const Rva0007B342 &o);
	void rva0007B367(const Rva0007B342 &o);
private:
	float x;
	float y;
};

void Rva0007B342::rva0007B342(const Rva0007B342 &o)
{
	if (x > o.x)
		x = o.x;
	if (y > o.y)
		y = o.y;
}

void Rva0007B342::rva0007B367(const Rva0007B342 &o)
{
	if (o.x > x)
		x = o.x;
	if (o.y > y)
		y = o.y;
}

// --- 0x0007DE26 (67B): four floats scaled, returned by value.
class Rva0007DE26
{
public:
	Rva0007DE26() {}
	Rva0007DE26(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
	Rva0007DE26 rva0007DE26(float s) const;
private:
	float x;
	float y;
	float z;
	float w;
};

Rva0007DE26 Rva0007DE26::rva0007DE26(float s) const
{
	return Rva0007DE26(x * s, y * s, z * s, w * s);
}

// --- 0x0007DF14 (40B): sign of a float as 1, -1 or 0.
float rva0007DF14(float x)
{
	if (x > 0.0f)
		return 1.0f;
	if (x < 0.0f)
		return -1.0f;
	return 0.0f;
}

// --- 0x0007E9DF (13B): a (container, index 0) cursor; 0x0007E9EC (22B):
// its post-increment.
class Rva0007E9DF;

struct GapCursor
{
	GapCursor(const Rva0007E9DF *owner, int index) : m_owner(owner), m_index(index) {}
	GapCursor rva0007E9EC(int);
	const Rva0007E9DF *m_owner;
	int m_index;
};

class Rva0007E9DF
{
public:
	GapCursor rva0007E9DF() const;
};

GapCursor Rva0007E9DF::rva0007E9DF() const
{
	return GapCursor(this, 0);
}

GapCursor GapCursor::rva0007E9EC(int)
{
	GapCursor old = *this;
	++m_index;
	return old;
}

// --- 0x0007EB3C (21B): _STL::operator!= over the rowed operator== 0x0007E394.
struct Rva0007E394Element;

namespace _STL
{
	template <class T1, class T2> struct pair
	{
		T1 first;
		T2 second;
	};
	template <class T1, class T2> bool operator==(const pair<T1, T2> &a, const pair<T1, T2> &b);
	template <class T1, class T2> inline bool operator!=(const pair<T1, T2> &a, const pair<T1, T2> &b)
	{
		return !(a == b);
	}
}

template bool _STL::operator!=(const _STL::pair<const unsigned int, Rva0007E394Element *> &, const _STL::pair<const unsigned int, Rva0007E394Element *> &);

// --- 0x000824E3 / 0x000824EE (11B each), 0x00058AD3 (11B): owners clearing a
// leading vector through its rowed erase (0x000819EC / 0x00239EA5); retail
// keeps separate copies, so each owner is its own view.
struct TreeHintRef00217D4C;
struct OpaqueRefElement4;

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> > class vector
	{
	public:
		T *erase(T *first, T *last);
		void clear() { erase(m_start, m_finish); }
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class Rva000824E3
{
public:
	void rva000824E3();
	void rva000824EE();
private:
	_STL::vector<TreeHintRef00217D4C> m_hints;
};

void Rva000824E3::rva000824E3()
{
	m_hints.clear();
}

void Rva000824E3::rva000824EE()
{
	m_hints.clear();
}

class Rva00058AD3
{
public:
	void rva00058AD3();
private:
	_STL::vector<OpaqueRefElement4> m_refs;
};

void Rva00058AD3::rva00058AD3()
{
	m_refs.clear();
}

// --- 0x00085265 (17B): float at +0xB0; 0x00085276 (15B): store a word to
// VA 0x00DFF490 unless it is -1.
class Rva00085265
{
public:
	void rva00085265(float value);
private:
	char m_pad00[0xB0];
	float m_B0;
};

void Rva00085265::rva00085265(float value)
{
	m_B0 = value;
}

extern int g_screenFilterPass;	// VA 0x00DFF490 (ByteFillNO1.cpp)

void rva00085276(int value)
{
	if (value != -1)
		g_screenFilterPass = value;
}

// --- 0x0008552B (16B): copy three words in.
struct GapWords3
{
	int a;
	int b;
	int c;
};

class Rva0008552B
{
public:
	void rva0008552B(const GapWords3 &value);
private:
	GapWords3 m_value;
};

void Rva0008552B::rva0008552B(const GapWords3 &value)
{
	m_value = value;
}

// --- 0x0008557F / 0x00085599 (26B each): fade parameter setters (restart
// the fade, store frames and direction) of ScreenBWFilter's public statics
// and of ScreenCrossFadeFilter's (0x00DEBFF8..0x00DEC000).
class ScreenBWFilter
{
public:
	static int m_curFadeFrame;
	static int m_fadeFrames;
	static int m_fadeDirection;
};

// Zero Hour ScreenCrossFadeFilter statics (VA 0x00DEBFF8..0x00DEC000), defined in
// ScreenCrossFadeFilterUpdateFadeLevel.cpp.
class ScreenCrossFadeFilter
{
public:
	static int m_curFadeFrame;
	static int m_fadeFrames;
	static int m_fadeDirection;
};

void rva0008557F(int frames, int direction)
{
	ScreenBWFilter::m_curFadeFrame = 0;
	ScreenBWFilter::m_fadeFrames = frames;
	ScreenBWFilter::m_fadeDirection = direction;
}

void rva00085599(int frames, int direction)
{
	ScreenCrossFadeFilter::m_curFadeFrame = 0;
	ScreenCrossFadeFilter::m_fadeFrames = frames;
	ScreenCrossFadeFilter::m_fadeDirection = direction;
}

// --- 0x000855BA (23B): the larger of two floats.
float rva000855BA(float a, float b)
{
	if (a > b)
		return a;
	return b;
}

// --- 0x00094AA0 / 0x00094AB3 (19B each): the +0x30 / +0x3C float triples
// returned by value.
struct GapTriple3
{
	float x;
	float y;
	float z;
};

class Rva00094AA0
{
public:
	GapTriple3 rva00094AA0() const;
	GapTriple3 rva00094AB3() const;
private:
	char m_pad00[0x30];
	GapTriple3 m_30;
	GapTriple3 m_3C;
};

GapTriple3 Rva00094AA0::rva00094AA0() const
{
	return m_30;
}

GapTriple3 Rva00094AA0::rva00094AB3() const
{
	return m_3C;
}

// --- 0x0008564A (45B): fill a record from another of a different layout,
// returning this: the string at +0x0C from the source's +8 through the
// rowed narrow StringBase<char>::set (0x000366F0), then the three words at
// +0 from the source's +0x0C and the word at +0x10 from its +4.
template <class T> class StringBase
{
public:
	void set(const StringBase &other);
private:
	T *m_data;
};

struct GapWords3B
{
	int w[3];
};

struct Rva0008564ASource
{
	int m_00;
	int m_04;
	StringBase<char> m_08;
	GapWords3B m_0C;
};

class Rva0008564A
{
public:
	Rva0008564A &rva0008564A(const Rva0008564ASource &source);
private:
	GapWords3B m_00;
	StringBase<char> m_0C;
	int m_10;
};

Rva0008564A &Rva0008564A::rva0008564A(const Rva0008564ASource &source)
{
	m_0C.set(source.m_08);
	m_00 = source.m_0C;
	m_10 = source.m_04;
	return *this;
}

// ---------------------------------------------------------------------------
// Unreferenced leaves whose skeletons match rowed twins (twins.tsv leads);
// each is verified on its own bytes. Owners are address-derived views.

class AsciiString;
class RenderObjClass;

// 0x0005CE73 (11B): forward a key to the rowed Rva00056CF8::rva0005B633
// (0x0005B633) of the member at +0x1B8, a tail jump.
class Rva00056CF8
{
public:
	unsigned int rva0005B633(const AsciiString &key);
};

class Rva0005CE73
{
public:
	unsigned int rva0005CE73(const AsciiString &key);
private:
	char m_pad[0x1B8];
	Rva00056CF8 m_1B8;
};

unsigned int Rva0005CE73::rva0005CE73(const AsciiString &key)
{
	return m_1B8.rva0005B633(key);
}

// 0x0006F23F (11B): remove a render object from the RefMultiListClass at
// +0x114 (rowed Remove 0x0006EF4E), a tail jump.
template <class T> class RefMultiListClass
{
public:
	bool Remove(T *obj);
};

class Rva0006F23F
{
public:
	bool rva0006F23F(RenderObjClass *obj);
private:
	char m_pad[0x114];
	RefMultiListClass<RenderObjClass> m_114;
};

bool Rva0006F23F::rva0006F23F(RenderObjClass *obj)
{
	return m_114.Remove(obj);
}

// 0x0007E0CE / 0x0007E0F8 (11B each): addresses of dword slots in the
// arrays at +0x50 and +0x44; 0x0007E0E2 (8B): the rowed
// RiverArea::getTextureName (0x0030BBA9) of the pointer at +0x40, a tail
// jump.
class RiverArea
{
public:
	void *getTextureName(int index);
};

class Rva0007E0CE
{
public:
	void *rva0007E0CE(int index);
	void *rva0007E0E2(int index);
	void *rva0007E0F8(int index);
private:
	char m_pad[0x40];
	RiverArea *m_40;
	int m_44[3];
	int m_50[4];
};

void *Rva0007E0CE::rva0007E0CE(int index)
{
	return &m_50[index];
}

void *Rva0007E0CE::rva0007E0E2(int index)
{
	return m_40->getTextureName(index);
}

void *Rva0007E0CE::rva0007E0F8(int index)
{
	return &m_44[index];
}

// 0x0004CAA7 (10B) / 0x0007DEBE (10B): static setters of the byte at
// VA 0x00DB5F7D and of bfmeCameraProjectionOverride (VA 0x00DEDA05).
extern unsigned char g_Va00DB5F7D;
extern bool bfmeCameraProjectionOverride;

void rva0004CAA7(unsigned char value)
{
	g_Va00DB5F7D = value;
}

void rva0007DEBE(bool value)
{
	bfmeCameraProjectionOverride = value;
}

// 0x00063343 (10B): set the flag at +9.
class Rva00063343
{
public:
	void rva00063343(bool value);
private:
	char m_pad[9];
	bool m_09;
};

void Rva00063343::rva00063343(bool value)
{
	m_09 = value;
}

// 0x0007FAAA (9B): address of a character at an offset from the buffer
// pointer at +0.
class Rva0007FAAA
{
public:
	const char *rva0007FAAA(unsigned int offset) const;
private:
	const char *m_00;
};

const char *Rva0007FAAA::rva0007FAAA(unsigned int offset) const
{
	return m_00 + offset;
}

// 0x00054F32 (9B): run the rowed Rva0005333FHolder::rva0005333F
// (0x0005333F) on an element in place, a tail jump (_Destroy's shape).
class Rva0005333FHolder
{
public:
	void rva0005333F();
};

void rva00054F32(Rva0005333FHolder *p)
{
	p->rva0005333F();
}

// 0x00051888 (14B), unreferenced: post-increment the counter at +0xD0,
// returning its previous value.
class Rva00051888
{
public:
	int rva00051888();
private:
	char m_pad[0xD0];
	int m_D0;
};

int Rva00051888::rva00051888()
{
	return m_D0++;
}

// 0x00042334 (6B), unreferenced: timeGetTime through its winmm import, a
// tail jump.

unsigned long rva00042334()
{
	return timeGetTime();
}

// 0x0007FB4B (13B), unreferenced: the second word of the 8-byte entry the
// index at +4 selects in the table at +0x14 of the object the pointer at +0
// names.
struct Rva0007FB4BEntry
{
	int m_00;
	int m_04;
};

struct Rva0007FB4BTable
{
	char m_pad[0x14];
	Rva0007FB4BEntry *m_14;
};

class Rva0007FB4B
{
public:
	int rva0007FB4B() const;
private:
	Rva0007FB4BTable *m_00;
	int m_04;
};

int Rva0007FB4B::rva0007FB4B() const
{
	return m_00->m_14[m_04].m_04;
}

// 0x00085299 (9B) / 0x000855B3 (7B), unreferenced: whether the byte at +0x1C
// is clear, and whether the word at +0 is set.
class Rva00085299
{
public:
	bool rva00085299() const;
	bool rva000855B3() const;
private:
	int m_00;
	char m_pad[0x18];
	unsigned char m_1C;
};

bool Rva00085299::rva00085299() const
{
	return m_1C == 0;
}

bool Rva00085299::rva000855B3() const
{
	return m_00 ? true : false;
}

// 0x00078298 (4B), unreferenced: address of the byte at +9.
class Rva00078298
{
public:
	unsigned char *rva00078298();
private:
	char m_pad[9];
	unsigned char m_09;
};

unsigned char *Rva00078298::rva00078298()
{
	return &m_09;
}

// Tail-jump forwarders to a rowed member of the object at +0 (unreferenced):
// 0x0005CC23 -> Rva00056CF8::rva0005B633 (0x0005B633), 0x00085294 ->
// Rva00148F5ECache::get (0x00148F5E), 0x00073421 -> Rva00072FE6::rva000733D8
// (0x000733D8), 0x000730D9 -> Rva00072FE6::rva00072FE6 (0x00072FE6),
// 0x00057AE9 -> Rva00056DA2::rva00056DA2 (0x00056DA2), 0x0005A07F ->
// Rva00058B90::rva00058B90 (0x00058B90).
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	NameKeyType get();
};

class Rva00072FE6
{
public:
	void rva00072FE6();
	unsigned int rva000733D8(const int &key);
};

class Rva00056DA2
{
public:
	void rva00056DA2();
};

class Rva0036CA00Str;

class Rva00058B90
{
public:
	void rva00058B90(const Rva0036CA00Str &value);
};

class Rva0005CC23
{
public:
	unsigned int rva0005CC23(const AsciiString &key);
private:
	Rva00056CF8 m_00;
};

unsigned int Rva0005CC23::rva0005CC23(const AsciiString &key)
{
	return m_00.rva0005B633(key);
}

class Rva00085294
{
public:
	NameKeyType rva00085294();
private:
	Rva00148F5ECache m_00;
};

NameKeyType Rva00085294::rva00085294()
{
	return m_00.get();
}

class Rva00073421
{
public:
	unsigned int rva00073421(const int &key);
	void rva000730D9();
private:
	Rva00072FE6 m_00;
};

unsigned int Rva00073421::rva00073421(const int &key)
{
	return m_00.rva000733D8(key);
}

void Rva00073421::rva000730D9()
{
	m_00.rva00072FE6();
}

class Rva00057AE9
{
public:
	void rva00057AE9();
private:
	Rva00056DA2 m_00;
};

void Rva00057AE9::rva00057AE9()
{
	m_00.rva00056DA2();
}

class Rva0005A07F
{
public:
	void rva0005A07F(const Rva0036CA00Str &value);
private:
	Rva00058B90 m_00;
};

void Rva0005A07F::rva0005A07F(const Rva0036CA00Str &value)
{
	m_00.rva00058B90(value);
}

// 0x000554F5 (5B), unreferenced: forwarder to the rowed
// Rva00053DC5::rva00054B9A (0x00054B9A) of the object at +0.
class Rva00053DC5
{
public:
	void rva00054B9A();
};

class Rva000554F5
{
public:
	void rva000554F5();
private:
	Rva00053DC5 m_00;
};

void Rva000554F5::rva000554F5()
{
	m_00.rva00054B9A();
}

// 0x000907BC (5B), unreferenced: tail jump into the rowed DX8_Assert
// (0x0069E440).
void DX8_Assert();

void rva000907BC()
{
	DX8_Assert();
}

// 0x0006F313 (5B), unreferenced: the template the OVERRIDE<LocomotorTemplate>
// at +0 points at, a tail jump into its rowed operator-> (0x0035C95F).
class LocomotorTemplate;

template <class T> class OVERRIDE
{
public:
	const T *operator->() const;
private:
	const T *m_ptr;
};

class Rva0006F313
{
public:
	const LocomotorTemplate *rva0006F313() const;
private:
	OVERRIDE<LocomotorTemplate> m_00;
};

const LocomotorTemplate *Rva0006F313::rva0006F313() const
{
	return m_00.operator->();
}

// 0x0004208C / 0x00042100 (5B each): ~W3DGameLogic and ~W3DModuleFactory,
// the Win32GameEngine createGameLogic / slot-31 products' destructors (their
// scalar deleting destructors 0x00042070 / 0x000420E4 call them), each a lone
// tail jump into its base's rowed destructor ??1GameLogic (0x00243BA0) and ??1Rva00256E96 (0x00256E96, ModuleFactory). novtable keeps
// the dead vptr store out, as retail has none.
// class-gate: allow GameLogic base view that declares only the virtual destructor ~W3DGameLogic chains to
class GameLogic
{
public:
	virtual ~GameLogic();
};

class Rva00256E96
{
public:
	virtual ~Rva00256E96();
};

class __declspec(novtable) W3DGameLogic : public GameLogic
{
public:
	virtual ~W3DGameLogic();
};

W3DGameLogic::~W3DGameLogic()
{
}

class __declspec(novtable) W3DModuleFactory : public Rva00256E96
{
public:
	virtual ~W3DModuleFactory();
};

W3DModuleFactory::~W3DModuleFactory()
{
}

// 0x00041EB9 (5B), unreferenced: the rowed virtual GameEngine::rva0023054C
// (0x0023054C) called non-virtually (qualified) on the GameEngine at +0, a
// tail jump -- the shape of a derived engine forwarding to its base.
class GameEngine
{
public:
	virtual void rva0023054C();
};

class Rva00041EB9
{
public:
	void rva00041EB9();
private:
	GameEngine m_00;
};

void Rva00041EB9::rva00041EB9()
{
	m_00.GameEngine::rva0023054C();
}
