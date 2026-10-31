// cl: /DNDEBUG /MD
//
// More null-checked member-pointer forwarders (VslotNullCheckedForwarders.cpp
// shape, found by a .text byte scan of unowned starts): load the pointer at
// +N and when set tail-jump to one method with the caller's stack arguments
// (ret N gives the count). Rowed targets keep their row spellings
// (ShellMenuScheme::draw, W3DPropBuffer::removeProp, Rva000D3A17,
// Rva00270025::rva0027006C); forwarders that already carry a pin keep it
// (Rva0023D6D5Callee::thru, Rva00068061NullTarget, Rva00068283NullTarget);
// unrowed targets arrive as address-derived pins. Layout per forwarder:
//   0x0020065A +0x4 -> ShellMenuScheme::draw (0 arg)
//   0x00068373 +0x3858 -> W3DPropBuffer::removeProp (1 arg)
//   0x000682FA +0x3874 -> Rva000D3A17::rva000D3A17 (0 arg)
//   0x002722F4 +0x354 -> Rva00270025::rva0027006C (1 arg)
//   0x001EC98E +0x10 -> LinearCampaign::addCarryoverStuffToMap (0 arg)
//   0x00068061 +0x3854 -> W3DShrubBuffer::rva000E7734 (1 arg)
//   0x00068283 +0x3850 -> W3DTreeBuffer::rva000EA2C0 (1 arg)
//   0x00068395 +0x3860 -> W3DFloorBuffer::rva000E6005 (5 arg)
//   0x005CD9F2 +0x1C -> Rva005E58ED::rva005E58ED (0 arg)
//   0x005CDD25 +0x24 -> Rva005E58ED::rva005E58ED (0 arg)
//   0x005CE9F7 +0x10 -> Rva005E88DDNullTarget::rva005E88DD (0 arg)
//   0x005CEA04 +0x10 -> Rva005E8F49Owner::rva005E8F49 (0 arg)
//   0x00068385 +0x3858 -> Rva000EE198Owner::rva000EE198 (0 arg)
//   0x00068D43 +0x3850 -> Rva000EDB47NullTarget::rva000EDB47 (0 arg)
//   0x0007E17B +0x100 -> WaterTracksRenderSystem::rva0010004D (1 arg)

typedef int Int;

class ShellMenuScheme
{
public:
	void draw();
};

class Rva0020065ANullForwarder
{
public:
	void draw();
private:
	char m_lead[0x4];
	ShellMenuScheme *m_member;
};

void Rva0020065ANullForwarder::draw()
{
	if (m_member)
		m_member->draw();
}

class W3DPropBuffer
{
public:
	void removeProp(Int a0);
};

class Rva00068373NullForwarder
{
public:
	void rva00068373(Int a0);
private:
	char m_lead[0x3858];
	W3DPropBuffer *m_member;
};

void Rva00068373NullForwarder::rva00068373(Int a0)
{
	if (m_member)
		m_member->removeProp(a0);
}

class Rva000D3A17
{
public:
	void rva000D3A17();
};

class Rva000682FANullForwarder
{
public:
	void rva000682FA();
private:
	char m_lead[0x3874];
	Rva000D3A17 *m_member;
};

void Rva000682FANullForwarder::rva000682FA()
{
	if (m_member)
		m_member->rva000D3A17();
}

class Rva00270025
{
public:
	void rva0027006C(Int a0);
};

class Rva002722F4NullForwarder
{
public:
	void rva002722F4(Int a0);
private:
	char m_lead[0x354];
	Rva00270025 *m_member;
};

class LinearCampaign
{
public:
	void addCarryoverStuffToMap();
};

class Rva0023D6D5Callee
{
public:
	void thru();
private:
	char m_lead[0x10];
	LinearCampaign *m_member;
};

class Thing;
class W3DShrubBuffer
{
public:
	void rva000E7734(Thing *a0);
};

class Rva00068061NullTarget
{
public:
	void rva00068061(Int a0);
private:
	char m_lead[0x3854];
	W3DShrubBuffer *m_member;
};

void Rva00068061NullTarget::rva00068061(Int a0)
{
	if (m_member)
		m_member->rva000E7734((Thing *)a0);
}

class W3DTreeBuffer
{
public:
	void rva000EA2C0(void *a0);
};

class Rva00068283NullTarget
{
public:
	void rva00068283(Int a0);
private:
	char m_lead[0x3850];
	W3DTreeBuffer *m_member;
};

void Rva00068283NullTarget::rva00068283(Int a0)
{
	if (m_member)
		m_member->rva000EA2C0((void *)a0);
}

class Rva005E58ED
{
public:
	void rva005E58ED();
};

class Rva005CD9F2NullForwarder
{
public:
	void rva005CD9F2();
private:
	char m_lead[0x1C];
	Rva005E58ED *m_member;
};

void Rva005CD9F2NullForwarder::rva005CD9F2()
{
	if (m_member)
		m_member->rva005E58ED();
}

class Rva005CDD25NullForwarder
{
public:
	void rva005CDD25();
private:
	char m_lead[0x24];
	Rva005E58ED *m_member;
};

void Rva005CDD25NullForwarder::rva005CDD25()
{
	if (m_member)
		m_member->rva005E58ED();
}

class Rva005E88DDNullTarget
{
public:
	void rva005E88DD();
};

class Rva005CE9F7NullForwarder
{
public:
	void rva005CE9F7();
private:
	char m_lead[0x10];
	Rva005E88DDNullTarget *m_member;
};

void Rva005CE9F7NullForwarder::rva005CE9F7()
{
	if (m_member)
		m_member->rva005E88DD();
}

class Rva005E8F49Owner
{
public:
	void rva005E8F49();
};

class Rva005CEA04NullForwarder
{
public:
	void rva005CEA04();
private:
	char m_lead[0x10];
	Rva005E8F49Owner *m_member;
};

void Rva005CEA04NullForwarder::rva005CEA04()
{
	if (m_member)
		m_member->rva005E8F49();
}

class Rva000EE198Owner
{
public:
	void rva000EE198();
};

class Rva00068385NullForwarder
{
public:
	void rva00068385();
private:
	char m_lead[0x3858];
	Rva000EE198Owner *m_member;
};

void Rva00068385NullForwarder::rva00068385()
{
	if (m_member)
		m_member->rva000EE198();
}

class Rva000EDB47NullTarget
{
public:
	void rva000EDB47();
};

class Rva00068D43NullForwarder
{
public:
	void rva00068D43();
private:
	char m_lead[0x3850];
	Rva000EDB47NullTarget *m_member;
};


class RenderInfoClass;
class WaterTracksRenderSystem
{
public:
	void flush(RenderInfoClass &a0);
};

class Rva0007E17BNullForwarder
{
public:
	void rva0007E17B(Int a0);
private:
	char m_lead[0x100];
	WaterTracksRenderSystem *m_member;
};

void Rva0007E17BNullForwarder::rva0007E17B(Int a0)
{
	if (m_member)
		m_member->flush(*(RenderInfoClass *)a0);
}

// Two more with a ret 4 tail: 0x000B22E4 +0x4 -> rowed Shadow::setColor
// (1 arg); 0x004FC176 +0x20 -> 0x004E0D19 (1 arg, address-derived pin).
class Shadow
{
public:
	void setColor(Int a0);
};

class Rva000B22E4NullForwarder
{
public:
	void rva000B22E4(Int a0);
private:
	char m_lead[0x4];
	Shadow *m_member;
};

void Rva000B22E4NullForwarder::rva000B22E4(Int a0)
{
	if (m_member)
		m_member->setColor(a0);
}

class Rva004E0D19NullTarget
{
public:
	void rva004E0D19(Int a0);
};

class Rva004FC176NullForwarder
{
public:
	void rva004FC176(Int a0);
private:
	char m_lead[0x20];
	Rva004E0D19NullTarget *m_member;
};


// Three more null-checked direct forwarders from the wide family scan. The
// wrapper identities and the two unrowed callees remain address-derived; the
// third callee is the already-rowed AITargetChooser::rva00505408. Field offsets
// and return/argument shapes come from each retail body.
class Rva001EC859
{
public:
	void *rva001EC859(Int a0, Int a1);
};

class Rva001EC99B
{
public:
	void *rva001EC99B(Int a0, Int a1);
private:
	char m_lead[0x10];
	Rva001EC859 *m_member;
};

class Rva001EC8C0
{
public:
	bool rva001EC8C0(Int a0, Int a1, Int a2);
};

class Rva001EC9AC
{
public:
	bool rva001EC9AC(Int a0, Int a1, Int a2);
private:
	char m_lead[0x10];
	Rva001EC8C0 *m_member;
};

class AsciiString;

class Gen_uw_000e5033;
class W3DFloorBuffer
{
public:
	Gen_uw_000e5033 *addFloor(Int a0, AsciiString *a1, AsciiString *a2, bool a3, bool a4);
};

class BaseHeightMapRenderObjClass
{
public:
	void rva00068395(Int a0, AsciiString *a1, AsciiString *a2, bool a3, bool a4);
private:
	char m_lead[0x3860];
	W3DFloorBuffer *m_member;
};

void BaseHeightMapRenderObjClass::rva00068395(Int a0, AsciiString *asciiString, AsciiString *a2, bool a3, bool a4)
{
	if (m_member)
		m_member->addFloor(a0, asciiString, a2, a3, a4);
}
