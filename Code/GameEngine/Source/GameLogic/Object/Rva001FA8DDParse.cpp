// cl: /DNDEBUG /MD /EHsc
// ?Rva001FA8DDParse@@YAXPAVINI@@PAX@Z retail 0x001FA8DD 110B.
// INI token dispatch via AsciiString temp, table at 0x9FDD5C, virtual create plus append to list at +0xC4.
// Evidence: getNextToken 0x0002DF97, StringBase ctor 0x00037BA0, compare 0x000069B1, virtual slot 0, append 0x005A0B4C, releaseBuffer 0x00036410.
class INI
{
public:
	const char *getNextToken(const char *seps);
};

struct Rva002BA8F1Listener;

template <typename T> class StringBase
{
	friend void Rva001FA8DDParse(INI *, void *);
	StringBase(const char *s);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
public:
	int compare(const char *s) const;
private:
	void *m_data;
};

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

namespace FXParticleSystem
{
template <int CATEGORY> class CategoryModuleClass
{
public:
	static CategoryModuleClass<CATEGORY> *s_head;
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
	StringBase<char> tmp(token);
	// Retail reads VA 0x00DFDD5C, the category-8 getFirst() slot (RVA 0x001F4466).
	TableEntry *entry = *(TableEntry * volatile *)&FXParticleSystem::CategoryModuleClass<8>::s_head;
	while (tmp.compare(entry->m_name) != 0)
		entry = entry->m_next;
	Rva002BA8F1Listener *listener = entry->create(ini);
	holder->m_list.append(listener);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva001FA8DDParse@@YAXXZ=?Rva001FA8DDParse@@YAXPAVINI@@PAX@Z")
