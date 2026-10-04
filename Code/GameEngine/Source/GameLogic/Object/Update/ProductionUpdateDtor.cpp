// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ??1ProductionUpdate@@UAE@XZ @0x0049E1BF 181B
// ProductionUpdate dtor via BFME1 donor ProductionUpdateDestructor.cpp:113 plus
// ctor TU ProductionUpdateCtor.cpp layout (base 0x20 plus ifaces at 0x20/0x24,
// queue at 0x28, list at 0x124, int at 0x12C, vector at 0x130, size 0x140).
// Evidence: pin ??1ProductionUpdate@@UAE@XZ, retail caller 0x0049E34F
// ??_GProductionUpdate, vtable stores at +0/+0xC/+0x10/+0x20/+0x24.
#include <list>
#include <vector>
#include "ascii_string.h"

class Rva0049B47CFold
{
public:
	virtual ~Rva0049B47CFold();
	int m_pad[2];
};

class MiBase1
{
public:
	virtual void f1();
};

class PrimaryP : public Rva0049B47CFold, public MiBase1
{
public:
	~PrimaryP() {}
};

class Rva0024A797_B2
{
public:
	virtual void f2();
	int m_pad2[3];
};

class Rva0024A797 : public PrimaryP, public Rva0024A797_B2
{
public:
	virtual ~Rva0024A797();
};

class Iface20
{
public:
	virtual void s20() = 0;
};

class Iface24
{
public:
	virtual void s24() = 0;
};

class ProductionEntry
{
public:
	virtual void *scalarDeleting(unsigned int flags);
};

class Rva0049D526
{
public:
	void rva0049D57F(void *entry);
};

class AudioManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(int x);
};

extern AudioManager *TheAudio;

class ProductionUpdate : public Rva0024A797, public Iface20, public Iface24
{
public:
	virtual ~ProductionUpdate();
private:
	ProductionEntry *m_queue28;
	char m_pad2C[0xF8];
	_STL::_List_base<int, _STL::allocator<int> > m_list124;
	int m_128;
	int m_12C;
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_vec130;
};

ProductionUpdate::~ProductionUpdate()
{
	while (m_queue28)
	{
		ProductionEntry *entry = m_queue28;
		((Rva0049D526 *)this)->rva0049D57F(entry);
		void *p = entry ? entry->scalarDeleting(0) : 0;
		::operator delete(p);
	}
	if (TheAudio)
		TheAudio->s27(m_12C);
}
