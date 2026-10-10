// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ??0Rva00427157@@QAE@ABVAsciiString@@PBV0@@Z @0x00427157 62B ctor copies AsciiString at +0 via rowed StringBase copy 0x000365F0 fills 8 floats at +4 with 1.0f if src null else copies 8 floats from src+4 caller 0x004273FF
#include <hash_map>
// Suppress the TU's non-retail const-begin copy (row 54 family-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

namespace rts
{
template <typename T> struct hash;
template <> struct hash<NameKeyType>
{
	unsigned int operator()(const NameKeyType &v) const;
};
}

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct FieldParse;

class Rva00427157
{
public:
	Rva00427157(const AsciiString &name, const Rva00427157 *src);
	float rva004270FA(int index);
	friend void Rva00427114Parse(class INI *ini, Rva00427157 *store);
private:
	AsciiString m_name;
	float m_vals[8];
};

typedef const char *ConstCharPtr;
typedef const ConstCharPtr *ConstCharPtrArray;

class INI
{
public:
	const char *getNextToken(const char *seps);
	float dup_002EE10(const char *token);
	int scanIndexList(const char *token, ConstCharPtrArray nameList);
	void initFromINI(void *what, const FieldParse *parseTable);
};

extern ConstCharPtr g_00DC85C4[];
extern const FieldParse g_00C3C614[];

Rva00427157::Rva00427157(const AsciiString &name, const Rva00427157 *src) : m_name(name)
{
	if (!src) {
		for (int i = 0; i < 8; ++i)
			m_vals[i] = 1.0f;
	} else {
		for (int i = 0; i < 8; ++i)
			m_vals[i] = src->m_vals[i];
	}
}

float Rva00427157::rva004270FA(int index)
{
	return m_vals[index];
}

void Rva00427114Parse(INI *ini, Rva00427157 *store)
{
	const char *key = ini->getNextToken(0);
	const char *val = ini->getNextToken(0);
	float f = ini->dup_002EE10(val);
	int idx = ini->scanIndexList(key, g_00DC85C4);
	store->m_vals[idx] = f;
}

typedef _STL::hash_map<NameKeyType, const Rva00427157 *, rts::hash<NameKeyType>, _STL::equal_to<NameKeyType> > ArmorMap;

class LivingWorldAutoResolveArmorStore
{
public:
	const Rva00427157 *find(const AsciiString &name);
	const Rva00427157 *getDefault();
	static void parseArmorDefinition(INI *ini);
private:
	char m_pad[0xC];
	ArmorMap m_map;
};

const Rva00427157 *LivingWorldAutoResolveArmorStore::find(const AsciiString &name)
{
	NameKeyType key = TheNameKeyGenerator->nameToKey(name);
	ArmorMap::const_iterator it = m_map.find(key);
	if (it != m_map.end())
		return it->second;
	return (const Rva00427157 *)it._M_cur;
}

const Rva00427157 *LivingWorldAutoResolveArmorStore::getDefault()
{
	AsciiString name("AutoResolve_DefaultArmor");
	return find(name);
}

extern LivingWorldAutoResolveArmorStore *TheLivingWorldAutoResolveArmorStore;

void LivingWorldAutoResolveArmorStore::parseArmorDefinition(INI *ini)
{
	const char *token = ini->getNextToken(0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(token);
	const Rva00427157 *defaultArmor = TheLivingWorldAutoResolveArmorStore->getDefault();
	ArmorMap &armorMap = TheLivingWorldAutoResolveArmorStore->m_map;
	ArmorMap::iterator it;
	it = armorMap.find(key);
	if (it != armorMap.end())
	{
		Rva00427157 local(AsciiString(token), defaultArmor);
		ini->initFromINI(&local, g_00C3C614);
		return;
	}
	Rva00427157 *p = new Rva00427157(AsciiString(token), defaultArmor);
	TheLivingWorldAutoResolveArmorStore->m_map[key] = p;
	ini->initFromINI(p, g_00C3C614);
}


struct INIException
{
	char *mFailureMessage;
	int mErrorCode;
	INIException(int argCount, const char *format, ...);
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
struct Rva00427294ThrowInfoAnchor { int a; int b; int c; int d; };
static const Rva00427294ThrowInfoAnchor rva00427294ThrowInfoAnchor = { 0, 0, 0, 0 };

void __cdecl Rva00427294Parse(INI *ini, void *dummy1, void *instance, void *dummy2)
{
	const char *token = ini->getNextToken(0);
	*(const Rva00427157 **)instance = TheLivingWorldAutoResolveArmorStore->find(AsciiString(token));
	if (*(const Rva00427157 **)instance == 0)
	{
		INIException e(1, "Unknown LivingWorldAutoResolveArmor %s", token);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&rva00427294ThrowInfoAnchor);
	}
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_00DC85C4@@3PAPBDA=?g_Va00DC85C4Names@@3PAPBDA")
