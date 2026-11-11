// Opaque member ABI views use explicit Rva names. Target callee identities now known:
// +4 member cleanup at0x0033B1CD calls protected StringBase<unsigned short>::~StringBase at0x00036E70.
// +0xC member cleanup at0x005CDDF0 calls Coord2D::~Coord2D at0x000B3FD0.
// Holder identity and complete member layouts remain unproven; only access offsets and call ABI are claimed.
// Family-7 tail pairs (20B each): each holder method calls first() on
// itself, then tail-calls second() on a member (three members at positive
// offsets, one reached at this-8). first/second are opaque address-named
// pins; holder, member and callee identities are unproven.
class Rva0004378DMember
{
public:
	void second();
};

class Rva00043511
{
public:
	void rva0004353C();
};

class Display
{
public:
	void update();
};

class Rva0004378D
{
public:
	void method();
	void first();
private:
	char m_pad[0x280];
	Rva0004378DMember m_280; // +0x280
};

void Rva0004378D::method()
{
	((Display *)this)->update();
	((Rva00043511 *)&m_280)->rva0004353C();
}

class Rva0033B1CDMbr
{
public:
	void second();
};

class Rva0033B1CD
{
public:
	void method();
	void first();
private:
	int m_pad;
	Rva0033B1CDMbr m_04; // +4
};


class Rva005CDDF0Mbr
{
public:
	void second();
};

#include "../../Include/GameClient/Drawable.h"

class Rva005E590F
{
public:
	void rva005E590F();
};

class Rva005CDDF0
{
public:
	void method();
	void first();
private:
	char m_pad[0xC];
	Rva005CDDF0Mbr m_0C; // +0xC
};

void Rva005CDDF0::method()
{
	((Rva005E590F *)this)->rva005E590F();
	((Drawable *)&m_0C)->rva000B3FD0();
}


class Rva005E549E
{
public:
	virtual void rva005E549E();
};

#include "../../Include/Common/Rva005F327ARun.h"

class Rva005E5554
{
public:
	void method();
	void first();
};

void Rva005E5554::method()
{
	((Rva005E549E *)this)->Rva005E549E::rva005E549E();
	((Rva005F327ARun *)((char *)this - 8))->run();
}
