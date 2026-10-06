// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??0Rva0041386B@@QAE@XZ @0x0041386B 54B: thiscall ctor with vector at +0 and ModuleTemplateMap at +0xC.
// Evidence: chain/unlock lane, EH prolog, rowed Vector_base BfmeE16 at 0x00211E58 and rowed map ctor at 0x00413727, caller at 0x00413B88.
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
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
};

extern struct FieldParse g_00C39AF8;

class Rva0041386B
{
public:
	Rva0041386B();
	void rva0041393F(class INI *ini);
private:
	_STL::vector<BfmeE16> m_vec00;
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > > m_map0C;
};
Rva0041386B::Rva0041386B()
{
}

// ?rva0041393F@Rva0041386B@@QAEXPAVINI@@@Z @0x0041393F 18B: INI-field init
// forwarder. Caller 0x00413B95 passes ecx = Rva0041386B local and INI * in esi;
// retail pushes the FieldParse table 0x00839AF8 then this, then calls rowed
// INI::initFromINI 0x0002DE78 with ecx = INI *. Honest address name; table is
// an unresolved g_ stopgap until its owner TU defines it.
void Rva0041386B::rva0041393F(INI *ini)
{
	ini->initFromINI(this, &g_00C39AF8);
}
