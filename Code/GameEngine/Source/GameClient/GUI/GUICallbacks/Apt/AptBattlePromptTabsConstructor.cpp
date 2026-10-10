// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva005FE750@@QAE@HABVAsciiString@@@Z, retail 0x005FE640..0x005FE750
// (272 bytes, EH, ret 8). The battle prompt player tab strip,
// StrategicHUD::BattlePromptPlayerTabsMovieClip (class keeps its address name
// Rva005FE750 from its rowed dtor; vtable 0x0087A3F4). Layout from the rowed
// dtor and HidePlayerName / SelectTab views: level +4, player prefix +8, the
// two 12-byte name lists +0x0C / +0x18 (+0x0C is the command map adder), tab
// index +0x24 (-1 = none), tab record vector +0x28, hide counter +0x34.
// Body: stores the level and prefix, creates the (empty) lists, sets the
// selected tab to none, makes a one-record vector, hides the player name
// (rowed 0x005FE047), clears the SetPlayerNameString display (rowed 0x005FDF1C)
// and binds "_level%u.<prefix>_OnTabClicked". Pattern follows Rva0057C04F.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class AptCommandTarget
{
};

struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

class AptCommandMap
{
public:
	void *m_vtbl;
	int m_refCount;
};

template <class T> class AptRef
{
public:
	AptRef(const DelegateDesc *desc) { rva00579E47(desc); }
	AptRef &rva00579E47(const DelegateDesc *desc);
	AptRef(const AptRef &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	T *m_ptr;
};

class AptCommandMapAdder
{
public:
	AptCommandMapAdder();
	~AptCommandMapAdder();
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);

	__forceinline void AddCommandMapDelegate(const AsciiString &name, DelegateDesc desc)
	{
		AddCommandMap(name, &desc);
	}

private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	Rva005242D7();
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src);

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString();

	Rva000B3F84Pair m_right;
};
inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_right = text;
	return result;
}

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

struct BfmeContainerRecord005FDEC7
{
	unsigned int word0;
	unsigned int word4;
	UnicodeString text08;
};

// The tab record vector (STLport vector of 12-byte records, rowed dtor
// 0x005FE4A3): declared only, as in Rva005FE750.cpp, so the size constructor
// stays the pinned out-of-line 0x005FE409.
namespace _STL
{
template <> class vector<BfmeContainerRecord005FDEC7, allocator<BfmeContainerRecord005FDEC7> >
{
public:
	explicit vector(unsigned int n);
	~vector();
private:
	BfmeContainerRecord005FDEC7 *m_begin;
	BfmeContainerRecord005FDEC7 *m_finish;
	BfmeContainerRecord005FDEC7 *m_end;
};
}
typedef _STL::vector<BfmeContainerRecord005FDEC7, _STL::allocator<BfmeContainerRecord005FDEC7> > Rva005FE409Vector;

struct Rva005FDF1COuter;
namespace StrategicHUD
{
	class BattlePromptPlayerTabsMovieClip { public: void HidePlayerName(); };
	void __cdecl SetPlayerNameString(int level, Rva005FDF1COuter *outer, const UnicodeString &text);
}

class Rva005FE750
{
public:
	Rva005FE750(int level, const AsciiString &name);
	virtual ~Rva005FE750();
	void OnTabClicked(const char *path);
private:
	int m_level04;
	AsciiString m_08;
	AptCommandMapAdder m_0C;
	Rva005242D7 m_18;
	int m_24;
	Rva005FE409Vector m_28;
	int m_count34;
};

Rva005FE750::Rva005FE750(int level, const AsciiString &name)
	: m_level04(level), m_08(name), m_24(-1), m_28(1), m_count34(0)
{
	((StrategicHUD::BattlePromptPlayerTabsMovieClip *)this)->HidePlayerName();
	StrategicHUD::SetPlayerNameString(m_level04, (Rva005FDF1COuter *)&m_08, UnicodeString::TheEmptyString);
	AsciiString prefix;
	prefix.format("_level%u.", m_level04);
	m_0C.AddCommandMapDelegate(prefix + m_08 + "_OnTabClicked", DelegateDesc(this, &Rva005FE750::OnTabClicked));
}
