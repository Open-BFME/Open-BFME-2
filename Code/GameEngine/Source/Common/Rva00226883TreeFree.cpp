// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?rva00226883@Rva00226883@@QAEXPAX@Z, retail 0x00226883 45B.
// Tree free twin of 0x00226829: recursive child at +0x0C then free node and iterate sibling at +0x08.
// Evidence: self-recursive call at 0x226895; free row at 0x30830; caller 0x2299AD;
// identical shape to Rva00226829TreeFree.cpp; prev Rva00226856 row.

// Retail calls free directly (the game allocator), not through the CRT
// import: read <stdlib.h> without dllimport.
#define _CRTIMP
#include <stdlib.h>
#undef _CRTIMP

#include "../../Include/Common/Rva00226883.h"

struct RbTreeNode
{
	char m_pad[8]; // +0x00..0x07
	RbTreeNode *m_next; // +0x08 sibling
	RbTreeNode *m_child; // +0x0C child
};

struct RbTreeHeader
{
	char m_pad00[4]; // +0x00
	RbTreeNode *m_first; // +0x04
	RbTreeHeader *m_next; // +0x08
	RbTreeHeader *m_child; // +0x0C
};

void Rva00226883::rva00226883(void *node)
{
	if (!node)
		return;
	RbTreeNode *cur = (RbTreeNode *)node;
	do {
		rva00226883(cur->m_child);
		RbTreeNode *next = cur->m_next;
		free(cur);
		cur = next;
	} while (cur);
}

void Rva00226883::rva0022999F()
{
	if (m_04Flag == 0)
		return;
	RbTreeHeader *head = (RbTreeHeader *)m_header.m_00Head;
	rva00226883(head->m_first);
	((RbTreeHeader *)m_header.m_00Head)->m_next = (RbTreeHeader *)m_header.m_00Head;
	((RbTreeHeader *)m_header.m_00Head)->m_first = 0;
	((RbTreeHeader *)m_header.m_00Head)->m_child = (RbTreeHeader *)m_header.m_00Head;
	m_04Flag = 0;
}

// Three more clears of the rva0022999F shape, byte-identical to it except for the
// recursive free they call: the rowed frees of their own trees (0x00226829,
// 0x00226856, 0x002268B0, each 45 bytes like 0x00226883). Owners keep their
// address tokens; the layout is the one rva0022999F reads.

// ?clear@Rva00226829@@QAEXXZ @0x0022994D 41B -> Rva00226829::rva00226829
class Rva00226829
{
public:
	void rva00226829(void *node);
	void clear();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00226829::clear()
{
	if (m_04Flag == 0)
		return;
	RbTreeHeader *head = (RbTreeHeader *)m_00Head;
	rva00226829(head->m_first);
	((RbTreeHeader *)m_00Head)->m_next = (RbTreeHeader *)m_00Head;
	((RbTreeHeader *)m_00Head)->m_first = 0;
	((RbTreeHeader *)m_00Head)->m_child = (RbTreeHeader *)m_00Head;
	m_04Flag = 0;
}

// ?rva00229976@Rva00226856@@QAEXXZ @0x00229976 41B -> Rva00226856::rva00226856
class Rva00226856
{
public:
	void rva00226856(void *node);
	void rva00229976();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva00226856::rva00229976()
{
	if (m_04Flag == 0)
		return;
	RbTreeHeader *head = (RbTreeHeader *)m_00Head;
	rva00226856(head->m_first);
	((RbTreeHeader *)m_00Head)->m_next = (RbTreeHeader *)m_00Head;
	((RbTreeHeader *)m_00Head)->m_first = 0;
	((RbTreeHeader *)m_00Head)->m_child = (RbTreeHeader *)m_00Head;
	m_04Flag = 0;
}

// ?rva002299C8@Rva002268B0@@QAEXXZ @0x002299C8 41B -> Rva002268B0::rva002268B0
class Rva002268B0
{
public:
	void rva002268B0(void *node);
	void rva002299C8();
private:
	void *m_00Head; // +0x00
	int m_04Flag; // +0x04
};

void Rva002268B0::rva002299C8()
{
	if (m_04Flag == 0)
		return;
	RbTreeHeader *head = (RbTreeHeader *)m_00Head;
	rva002268B0(head->m_first);
	((RbTreeHeader *)m_00Head)->m_next = (RbTreeHeader *)m_00Head;
	((RbTreeHeader *)m_00Head)->m_first = 0;
	((RbTreeHeader *)m_00Head)->m_child = (RbTreeHeader *)m_00Head;
	m_04Flag = 0;
}
