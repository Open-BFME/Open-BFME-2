// cl: /DNDEBUG /MD
//
// Guarded three-test field query at retail 0x002A7588 (48 bytes).
// Dedicated TU beside the neighbour Rva002A73B8Dtor.cpp row block, whose
// // cl: line is copied above.
//
// Retail reads a pointer argument, follows its +0x4 link, then requires bit
// 0x02 set and the sign bit clear in the dword at +0x108 plus bit 0x20 clear
// in the byte at +0x115 before returning the dword at +0x618, else 0. Callers
// are the 17B add/sub wrappers at 0x002A75B8/0x002A75C9. The owning classes
// are unproven, so the ledger name claims only the address plus the
// witnessed shape; no calls, so the gate resolves it directly.

struct Rva002A7588Mid
{
	char m_pad[0x108];
	int m_flags108; // +0x108
	char m_pad10C[9]; // 0x10C..0x114
	unsigned char m_b115; // +0x115
	char m_pad116[0x618 - 0x116];
	int m_i618; // +0x618
};

struct Rva002A7588In
{
	char m_pad[4];
	Rva002A7588Mid *m_p4; // +0x4
};

class Rva002A7588
{
public:
	int rva002A7588(Rva002A7588In *p);
};

int Rva002A7588::rva002A7588(Rva002A7588In *p)
{
	if (p == 0)
		return 0;
	Rva002A7588Mid *q = p->m_p4;
	if ((q->m_flags108 & 2) == 0)
		return 0;
	if ((q->m_flags108 & 0x80) != 0)
		return 0;
	if ((q->m_b115 & 0x20) != 0)
		return 0;
	return q->m_i618;
}

// Add wrapper at retail 0x002A75B8 (17 bytes): forwards this plus its own
// argument to the query above and accumulates the result into the dword at
// +0x8. Sole caller 0x002A9B50. Owning class unproven: opaque holder.

class Rva002A75B8
{
public:
	int rva002A75B8(Rva002A7588In *p);

private:
	char m_lead[8];
	int m_i8; // +0x08
};

int Rva002A75B8::rva002A75B8(Rva002A7588In *p)
{
	Rva002A7588 *self = reinterpret_cast<Rva002A7588 *>(this);
	int v = self->rva002A7588(p);
	m_i8 += v;
	return v;
}

// Sub wrapper at retail 0x002A75C9 (17 bytes): same shape, subtracts.
// Sole caller 0x002A9B73. Opaque holder.

class Rva002A75C9
{
public:
	int rva002A75C9(Rva002A7588In *p);

private:
	char m_lead[8];
	int m_i8; // +0x08
};

int Rva002A75C9::rva002A75C9(Rva002A7588In *p)
{
	Rva002A7588 *self = reinterpret_cast<Rva002A7588 *>(this);
	int v = self->rva002A7588(p);
	m_i8 -= v;
	return v;
}
