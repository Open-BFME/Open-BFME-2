// cl: /O1 /MD
// Wave-3 shape-family batch, five 36-byte frameless reserve-then-set twins:
//   push esi; eax=[this+0x10]+1; C1(eax); C2(b, a); return a; ret 8
// (C1 is a one-arg thiscall on the same this with ecx passing through; C2 a
// two-arg thiscall on the same this; the body returns its first argument.
// Only the two callee addresses differ per member, except 0x003EF34A and
// 0x0052B7F8 which share C1 0x00212858.) The shared C1 reads an int-vector
// count at this+4 and grows via 0x0005571B when the request exceeds it, so
// C1 is a reserve-like grower and C2 the indexed set; owner class identities
// are unproven, so each body gets an address-named owner with its two
// callees pinned. 0x00212858 carries one pin per owner spelling (alias pins,
// same bytes).
//
//   body        C1 (reserve)  C2 (set)
//   0x00057B27  0x00056BFE    0x00054BC3
//   0x00057D38  0x0053F1EC    0x000556AB
//   0x000E0536  0x000E0322    0x000E0298
//   0x003EF34A  0x00212858    0x003EF264
//   0x0052B7F8  0x00212858    0x0052B737
class Rva00057B27
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva00056BFE(unsigned int n);
	void rva00054BC3(unsigned int a, unsigned int b);
	int rva00057B27(unsigned int a, unsigned int b);
};

int Rva00057B27::rva00057B27(unsigned int a, unsigned int b)
{
	rva00056BFE(m_count10 + 1);
	rva00054BC3(a, b);
	return a;
}

class Rva00057D38
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva0053F1EC(unsigned int n);
	void rva000556AB(unsigned int a, unsigned int b);
	int rva00057D38(unsigned int a, unsigned int b);
};

int Rva00057D38::rva00057D38(unsigned int a, unsigned int b)
{
	rva0053F1EC(m_count10 + 1);
	rva000556AB(a, b);
	return a;
}

class Rva000E0536
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva000E0322(unsigned int n);
	void rva000E0298(unsigned int a, unsigned int b);
	int rva000E0536(unsigned int a, unsigned int b);
};

int Rva000E0536::rva000E0536(unsigned int a, unsigned int b)
{
	rva000E0322(m_count10 + 1);
	rva000E0298(a, b);
	return a;
}

class Rva003EF34A
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva00212858(unsigned int n);
	void rva003EF264(unsigned int a, unsigned int b);
	int rva003EF34A(unsigned int a, unsigned int b);
};

int Rva003EF34A::rva003EF34A(unsigned int a, unsigned int b)
{
	rva00212858(m_count10 + 1);
	rva003EF264(a, b);
	return a;
}

class Rva0052B7F8
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva00212858(unsigned int n);
	void rva0052B737(unsigned int a, unsigned int b);
	int rva0052B7F8(unsigned int a, unsigned int b);
};

int Rva0052B7F8::rva0052B7F8(unsigned int a, unsigned int b)
{
	rva00212858(m_count10 + 1);
	rva0052B737(a, b);
	return a;
}
