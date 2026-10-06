// cl: /MD
// ??0Rva00080221@@QAE@PBH@Z, retail 0x00080221 (53B).
// Honest-address ctor for an unknown ref-counted wrapper (12B impl with
// vtable VA 0x00BC6FF4 at +0, refcount at +4, int value at +8). Evidence:
// stores vtable 0x007C6FF4, calls rowed operator new ??2@YAPAXI@Z at
// 0x0002FDA0 with null check (push 0xC + test + je + xor), copies *arg to
// +8, publishes impl to [this+0] then bumps refcount 0->1 via inc [eax+4],
// returns this (mov eax,esi, ret 4). 19 callers including 0x0007FFED which
// builds a stack temp for ReflectionTexture/BlendUsingTerrainAlpha/
// TransparentWaterDepth dispatch. Neighbours are STLport WWLib TUs; new TU
// uses /O1 /MD per manual-vtable ctor precedent Rva00575540Ctor.cpp.
void *__cdecl operator new(unsigned int size);

// The impl is a class over a ref-counted base with an inline empty destructor,
// so its vtable (VA 0x00BC6FF4 in retail) is emitted and resolved in this unit
// rather than written as an address. The base ctor zeroes the count, then the
// derived vtable store, then the value, as retail orders the stores.
struct Rva00080221RefImpl
{
	virtual ~Rva00080221RefImpl() {}
	int m_ref;
	Rva00080221RefImpl() : m_ref(0) {}
};

struct Rva007C6FF4Impl : Rva00080221RefImpl
{
	int m_value;
	Rva007C6FF4Impl(const int &value) : m_value(value) {}
};

class Rva00080221
{
public:
	Rva00080221(const int *arg);
private:
	Rva007C6FF4Impl *m_impl;
};

Rva00080221::Rva00080221(const int *arg)
{
	Rva007C6FF4Impl *p = new Rva007C6FF4Impl(*arg);
	m_impl = p;
	if (p != 0)
		++p->m_ref;
}

// Seven more constructors of this 53-byte shape, each installing its own impl
// vtable (the only differing operand; no other unit references these vtables):
// 0x00211E75 (VA 0xbe5128), 0x002D4594 (VA 0xc02aec), 0x002D45C9 (VA 0xc02af4),
// 0x002D45FE (VA 0xc02afc), 0x004106FA (VA 0xc39634), 0x0044BC76 (VA 0xc3ed7c), 0x005773DB (VA 0xc6e970).
// Each impl is a class over the same ref-counted base. Owners keep their
// addresses.

// ??0Rva00211E75@@QAE@PBH@Z @0x00211E75 53B, impl vtable VA 0xbe5128
struct Impl00211E75 : Rva00080221RefImpl
{
	int m_value;
	Impl00211E75(const int &value) : m_value(value) {}
};

class Rva00211E75
{
public:
	Rva00211E75(const int *arg);
private:
	Impl00211E75 *m_impl;
};

Rva00211E75::Rva00211E75(const int *arg)
{
	Impl00211E75 *p = new Impl00211E75(*arg);
	m_impl = p;
	if (p != 0)
		++p->m_ref;
}

// ??0Rva002D4594@@QAE@PBH@Z @0x002D4594 53B, impl vtable VA 0xc02aec
struct Impl002D4594 : Rva00080221RefImpl
{
	int m_value;
	Impl002D4594(const int &value) : m_value(value) {}
};

class Rva002D4594
{
public:
	Rva002D4594(const int *arg);
private:
	Impl002D4594 *m_impl;
};

Rva002D4594::Rva002D4594(const int *arg)
{
	Impl002D4594 *p = new Impl002D4594(*arg);
	m_impl = p;
	if (p != 0)
		++p->m_ref;
}

// ??0Rva002D45C9@@QAE@PBH@Z @0x002D45C9 53B, impl vtable VA 0xc02af4
struct Impl002D45C9 : Rva00080221RefImpl
{
	int m_value;
	Impl002D45C9(const int &value) : m_value(value) {}
};

class Rva002D45C9
{
public:
	Rva002D45C9(const int *arg);
private:
	Impl002D45C9 *m_impl;
};

Rva002D45C9::Rva002D45C9(const int *arg)
{
	Impl002D45C9 *p = new Impl002D45C9(*arg);
	m_impl = p;
	if (p != 0)
		++p->m_ref;
}

// ??0Rva002D45FE@@QAE@PBH@Z @0x002D45FE 53B, impl vtable VA 0xc02afc
struct Impl002D45FE : Rva00080221RefImpl
{
	int m_value;
	Impl002D45FE(const int &value) : m_value(value) {}
};

class Rva002D45FE
{
public:
	Rva002D45FE(const int *arg);
private:
	Impl002D45FE *m_impl;
};

Rva002D45FE::Rva002D45FE(const int *arg)
{
	Impl002D45FE *p = new Impl002D45FE(*arg);
	m_impl = p;
	if (p != 0)
		++p->m_ref;
}

// ??0Rva004106FA@@QAE@PBH@Z @0x004106FA 53B, impl vtable VA 0xc39634
struct Impl004106FA : Rva00080221RefImpl
{
	int m_value;
	Impl004106FA(const int &value) : m_value(value) {}
};

class Rva004106FA
{
public:
	Rva004106FA(const int *arg);
private:
	Impl004106FA *m_impl;
};

Rva004106FA::Rva004106FA(const int *arg)
{
	Impl004106FA *p = new Impl004106FA(*arg);
	m_impl = p;
	if (p != 0)
		++p->m_ref;
}

// ??0Rva0044BC76@@QAE@PBH@Z @0x0044BC76 53B, impl vtable VA 0xc3ed7c
struct Impl0044BC76 : Rva00080221RefImpl
{
	int m_value;
	Impl0044BC76(const int &value) : m_value(value) {}
};

class Rva0044BC76
{
public:
	Rva0044BC76(const int *arg);
private:
	Impl0044BC76 *m_impl;
};

Rva0044BC76::Rva0044BC76(const int *arg)
{
	Impl0044BC76 *p = new Impl0044BC76(*arg);
	m_impl = p;
	if (p != 0)
		++p->m_ref;
}

// ??0Rva005773DB@@QAE@PBH@Z @0x005773DB 53B, impl vtable VA 0xc6e970
struct Impl005773DB : Rva00080221RefImpl
{
	int m_value;
	Impl005773DB(const int &value) : m_value(value) {}
};

class Rva005773DB
{
public:
	Rva005773DB(const int *arg);
private:
	Impl005773DB *m_impl;
};

Rva005773DB::Rva005773DB(const int *arg)
{
	Impl005773DB *p = new Impl005773DB(*arg);
	m_impl = p;
	if (p != 0)
		++p->m_ref;
}
