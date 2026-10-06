// cl: /O1 /EHsc /MD /arch:SSE
// stlport
// AttributeModifierStore.cpp -- AttributeModifierStore members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function; retail supplies the bytes.
//
// The store keeps its modifiers in a vector at +0x0C; the per-modifier
// query (0x004036B1) is rowed under a placeholder name with the argument
// types its row carries.

#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

template <class T> class StringBase;

class Rva004036B1
{
public:
	Bool rva004036B1(void *key, float *value, const StringBase<char> *name);	// 0x004036B1
};

class AttributeModifierStore
{
public:
	Bool getModifier(Int index, void *key, float *value, const StringBase<char> *name);

private:
	unsigned char m_pad00[0xc];
	std::vector<Rva004036B1 *> m_modifiers;		// +0x0C
};

// AttributeModifierStore::getModifier, retail 0x00214762.
Bool AttributeModifierStore::getModifier(Int index, void *key, float *value, const StringBase<char> *name)
{
	if (index < 0 || index > m_modifiers.size() - 1 || m_modifiers[index] == 0)
		return false;
	return m_modifiers[index]->rva004036B1(key, value, name);
}
