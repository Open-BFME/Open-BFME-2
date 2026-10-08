// cl: /Ireference/shims/bfme2_ascii
// ?rva004FBC02@Rva004FBC02@@QAEXPBURva004FBC02Src@@@Z 0x004FBC02 21: copies 12 bytes
// from arg to +0x18 and sets byte at +0x24 to 1. Evidence: callers 0x002BA331 and
// 0x002BA7E1 pass a pointer; no other callees.

struct Rva004FBC02Src
{
	int m_0;
	int m_4;
	int m_8;
};

class Rva004FBC02
{
private:
	char m_pad[0x18];
	Rva004FBC02Src m_18;
	unsigned char m_24;
public:
	void rva004FBC02(const Rva004FBC02Src *src);
};

void Rva004FBC02::rva004FBC02(const Rva004FBC02Src *src)
{
	m_18 = *src;
	m_24 = 1;
}

// ?rva004FBDB0@Rva004FBDB0@@QAEXH@Z 0x004FBDB0 28: forwards int arg to slot-12
// virtual on the object looked up by this+0x18 key in the global map at 0x009FE1C8
// via rowed Rva002120A4::rva002120A4; returns on miss. Evidence: callers 0x004FBFF4
// 0x004FC0E2 0x004FC0AD pass 0/1 int; callees rowed; global name in use.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class Rva002120A4
{
public:
	int rva002120A4(NameKeyType key);
};

class Rva0021294A;
class LivingWorldManager; extern LivingWorldManager *TheLivingWorldManager;

// Slot-12 target is unidentified; dummies pad the vtable so slot12 lands at +0x30.
class Rva004FBDB0Target
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void slot12(int arg);
};

class Rva004FBDB0
{
private:
	char m_pad[0x18];
	NameKeyType m_key;
public:
	void rva004FBDB0(int arg);
};

void Rva004FBDB0::rva004FBDB0(int arg)
{
	int found = ((Rva002120A4 *)TheLivingWorldManager)->rva002120A4(m_key);
	if (found == 0)
		return;
	((Rva004FBDB0Target *)found)->slot12(arg);
}

// ?rva004FBDCC@Rva004FBDCC@@QAEXXZ 0x004FBDCC 19: pushes this+0x18 then sets
// byte at +0x1c to 1 and forwards the int to Rva00DFE1C8Host::rva00212655
// through global TheLivingWorldManager. Evidence: pin 0x00212655 plus caller 0x002BAF01.
class Rva00DFE1C8Host
{
public:
	void rva00212655(int val);
};

class Rva004FBDCC
{
private:
	char m_pad[0x18];
	int m_18;
	bool m_1c;
public:
	void rva004FBDCC();
};

void Rva004FBDCC::rva004FBDCC()
{
	m_1c = true;
	((Rva00DFE1C8Host *)TheLivingWorldManager)->rva00212655(m_18);
}
