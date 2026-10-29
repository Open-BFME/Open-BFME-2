// cl: /DNDEBUG /MD /EHsc /Oy-
//
// Wave-3 F22 shape family: ebp-frame forwarders. Each body passes its first
// two stack args through to a pinned thiscall callee plus a pointer computed
// as (char*)&second_param + 3 (observed `lea eax,[ebp+0xF]`), then cleans
// its own 8 or 12 bytes (ret 8 / ret 0xC). The callee (`ret 0xC`) never reads
// its third stack slot -- a vestigial parameter -- and takes `this` straight
// from the wrapper's ecx, so each wrapper is a method of an opaque class
// cast to the callee's class. Identities beyond these shapes are not
// recovered.
//

class Rva001EF83A
{
public:
	void rva001EF83A(int a, int b, char *p);
};

class Rva001EFC42
{
public:
	void rva001EFC42(int a, int b, int c);
};


class Rva0018C73C
{
public:
	void rva0018C73C(int a, int b, char *p);
};

class Rva0018C822
{
public:
	void assign(int first, int last, int c);
};

void Rva0018C822::assign(int first, int last, int c)
{
	((Rva0018C73C *)this)->rva0018C73C(first, last, (char *)&last + 3);
}

class Rva0018C838
{
public:
	void rva0018C838(int first, int last);
};

void Rva0018C838::rva0018C838(int first, int last)
{
	((Rva0018C73C *)this)->rva0018C73C(first, last, (char *)&last + 3);
}

class Rva001DA112
{
public:
	void rva001DA112(int a, int b, char *p);
};

class Rva001DA73E
{
public:
	void rva001DA73E(int first, int last, int c);
};

void Rva001DA73E::rva001DA73E(int first, int last, int c)
{
	((Rva001DA112 *)this)->rva001DA112(first, last, (char *)&last + 3);
}

class Rva001DAB29
{
public:
	void rva001DAB29(int first, int last);
};

void Rva001DAB29::rva001DAB29(int first, int last)
{
	((Rva001DA112 *)this)->rva001DA112(first, last, (char *)&last + 3);
}

class Rva00569F0C
{
public:
	void rva00569F0C(int a, int b, char *p);
};

class Rva0056A2DE
{
public:
	void rva0056A2DE(int first, int last, int c);
};

void Rva0056A2DE::rva0056A2DE(int first, int last, int c)
{
	((Rva00569F0C *)this)->rva00569F0C(first, last, (char *)&last + 3);
}

class Rva0056A362
{
public:
	void rva0056A362(int first, int last);
};

void Rva0056A362::rva0056A362(int first, int last)
{
	((Rva00569F0C *)this)->rva00569F0C(first, last, (char *)&last + 3);
}

class Rva005F4F74
{
public:
	void rva005F4F74(int a, int b, char *p);
};

class Rva005F50A3
{
public:
	void rva005F50A3(int a, int b, int c);
};


class Rva005F50D3
{
public:
	void rva005F50D3(int a, int b);
};

// 0x002B2955 (15B): the same ebp frame around a tail jump: the seven stack
// arguments go unchanged to the rowed
// LivingWorldRegionManager::SetRegionReinforcements (0x0020EEC8) on the
// manager at +0xB0 of the receiver (TheLivingWorldLogic keeps its region
// manager there; the receiver's class is not established).
class LivingWorldRegionManager
{
public:
	void SetRegionReinforcements(int a, int b, int c, int d, int e, int f, int g);
};

class Rva002B2955
{
public:
	void rva002B2955(int regionID, int reinforcements, int c, int d, int e, int f, int g);
private:
	char m_pad00[0xB0];
	LivingWorldRegionManager *m_regionManager; // +0xB0
};

void Rva002B2955::rva002B2955(int regionID, int reinforcements, int c, int d, int e, int f, int g)
{
	m_regionManager->SetRegionReinforcements(regionID, reinforcements, c, d, e, f, g);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0018C73C reads ?assign@Rva0018C73CWordVector@@QAEXURva005E59FCKeyIterator@@0ABUforward_iterator_tag@_STL@@@Z
#pragma comment(linker, "/alternatename:?rva0018C73C@Rva0018C73C@@QAEXHHPAD@Z=?assign@Rva0018C73CWordVector@@QAEXURva005E59FCKeyIterator@@0ABUforward_iterator_tag@_STL@@@Z")
//   0x00569F0C reads ?rva00569F0C@Rva00569F0CVec@@QAEXPAX0PA_N@Z
#pragma comment(linker, "/alternatename:?rva00569F0C@Rva00569F0C@@QAEXHHPAD@Z=?rva00569F0C@Rva00569F0CVec@@QAEXPAX0PA_N@Z")
