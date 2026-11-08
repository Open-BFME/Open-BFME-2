// cl: /DNDEBUG /MD /EHsc
// ?Rva001FA8DDParse@@YAXPAVINI@@PAX@Z retail 0x001FA8DD 110B.
// INI token dispatch via AsciiString temp, table at 0x9FDD5C, virtual create plus append to list at +0xC4.
// Evidence: getNextToken 0x0002DF97, StringBase ctor 0x00037BA0, compare 0x000069B1, virtual slot 0, append 0x005A0B4C, releaseBuffer 0x00036410.
#include "../../../Include/Common/INI/INI.h"

struct Rva002BA8F1Listener;

struct TableEntry
{
	virtual Rva002BA8F1Listener *create(INI *ini);
	const char *m_name;
	int m_08;
	TableEntry *m_next;
};

struct Rva002BA8F1Listener
{
};

void Rva001FA8DDParse(INI *ini, void *instance);

namespace FXParticleSystem
{
template <int CATEGORY> class CategoryModuleClass
{
private:
	friend void ::Rva001FA8DDParse(INI *, void *);
	static const CategoryModuleClass<CATEGORY> *s_first;
};
}

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);
};

struct Rva001FA8DDHolder
{
	char _pad[0xC4];
	Rva005A0B4CList m_list;
};

void Rva001FA8DDParse(INI *ini, void *instance)
{
	Rva001FA8DDHolder *holder = static_cast<Rva001FA8DDHolder *>(instance);
	const char *token = ini->getNextToken(0);
	AsciiString tmp(token);
	// Retail reads VA 0x00DFDD5C, the category-8 getFirst() slot (RVA 0x001F4466).
	TableEntry *entry = *(TableEntry * volatile *)&FXParticleSystem::CategoryModuleClass<8>::s_first;
	while (tmp.compare(entry->m_name) != 0)
		entry = entry->m_next;
	Rva002BA8F1Listener *listener = entry->create(ini);
	holder->m_list.append(listener);
}
