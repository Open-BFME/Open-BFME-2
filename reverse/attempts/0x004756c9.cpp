// ?backAwaySomeMembersFrom@HordeContain@@UAEXPAVObject@@@Z
// partial score=0.9 date=2026-10-08
// Bank for ?backAwaySomeMembersFrom@HordeContain@@UAEXPAVObject@@@Z @0x004756C9 (525 B)
// Unit: Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp (/O1 /arch:SSE /G7). Apply the declarations below to that unit.
// Exact through the Coord3D::normalize call (0x475838) except the call to the
// unrowed STLport map<int,Rva00469155>::operator[] at 0x473F81 (needs a symbols.csv pin).
// Remaining diff: the scale/add tail. Retail loads cur.y/cur.z, s=dist*10, dir.y/dir.z
// into xmm3/xmm4, movaps xmm5,s; mulss xmm5,[dir.x]; mulss xmm3/xmm4 by s, then cur.x late
// into xmm0. cl here loads cur.x/y/z first and multiplies all dir components as memory
// operands. Tried: set/member/struct copies for pos and offset, explicit s, operand
// orders, z-y-x adds, block scopes, user dtor on Coord3D, CSE'd distance*10 -- no change
// or worse. Struct-copy offset (Coord3D offset = dir) gives retail's cur-load shape but
// keeps a movsd copy and dead stores.
#if 0 // declaration changes (git diff of the unit)
	void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
	void sub(const Coord3D *a) { x -= a->x; y -= a->y; z -= a->z; }
	void normalize();
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);
	unsigned char m_pad1D9[0x1DC - 0x1D9];
	int m_1DC; // +0x1DC (back-away frames, min and max)
	int m_1E0; // +0x1E0
	float m_1E4; // +0x1E4 (back-away distance, min and max)
	float m_1E8; // +0x1E8
	float m_1EC; // +0x1EC (chance a member backs away)
	float m_1F0; // +0x1F0 (zero: roll the chance)
	unsigned char m_pad1F4[0x224 - 0x1F4];
	virtual void gap102() = 0; virtual void backAwaySomeMembersFrom(Object *attacker) = 0; virtual void gap104() = 0; virtual void gap105() = 0;
// A backing-away member's goal: where it heads and for how many frames (the
// rowed default ctor 0x00469155 zeroes both).
class Rva00469155
{
public:
	Rva00469155();
	Coord3D m_pos; // +0x00
	int m_0C; // +0x0C
};
	virtual void backAwaySomeMembersFrom(Object *attacker);
	_STL::map<int, Rva00469155> m_1A0; // +0x1A0 (backing-away members by Object ID)
	unsigned char m_pad2A5[0x2B0 - 0x2A5];
	int m_2B0; // +0x2B0 (the Object ID members last backed away from)
	unsigned char m_pad2B4[0x2B8 - 0x2B4];

#endif
// ?backAwaySomeMembersFrom@HordeContain@@UAEXPAVObject@@@Z @0x004756C9: slot 103
// (WorldBuilder twin HordeContain::backAwaySomeMembersFrom). Unless the owner or
// the member carries status 0x45, a member backs away only on a roll under
// module data +0x1EC when +0x1F0 is zero. Each one that does gets a goal in the
// +0x1A0 map: its position pushed away from the attacker by a random distance
// times ten, for a random frame count. The attacker's ID is kept at +0x2B0 and
// the module wakes next frame.
void HordeContain::backAwaySomeMembersFrom(Object *attacker)
{
	if (!attacker)
		return;
	Coord3D attackerPos;
	attackerPos.set(attacker->getPosition());
	const _STL::list<Object *> *items = containedItems();
	const HordeContainModuleDataFields *data = fields();
	if (!data)
		return;
	bool disabled = m_object->testStatus((ObjectStatusTypes)0x45);
	for (_STL::list<Object *>::const_iterator it = items->begin(); it != items->end(); ++it)
	{
		Object *obj = *it;
		if (!disabled && !obj->testStatus((ObjectStatusTypes)0x45) && data->m_1F0 == 0.0f)
		{
			if (GetGameLogicRandomValueReal(0.0f, 1.0f, HORDECONTAIN_SOURCE_FILE, 8016) > data->m_1EC)
				continue;
		}
		float distance = GetGameLogicRandomValueReal(data->m_1E4, data->m_1E8, HORDECONTAIN_SOURCE_FILE, 8021);
		int frames = GetGameLogicRandomValue(data->m_1DC, data->m_1E0, HORDECONTAIN_SOURCE_FILE, 8022);
		Rva00469155 &goal = m_1A0[obj->getID()];
		Coord3D pos;
		{
			Coord3D dir;
			dir.x = obj->getPosition()->x;
			dir.y = obj->getPosition()->y;
			dir.z = obj->getPosition()->z;
			dir.x -= attackerPos.x;
			dir.y -= attackerPos.y;
			dir.z -= attackerPos.z;
			dir.normalize();
			dir.scale(distance * 10.0f);
			pos.set(obj->getPosition());
			pos.add(&dir);
		}
		goal.m_pos = pos;
		goal.m_0C = frames;
	}
	m_2B0 = attacker->getID();
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}
