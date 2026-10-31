// cl: /DNDEBUG /MD
//
// ?cohereMoveSpeed@AIGroup@@QAEXXZ, retail 0x0036DF92, 223B.
// AIGroup two-pass member walk: first finds the minimum positive worker
// value, second spreads it to members without a victim. Evidence: caller at
// 0x00372C05 calls AIGroup::isIdle then this then 0x003705C2 on the same this;
// list head at +4 with next at +0 and Object at +8 (same as Rva0036E346
// neighbours); Object+0x258 AIUpdate with rowed getCurrentVictim; entry via
// rowed Object::rva0028AC4E with disp8 float at +0x40 and pinned worker
// 0x001E46E1 writing +0x2C; sentinel -1.0f at g_00BBB9AC.

#include <list>


extern float g_00BBB9AC;

class Object;
class AIUpdateInterface;

class Rva0008BB38FloatField
{
public:
	float get() const;
};

struct Rva0028AC4EEntry
{
	char m_pad00[0x2C];
	float m_2C;
	char m_pad30[0x40 - 0x30];
	float m_40;
};

class Locomotor
{
public:
	float getMaxSpeed(Object *obj) const;
};

class Object
{
public:
	const struct Rva0028AC4EEntry *rva0028AC4E() const;
	char m_pad00[0x258];
	AIUpdateInterface *m_ai;
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class AIGroup
{
public:
	void cohereMoveSpeed();

private:
	std::list<Object *> m_memberList;
};

void AIGroup::cohereMoveSpeed()
{
	std::list<Object *>::iterator head = m_memberList.end();
	float best = g_00BBB9AC;
	for (std::list<Object *>::iterator node = m_memberList.begin(); node != head; ++node) {
		Object *obj = *node;
		const Rva0028AC4EEntry *entry = obj->rva0028AC4E();
		if (entry != 0) {
			float m = ((const Rva0008BB38FloatField *)entry)->get();
			if (m > 0.0f) {
				((Rva0028AC4EEntry *)entry)->m_2C = g_00BBB9AC;
				float v = ((Locomotor *)entry)->getMaxSpeed(obj);
				if (v > 0.0f) {
					if (best > v || best == g_00BBB9AC)
						best = v;
				}
			}
		}
	}
	for (std::list<Object *>::iterator node = m_memberList.begin(); node != head; ++node) {
		Object *obj = *node;
		const Rva0028AC4EEntry *entry = obj->rva0028AC4E();
		if (entry == 0)
			continue;
		AIUpdateInterface *ai = obj->m_ai;
		if (ai != 0) {
			Object *victim = ai->getCurrentVictim();
			if (victim == 0) {
				((Rva0028AC4EEntry *)entry)->m_2C = best;
				continue;
			}
		}
		((Rva0028AC4EEntry *)entry)->m_2C = g_00BBB9AC;
	}
}
