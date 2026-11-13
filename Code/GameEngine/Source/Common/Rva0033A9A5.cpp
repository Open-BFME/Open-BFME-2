// cl: /MD
// ?getCurrentLivingWorldAutoResolveArmor@Rva0033A9A5@@QAEPBVRva00427157@@PBX@Z @0x0033A9A5 61B.
// Array scan over 0x104 entries from +0x3EC to +0x3F0 via rowed
// Rva0033A8D9 tester; on match return entry armor else rowed
// LivingWorldAutoResolveArmorStore::getDefault via g_00E031F0.
// Evidence: rowed 0x0033A8D9 plus rowed 0x0042724D plus ret-4.
class Rva00427157;

class Rva0033A8D9
{
public:
	bool rva0033A8D9(const void *mask) const;
};

struct AutoResolveArmorEntry
{
	const Rva00427157 *armor;
	char m_pad[0x104 - 4];
};

#include "../../Include/Common/LivingWorldAutoResolveArmorStore.h"

class LivingWorldAutoResolveArmorStore; extern LivingWorldAutoResolveArmorStore *TheLivingWorldAutoResolveArmorStore;

class Rva0033A9A5
{
public:
	const Rva00427157 *getCurrentLivingWorldAutoResolveArmor(const void *arg);

private:
	char m_pad[0x3EC];
	AutoResolveArmorEntry *m_begin;
	AutoResolveArmorEntry *m_end;
};

const Rva00427157 *Rva0033A9A5::getCurrentLivingWorldAutoResolveArmor(const void *arg)
{
	AutoResolveArmorEntry *begin = m_begin;
	AutoResolveArmorEntry *end = m_end;
	for (AutoResolveArmorEntry *entry = begin; entry != end; entry = (AutoResolveArmorEntry *)((char *)entry + 0x104)) {
		if (((const Rva0033A8D9 *)entry)->rva0033A8D9(arg))
			return entry->armor;
	}
	return TheLivingWorldAutoResolveArmorStore->getDefault();
}
