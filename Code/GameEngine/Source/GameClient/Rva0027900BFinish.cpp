// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?rva0027900B@@YA_NPAD@Z @0x0027900B 105B: static (internal-linkage) helper,
// NOT a thiscall member. The sole call site 0x0027916A sets the object pointer
// in EAX (`mov eax,edi; call`), which MSVC only does for an internal-linkage
// function whose call sites it can see -- exactly the Lua `_currentpc`/`_ZNAME`
// shape in this tree. Modeled as a static free function taking the object byte
// pointer; an in-TU scaffold caller supplies the visible call site that makes
// the compiler pick the EAX convention.
//
// PlayerTemplateStore lookup: match +0x6C string via rowed StringBase compare
// (0x000069D6) against each template +0x18 then return the +0x1BC flag.
// Callees rowed getNthPlayerTemplate 0x001FD3C6, ThePlayerTemplateStore.

#include "ascii_string.h"

class PlayerTemplate
{
public:
	char m_pad[0x18];
	AsciiString m_name18;
	char m_pad2[0x1BC - 0x18 - 4];
	bool m_flag1BC;
};

class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(int i) const;
private:
	char m_pad[0xC];
public:
	int m_minC;
	int m_max10;
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

struct BaseWithString
{
	char m_pad[0x6C];
	AsciiString m_str6C;
};

// ?rva0027900B@@YA_NPAD@Z
static bool rva0027900B(char *self)
{
	BaseWithString *base = *(BaseWithString **)(self + 4);
	const StringBase<char> *needle = 0;
	if (base != 0)
	{
		needle = (const StringBase<char> *)&base->m_str6C;
		for (int i = 0; i < (ThePlayerTemplateStore->m_max10 - ThePlayerTemplateStore->m_minC) / 0x1DC; ++i)
		{
			const PlayerTemplate *pt = ThePlayerTemplateStore->getNthPlayerTemplate(i);
			if (pt == 0)
				continue;
			if (needle->compare(*(const StringBase<char> *)&pt->m_name18) == 0)
				return pt->m_flag1BC;
		}
	}
	return false;
}

// Codegen scaffold only: the retail call site at 0x0027916A lives in a still
// unrecovered Drawable body. This visible external caller is what makes the
// compiler emit the static helper with its object argument in EAX.
bool callerForRva0027900B(char *self)
{
	return rva0027900B(self);
}
