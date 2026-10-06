// cl: /O1 /DNDEBUG /MD /G7
//
// Three bool forwards to the pinned 0x005CCB7B (which tail-jumps to
// 0x005CCAEC, a byte compare-and-store of its argument), each after the
// shared empty body 0x000B3FD0:
//   0x005D1AE9 24B passes the +0x1C byte of the +0x10 object;
//   0x005D1CAF 36B passes true without a +0x14 object, else its 0x0056A989;
//   0x005D20C1 36B the same over 0x00318F42.
// Target facts: callers push the bool as a bare byte (mov al/cl; push),
// which /G7 produces and the default does not, and both getters return bool
// (xor al,al false paths, test al at the call). Names are address-derived;
// identities are not recovered.

class Rva000B3FD0Empty
{
public:
	void rva000B3FD0Empty();
};

class Rva005CCB7B
{
public:
	void rva005CCB7B(bool b);
};

struct Rva005D1AE9Mid
{
	unsigned char m_pad[0x1C];
	bool m_1C;
};

class Rva005D1AE9
{
public:
	void rva005D1AE9();
protected:
	unsigned char m_pad[0x10];
	Rva005D1AE9Mid *m_10;
};

void Rva005D1AE9::rva005D1AE9()
{
	((Rva000B3FD0Empty *)this)->rva000B3FD0Empty();
	((Rva005CCB7B *)this)->rva005CCB7B(m_10->m_1C);
}

class Rva0056A989
{
public:
	bool rva0056A989();
};

class Rva005D1CAF
{
public:
	void rva005D1CAF();
protected:
	unsigned char m_pad[0x14];
	Rva0056A989 *m_14;
};

void Rva005D1CAF::rva005D1CAF()
{
	((Rva000B3FD0Empty *)this)->rva000B3FD0Empty();
	((Rva005CCB7B *)this)->rva005CCB7B(m_14 == 0 || m_14->rva0056A989());
}

class Rva00318F42
{
public:
	bool rva00318F42();
};

class Rva005D20C1
{
public:
	void rva005D20C1();
protected:
	unsigned char m_pad[0x14];
	Rva00318F42 *m_14;
};

void Rva005D20C1::rva005D20C1()
{
	((Rva000B3FD0Empty *)this)->rva000B3FD0Empty();
	((Rva005CCB7B *)this)->rva005CCB7B(m_14 == 0 || m_14->rva00318F42());
}
