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
	void rva0018C822(int a, int b, int c);
};

void Rva0018C822::rva0018C822(int a, int b, int c)
{
	((Rva0018C73C *)this)->rva0018C73C(a, b, (char *)&b + 3);
}

class Rva0018C838
{
public:
	void rva0018C838(int a, int b);
};

void Rva0018C838::rva0018C838(int a, int b)
{
	((Rva0018C73C *)this)->rva0018C73C(a, b, (char *)&b + 3);
}

class Rva001DA112
{
public:
	void rva001DA112(int a, int b, char *p);
};

class Rva001DA73E
{
public:
	void rva001DA73E(int a, int b, int c);
};

void Rva001DA73E::rva001DA73E(int a, int b, int c)
{
	((Rva001DA112 *)this)->rva001DA112(a, b, (char *)&b + 3);
}

class Rva001DAB29
{
public:
	void rva001DAB29(int a, int b);
};

void Rva001DAB29::rva001DAB29(int a, int b)
{
	((Rva001DA112 *)this)->rva001DA112(a, b, (char *)&b + 3);
}

class Rva00569F0C
{
public:
	void rva00569F0C(int a, int b, char *p);
};

class Rva0056A2DE
{
public:
	void rva0056A2DE(int a, int b, int c);
};

void Rva0056A2DE::rva0056A2DE(int a, int b, int c)
{
	((Rva00569F0C *)this)->rva00569F0C(a, b, (char *)&b + 3);
}

class Rva0056A362
{
public:
	void rva0056A362(int a, int b);
};

void Rva0056A362::rva0056A362(int a, int b)
{
	((Rva00569F0C *)this)->rva00569F0C(a, b, (char *)&b + 3);
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
