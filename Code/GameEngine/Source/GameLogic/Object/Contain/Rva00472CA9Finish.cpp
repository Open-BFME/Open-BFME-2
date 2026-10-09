// cl: /MD /Oa
// stlport
#include <map>

enum WeaponSetType
{
	WST_0 = 0
};

class Object
{
public:
	void setWeaponSetFlag(WeaponSetType t);
	void clearWeaponSetFlag(WeaponSetType t);
	unsigned char m_pad[0x74];
	int m_id;
};

class Rva00469294
{
public:
	void *rva00469294(int key);
};

class BfmeObject872Header
{
	char m_bytes[16];
public:
	BfmeObject872Header(const BfmeObject872Header &other);
};

struct HordeContainSlot
{
	int m_key;
	char m_pad[0x18];
};

class HordeContain
{
public:
	// Slot 32 of HordeContain's vftable 0x00C45050 (inherited unchanged by
	// HorseHordeContain and AODHordeContain): virtual, with the vptr at +0.
	virtual void rva00472CA9(Object *obj);
private:
	Rva00469294 *m_4;
	unsigned char m_pad2[0x17C - 0x8];
	_STL::map<int, int> m_map;
	HordeContainSlot *m_slots;
};

void HordeContain::rva00472CA9(Object *obj)
{
	int id = obj->m_id;
	int v = m_map[id];
	int key = *(int *)((char *)m_slots + v * 0x1C);
	void *e = m_4->rva00469294(key);
	if (!e)
		return;
	if (*(unsigned char *)((char *)e + 0x34) == 0)
		return;
	BfmeObject872Header h1(*(BfmeObject872Header *)((char *)e + 0x14));
	BfmeObject872Header h2(*(BfmeObject872Header *)((char *)e + 0x24));
	for (int i = 0; i < 0x68; ++i) {
		unsigned int bit = 1u << (i & 31);
		unsigned int word = ((unsigned int)i >> 5) * 4;
		if (*(unsigned int *)((char *)&h1 + word) & bit)
			obj->setWeaponSetFlag((WeaponSetType)i);
		else if (*(unsigned int *)((char *)&h2 + word) & bit)
			obj->clearWeaponSetFlag((WeaponSetType)i);
	}
}
