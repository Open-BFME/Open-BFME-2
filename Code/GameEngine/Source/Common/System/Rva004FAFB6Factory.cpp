// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva004FAFB6@Rva004FAC21@@UAEPAVRva004FADF4@@I@Z @0x004FAFB6 60B evidence: chain via just-landed Rva004FADF4 0x004FADF4; new 0x30 plus II ctor; vtable slot 1 of 0x008633B0 Rva004FAC21; caller none.
// Honest Rva factory returning new Rva004FADF4 via EH new.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva0059B7CB
{
public:
	Rva0059B7CB(unsigned int field04, unsigned int field08);
	virtual void slot00();
private:
	unsigned int m_field04;
	unsigned int m_field08;
};

class Rva004FAC6B
{
public:
	Rva004FAC6B();
	virtual void slot00();
private:
	char m_pad[0x10];
};

class Rva004FADF4 : public Rva0059B7CB, public Rva004FAC6B
{
public:
	Rva004FADF4(unsigned int a, unsigned int b);
	virtual void slot00();
private:
	_STL::vector<BfmeE16> m_vec;
	int m_2c;
};

void *__cdecl operator new(unsigned int size);

class Rva004FAC21
{
public:
	virtual Rva004FADF4 *rva004FAFB6(unsigned int arg);
};

Rva004FADF4 *Rva004FAC21::rva004FAFB6(unsigned int arg)
{
	return new Rva004FADF4(arg, (unsigned int)this);
}
