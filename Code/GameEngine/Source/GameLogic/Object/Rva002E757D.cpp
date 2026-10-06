// cl: /DNDEBUG /MD /EHsc
// ?rva002E757D@Rva002E757D@@QAE_NPBUCoord3D@@@Z @0x002E757D 38B
// Evidence: chain from Bridge::isPointOnBridge 0x0027EEAD; walks Bridge list head +0x5C next +0x04; callers 0x002803A3 0x002EF6C5.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Bridge
{
public:
	bool isPointOnBridge(const Coord3D *p);
	Bridge *getNext() { return m_next; }

private:
	char m_pad00[4];
	Bridge *m_next;
};

class Rva002E757D
{
public:
	bool rva002E757D(const Coord3D *p);

private:
	char m_pad00[0x5C];
	Bridge *m_head;
};

bool Rva002E757D::rva002E757D(const Coord3D *p)
{
	for (Bridge *b = m_head; b; b = b->getNext()) {
		if (b->isPointOnBridge(p))
			return true;
	}
	return false;
}
