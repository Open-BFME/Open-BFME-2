// ??0Impl@AptLoadMovieFrame@@QAE@HABVAsciiString@@@Z
// partial score=0.96 date=2026-10-07
// Banked partial for AptLoadMovieFrame::Impl::Impl 0x0057C3C4 (see re_attempts.log).
// Resolving the 0x00109CFD call needs this symbols.csv pin (placeholder-named fold alias):
// ??HRva00109CFD@@YA?AUAsciiStringPlusStringText@@ABUAsciiStringPlusString@@PBD@Z,0x00109CFD
// Outside Code/ the scratch copy needs /O1 on the cl line; in Code/GameEngine the region supplies it.
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

const char *__cdecl Rva00412845AfterLevel(const char *path);
int __cdecl Rva004128BBGetLevel(const char *path);

// The narrow concatenation nodes, as rowed in RegistryAsciiPath.cpp.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}

	const char *m_ptr;
	int m_len;
};

struct AsciiStringRef
{
	const AsciiString *m_string;
};

// "string + string"
struct AsciiStringPlusString : AsciiStringRef
{
	AsciiStringRef m_second;
};

// "string + string + text"; its conversion is rowed at 0x0050F74B.
struct AsciiStringPlusStringText : AsciiStringPlusString
{
	operator AsciiString();

	Rva000B3F84Pair m_text;
};

inline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

// "8-byte node + text" is one identical-code fold at 0x00109CFD for every
// 8-byte left node; the ledger owns it as the AsciiStringRefWithChar overload.
// This unit's string-plus-string overload reaches it under the address name.
namespace Rva00109CFD
{
AsciiStringPlusStringText __cdecl operator+(const AsciiStringPlusString &left, const char *right);
}
using Rva00109CFD::operator+;

// The bound callbacks are handed over as a by-value delegate the callee
// destroys, built in place from an {object, method} pair by the rowed
// constructor 0x00579E47, as in StrategicHUD.cpp.
struct DelegateDesc;

class Rva00579E47
{
public:
	Rva00579E47(const DelegateDesc &desc);
	Rva00579E47(const Rva00579E47 &other);
	~Rva00579E47();

private:
	void *m_ptr;
};

class Rva00579E47Delegate;

// The +0x08 member: the 12-byte vector of bound names (constructor 0x001F81BF,
// rowed destructor 0x0052413E); 0x0052458E binds a delegate under a name.
class Rva0052413E
{
public:
	Rva0052413E();
	~Rva0052413E();
	void rva0052458E(const AsciiString &name, Rva00579E47Delegate delegate);

private:
	unsigned char m_pad[0xC];
};

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
	Rva0052413E m_bindings; // +0x08
	Rva001531F2Ref m_onLoaded; // +0x14: set by LoadContent 0x0057C339
	bool m_loaded; // +0x18: set by LoadContent, cleared by UnloadContent
};

struct DelegateDesc
{
	DelegateDesc(AptLoadMovieFrame::Impl *object, void (AptLoadMovieFrame::Impl::*method)(const char *))
		: m_object(object), m_method(method) {}

	AptLoadMovieFrame::Impl *m_object;
	void (AptLoadMovieFrame::Impl::*m_method)(const char *);
};

class Rva00579E47Delegate : public Rva00579E47
{
public:
	Rva00579E47Delegate(DelegateDesc desc) : Rva00579E47(desc) {}
};

// Retail 0x0057C26C, 96 bytes: bound as "_level%u.<path>_OnContentLoaded";
// hands the loaded content's level and path to the LoadContent callback.
void AptLoadMovieFrame::Impl::OnContentLoaded(const char *path)
{
	if (m_loaded && m_onLoaded.isSet())
	{
		AsciiString name(Rva00412845AfterLevel(path));
		m_onLoaded.invoke(Rva004128BBGetLevel(path), (int)&name);
	}
}

// Retail 0x0057C3C4, 213 bytes.
AptLoadMovieFrame::Impl::Impl(int level, const AsciiString &name)
	: m_level(level), m_name(name), m_loaded(false)
{
	AsciiString prefix;
	prefix.format("_level%u.", m_level);
	m_bindings.rva0052458E(prefix + m_name + "_OnContentLoaded", Rva00579E47Delegate(DelegateDesc(this, &AptLoadMovieFrame::Impl::OnContentLoaded)));
}

// Retail 0x0057C499, 73 bytes.
AptLoadMovieFrame::AptLoadMovieFrame(int level, const AsciiString &name)
	: m_impl(new Impl(level, name))
{
}
