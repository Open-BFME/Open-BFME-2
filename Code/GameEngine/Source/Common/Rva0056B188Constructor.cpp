// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva0056B188@@QAE@PAVRva0056AC26Owner@@HPAURva0056B188Owner@@@Z, retail
// 0x0056B3F5..0x0056B460 (107 bytes, EH, ret 0xC). Constructor of the
// optional-owner listener of Rva0056B188Dtor.cpp (own vftables 0x00C6D3A8,
// 0x00C6D36C at +8 and 0x00C6D35C at +0x14): the rowed base Rva0056AC26 gets
// the owner argument, the int is kept at +0x1C, a flag at +0x20 is cleared and
// when an owner (list at +4) was passed the listener is registered with it
// (rowed append 0x005A0B4C). Class names address-derived.
class Rva0056AC26Owner;
struct Rva002BA8F1Listener;

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

struct Rva0056B188Owner
{
	int m_00;
	Rva005A0B4CList m_list; // +0x04
};

class Rva0056AC26A
{
public:
	virtual ~Rva0056AC26A();
private:
	int m_04;
};

class Rva0056AC26B
{
public:
	virtual ~Rva0056AC26B();
private:
	int m_04;
	int m_08;
};

class Rva0056AC26 : public Rva0056AC26A, public Rva0056AC26B
{
public:
	Rva0056AC26(Rva0056AC26Owner *owner);
	virtual ~Rva0056AC26();
};

class Rva0056B188Second
{
public:
	virtual ~Rva0056B188Second() {}
protected:
	Rva0056B188Owner *m_owner; // +0x04 in this base, +0x18 overall
};

class Rva0056B188 : public Rva0056AC26, public Rva0056B188Second
{
public:
	Rva0056B188(Rva0056AC26Owner *owner, int value, Rva0056B188Owner *parent);
	virtual ~Rva0056B188();
private:
	int m_1C;
	bool m_20;
};

Rva0056B188::Rva0056B188(Rva0056AC26Owner *owner, int value, Rva0056B188Owner *parent)
	: Rva0056AC26(owner)
{
	m_owner = parent;
	m_1C = value;
	m_20 = false;
	if (m_owner)
		m_owner->m_list.append((Rva002BA8F1Listener *)static_cast<Rva0056B188Second *>(this));
}
