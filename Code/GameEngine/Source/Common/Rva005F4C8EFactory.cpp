// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva005F4C8E@Rva005F4C52@@UAE?AV?$Rva005F4C8ERef@VRva005E6ED6Third@@@@HH@Z,
// retail 0x005F4C8E..0x005F4CF8 (106 bytes, EH, RET 12): slot 1 of
// Rva005F4C52's vtable. It returns a counted reference to the third
// interface (+0x14) of a new 0x2C-byte Rva005E6ED6 built from both arguments
// and the +0x08 member (0x005E6ED6, not yet rowed; pinned; it takes the
// hidden construct-virtual-bases flag 1). The count lives in a virtual base,
// so the reference reaches it through the interface's vbptr. No WorldBuilder
// name is matched.

class Rva005E6ED6Counted
{
public:
	virtual ~Rva005E6ED6Counted();
	void addRef() { ++m_refs; }
	int m_refs;
};

class Rva005E6ED6First : public virtual Rva005E6ED6Counted
{
public:
	virtual void first0();
	int m_08;
};

class Rva005E6ED6Second : public virtual Rva005E6ED6Counted
{
public:
	virtual void second0();
};

class Rva005E6ED6Third : public virtual Rva005E6ED6Counted
{
public:
	virtual void third0();
	int m_08;
};

class Rva005E6ED6 : public Rva005E6ED6First, public Rva005E6ED6Second, public Rva005E6ED6Third
{
public:
	Rva005E6ED6(int a, int b, void *owner);
private:
	int m_20;
};

template <class T>
class Rva005F4C8ERef
{
public:
	__forceinline Rva005F4C8ERef(T *p) : m_p(p) { if (p) p->addRef(); }
	Rva005F4C8ERef(const Rva005F4C8ERef &other);
	~Rva005F4C8ERef();
private:
	T *m_p;
};

class Rva005E5590Iface;

class Rva005F4C52
{
public:
	virtual Rva005F4C8ERef<Rva005E6ED6Third> rva005F4C8E(int a, int b);
	Rva005F4C8ERef<Rva005E5590Iface> rva005F4CF8(int a, int b);
private:
	unsigned char m_pad04[0x08 - 4];
	int m_08;
};

Rva005F4C8ERef<Rva005E6ED6Third> Rva005F4C52::rva005F4C8E(int a, int b)
{
	return Rva005F4C8ERef<Rva005E6ED6Third>(new Rva005E6ED6(a, b, &m_08));
}

// ?rva005FAB34@Rva005FAAA1@@QAE?AV?$Rva005F4C8ERef@VRva005E6ED6Second@@@@HH@Z,
// retail 0x005FAB34..0x005FAB9E (106 bytes, EH, RET 12): slot 5 of
// Rva005FAAA1's vtable, the same factory returning the second interface
// (+0x0C) of the new object.
class Rva005FAAA1
{
public:
	Rva005F4C8ERef<Rva005E6ED6Second> rva005FAB34(int a, int b);
private:
	unsigned char m_pad00[0x08];
	int m_08;
};

Rva005F4C8ERef<Rva005E6ED6Second> Rva005FAAA1::rva005FAB34(int a, int b)
{
	return Rva005F4C8ERef<Rva005E6ED6Second>(new Rva005E6ED6(a, b, &m_08));
}

// The same factory over two other counted classes:
//   ?rva005F4CF8@Rva005F4C52@@... @0x005F4CF8 106B, slot 3 of Rva005F4C52:
//     a new 0x24-byte Rva005E54F7 (constructor 0x005E5590), interface at +0x10;
//   ?rva005CDF8B@Rva005CDF6C@@... @0x005CDF8B 106B, slot 2 of Rva005CDF6C:
//     a new 0x30-byte Rva005CDE89 (0x005CDE89, pinned), interface at +0x0C.
struct RvaSmallVtableZeroBase { void *m_04; };
class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
    Rva0007DF07();
    virtual ~Rva0007DF07();
};
class Rva005CC5E5 : public virtual Rva0007DF07
{
public:
    __declspec(nothrow) Rva005CC5E5();
    virtual void slot0();
    virtual ~Rva005CC5E5();
};
class Rva005E3AE1 : public virtual Rva0007DF07
{
public:
    Rva005E3AE1();
    virtual void slot0() = 0;
    virtual ~Rva005E3AE1();
};
struct _Rva005E4AE2In;
class Rva005E4AE2
{
public:
    Rva005E4AE2(void *, _Rva005E4AE2In *, int);
private:
    char storage[0x30];
};
class Rva005E4B9D
{
public:
    Rva005E4B9D(Rva005E4AE2 *v);
    ~Rva005E4B9D();
    void clear();
    Rva005E4AE2 *value;
};
class Rva005E4F6D : public Rva005CC5E5, public Rva005E3AE1
{
public:
    Rva005E4F6D(_Rva005E4AE2In *, int);
    virtual ~Rva005E4F6D();
    virtual void slot0();
    virtual void slot1();
private:
    Rva005E4B9D child;
};
class AsciiString;
namespace StrategicHUD {
class ArmyDetailsMovieClip {public:
    ArmyDetailsMovieClip(int,const AsciiString &,int,bool);
    virtual ~ArmyDetailsMovieClip();
    virtual void notifyBackButtonClicked();
    virtual void notifyIconListBackgroundClicked();
private: class Impl *m_impl;
}; }
class Rva005E54AE:public StrategicHUD::ArmyDetailsMovieClip {public:Rva005E54AE(int,const AsciiString &,bool);virtual ~Rva005E54AE();};
class Rva005E54F7:public Rva005E54AE,public Rva005E4F6D {public:Rva005E54F7(int,const AsciiString &,void*);virtual ~Rva005E54F7();};
class Rva005E5590Iface : public virtual Rva005E6ED6Counted
{
public:
    virtual void iface0();
};

class Rva005CDE89First : public virtual Rva005E6ED6Counted
{
public:
	virtual void first0();
	int m_08;
};

class Rva005CDE89Iface : public virtual Rva005E6ED6Counted
{
public:
	virtual void iface0();
};

class Rva005CDE89 : public Rva005CDE89First, public Rva005CDE89Iface
{
public:
	Rva005CDE89(int a, int b, void *owner);
private:
	int m_14[5];
};

Rva005F4C8ERef<Rva005E5590Iface> Rva005F4C52::rva005F4CF8(int a, int b)
{
	// The existing return view reaches the same counted base through its
    // vbptr; the provider's real third interface is Rva005E3AE1 at +10.
    Rva005E54F7 *panel = new Rva005E54F7(a, *reinterpret_cast<const AsciiString *>(b), &m_08);
    return Rva005F4C8ERef<Rva005E5590Iface>(reinterpret_cast<Rva005E5590Iface *>(static_cast<Rva005E3AE1 *>(panel)));
}

class Rva005CDF6C
{
public:
	virtual Rva005F4C8ERef<Rva005CDE89Iface> rva005CDF8B(int a, int b);
private:
	unsigned char m_pad04[0x08 - 4];
	int m_08;
};

Rva005F4C8ERef<Rva005CDE89Iface> Rva005CDF6C::rva005CDF8B(int a, int b)
{
	return Rva005F4C8ERef<Rva005CDE89Iface>(new Rva005CDE89(a, b, &m_08));
}
