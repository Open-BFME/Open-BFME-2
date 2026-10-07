// cl: /O1 /G7 /arch:SSE /MD /EHsc

// ?rva00504E6D@Rva00504DF8@@QAE?AURva00504E6DResult@@PBX@Z 64B @0x00504E6D.
// Target facts: the body calls 0x005049C6 with its value pointer, compares
// the returned node to this+4, compares the first floats when the node is not
// the end, and conditionally calls 0x00504D57. The 8-byte return writes a
// node pointer and an inserted byte to the caller's result object.
// Structural inference: this view has a 16-byte range at offsets 0/4/8; the
// node value starts with a float. The class and value meanings stay unknown.
struct Rva00504DF8Value
{
	float m_key;
	char m_pad04[0x0c];
};

struct Rva00504E6DResult
{
	Rva00504E6DResult(void *node, bool inserted)
		: m_node(node), m_inserted(inserted) {}

	void *m_node;
	bool m_inserted;
};

class Rva00504DF8
{
public:
	void *rva005049C6(const void *value);
	void *rva00504D57(void *position, const void *value);
	Rva00504E6DResult rva00504E6D(const void *value);

private:
	void *m_begin;
	void *m_finish;
	void *m_capacity;
};

Rva00504E6DResult Rva00504DF8::rva00504E6D(const void *value)
{
	bool notInserted = true;
	void *position = rva005049C6(value);
	if (position == m_finish ||
		((Rva00504DF8Value *)position)->m_key > ((Rva00504DF8Value *)value)->m_key)
	{
		position = rva00504D57(position, value);
		notInserted = false;
	}

	return Rva00504E6DResult(position, !notInserted);
}

//
// 0x00504DF8 (64B): cursor-copy plus float clear. Copies +0x00/+0x04 from
// the source, advances the source cursor by 8 into the +0x08 subobject
// call (pinned 0x005048B5), copies +0x0C to +0x18, zeroes the four floats
// at +0x1C/+0x20/+0x24/+0x28 via one xorps, returns this. /arch:SSE for
// the movss stores (float TU precedent). Identities unproven.

class Rva005048B5
{
public:
	void rva005048B5(const void *p);
};

class Rva00504DF8Owner
{
public:
	Rva00504DF8Owner *rva00504DF8(const Rva00504DF8Owner *src);

private:
	int m_00;			// +0x00
	int m_04;			// +0x04
	Rva005048B5 m_08;		// +0x08
	char m_pad09[3];		// +0x09..0x0B
	int m_0C;			// +0x0C
	char m_pad10[8];		// +0x10..0x17
	int m_18;			// +0x18
	float m_1C;			// +0x1C
	float m_20;			// +0x20
	float m_24;			// +0x24
	float m_28;			// +0x28
};

Rva00504DF8Owner *Rva00504DF8Owner::rva00504DF8(const Rva00504DF8Owner *src)
{
	m_00 = src->m_00;
	m_04 = src->m_04;
	src = (const Rva00504DF8Owner *)((const char *)src + 8);
	m_08.rva005048B5(src);
	m_18 = m_0C;
	m_1C = m_20 = m_24 = m_28 = 0.0f;
	return this;
}

// ---- 0x00504E38 (53B): temp init plus conditional free, returning this.
// Builds an Rva00504DF8Owner temp from the source, runs the pinned
// 0x0050492F on this with the temp address, frees the dword at temp+8
// through rowed _free when nonzero. Outer identity unproven.
extern "C" void __cdecl free(void *block);

class Rva0050492F
{
public:
	void rva0050492F(Rva00504DF8Owner *tmp);
};

class Rva00504E38Owner
{
public:
	Rva00504E38Owner *rva00504E38(const Rva00504DF8Owner *src);
};

Rva00504E38Owner *Rva00504E38Owner::rva00504E38(const Rva00504DF8Owner *src)
{
	Rva00504DF8Owner tmp;
	tmp.rva00504DF8(src);
	((Rva0050492F *)this)->rva0050492F(&tmp);
	void *p = *(void **)((char *)&tmp + 8);
	if (p)
		free(p);
	return this;
}
