// cl: /O1 /EHs /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??0Rva003B11AD@@QAE@XZ retail 0x003B11AD 37B
// Evidence: vtable store plus baseConstruct 0x001B4E63 plus Vector_base 0x00211E58 at +0xC plus clear +0x18; caller 0x0022EC4B; neighbours 0x003B1101/0x003B1337 share O1 EHs SSE flags; precedent Rva00426402Ctor.cpp for novtable base plus vector layout
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class BFME2NativeNetwork
{
public:
	BFME2NativeNetwork *baseConstruct();
};

class __declspec(novtable) Rva003B11ADBase
{
public:
	Rva003B11ADBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual void unused();
	char m_flag;
	int m_value;
};

class Rva003B11AD : public Rva003B11ADBase
{
public:
	Rva003B11AD();
protected:
	virtual ~Rva003B11AD();
private:
	_STL::vector<BfmeE16> m_vec0C;
	int m_18;
};

Rva003B11AD::Rva003B11AD()
	: m_vec0C()
	, m_18(0)
{
}
