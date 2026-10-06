// cl: /MD /O1 /arch:SSE /G7
// ??1Rva005CCD3E@@QAE@XZ @0x005CCD3E 26B dtor clears pointer with delete. Evidence: ret plus calls 0x005CCC69 0x0002FD60 plus caller 0x005CCDDD plus LINK 0x005CCDDD.
// True size 26B up to ret; packet 35B includes 9B tail thunk at 0x005CCD58 calling 0x005F8F96.
class Rva005CCC69
{
public:
	virtual ~Rva005CCC69();
};
class Rva005CCD3E
{
public:
	~Rva005CCD3E();
private:
	Rva005CCC69 *m_ptr;
};
Rva005CCD3E::~Rva005CCD3E()
{
	Rva005CCC69 *p = m_ptr;
	m_ptr = 0;
	if (p) {
		p->Rva005CCC69::~Rva005CCC69();
		::operator delete(p);
	}
}
