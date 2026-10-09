// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1
// AptLoadMovieFrame, the strategic HUD's load-dialog frame.
//
// The class name is WorldBuilder's (AptLoadMovieFrame.cpp, Impl::UnloadContent
// at 0x0057C236, rowed in Rva0057C236UnloadContent.cpp). StrategicHUD's
// OnLoadDialogFrameLoaded 0x0042DC04 news the 8-byte frame (vtable 0x00C6F304,
// one slot: the deleting destructor 0x0057C4E2) from the loaded movie's level
// and path; the frame owns its 0x1C-byte Impl at +4. The frame's rowed
// members (destructor 0x0057C3B6 and its Impl clear 0x0057C39C, the forwarders
// 0x0057C2CC and 0x0057C394) and the Impl's (destructor 0x0057C2D4,
// UnloadContent, LoadContent 0x0057C339) live in other units under address
// names; the layout below is the one they and the constructor 0x0057C3C4 use:
// level, path, the bound-name vector, the content callback, the loaded flag.
#include "ascii_string.h"

namespace AptUtils { const char *__cdecl SkipLevelN(const char *path); }
namespace AptUtils { int __cdecl LevelIndexFromTarget(const char *path); }

// Adopt the verified Rva0057C04F constructor delegate/concat pattern.
// AddCommandMapDelegate gives retail temporary lifetimes; source9cb BFME1
// donor is not used for this compiler delta, which is established by BFME2
// matched sibling57C152 and native57C3C4 full bytes.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
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
	AptRef &rva00579E47(const DelegateDesc *desc); // 0x00579E47
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

// The 12-byte command-map name list: ctor 0x001F81BF (ICF fold, pinned),
// AddCommandMap 0x0052458E, dtor 0x0052413E (pinned).
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
	char m_pad[12]; // +0x0C size 12 so +0x18 flag follows
};

class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *init(const char *src); // 0x000B3F84

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
	operator AsciiString(); // 0x0050F74B

	Rva000B3F84Pair m_right;
};
// ?operator+(AsciiStringPlusString, text) present-unmatched (inline, emitted out of line; ICF-folded at 0x00109CFD; pinned)
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

// The +0x14 content callback: a reference-counted functor released by the
// rowed holder destructor 0x005F8F96 and fired through the rowed two-argument
// invoke 0x001531F2.
class Rva001531F2Ref
{
public:
	Rva001531F2Ref() : m_op(0) {}
	~Rva001531F2Ref();
	int invoke(int a, int b);
	bool isSet() const { return m_op != 0; }

private:
	void *m_op;
};

class AptLoadMovieFrame
{
public:
	class Impl;

	AptLoadMovieFrame(int level, const AsciiString &name);
	virtual ~AptLoadMovieFrame();

private:
	Impl *m_impl; // +0x04, owned
};

class AptLoadMovieFrame::Impl
{
public:
	Impl(int level, const AsciiString &name);

	void OnContentLoaded(const char *path);

private:
	int m_level; // +0x00: the movie's level, "_level%u"
	AsciiString m_name; // +0x04: the frame's path in the movie
	AptCommandMapAdder m_bindings; // +0x08
	Rva001531F2Ref m_onLoaded; // +0x14: set by LoadContent 0x0057C339
	bool m_loaded; // +0x18: set by LoadContent, cleared by UnloadContent
};

// Retail 0x0057C26C, 96 bytes: bound as "_level%u.<path>_OnContentLoaded";
// hands the loaded content's level and path to the LoadContent callback.
void AptLoadMovieFrame::Impl::OnContentLoaded(const char *path)
{
	if (m_loaded && m_onLoaded.isSet())
	{
		AsciiString name(AptUtils::SkipLevelN(path));
		m_onLoaded.invoke(AptUtils::LevelIndexFromTarget(path), (int)&name);
	}
}

// Retail 0x0057C499, 73 bytes. The Impl constructor 0x0057C3C4 binds
// OnContentLoaded under "_level%u.<path>_OnContentLoaded".
AptLoadMovieFrame::AptLoadMovieFrame(int level, const AsciiString &name)
	: m_impl(new Impl(level, name))
{
}

// Retail 0x0057C3C4, 213 bytes.
AptLoadMovieFrame::Impl::Impl(int level, const AsciiString &name)
	: m_level(level), m_name(name), m_loaded(false)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	m_bindings.AddCommandMapDelegate(prefix + m_name + "_OnContentLoaded", DelegateDesc(this, &AptLoadMovieFrame::Impl::OnContentLoaded));
}

