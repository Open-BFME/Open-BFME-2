// cl: /DNDEBUG /MD /EHs-c-
// ?rva002C9DF5@Weapon@@QBEXPBVObject@@PBX@Z
//
// retail 0x002C9DF5 (83 bytes). Unlock: Player iterate with template+0x28 squared range.
// Controlling player via Object getControllingPlayer (rowed 0x0028AFA9); if null return;
// else iterateObjects (pinned 0x002AB08B) with callback 0x006C9D47 and 12B userdata
// {source, other, squared range}. Evidence: [ecx+4] WeaponTemplate, +0x28 float;
// callers 0x002CE363; neighbours WeaponIsWithinTargetPitch.cpp.

class Object;
class Player;

typedef int (__cdecl *ObjectIterateFunc)(Object *obj, void *userData);

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	int iterateObjects(ObjectIterateFunc func, void *userData) const;
};

struct WeaponTemplateRange
{
	char m_pad00[0x28];
	float m_range; // +0x28
};

struct IterateData
{
	const Object *m_source; // +0
	const void *m_other; // +4
	float m_rangeSqr; // +8
};

void __cdecl Rva006C9D47(Object *obj, void *userData);

class Weapon
{
public:
	void rva002C9DF5(const Object *source, const void *other) const;

private:
	char m_pad00[4];
	const WeaponTemplateRange *m_template; // +4
};

void Weapon::rva002C9DF5(const Object *source, const void *other) const
{
	Player *player = source->getControllingPlayer();
	if (player == 0)
		return;
	IterateData data;
	data.m_source = source;
	data.m_other = other;
	data.m_rangeSqr = 0.0f;
	float range = m_template->m_range;
	data.m_rangeSqr = range * range;
	player->iterateObjects((int (*)(Object *, void *))Rva006C9D47, &data);
}
