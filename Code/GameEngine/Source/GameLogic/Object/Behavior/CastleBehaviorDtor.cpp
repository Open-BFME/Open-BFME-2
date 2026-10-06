// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1CastleBehavior@@UAE@XZ @0x0039857D 225B evidence: pinned name; vtable VA 0x00C1A780 slot0 deleting dtor caller 0x00399357; donor open-bfme-1 CastleBehaviorDestructorThunk.cpp; callees rowed 0x00397E50 0x003968D3 0x00036410 0x002F0B52 0x00030830 0x00455050
#include "ascii_string.h"

void __cdecl free(void *p);

class Rva00397E50
{
public:
	void rva00397E50();
};

class Rva002EE9B7
{
public:
	~Rva002EE9B7();
private:
	char m_pad[12];
};

class Rva00395CEB
{
public:
	~Rva00395CEB();
private:
	char m_pad[12];
};

class Rva0024A797_Root
{
public:
	virtual ~Rva0024A797_Root();
private:
	char m_pad04[8];
};

class Rva0024A797_Mid
{
public:
	virtual void f1();
};

class Rva0024A797_B2
{
public:
	virtual void f2();
private:
	char m_pad08[12];
};

class Rva0024A797 : public Rva0024A797_Root, public Rva0024A797_Mid, public Rva0024A797_B2
{
public:
	virtual ~Rva0024A797();
};

class Rva00455050_E1
{
public:
	virtual void fe();
};

class Rva00455050 : public Rva0024A797, public Rva00455050_E1
{
public:
	virtual ~Rva00455050();
private:
	char m_pad24[12];
};

class CastleBehavior_30
{
public:
	virtual void f30();
};

struct Rva0039857DVec
{
	void *m_begin;
	void *m_end;
	void *m_cap;
	~Rva0039857DVec()
	{
		if (m_begin != 0)
			free(m_begin);
	}
};

class CastleBehavior : public Rva00455050, public CastleBehavior_30
{
public:
	virtual ~CastleBehavior();
private:
	char m_pad34[0x1c];
	Rva0039857DVec m_vec50;
	Rva0039857DVec m_vec5c;
	Rva0039857DVec m_vec68;
	Rva0039857DVec m_vec74;
	Rva0039857DVec m_vec80;
	Rva002EE9B7 m_tree8c;
	AsciiString m_str98;
	char m_pad9c[4];
	Rva00395CEB m_mapA0;
};

// ??1CastleBehavior@@UAE@XZ
CastleBehavior::~CastleBehavior()
{
	((Rva00397E50 *)this)->rva00397E50();
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f1@Rva0024A797_Mid@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
