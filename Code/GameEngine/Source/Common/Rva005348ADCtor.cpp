// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0Rva005348AD@@QAE@XZ
// retail 0x005348AD 58B: honest-address ctor constructing list<BfmePod8> at +0
// via the rowed _List_base 0x0035C9A6 and map<NameKeyType ModuleTemplate> at +4
// via the rowed map ctor 0x00413727 then bool at +0x10 = false.
// Called once from unclaimed 0x002F364A. Evidence: callee rows plus retail
// member layout list(4) map(12) bool.
#include <list>
#include <map>

struct BfmePod8
{
	int a[2];
};

enum NameKeyType
{
	NAMEKEY_FIRST = 0
};

class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		const void *m_createProc;
		const void *m_createDataProc;
		const void *m_data;
		int m_whichInterfaces;
	};
};

class Rva005348AD
{
public:
	Rva005348AD();

private:
	_STL::list<BfmePod8> m_list;
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate> m_map;
	bool m_flag;
};

Rva005348AD::Rva005348AD()
	: m_flag(false)
{
}
