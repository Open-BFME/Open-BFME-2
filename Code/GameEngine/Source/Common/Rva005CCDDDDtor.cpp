// cl: /MD /O1 /arch:SSE /G7 /EHsc
// ??1Rva005CCDDD@@UAE@XZ @0x005CCDDD 54B dtor stores vtables plus member Rva005CCD3E at +8. Evidence: ret plus calls 0x005CCD3E 0x00629188 plus pin plus LINK plus callers 0x005CCF2E 0x005D1D7C 0x005D2155.
class Rva005CCC69;
class Rva005CCD3E
{
public:
	~Rva005CCD3E();
private:
	Rva005CCC69 *m_ptr;
};
class Rva005CCDDDBase
{
public:
	virtual ~Rva005CCDDDBase() {}
};
class Rva005CCDDD : public Rva005CCDDDBase
{
public:
	virtual ~Rva005CCDDD();
private:
	char m_pad[4];
	Rva005CCD3E m_08;
};
Rva005CCDDD::~Rva005CCDDD()
{
}
