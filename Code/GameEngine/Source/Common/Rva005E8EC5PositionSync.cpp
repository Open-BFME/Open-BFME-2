// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ?rva005E8EC5@Rva005E8EC5@@QAEXXZ, retail 0x005E8EC5..0x005E8F49 (132 bytes,
// plain RET). WorldBuilder's twin 0x01608500 is unnamed, so every name here
// is address-derived. The member at +0x08 is the object whose count
// (0x005F8408), clear (0x005F884D), position setter (0x005F83F4) and notify
// (0x005F8427) are rowed. When it holds entries it is cleared unless the
// target at +0x04 has a zero +0x20 and its +0x1C gate (0x003F07CE) passes.
// The target's 2-D position at +0x28 is then lifted to 3-D (z = 0) through
// the +0x00 host's rowed 0x002BF5B0, stored through the setter and
// announced. The earlier blocked verdict predates those callee rows.

#include "../../../Libraries/Include/Lib/Coord2D.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

struct Rva005F83F4Data
{
	int m_data[3];
};

class Rva002D3627Host
{
public:
	bool rva002BF5B0(const Coord2D *in, Coord3D *out);
};

class Rva003F07CEOwner
{
public:
	bool rva003F07CE();
};

class Rva005F8427
{
public:
	int rva005F8408() const;
	void rva005F8427();
};

class Rva005F884D
{
public:
	void rva005F884D();
};

class Rva005F83F4
{
public:
	void rva005F83F4(const Rva005F83F4Data &src);
};

struct Rva005E8EC5Target
{
	unsigned char m_pad00[0x1C];
	Rva003F07CEOwner *m_gate1C;
	int m_20;
	unsigned char m_pad24[4];
	Coord2D m_position28;
};

class Rva005E8EC5
{
public:
	void rva005E8EC5();

private:
	Rva002D3627Host *m_host00;
	Rva005E8EC5Target *m_target04;
	unsigned char m_member08[4];
};

void Rva005E8EC5::rva005E8EC5()
{
	if (reinterpret_cast<Rva005F8427 *>(m_member08)->rva005F8408() > 0)
	{
		if (m_target04->m_20 != 0 || !m_target04->m_gate1C->rva003F07CE())
			reinterpret_cast<Rva005F884D *>(m_member08)->rva005F884D();
	}
	const Coord2D &source = m_target04->m_position28;
	Coord2D position;
	position.x = source.x;
	position.y = source.y;
	Coord3D lifted;
	lifted.x = position.x;
	lifted.y = position.y;
	lifted.z = 0.0f;
	m_host00->rva002BF5B0(&position, &lifted);
	reinterpret_cast<Rva005F83F4 *>(m_member08)->rva005F83F4(*reinterpret_cast<const Rva005F83F4Data *>(&lifted));
	reinterpret_cast<Rva005F8427 *>(m_member08)->rva005F8427();
}
