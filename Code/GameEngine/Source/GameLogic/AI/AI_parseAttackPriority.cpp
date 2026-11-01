// cl: /O1 /EHsc /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?parseAttackPriority@AI@@SAXPAVINI@@PAX1PBX@Z, retail 0x002FFD03 (192B). INI field-table callback
// (INI*, instance = the AI data, store, userData): the next token names an entry of the AI
// data's named-list chain (+0xFC, linked through +0x10); an existing entry has its list (+0x0C)
// cleared, a missing one is allocated (0x14 B, rowed ctor 0x002FED8D over the name, unwound on a
// throwing ctor) and pushed at the head; the entry is then filled through initFromINI with the
// table at VA 0x00C07414. Evidence: target bytes and the AI::parseSideInfo sibling at
// 0x002FE940 (same lookup/allocate/push shape); the list head at +0xFC and the 0x14-byte node
// match AI::newOverride (0x002FFDC3, AIConstructor.cpp). Name: the AIData field table maps
// "AttackPriority" (0x00C06834) to this body, its own table holds "Default" and "Target", and
// BFME 1's AI::parseAttackPriority (b1 0x0014E130) has the same lookup/clear/allocate shape.
#include <list>
#include "ascii_string.h"

namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<AsciiString> >::deallocate(_List_node<AsciiString>* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<AsciiString>*,_List_node<AsciiString>,allocator<_List_node<AsciiString> > >::deallocate(_List_node<AsciiString>* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<_List_node<AsciiString> >&>(*this),(_List_node<AsciiString>*)0).deallocate(__p,__n);
}
}

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
};

struct FieldParse
{
	const char *token;
	void (*parse)(INI *, void *, void *, const void *);
	const void *userData;
	int offset;
};

// Unrowed INI callback for the "Target" field (pinned at 0x002FEE2C).
void Rva002FEE2CParse(INI *ini, void *instance, void *store, const void *userData);

class Rva002FED8D
{
public:
	Rva002FED8D(AsciiString name);
	virtual ~Rva002FED8D();
	AsciiString name;
	unsigned int value;
	_STL::list<AsciiString> tail;
	Rva002FED8D *next;
};

struct Rva002FFD03Data
{
	unsigned char m_pad[0xFC];
	Rva002FED8D *m_namedLists;
};

#include "../../../Include/GameLogic/AI.h"

void AI::parseAttackPriority(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	// Retail's two-field table (.rdata RVA 0x00807414): "Default" with INI::parseInt into the
	// node's +8 value and "Target" with the callback above into the list at +0x0C.
	static const FieldParse fieldParse[] =
	{
		{ "Default", &INI::parseInt, 0, 8 },
		{ "Target", &Rva002FEE2CParse, 0, 12 },
		{ 0, 0, 0, 0 }
	};

	const char *c = ini->getNextToken();
	AsciiString name(c);

	Rva002FFD03Data *data = (Rva002FFD03Data *)instance;
	Rva002FED8D *node = data->m_namedLists;
	while (node)
	{
		if (name.compare(node->name) == 0)
		{
			node->tail.clear();
			break;
		}
		node = node->next;
	}
	if (node == 0)
	{
		node = new Rva002FED8D(name);
		node->next = data->m_namedLists;
		data->m_namedLists = node;
	}
	ini->initFromINI(node, fieldParse);
}
