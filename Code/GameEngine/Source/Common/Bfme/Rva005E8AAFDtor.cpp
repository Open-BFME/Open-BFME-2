// cl: /EHsc /MD
// ??1Rva005E8AAF@@UAE@XZ @0x005E8AAF 48B
// Virtual dtor with member Rva005E8908 at +8 via rowed dtor 0x005E8908 then
// storing base vtable 0x007C6F20 via empty inline base dtor. Same recipe as
// Rva00517397Dtor novtable derived plus base store. Called by deleting dtor
// 0x005E8A93. Unlocks 0x005E8A93.
class Rva005E8908
{
public:
	~Rva005E8908();

private:
	char m_pad[0x1C];
};

class Rva005E8AAFBase
{
public:
	__forceinline ~Rva005E8AAFBase() {}
	virtual void keep() {}
};

class __declspec(novtable) Rva005E8AAF : public Rva005E8AAFBase
{
public:
	virtual ~Rva005E8AAF();

private:
	int m_pad04;
	Rva005E8908 m_08; // +8
};

Rva005E8AAF::~Rva005E8AAF()
{
}
