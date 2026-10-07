// ?rva002B8660@Rva002B8660@@QAEPAXHH@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8660@Rva002B8660@@QAEPAXHH@Z @0x002B8660 74B. Multimap insert at this+0x13c with key from spawn-army +0x4c and value from arg +0x14 after LivingWorldCampaignManager::UseGenericSpawnArmyForPlayer; same +0x13c/+0x4c/+0x14 shape as rowed neighbour Rva002B86AA lookup at 0x002B86AA; prev 0x002B8644 next 0x002B86AA contiguous; callees rowed 0x003B8CE0 and 0x004FF876; caller 0x0059E7AA; address-derived honest name.
// Evidence: retail push ebp mov ebp esp push ecx2 push ebx mov ebx ebp+C push esi push edi push ebx push ebp+8 mov edi ecx mov ecx [0xE02D6C] call 0x3B8CE0 mov esi eax test je mov eax [esi+4C] mov ecx [ebx+14] mov ebp-8 eax lea push lea push lea ecx [edi+13C] call 0x4FF876 pop edi mov eax esi pop esi pop ebx leave ret 8.
#include <map>

typedef int Int;

class LivingWorldCampaignManager
{
public:
	void *UseGenericSpawnArmyForPlayer(Int a, Int b);
};

extern LivingWorldCampaignManager *g_00E02D6C;

struct Rva002B8660Key
{
	char m_pad00[0x4c];
	Int m_4c;
};

struct Rva002B8660Val
{
	char m_pad00[0x14];
	Int m_14;
};

class Rva002B8660
{
public:
	void *rva002B8660(Int a, Int b);
private:
	char m_pad00[0x13c];
	_STL::multimap<Int, Int> m_map13C;
};

void *Rva002B8660::rva002B8660(Int a, Int b)
{
	void *army = g_00E02D6C->UseGenericSpawnArmyForPlayer(a, b);
	if (army)
		m_map13C.insert(_STL::multimap<Int, Int>::value_type(((Rva002B8660Key *)army)->m_4c, ((Rva002B8660Val *)b)->m_14));
	return army;
}
