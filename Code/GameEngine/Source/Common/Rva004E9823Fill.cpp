// cl: /O1 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva004E9823@Rva004E9823@@QAEXPBVModuleData@@@Z @ 0x004E9823, 137 bytes.
// Armor-gated registry fill: look up parent's armor name through the ArmorStore
// at g_00E0312C via rowed find 0x0041F474, new a 0x188-byte SkirmishAI with
// (parent, armor, map-empty) via rowed ctor 0x002C6EE0, file it under the
// parent's +0x54 key via rowed map<int,int>::operator[] 0x0028932C, push the
// parent via rowed vector<const ModuleData*>::push_back 0x004DFCB0, set +0x24.
// The +0x4 read is the map's own node count (size() == 0 inlined).
// The historical ModuleData/ArmorTemplate names below are opaque ABI views.
// The named SkirmishAI provider establishes the constructor receiver and
// Player argument; this caller does not prove the registry's semantic type.
#include <map>
#include <vector>
#include <new>

class AsciiString;
class ModuleData;
class ArmorTemplate;
class Player;

class ArmorStore
{
public:
	const ArmorTemplate *rva0041F474(const AsciiString &name) const;
};

ArmorStore *g_00E0312C = 0;

class SkirmishAI
{
public:
	SkirmishAI(Player *player, void *master, bool first);

private:
	char m_pad[0x188];
};

class Rva004E9823
{
public:
	void rva004E9823(const ModuleData *parent);

private:
	_STL::map<int, int> m_map; // +0x0
	_STL::vector<const ModuleData *> m_vec; // +0xC
	char m_pad18[0x24 - 0x18]; // +0x18
	bool m_24; // +0x24
};

void Rva004E9823::rva004E9823(const ModuleData *parent)
{
	const AsciiString *name = (const AsciiString *)((const char *)parent + 0x58);
	const ArmorTemplate *armor = g_00E0312C->rva0041F474(*name);
	SkirmishAI *p = new SkirmishAI((Player *)parent, (void *)armor, m_map.size() == 0);
	int key = *(const int *)((const char *)parent + 0x54);
	m_map[key] = (int)p;
	m_vec.push_back(parent);
	m_24 = true;
}
