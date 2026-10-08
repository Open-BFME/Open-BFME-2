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
//   0x001EC98E +0x10 -> Rva001EC63DNullTarget::rva001EC63D (0 arg)
//   0x00068061 +0x3854 -> Rva000E7734NullTarget::rva000E7734 (1 arg)
//   0x00068283 +0x3850 -> Rva000EA2C0NullTarget::rva000EA2C0 (1 arg)
//   0x00068395 +0x3860 -> Rva000E6005NullTarget::rva000E6005 (5 arg)
//   0x005CD9F2 +0x1C -> Rva005E58EDNullTarget::rva005E58ED (0 arg)
//   0x005CDD25 +0x24 -> Rva005E58EDNullTarget::rva005E58ED (0 arg)
//   0x005CE9F7 +0x10 -> Rva005E88DDNullTarget::rva005E88DD (0 arg)
//   0x005CEA04 +0x10 -> Rva005E8F49NullTarget::rva005E8F49 (0 arg)
//   0x00068385 +0x3858 -> Rva000EE198NullTarget::rva000EE198 (0 arg)
//   0x00068D43 +0x3850 -> Rva000EDB47NullTarget::rva000EDB47 (0 arg)
//   0x0007E17B +0x100 -> Rva0010004DNullTarget::rva0010004D (1 arg)

typedef int Int;

class ShellMenuScheme
{
public:
	void draw();
};

class Rva0020065ANullForwarder
{
public:
	void rva0020065A();
private:
	char m_lead[0x4];
	ShellMenuScheme *m_member;
};

void Rva0020065ANullForwarder::rva0020065A()
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

void Rva002722F4NullForwarder::rva002722F4(Int a0)
{
	if (m_member)
		m_member->rva0027006C(a0);
}

class Rva001EC63DNullTarget
{
public:
	void rva001EC63D();
};

class Rva0023D6D5Callee
{
public:
	void thru();
private:
	char m_lead[0x10];
	Rva001EC63DNullTarget *m_member;
};

void Rva0023D6D5Callee::thru()
{
	if (m_member)
		m_member->rva001EC63D();
}

class Rva000E7734NullTarget
{
public:
	void rva000E7734(Int a0);
};

class Rva00068061NullTarget
{
public:
	void rva00068061(Int a0);
private:
	char m_lead[0x3854];
	Rva000E7734NullTarget *m_member;
};

void Rva00068061NullTarget::rva00068061(Int a0)
{
	if (m_member)
		m_member->rva000E7734(a0);
}

class Rva000EA2C0NullTarget
{
public:
	void rva000EA2C0(Int a0);
};

class Rva00068283NullTarget
{
public:
	void rva00068283(Int a0);
private:
	char m_lead[0x3850];
	Rva000EA2C0NullTarget *m_member;
};

void Rva00068283NullTarget::rva00068283(Int a0)
{
	if (m_member)
		m_member->rva000EA2C0(a0);
}

class Rva005E58EDNullTarget
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
	Rva005E58EDNullTarget *m_member;
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
	Rva005E58EDNullTarget *m_member;
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

class Rva005E8F49NullTarget
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
	Rva005E8F49NullTarget *m_member;
};

void Rva005CEA04NullForwarder::rva005CEA04()
{
	if (m_member)
		m_member->rva005E8F49();
}

class Rva000EE198NullTarget
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
	Rva000EE198NullTarget *m_member;
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


class Rva0010004DNullTarget
{
public:
	void rva0010004D(Int a0);
};

class Rva0007E17BNullForwarder
{
public:
	void rva0007E17B(Int a0);
private:
	char m_lead[0x100];
	Rva0010004DNullTarget *m_member;
};

void Rva0007E17BNullForwarder::rva0007E17B(Int a0)
{
	if (m_member)
		m_member->rva0010004D(a0);
}

// Two more with a ret 4 tail: 0x000B22E4 +0x4 -> rowed Shadow::rva00330995
// (1 arg); 0x004FC176 +0x20 -> 0x004E0D19 (1 arg, address-derived pin).
class Shadow
{
public:
	void rva00330995(Int a0);
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
		m_member->rva00330995(a0);
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

void *Rva001EC99B::rva001EC99B(Int a0, Int a1)
{
	if (m_member)
		return m_member->rva001EC859(a0, a1);
	return 0;
}

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

bool Rva001EC9AC::rva001EC9AC(Int a0, Int a1, Int a2)
{
	if (m_member)
		return m_member->rva001EC8C0(a0, a1, a2);
	return false;
}

class AsciiString;

class Rva000E6005NullTarget
{
public:
	void rva000E6005(Int a0, AsciiString *a1, AsciiString *a2, bool a3, bool a4);
};

class BaseHeightMapRenderObjClass
{
public:
	void rva00068395(Int a0, AsciiString *a1, AsciiString *a2, bool a3, bool a4);
private:
	char m_lead[0x3860];
	Rva000E6005NullTarget *m_member;
};

void BaseHeightMapRenderObjClass::rva00068395(Int a0, AsciiString *a1, AsciiString *a2, bool a3, bool a4)
{
	if (m_member)
		m_member->rva000E6005(a0, a1, a2, a3, a4);
}
