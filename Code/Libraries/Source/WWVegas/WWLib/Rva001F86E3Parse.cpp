// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva001F86E3Parse@@YAXPAVINI@@PAX@Z, retail 0x001F86E3, 110 bytes.
// INI token lookup in FXParticleSystem CategoryModuleClass<5> list then
// owned-pointer store at +0xBC via rowed rva001F43BD setter. Evidence:
// retail getNextToken 0x2DF97 row, StringBase ctor 0x37BA0 row, s_head
// 05 global 0x009FDD54, compare 0x69B1 row, virtual slot0 create,
// rva001F43BD 0x1F43BD row, releaseBuffer 0x36410 row, EH prolog row.
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

struct Rva001F86E3Owner
{
	char pad[0xBC];
	Rva001F43BD setter;
};

void Rva001F86E3Parse(INI *ini, void *owner)
{
	const char *token = ini->getNextToken((const char *)0);
	AsciiString name(token);
	FXParticleSystem::CategoryModuleClass<6> *mod = FXParticleSystem::CategoryModuleClass<6>::s_head;
	while (name.compare(mod->m_key) != 0)
		mod = mod->m_next;
	void *created = mod->v1(ini);
	((Rva001F86E3Owner *)owner)->setter.rva001F43BD(created);
}
