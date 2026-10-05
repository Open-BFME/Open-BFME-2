// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?Rva001F84BDParse@@YAXPAVINI@@PAX@Z @0x001F84BD 110B: INI token lookup in the
// FXParticleSystem CategoryModuleClass<1> registry (list head 0x009FDD40),
// storing the module the matching class creates in the owned pointer at
// +0xA8 through the rowed rva001F43BD setter. One of the nine
// per-category parse functions the matched Rva001FB912Init family installs
// (siblings Rva001F852BParse, Rva001F86E3Parse); the 2006 demo's relocations
// and that Init's parse-pointer store place the start.
#include "ascii_string.h"

class INI
{
public:
	const char *getNextToken(const char *seps);
};

class Rva001F43BD
{
public:
	void rva001F43BD(void *p);
};

class FXParticleSystem
{
public:
	template <int CATEGORY>
	class CategoryModuleClass
	{
	public:
		virtual void *v1(INI *ini);
		const char *m_key;
		const char *m_name;
		CategoryModuleClass *m_next;
		static CategoryModuleClass *s_head;
	};
};

struct Rva001F84BDOwner
{
	char pad[0xA8];
	Rva001F43BD setter;
};

// ?Rva001F84BDParse@@YAXPAVINI@@PAX@Z
void Rva001F84BDParse(INI *ini, void *owner)
{
	const char *token = ini->getNextToken((const char *)0);
	AsciiString name(token);
	FXParticleSystem::CategoryModuleClass<1> *mod = FXParticleSystem::CategoryModuleClass<1>::s_head;
	while (name.compare(mod->m_key) != 0)
		mod = mod->m_next;
	void *created = mod->v1(ini);
	((Rva001F84BDOwner *)owner)->setter.rva001F43BD(created);
}
