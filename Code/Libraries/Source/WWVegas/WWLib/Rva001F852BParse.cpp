// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva001F852BParse@@YAXPAVINI@@PAX@Z @0x001F852B 110B: INI token lookup in FXParticleSystem CategoryModuleClass<1> list then owned-pointer store at +0xAC via rowed rva001F43BD setter; twin of Rva001F86E3Parse 0x001F86E3 with s_first $01 at 0x009FDD44 and AC offset; evidence retail getNextToken 0x2DF97 row StringBase ctor 0x37BA0 row compare 0x69B1 row virtual slot0 create rva001F43BD 0x1F43BD row releaseBuffer 0x36410 row EH prolog row.
#include "ascii_string.h"

#include "../../../../GameEngine/Include/Common/INI/INI.h"

class Rva001F43BD
{
public:
	void rva001F43BD(void *p);
};

void Rva001F852BParse(INI *ini, void *owner);

namespace FXParticleSystem
{
	template <int CATEGORY>
	class CategoryModuleClass
	{
	public:
		virtual void *v1(INI *ini) const;
		const char *m_key;
		const char *m_name;
		const CategoryModuleClass *m_next;

	private:
		friend void ::Rva001F852BParse(INI *, void *);
		static const CategoryModuleClass *s_first;
	};
}

struct Rva001F852BOwner
{
	char pad[0xAC];
	Rva001F43BD setter;
};

class HierarchyPrototype
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual int slot10();
	virtual void slot11();
	void Release_Ref();

	char m_pad[0x10];
	class HTreeClass *m_tree;
};

class HierarchyPrototypeRef
{
public:
	~HierarchyPrototypeRef()
	{
		if (m_object != 0)
			m_object->Release_Ref();
	}

private:
	HierarchyPrototype *m_object;
};

extern HierarchyPrototypeRef __cdecl Rva0061F230_GetPrototype(const char *name);

// ?Rva001F852BParse@@YAXPAVINI@@PAX@Z
void Rva001F852BParse(INI *ini, void *owner)
{
	const char *token = ini->getNextToken((const char *)0);
	AsciiString name(token);
	const FXParticleSystem::CategoryModuleClass<2> *mod = FXParticleSystem::CategoryModuleClass<2>::s_first;
	while (name.compare(mod->m_key) != 0)
		mod = mod->m_next;
	void *created = mod->v1(ini);
	((Rva001F852BOwner *)owner)->setter.rva001F43BD(created);
}
