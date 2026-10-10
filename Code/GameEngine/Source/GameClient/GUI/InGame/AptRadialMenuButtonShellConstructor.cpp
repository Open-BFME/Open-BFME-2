// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE
// AptRadialMenu::Impl::ButtonShell::ButtonShell, retail 0x00577FE2 (423 bytes).
//
// Target evidence: WorldBuilder twin 0x014C6790 (AptRadialMenu::Impl::
// ButtonShell::ButtonShell). vftable 0x00C6EA80; the owning Impl at +0x08
// and the shell's slot argument at +0x0C; the button index from
// Impl::OnButtonCreated (0x005778E3) at +0x10; +0x14..+0x24 cleared and the
// enabled flag +0x28 set. It formats the index, asks the owner
// (0x00577A0E) for its movie name, binds "<movie>_OnButtonFrameLoaded_<n>"
// and "..._OnButtonFrameUnloaded_<n>" with TheAptPlayer to the frame
// callbacks 0x00577A2A and 0x0057792E, then fires "CreateButton" on the
// holder movie through 0x00525203.
//
// Codegen note: the delegate holder constructor (row 0x00579E47) is visible
// inline-never-inlined (the lever of ab181d4413), so the index text and the
// movie name share the dead argument homes [ebp+8]/[ebp+0xC] as retail does.
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

class AptPlayer
{
public:
	void AddCommandMap(const AsciiString &name, AptRef<AptCommandMap> map);
};
extern AptPlayer *TheAptPlayer;

// RegistryAsciiPath's concatenation nodes, spelled as the ledger rows them.
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
struct Rva002226E5TextPlusString : AsciiStringRef
{
	Rva000B3F84Pair m_text;
};
struct AsciiStringPlusText : Rva002226E5TextPlusString
{
};
struct Rva0020F58E
{
	operator AsciiString();
	Rva002226E5TextPlusString m_left;
	AsciiStringRef m_right;
};
struct AptTextPlusStringPlusString : Rva0020F58E
{
};
AsciiStringPlusText operator+(const AsciiString &left, const char *right);
AptTextPlusStringPlusString operator+(const Rva002226E5TextPlusString &left, const AsciiString &right);

int __cdecl Rva00525203Fire(void *player, void *movie, const char *path, const char *name, const AsciiString *argument);

struct RadialButtonMovie
{
	void *getMovie() const { return m_movie; }
	char m_pad00[4];
	void *m_movie; // +0x04
	AsciiString m_path; // +0x08
};
struct RadialButtonHolder
{
	RadialButtonMovie *m_button;
};

class Rva00577A2A
{
public:
	void rva00577A2A(const char *unused);
};

namespace AptRadialMenu_ns {}

class AptRadialMenu
{
public:
	class Impl
	{
	public:
		class ButtonShell;
		int OnButtonCreated();
	private:
		char m_pad00[0x40];
	public:
		RadialButtonHolder *m_holder; // +0x40
	};
};

class Rva00577A0E
{
public:
	AsciiString rva00577A0E() const;
};

// The reference-counted Apt object base (count at +0x04).
class Rva00577FE2Base
{
public:
	Rva00577FE2Base() : m_references(0) {}
	virtual ~Rva00577FE2Base();
	int m_references;
};

// +0x14: a three-pointer list the shell owns.
class Rva00577FE2List
{
public:
	Rva00577FE2List() : m_start(0), m_finish(0), m_end(0) {}
	~Rva00577FE2List();
	void *m_start;
	void *m_finish;
	void *m_end;
};

class AptRadialMenu::Impl::ButtonShell : public Rva00577FE2Base
{
public:
	ButtonShell(Impl *impl, int slot);
	virtual ~ButtonShell();
	void rva0057792E(const char *unused);
private:
	Impl *m_impl;
	int m_slot;
	int m_index;
	Rva00577FE2List m_14;
	int m_20;
	int m_24;
	bool m_enabled;
};

AptRadialMenu::Impl::ButtonShell::ButtonShell(Impl *impl, int slot)
	: m_impl(impl),
	  m_slot(slot),
	  m_index(impl->OnButtonCreated()),
	  m_20(0),
	  m_24(0),
	  m_enabled(true)
{
	AsciiString indexText;
	indexText.format("%d", m_index);
	AsciiString movie = ((const Rva00577A0E *)m_impl)->rva00577A0E();
	TheAptPlayer->AddCommandMap(movie + "_OnButtonFrameLoaded_" + indexText,
		AptRef<AptCommandMap>(MakeDelegate(this, &Rva00577A2A::rva00577A2A)));
	TheAptPlayer->AddCommandMap(movie + "_OnButtonFrameUnloaded_" + indexText,
		AptRef<AptCommandMap>(MakeDelegate(this, &ButtonShell::rva0057792E)));
	RadialButtonMovie *button = m_impl->m_holder->m_button;
	Rva00525203Fire(TheAptPlayer, button->getMovie(), button->m_path.str(), "CreateButton", &indexText);
}
