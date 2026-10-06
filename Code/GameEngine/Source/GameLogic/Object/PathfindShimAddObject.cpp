// cl: /DNDEBUG /MD /EHsc
// ?addObjectToPathfindMap@BFMEPathfinderMapShim@@QAEXPAVObject@@@Z @0x002E7178
// ?rva002E718A@BFMEPathfinderMapShim@@QAEXPAVObject@@@Z @0x002E718A 17B: adjacent sibling
// Shard TU: friend_notifyOfNewMapBoundary lives in
// Object_friendNotifyOfNewMapBoundary.cpp under /Oy- frames; this frameless
// leaf needs no frame so it lives here. Second body abuts first and forwards
// to same helper with 0 0 0 vs 1 0 0; same class proven by adjacency and shape.

class Object;

void __stdcall Rva00530212Helper(Object *object, int a1, int a2, int a3);

class Rva0036666B
{
public:
	bool rva0036666B();
};

class Rva00366561
{
public:
	bool rva00366561(int a, int b);
};

class BFMEPathfinderMapShim
{
public:
	void addObjectToPathfindMap(Object *object);
	void rva002E718A(Object *object);
	void rva002E719B(Object *object);
	void rva002E71AD(Object *object);
	int rva002E71BF(int arg);
private:
	char m_pad00[0x60];
	struct Slot { char bytes[0x40]; };
	Slot m_slots[16];
};

// ?addObjectToPathfindMap@BFMEPathfinderMapShim@@QAEXPAVObject@@@Z
void BFMEPathfinderMapShim::addObjectToPathfindMap(Object *object)
{
	Rva00530212Helper(object, 1, 0, 0);
}

void BFMEPathfinderMapShim::rva002E718A(Object *object)
{
	Rva00530212Helper(object, 0, 0, 0);
}

void BFMEPathfinderMapShim::rva002E719B(Object *object)
{
	Rva00530212Helper(object, 0, 0, 1);
}

void BFMEPathfinderMapShim::rva002E71AD(Object *object)
{
	Rva00530212Helper(object, 0, 1, 0);
}

// ?rva002E71BF@BFMEPathfinderMapShim@@QAEHH@Z @0x002E71BF 70B
// Evidence: unlock lane; callees rowed 0x0036666B 0x00366561; callers 0x002802E3 0x002812A4; array +0x60 stride 0x40 indices 2..15.
int BFMEPathfinderMapShim::rva002E71BF(int arg)
{
	int i = 2;
	Slot *p = &m_slots[2];
	for (; i <= 0xf; ++i, ++p) {
		if (!((Rva0036666B *)p)->rva0036666B())
			goto second;
	}
	return 1;
second:
	if (!((Rva00366561 *)&m_slots[i])->rva00366561(arg, i))
		return 1;
	return i;
}
