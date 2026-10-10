// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva0056B2DD@@QAE@PAVRva0056AC26Owner@@PAUParent0056B2DD@@H@Z, retail
// 0x0056B599..0x0056B613 (122 bytes, EH, ret 0xC). Constructor of the
// parent listener of Rva0056B2DDDtor.cpp (vtables 0x00C6D470, 0x00C6D434 at
// +8 and 0x00C6D420 at +0x14): the rowed base Rva0056AC26 gets the owner,
// the listener is registered with the list at +8 of the parent (rowed append
// 0x005A0B4C), the int is kept at +0x1C and, when TheLivingWorldManager has
// its notifier at +0x268, that is told the int (rowed 0x003EE91A). Class and
// parent names address-derived.
class Rva0056AC26Owner;
struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

struct Parent0056B2DD
{
	char pad[8];
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

class __declspec(novtable) Rva0056B2DDB1
{
public:
	virtual ~Rva0056B2DDB1() {}
	virtual void b1Anchor();
	int m_a8;
	int m_bC;
};

class Rva0056B2DDB2
{
public:
	Rva0056B2DDB2() {}
	virtual ~Rva0056B2DDB2() {}
};

class Rva003EE91A
{
public:
	void rva003EE91A(int v);
};

class Rva0021294A
{
public:
	char m_pad[0x268];
	Rva003EE91A *m_268;
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

class Rva0056B2DD : public Rva0056AC26, public Rva0056B2DDB1, public Rva0056B2DDB2
{
public:
	Rva0056B2DD(Rva0056AC26Owner *owner, Parent0056B2DD *parent, int value);
	virtual ~Rva0056B2DD();
private:
	Parent0056B2DD *m_parent18;
	int m_x1C;
};

Rva0056B2DD::Rva0056B2DD(Rva0056AC26Owner *owner, Parent0056B2DD *parent, int value)
	: Rva0056AC26(owner), m_parent18(parent), m_x1C(value)
{
	m_parent18->holder.append((Rva002BA8F1Listener *)static_cast<Rva0056B2DDB2 *>(this));
	Rva003EE91A *notifier = ((Rva0021294A *)TheLivingWorldManager)->m_268;
	if (notifier)
		notifier->rva003EE91A(value);
}
