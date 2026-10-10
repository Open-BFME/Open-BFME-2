// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE
// Rva00510CC3::Rva00510CC3, retail 0x00510B72 (309 bytes).
//
// Target evidence: a sibling of the row-list constructor 0x005103A3 over the
// same Apt row base Rva0050EA74 (0x0050EA74: level +0x08, name +0x0C); vftable
// 0x00C65670, the command-map storage Rva0052413E at +0x14 (0x001F81BF), a
// cleared flag +0x20 and the holder +0x24 that its rowed destructor 0x00510CC3
// clears. It binds "_level<n>.<name>_OnEnabledContentLoaded" and
// "..._OnEnabledContentUnloaded" through delegate descriptors to the rowed
// callbacks 0x005108EB and OnEnabledContentUnloaded 0x00510233. The
// concatenation is RegistryAsciiPath's expression template (0x00109CFD, the
// AsciiStringPlusString + text operator; conversion 0x0050F74B).
//
// Codegen note: the delegate holder constructor (row 0x00579E47,
// Rva00579E47Delegate.cpp) is defined inline (never inlined), as in the Apt
// binding recoveries of ab181d4413, so the level prefix and each name share
// the dead argument homes [ebp+0xC]/[ebp+8] like retail.
#include "ascii_string.h"

void *__cdecl operator new(unsigned int size) throw();

struct DelegateDesc {
	template <class T, class M> DelegateDesc(T *object, M method) : m_object(object), m_method(*(void **)&method) {}
	void *m_object;
	void *m_method;
};

template <class T, class M> __forceinline DelegateDesc MakeDelegate(T *object, M method)
{
	DelegateDesc desc(object, method);
	return desc;
}

struct ImplBase {
	virtual ~ImplBase() {}
	int m_ref;
	ImplBase() : m_ref(0) {}
};

struct Impl : ImplBase {
	virtual void rva005b4c73(const char *argument);
	void *m_object;
	void *m_method;
	Impl(const DelegateDesc &d) : m_object(d.m_object), m_method(d.m_method) {}
};

class Rva00579E47 {
public:
	__declspec(noinline) Rva00579E47(const DelegateDesc &d)
	{
		Impl *p = new Impl(d);
		m_ptr = p;
		if (p)
			p->m_ref++;
	}
private:
	Impl *m_ptr;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class AptCommandMap;
template <class T> class AptRef : public Rva00579E47
{
public:
	AptRef(const DelegateDesc &desc) : Rva00579E47(desc) {}
	AptRef(const AptRef &other);
	~AptRef()
	{
		if (*(void **)this)
			ReleaseTreeHintRef00217D4C(*(TargetRef00217D4C **)this);
	}
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
	Rva000B3F84Pair m_text;
};

inline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString node;
	node.m_string = &left;
	node.m_second.m_string = &right;
	return node;
}

inline AsciiStringPlusStringText operator+(const AsciiStringPlusString &left, const char *right)
{
	Rva000B3F84Pair text;
	text.init(right);
	AsciiStringPlusStringText result;
	static_cast<AsciiStringPlusString &>(result) = left;
	result.m_text = text;
	return result;
}

class Rva0050EA74
{
public:
	Rva0050EA74(int level, const AsciiString &name);
	virtual ~Rva0050EA74();
	virtual void show();
	virtual void hide();
	virtual int v03(int message, int key, int state);
	virtual int v04(int message, int key, int state);
	virtual void v05();

	int m_references; // +0x04
	int m_level; // +0x08
	AsciiString m_name; // +0x0C
	bool m_shown; // +0x10
};

class Rva0052413E
{
public:
	Rva0052413E();
	~Rva0052413E();
private:
	char m_pad[0xC];
};

class AptCommandMapAdder : public Rva0052413E
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
};

class Rva0050F6AD
{
public:
	Rva0050F6AD() : m_ptr(0) {}
	~Rva0050F6AD() { rva0050F6AD(); }
	void rva0050F6AD();
private:
	void *m_ptr;
};

class Rva005108EB
{
public:
	void rva005108EB(const char *unused);
};

class Rva00510CC3 : public Rva0050EA74
{
public:
	Rva00510CC3(int level, const AsciiString &name);
	virtual ~Rva00510CC3();
	void OnEnabledContentUnloaded(const char *unused);
private:
	AptCommandMapAdder m_14;
	bool m_20;
	Rva0050F6AD m_24;
};

Rva00510CC3::Rva00510CC3(int level, const AsciiString &name)
	: Rva0050EA74(level, name),
	  m_20(false)
{
	AsciiString levelName;
	levelName.format("_level%u.", m_level);
	m_14.AddCommandMap((levelName + m_name) + "_OnEnabledContentLoaded",
		AptRef<AptCommandMap>(MakeDelegate(this, &Rva005108EB::rva005108EB)));
	m_14.AddCommandMap((levelName + m_name) + "_OnEnabledContentUnloaded",
		AptRef<AptCommandMap>(MakeDelegate(this, &Rva00510CC3::OnEnabledContentUnloaded)));
}
