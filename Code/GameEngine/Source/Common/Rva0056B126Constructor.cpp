// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva0056B126@@QAE@PAVRva0056AC26Owner@@PAUParent0056B126@@H@Z, retail
// 0x0056B372..0x0056B3D9 (103 bytes, EH, ret 0xC). Constructor of the parent
// listener of Rva0056B126Dtor.cpp (vtables 0x00C6D348, 0x00C6D30C at +8 and
// 0x00C6D2FC at +0x14): the rowed base Rva0056AC26 gets the owner, the parent
// and the int are kept at +0x18 / +0x1C, a flag at +0x20 is cleared and the
// listener at +0x14 is registered with the list at +4 of the parent (rowed
// append 0x005A0B4C). Class and parent names address-derived.
class Rva0056AC26Owner;
struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

struct Parent0056B126
{
	char pad[4];
	Rva005A0B4CList holder;
};

class Rva0056AC26
{
public:
	Rva0056AC26(Rva0056AC26Owner *owner);
	virtual ~Rva0056AC26();
private:
	char m_pad04[4];
};

class __declspec(novtable) Rva0056B126B1
{
public:
	virtual ~Rva0056B126B1() {}
	virtual void b1Anchor();
	int m_a8;
	int m_bC;
};

class Rva0056B126B2
{
public:
	Rva0056B126B2();
	virtual ~Rva0056B126B2() {}
};
// ??0Rva0056B126B2@@QAE@XZ @0x002B2523 9B: the default constructor, storing the
// class's own vtable (VA 0x00BFDF68) and returning this.
Rva0056B126B2::Rva0056B126B2()
{
}

class Rva0056B126 : public Rva0056AC26, public Rva0056B126B1, public Rva0056B126B2
{
public:
	Rva0056B126(Rva0056AC26Owner *owner, Parent0056B126 *parent, int value);
	virtual ~Rva0056B126();
private:
	Parent0056B126 *m_parent18;
	int m_1C;
	bool m_20;
};

Rva0056B126::Rva0056B126(Rva0056AC26Owner *owner, Parent0056B126 *parent, int value)
	: Rva0056AC26(owner), m_parent18(parent), m_1C(value), m_20(false)
{
	m_parent18->holder.append((Rva002BA8F1Listener *)static_cast<Rva0056B126B2 *>(this));
}
