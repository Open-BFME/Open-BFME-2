// ??0Rva005C7954Elem@@QAE@PAVRva005C802B@@PAVAptMovieClipFrame@@ABVAsciiString@@@Z
// partial score=0.9864 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /arch:SSE
// ??1Rva005C7954Elem@@QAE@XZ @0x005C7954 213B: non-virtual dtor with twin AptCall hides plus 5 member dtors.
// Evidence: callers 0x005C7C88 deleting dtor plus 0x005C7CAD clear in OpaqueScalarDeletingDtors.cpp; callees rowed 0x005FB5E6 AptCall plus 0x005C3209 plus 4 vector dtors plus releaseBuffer 0x00036410; strings SetAutoAbilityOverlayState SetFlashEffectState _hide plus g_Rva0107301CEmptyString plus TheRva00222A8BTarget; neighbour Rva005C7A29Overlay.cpp layout +08 +0C +4C +54 +55.
#include "ascii_string.h"
#include "unicode_string.h"

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0);

class AptMovieClipFrame
{
public:
	void rva005C3209();
 bool CreateContentMovieClip(const AsciiString &, const AsciiString &, int *, AsciiString *);
};

// Owner vtable installed by the factory at 0x005C802B. Callback bodies
// 0x005C78D0 and 0x005C790D prove the seven-slot prefix used here.
class Rva005C802B
{
public:
	virtual ~Rva005C802B();
	virtual void vslot1();
	virtual void vslot2();
	virtual void vslot3();
	virtual void vslot4();
	virtual void vslot5();
	virtual void vslot6();
};

class BfmeAptWindowManager { public: void bfmeSetText(const AsciiString &, const UnicodeString &, bool); };
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
struct CommandButtonMouseState
{
	char m_pad[0x318];
	int m_button;
};

namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};

template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &alloc);

protected:
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

class AptCommandTarget
{
};

struct DelegateDesc
{
	template <class T> DelegateDesc(T *object, void (T::*method)(const char *path))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	template <class T> DelegateDesc(T *object, void (T::*method)(int))
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
	_STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> > m_names;
};

// "prefix + name + text" concat nodes (layout as in System/RegistryAsciiPath.cpp).
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

static __forceinline AsciiStringPlusString operator+(const AsciiString &left, const AsciiString &right)
{
	AsciiStringPlusString result;
	result.m_string = &left;
	result.m_second.m_string = &right;
	return result;
}

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


// Timer binding: the (object, method) payload the rowed binder 0x005E1260
// copies into its reference-counted body.
struct Init005E1260
{
	template <class T> Init005E1260(T *object, void (T::*method)(const char *))
		: m_object(reinterpret_cast<AptCommandTarget *>(object)), m_method(reinterpret_cast<void (AptCommandTarget::*)(const char *path)>(method)) {}

	AptCommandTarget *m_object;
	void (AptCommandTarget::*m_method)(const char *path);
};

class AptTimer
{
public:
	void *m_vtbl;
	int m_refCount;
};

template <> class AptRef<AptTimer>
{
public:
	AptRef(const Init005E1260 *init) { rva005E1260(init); }
	AptRef &rva005E1260(const Init005E1260 *init); // 0x005E1260
	AptRef(const AptRef &that);
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr);
	}

private:
	AptTimer *m_ptr;
};

// The 12-byte timer name list: ctor 0x001F81BF (ICF fold, pinned; defined
// below as its fold proof), AddTimer 0x005247A9.
class AptTimerAdder
{
public:
	AptTimerAdder();
	~AptTimerAdder();
	void AddTimer(const AsciiString &name, AptRef<AptTimer> timer);

	__forceinline void AddTimerBinding(const AsciiString &name, Init005E1260 init)
	{
		AddTimer(name, &init);
	}

private:
	_STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> > m_names;
};

// ?AptTimerAdder::AptTimerAdder present-unmatched (ICF-folded at 0x001F81BF; pinned)
AptTimerAdder::AptTimerAdder()
	: m_names(_STL::allocator<AsciiString>())
{
}


class AptOverButtonHandler { public: void *m_vtbl; int m_refCount; };
template <> class AptRef<AptOverButtonHandler>
{
public:
    AptRef(const DelegateDesc *desc)
    { reinterpret_cast<AptRef<AptCommandMap> *>(this)->rva00579E47(desc); }
    ~AptRef() { if (m_ptr) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_ptr); }
private:
    AptOverButtonHandler *m_ptr;
};
class Rva00524415 { public: Rva00524415(); private: char m_pad[0x18]; };
class AptOverButtonHandlerAdder : public Rva00524415
{
public:
    AptOverButtonHandlerAdder() {}
    ~AptOverButtonHandlerAdder();
    void AddOverButtonHandler(int level, const AsciiString &name, AptRef<AptOverButtonHandler> handler);
    __forceinline void AddOverButtonDelegate(const int &level, const AsciiString &name, DelegateDesc desc)
    { AddOverButtonHandler(level, name, reinterpret_cast<const DelegateDesc *>(&desc)); }
};
struct AsciiStringRefWithChar : AsciiStringRef
{
    operator AsciiString();
    char m_char;
};
static __forceinline AsciiStringRefWithChar operator+(const AsciiString &left, char right)
{
    AsciiStringRefWithChar result;
    result.m_string = &left;
    result.m_char = right;
    return result;
}
namespace AptUtils { AsciiString DotPath2SlashPath(const char *path); }
class Rva005CB260 { public: void rva005CB260(); };

class Rva005242D7
{
public:
    Rva005242D7();
    ~Rva005242D7();
private:
    _STL::_Vector_base<AsciiString, _STL::allocator<AsciiString> > m_names;
};
Rva005242D7::Rva005242D7() : m_names(_STL::allocator<AsciiString>()) {}
AptCommandMapAdder::AptCommandMapAdder() : m_names(_STL::allocator<AsciiString>()) {}
class Rva005C7954Elem
{
public:
	~Rva005C7954Elem();
 Rva005C7954Elem(Rva005C802B *, AptMovieClipFrame *, const AsciiString &);
	void OnInitialized(const char *path);
	void OnOverButton(const char *path);
	void OnPress(const char *path);
private:
	Rva005C802B *m_00;
	AptMovieClipFrame *m_04;
	int m_08;
	AsciiString m_0C;
	AptCommandMapAdder m_10;
	AptOverButtonHandlerAdder m_1C;
	Rva005242D7 m_34;
	AptTimerAdder m_40;
	bool m_4C;
	char _pad4D[3];
	int m_50;
	bool m_54;
	bool m_55;
 char m_pad56[2];
 int m_58;
 int m_5C;
};

// Constructor 0x005C7D4A binds this callback to "_OnInitialized";
// retail 0x005C78C9..0x005C78D0 writes the initialized flag and returns 4.
void Rva005C7954Elem::OnInitialized(const char *path)
{
	m_4C = true;
}

// Bound by the constructor to the over-button handler. The body ends at
// 0x005C7917; the following getter is a separate, already-owned body.
void Rva005C7954Elem::OnOverButton(const char *path)
{
	m_00->vslot2();
}

// Constructor binds "_OnPress" at 0x005C7E90. Retail reads the player's
// mouse-button word at +0x318 and dispatches mode 6 through slots 3/5,
// other modes through slots 4/6. Other mouse buttons do nothing.
void Rva005C7954Elem::OnPress(const char *path)
{
	int button = reinterpret_cast<CommandButtonMouseState *>(g_bfmeAptWindowManager)->m_button;
	if (button == 0) {
		if (m_50 == 6)
			m_00->vslot3();
		else
			m_00->vslot4();
	} else if (button == 2) {
		if (m_50 == 6)
			m_00->vslot5();
		else
			m_00->vslot6();
	}
}

Rva005C7954Elem::~Rva005C7954Elem()
{
	if (m_4C) {
		if (m_54) {
			char *t = *(char **)(void *)&m_0C;
			const char *s = t ? t + 8 : "";
			Rva005FB5E6AptCall(TheRva00222A8BTarget, reinterpret_cast<void *>(m_08), s, "SetAutoAbilityOverlayState", "_hide");
		}
		if (m_55) {
			char *t = *(char **)(void *)&m_0C;
			const char *s = t ? t + 8 : "";
			Rva005FB5E6AptCall(TheRva00222A8BTarget, reinterpret_cast<void *>(m_08), s, "SetFlashEffectState", "_hide");
		}
	}
	m_04->rva005C3209();
}

Rva005C7954Elem::Rva005C7954Elem(Rva005C802B *owner, AptMovieClipFrame *frame, const AsciiString &instance)
    : m_00(owner), m_04(frame), m_08(-1), m_4C(false), m_50(0),
      m_54(false), m_55(false), m_58(0), m_5C(0)
{
    m_04->CreateContentMovieClip(AsciiString("CommandButton"), instance, &m_08, &m_0C);
    AsciiString prefix;
    prefix.format("_level%u.", m_08);
    m_10.AddCommandMapDelegate(prefix + m_0C + "_OnInitialized", DelegateDesc(this, &Rva005C7954Elem::OnInitialized));
    m_10.AddCommandMapDelegate(prefix + m_0C + "_OnPress", DelegateDesc(this, &Rva005C7954Elem::OnPress));
    m_40.AddTimerBinding(prefix + m_0C + "_Timer", Init005E1260(m_00, reinterpret_cast<void (Rva005C802B::*)(const char *)>(&Rva005CB260::rva005CB260)));
    m_1C.AddOverButtonDelegate(m_08, AptUtils::DotPath2SlashPath(m_0C.str()) + '/', DelegateDesc(this, &Rva005C7954Elem::OnOverButton));
    AsciiString textPath;
    textPath.format("APT:_level%u.%s_ProductionCount", m_08, m_0C.str());
    g_bfmeAptWindowManager->bfmeSetText(textPath, UnicodeString(L""), false);
}
