// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE
// Rva00527827::Rva00527827, retail 0x00527C04 (202 bytes).
//
// Target evidence: the constructor installs vftable 0x00C68088, keeps its
// int argument at +0x04 and a copy of its name at +0x08, clears +0x0C..+0x14
// and the +0x1C string, sets +0x18 to -1, asks 0x00527B03 (the method just
// before it) for the movie name and registers "<movie>_Content" with
// TheAptPlayer's custom renders (0x0022464C) bound to this object's
// 0x00527827 render callback, which the ledger rows under Rva00527827.
// WorldBuilder twin 0x013D0080 has the same shape (an empty polymorphic base,
// the member list, the "_Content" concatenation through
// AsciiStringPlusText 0x000B49C5/0x000BC4F7). Class name: the address-named
// owner of the bound callback.
//
// Codegen note: the delegate holder constructor (row 0x00579E47,
// Rva00579E47Delegate.cpp) is defined here inline (never inlined), as in the
// Apt binding recoveries of ab181d4413: retail's compiler knew it only reads
// the descriptor, which lets the movie name and the concatenated name share
// the dead argument homes [ebp+0xC]/[ebp+8].
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

class AptCustomRender;
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

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

class AptPlayer
{
public:
	void AddCustomRender(const AsciiString &name, AptRef<AptCustomRender> render);
};
extern AptPlayer *TheAptPlayer;

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
struct AsciiStringPlusText : AsciiStringRef
{
	operator AsciiString();
	Rva000B3F84Pair m_right;
};
AsciiStringPlusText operator+(const AsciiString &left, const char *right);

class Rva00527827Base
{
public:
	virtual ~Rva00527827Base();
};

// +0x1C: the reference holder whose destructor 0x005F8F96 the unwind funclet
// calls (the ledger's Rva004F6966).
class Rva004F6966
{
public:
	Rva004F6966() : m_ptr(0) {}
	~Rva004F6966();
private:
	void *m_ptr;
};

class Rva00527827 : public Rva00527827Base
{
public:
	Rva00527827(int arg, const AsciiString &name);
	void rva00527827(int a, const float *b, int c, int d);
	__declspec(noinline) AsciiString rva00527B03();
private:
	int m_04;
	AsciiString m_name; // +0x08
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	Rva004F6966 m_1C;
};

Rva00527827::Rva00527827(int arg, const AsciiString &name)
	: m_04(arg),
	  m_name(name),
	  m_0C(0),
	  m_10(0),
	  m_14(0),
	  m_18(-1)
{
	AsciiString movie = rva00527B03();
	TheAptPlayer->AddCustomRender(movie + "_Content",
		AptRef<AptCustomRender>(MakeDelegate(this, &Rva00527827::rva00527827)));
}

// Native 00527B03..00527B81 is a complete 126-byte hidden-result method.
// WB13D08B0 corroborates _level%d and the separator/name aggregate.
// The concat provider's const-char* declaration is used only as its owned
// pointer ABI carrier: retail receives the address of this eight-byte view.
// The original source aggregate and class names remain unestablished.
struct Rva00527B03Arguments {
    char separator;
    const AsciiString *name;
    Rva00527B03Arguments(const char &a,const AsciiString &b):separator(a),name(&b) {}
};
AsciiString &Rva0052798FAppend(AsciiString &,const char *);
static __forceinline void Rva00527B03Append(AsciiString &text,Rva00527B03Arguments value)
{
    Rva0052798FAppend(text,reinterpret_cast<const char *>(&value));
}
// ?rva00527B03@Rva00527827@@QAE?AVAsciiString@@XZ
AsciiString Rva00527827::rva00527B03()
{
    AsciiString text;
    text.format("_level%d",m_04);
    Rva00527B03Append(text,Rva00527B03Arguments('.',m_name));
    return text;
}
