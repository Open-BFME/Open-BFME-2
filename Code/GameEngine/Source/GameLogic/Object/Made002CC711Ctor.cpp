// cl: /O1 /DNDEBUG /MD /arch:SSE
// ??0Made002CC711@@QAE@XZ @0x00508F51 59B: ParalyzeNugget ctor over rowed
// base Rva00507823; zeroes +0x128/+0x12c/+0x134, pi at +0x130 via 0x7C7468,
// vtable 0x8644A0. Caller parseParalyzeNugget 0x2CC736.

class Rva00507823
{
public:
	Rva00507823();
	virtual ~Rva00507823();

private:
	char m_pad[0x128 - 4];
};

class Made002CC711 : public Rva00507823
{
public:
	Made002CC711();

private:
	float m_128;
	int m_12C;
	float m_130;
	int m_134;
};

Made002CC711::Made002CC711()
{
	m_128 = 0.0f;
	m_12C = 0;
	m_130 = 3.1415927f;
	m_134 = 0;
}
