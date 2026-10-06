// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob2
// stlport
// ??1Rva0042FCE6@@QAE@XZ, retail 0x0042FCE6, 54 bytes.
// Dtor stores derived vtable 0x0083C960 destroys tree at +0x28 via rowed 0x00357C6A stores base vtable 0x007DBA74. Evidence: caller 0x0042FE1F deleting dtor base vtable matches BfmeOwnVVD base.
#include <map>

typedef _STL::pair<const unsigned int, void *> Rva0042FCE6Pair;
typedef _STL::_Rb_tree<unsigned int, Rva0042FCE6Pair, _STL::_Select1st<Rva0042FCE6Pair>, _STL::less<unsigned int>, _STL::allocator<Rva0042FCE6Pair> > Rva0042FCE6Tree;

class Rva0042FCE6Base
{
public:
	Rva0042FCE6Base() { }
	~Rva0042FCE6Base() { }
	virtual void rvaSlot0();
};

class Rva0042FCE6 : public Rva0042FCE6Base
{
public:
	~Rva0042FCE6();
private:
	char m_pad04[0x24];
	Rva0042FCE6Tree m_map28;
};

Rva0042FCE6::~Rva0042FCE6()
{
}
