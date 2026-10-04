// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva001ED41B@@UAE@XZ @0x001ED41B 91B: MI dtor with vector plus clear plus GameEngineDeletingBase plus final g_00BBB554. Evidence: pin plus caller 0x001ED530 deleting dtor plus prev 0x001ED413 plus next 0x001ED476 plus callees 0x001ED363 0x000AD6F4 0x001B4E74.
#include <vector>

class Rva001ED0DE
{
public:
	~Rva001ED0DE();
};

class Rva000AD6F4
{
public:
	~Rva000AD6F4() { clear(); }
	void clear();
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

class Rva001ED41BBase0
{
public:
	virtual ~Rva001ED41BBase0() {}
};

class Rva001ED41B : public Rva001ED41BBase0, public GameEngineDeletingBase
{
public:
	virtual ~Rva001ED41B();
private:
	char m_pad08[0x10 - 0x08];
	Rva000AD6F4 m_10;
	_STL::vector<Rva001ED0DE> m_14;
};

Rva001ED41B::~Rva001ED41B()
{
}
