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

class Rva001E46E1
{
public:
	float rva001E46E1(Object *obj);
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

struct ListNode
{
	ListNode *m_next;
	char m_pad04[4];
	Object *m_obj;
};

class AIGroup
{
public:
	void cohereMoveSpeed();

private:
	char m_pad00[4];
	ListNode *m_head;
};

void AIGroup::cohereMoveSpeed()
{
	ListNode *head = m_head;
	float best = g_00BBB9AC;
	for (ListNode *node = head->m_next; node != head; node = node->m_next) {
		Object *obj = node->m_obj;
		const Rva0028AC4EEntry *entry = obj->rva0028AC4E();
		if (entry != 0) {
			float m = ((const Rva0008BB38FloatField *)entry)->get();
			if (m > 0.0f) {
				((Rva0028AC4EEntry *)entry)->m_2C = g_00BBB9AC;
				float v = ((Rva001E46E1 *)entry)->rva001E46E1(obj);
				if (v > 0.0f) {
					if (best > v || best == g_00BBB9AC)
						best = v;
				}
			}
		}
	}
	for (ListNode *node = m_head->m_next; node != head; node = node->m_next) {
		Object *obj = node->m_obj;
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
