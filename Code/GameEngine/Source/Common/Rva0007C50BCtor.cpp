// cl: /EHsc /MD
// ??0Rva0007C50B@@QAE@XZ @0x0007C50B 174B, called from 0x0009A892.
// Allocates a 0x408-byte Rva007C454 (rowed ctor 0x0007C3CD) into the
// ref-counting holder at +0, then a 0x3FC-byte CameraClass (rowed ctor
// 0x00134AB0) into the plain pointer at +4, zeroes/sets the fields and
// writes 1 to +0xC4 and 0 to the byte at +0xFC of the first object.
// Target facts: retail's unwind map frees the first allocation in state 0,
// destroys +0 through the rowed Rva00087A93 dtor 0x0007B724 in state 1 and
// frees the second allocation in state 2 (+4 has no entry). The 1.0 is the
// compiler literal at 0x007BB8D8.
// Structural inference: the three floats at +8 and the five ints at +0x14
// are grouped into members with inline constructors; as loose scalars the
// holder's pointer load hoists above their stores, which retail keeps in
// declaration order.
class CameraClass
{
public:
	CameraClass();
	char m_pad0[0xC4];
	int m_c4;
	char m_pad1[0xFC - 0xC4 - 4];
	unsigned char m_fc;
	char m_pad2[0x3FC - 0xFC - 1];
};

class Rva007C454 : public CameraClass
{
public:
	Rva007C454();
private:
	char m_pad3FC[0x408 - 0x3FC];
};

class Rva00087A93
{
public:
	Rva00087A93(Rva007C454 *p) : m_data(p) {}
	~Rva00087A93();
	Rva007C454 *get() const { return m_data; }
private:
	Rva007C454 *m_data;
};

struct Rva0007C50BVec
{
	Rva0007C50BVec(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X;
	float Y;
	float Z;
};

struct Rva0007C50BInts
{
	Rva0007C50BInts() : a(0), b(0), c(0), d(0), e(0) {}
	int a;
	int b;
	int c;
	int d;
	int e;
};

class Rva0007C50B
{
public:
	Rva0007C50B();
private:
	Rva00087A93 m_a;
	CameraClass *m_b;
	Rva0007C50BVec m_c;
	Rva0007C50BInts m_f;
	bool m_k;
};

Rva0007C50B::Rva0007C50B() : m_a(new Rva007C454), m_b(new CameraClass), m_c(0.0f, 0.0f, 1.0f),
	m_k(true)
{
	Rva007C454 *camera = m_a.get();
	camera->m_c4 = 1;
	camera->m_fc = 0;
}
