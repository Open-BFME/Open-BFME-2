// cl: /MD
// ?rva00051CF1@Rva00051CF1@@QAE_NAAV1@@Z @0x00051CF1 49B
// Honest-address 5-element array equals via rowed ?rva00051CBA@Rva00051CBA@@QAEHABV1@@Z.
// Evidence: chain packet calls 0x00051CBA; loop bumps esi by 0x10 five times; caller 0x00052B53.
struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Coord3D : public Coord3DBase
{
public:
	bool equals(const Coord3DBase &that) const;
};

class Rva00051CBA
{
public:
	int rva00051CBA(const Rva00051CBA &other);

private:
	Coord3D m_coord;
	unsigned char m_flag0C;
	char m_pad0D[3];
};

class Rva00051CF1
{
public:
	bool rva00051CF1(Rva00051CF1 &other);

private:
	Rva00051CBA m_items[5];
};

bool Rva00051CF1::rva00051CF1(Rva00051CF1 &other)
{
	for (int i = 0; i < 5; ++i)
	{
		if ((unsigned char)other.m_items[i].rva00051CBA(m_items[i]) == 0)
			return false;
	}
	return true;
}
