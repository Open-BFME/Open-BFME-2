// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??0Rva00413F8B@@QAE@XZ @0x00413F8B 54B: thiscall ctor with vector at +0 and ModuleTemplateMap at +0xC.
// Evidence: unlock lane, EH prolog, rowed Vector_base BfmeE16 at 0x00211E58 and rowed map ctor at 0x00413727, same shape as Rva0041386B at 0x0041386B.
#include <vector>
#include <map>
struct BfmeE16 { char m_data[16]; };
enum NameKeyType { NK_ZERO = 0 };
class ModuleFactory
{
public:
	class ModuleTemplate
	{
	public:
		void *m_createProc;
		void *m_createDataProc;
		int m_whichInterfaces;
	};
};
class Rva00413F8B
{
public:
	Rva00413F8B();
private:
	_STL::vector<BfmeE16> m_vec00;
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > > m_map0C;
};
Rva00413F8B::Rva00413F8B()
{
}
