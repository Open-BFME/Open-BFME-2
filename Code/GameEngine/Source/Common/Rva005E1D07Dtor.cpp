// cl: /O1 /DNDEBUG /MD /GX
// ??1Rva005E1D07@@QAE@XZ @ 0x005E1D07 (58B). Outer dtor zeroes +0x24 then destroys +0x14 via rowed 0x005E1C9D then +0x0C via rowed virtual 0x005EFDDB. Evidence: chain from 0x005E1C9D plus callers 0x005E1D44 and 0x005E1E8D prev next same dir.
struct Rva005E1C9D
{
	char _00[12];
	~Rva005E1C9D();
};
struct Rva005EFDDB
{
	virtual ~Rva005EFDDB();
	void *m_04;
};
struct Rva005E1D07
{
	char _00[12];
	Rva005EFDDB m_0C;
	Rva005E1C9D m_14;
	char _20[4];
	int m_24;
	~Rva005E1D07();
};
Rva005E1D07::~Rva005E1D07()
{
	m_24 = 0;
}
