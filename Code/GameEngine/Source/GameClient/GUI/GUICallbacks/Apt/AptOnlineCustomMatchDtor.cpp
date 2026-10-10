// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??1AptOnlineCustomMatch@@UAE@XZ, retail 0x005A0009..0x005A00CC (195
// bytes); pinned until now as the opaque ??1Rva005A0009@@UAE@XZ.
//
// Identity: the scalar deleting dtor 0x005A0B62 that calls it is slot 0 of
// vftable 0x00871414, whose slot 2 is the rowed
// ?InitGadgets@AptOnlineCustomMatch@@UAEXXZ (0x0059EFA0) and slots 8/9 the
// rowed AptOnlineCustomMatch rva0059EF49/rva005A6697; the +0x60 vftable
// 0x008713B8 holds the rowed MpOwner* members of AptOnlineCustomMatch and
// the WorldBuilder twin of the ctor storing 0x00871414 (0x005A5BC7) pushes
// the AptOnline::CustomMatch callback names.
//
// Layout from the body: three bases -- the screen base at +0x00 (inline
// Rva0056DC6B dtor: vftable 0x0086DB78 then the rowed 0x005248D0), the
// MpOwner interface at +0x60 (rowed out-of-line 0x004444D2) and a 4-byte
// interface at +0x6C (inline dtor storing 0x00C711BC); members +0x70
// (rowed 0x004421E1), +0x450 (folded vector-style dtor 0x0007FAB3), +0x46C
// (rowed 0x0054F508) and the AsciiString at +0x4D0. The body drops the
// live-instance count at 0x00E063F0, clears the instance pointer at
// 0x00E063EC when it is this object and unregisters the +0x6C interface
// from the list at +0x2C of the object at 0x00E063F8 (rowed 0x002B7250).

#include "ascii_string.h"

class Rva005248D0
{
public:
	virtual ~Rva005248D0();

private:
	char m_pad[0x60 - 4];
};

class Rva0056DC6B : public Rva005248D0
{
public:
	virtual ~Rva0056DC6B();
};

inline Rva0056DC6B::~Rva0056DC6B()
{
}

class Rva004444D2
{
public:
	virtual ~Rva004444D2();

private:
	char m_pad[0x0C - 4];
};

class Rva0059EB41
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual ~Rva0059EB41() {}
};

class Rva004421E1
{
public:
	virtual ~Rva004421E1();

private:
	char m_pad[0x450 - 0x70 - 4];
};

class Rva0035A18D
{
public:
	~Rva0035A18D();

private:
	char m_pad[0x46C - 0x450];
};

class Rva0054F508
{
public:
	virtual ~Rva0054F508();

private:
	char m_pad[0x4D0 - 0x46C - 4];
};

class CreateAHeroData;

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class Rva005A6D47
{
public:
	char m_pad[0x2C];
	Rva002B7250 m_2C; // +0x2C
};

extern Rva005A6D47 *g_Va00E063F8;
extern int g_currentAptOnlineCustomMatch;
extern int g_Va00E063F0;

class AptOnlineCustomMatch : public Rva0056DC6B, public Rva004444D2, public Rva0059EB41
{
public:
	virtual ~AptOnlineCustomMatch();

private:
	Rva004421E1 m_70; // +0x70
	Rva0035A18D m_450; // +0x450
	Rva0054F508 m_46C; // +0x46C
	AsciiString m_4D0; // +0x4D0
};

AptOnlineCustomMatch::~AptOnlineCustomMatch()
{
	--g_Va00E063F0;
	if (g_currentAptOnlineCustomMatch == (int)this)
		g_currentAptOnlineCustomMatch = 0;
	if (g_Va00E063F8)
		g_Va00E063F8->m_2C.rva002B7250((CreateAHeroData *)static_cast<Rva0059EB41 *>(this));
}
