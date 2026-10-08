// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva005CCDDD@@UAE@XZ retail 0x005CCDDD, 54 B (the name its scalar
// deleting dtor 0x005CCF2B calls). Target evidence: stores its vtable
// 0x00C74F44, destroys the member at +0x08 through its out-of-line
// destructor 0x005CCD3E (pinned), then the inline base destructor resets the
// vptr to 0x00BC6F20. Empty in source; owner and member are address-named
// (WorldBuilder's map for 0x005CCD3E is not trusted).
class Rva005CCD3E
{
public:
	~Rva005CCD3E();					// 0x005CCD3E
private:
	unsigned char m_bytes[4];
};

class Rva005CCDDDBase
{
public:
	virtual ~Rva005CCDDDBase() {}
private:
	int m_04;
};

class Rva005CCDDD : public Rva005CCDDDBase
{
public:
	virtual ~Rva005CCDDD();
private:
	Rva005CCD3E m_08;				// +0x08
};

Rva005CCDDD::~Rva005CCDDD()
{
}
