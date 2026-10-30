// cl: /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// ?rva000E5EE5@Rva000E5EE5@@QAEXPBVRva0055A88BDwordField@@V?$StringBase@D@@@Z @0x000E5EE5 123B
// Target facts: 123B thiscall ret 8 (field ptr + by-value StringBase<char>),
// list at +0x18 (head->next, item at +0x08) like Rva000E5F60Lookup, null check
// on first arg, id via rowed get 0x0055A88B, matcher rowed rva000E5EC1
// 0x000E5EC1, on match clears dword at item+0x2C and sets byte at +0x9C.
// Donor: Code/GameEngine/Source/Common/Rva000E5F60Lookup.cpp (loop shape,
// by-value temp with __forceinline dtor) + Rva000E6135Method.cpp (get+matcher).
// The canonical frozen StringBase replaces the private copy; its switch
// declares the narrow teardown out of line, rowed at 0x00036410
// (StringBaseWideReleaseBuffer.cpp).
#define BFME_STRINGBASE_PUBLIC_DTOR
#include "string_base.h"

class Rva0055A88BDwordField
{
public:
	int get() const;
};

class Rva000E5EC1
{
public:
	bool rva000E5EC1(int id, const StringBase<char> &name) const throw();
	char m_pad00[0x2C];
	int m_2c; // +0x2C
	char m_pad30[0x1C];
	int m_id; // +0x4C
	char m_pad50[0x38];
	float m_88; // +0x88
	StringBase<char> m_name; // +0x8C
	char m_pad90[0xC];
	bool m_9c; // +0x9C
	char m_pad9D[0x3];
};

struct Rva000E5EE5Node
{
	Rva000E5EE5Node *m_next;
	void *m_prev;
	Rva000E5EC1 *m_item;
};

class Rva000E5EE5
{
public:
	void rva000E5EE5(const Rva0055A88BDwordField *idSrc, StringBase<char> name);
private:
	char m_pad[0x18];
	Rva000E5EE5Node *m_head;
};

void Rva000E5EE5::rva000E5EE5(const Rva0055A88BDwordField *idSrc, StringBase<char> name)
{
	if (idSrc == 0)
		return;
	Rva000E5EE5Node *cur = m_head->m_next;
	while (cur != m_head)
	{
		if (cur->m_item->rva000E5EC1(idSrc->get(), name))
		{
			Rva000E5EC1 *item = cur->m_item;
			item->m_2c = 0;
			item->m_9c = true;
			return;
		}
		cur = cur->m_next;
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?rva000E5EE5@Rva000E5EE5@@QAEXPBVRva0055A88BDwordField@@VAsciiString@@@Z=?rva000E5EE5@Rva000E5EE5@@QAEXPBVRva0055A88BDwordField@@V?$StringBase@D@@@Z")
