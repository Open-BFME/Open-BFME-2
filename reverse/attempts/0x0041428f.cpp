// ?Rva0041428FParse@@YAXPAVINI@@@Z
// partial score=0.99 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0041428FParse@@YAXPAVINI@@@Z RVA 0x0041428F size 120
// Target string and call sequence establish the parser operation; INIException layout follows the matched ctor TU.
// Donor layout: Code/GameEngine/Source/Common/INI/INIExceptionCtor.cpp. Target data: packet at 0x0041428F.
#include <map>
#include <vector>

struct BfmeE16
{
	char m_data[16];
};

enum NameKeyType
{
	NK_ZERO = 0
};

class INI
{
public:
	char m_pad00[8];
	int m_parseMode;
};

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
	void rva00414081(INI *ini);

private:
	_STL::vector<BfmeE16> m_vec00;
	_STL::map<NameKeyType, ModuleFactory::ModuleTemplate, _STL::less<NameKeyType>, _STL::allocator<_STL::pair<const NameKeyType, ModuleFactory::ModuleTemplate> > > m_map0C;
};

struct Rva00414258Element : Rva00413F8B
{
};

struct Rva0041428FRegistry
{
	char m_pad00[0x0c];
	_STL::vector<Rva00414258Element> m_elements;
};

extern Rva0041428FRegistry *g_00E0306C;

class INIException
{
public:
	char *m_failureMessage;
	int m_argCount;
	INIException(int, const char *, ...);
	INIException(const INIException &);
	~INIException();
};

void Rva0041428FParse(INI *ini)
{
	if (ini->m_parseMode != 1)
		throw INIException(8, "Cannot define LivingWorldAutoResolveResourceBonus except in modules");
	Rva00414258Element element;
	element.rva00414081(ini);
	g_00E0306C->m_elements.push_back(element);
}
