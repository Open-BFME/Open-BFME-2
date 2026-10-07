// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// Native 5CCD94..5CCDDD constructs the reference-counted base at +0,
// allocates a 28-byte child, and stores it at +8. Existing destructor
// 5CCDDD and vtable C74F44 establish the address-derived owner name.
struct RvaSmallVtableZeroBase
{
	void *m_04;
	RvaSmallVtableZeroBase() : m_04(0) {}
};

class Rva0007DF07 : public RvaSmallVtableZeroBase
{
public:
	Rva0007DF07() {}
	virtual ~Rva0007DF07() {}
};

class Rva005CCDDD;

// Existing ~Rva005CCC69 and its C74F24 vtable identify the child.
// Its constructor 5CCC50 stores the owner at +24, calls the 55-byte
// base constructor 5CCBD0, and returns this with RET4. Both bodies
// only write members and return; neither can throw a C++ exception.
class Rva005CCC69
{
public:
	Rva005CCC69(Rva005CCDDD *) throw();
	virtual ~Rva005CCC69();
private:
	char unknown04[0x24];
};

class Rva005CCDDD : public Rva0007DF07
{
public:
	Rva005CCDDD();
	virtual ~Rva005CCDDD();
private:
	Rva005CCC69 *payload;
};

Rva005CCDDD::Rva005CCDDD()
	: payload(new Rva005CCC69(this))
{
}
