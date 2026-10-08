// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0049D1CA@Rva0049D1CA@@QAEMPBVThingTemplate@@@Z @0x0049D1CA 122B ret 4.
// Product of the +8 floats on the list at [this-0x1C]+0x3C, starting at 1.
// A node counts when its filter accepts the template and the upgrade is
// absent or present on the object at this-0x18.

class ThingTemplate;
class Player;
class AsciiString;
class UpgradeTemplate;

class ObjectFilter
{
public:
	bool testTemplate(const ThingTemplate *tmpl, const Player *a, const Player *b);
 int m_id;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class Object
{
public:
	bool rva00290D2B(const UpgradeTemplate *upgrade) const;
};

struct Rva0049D1CAValue
{
	char m_name[4];
	ObjectFilter m_filter;
	float m_scale;
};

struct Rva0049D1CANode
{
	Rva0049D1CANode *m_next;
	Rva0049D1CANode *m_prev;
	Rva0049D1CAValue *m_value;
};

struct Rva0049D1CAHolder
{
	char m_pad[0x3C];
	Rva0049D1CANode *m_list;
};

class Rva0049D1CA
{
public:
	float rva0049D1CA(const ThingTemplate *tmpl);
};

float Rva0049D1CA::rva0049D1CA(const ThingTemplate *tmpl)
{
	float acc = 1.0f;
	Rva0049D1CAHolder *holder = *(Rva0049D1CAHolder **)((char *)this - 0x1C);
	Rva0049D1CANode *head = holder->m_list;
	Rva0049D1CANode *node = head->m_next;
	if (node != head)
	{
		do
		{
			Rva0049D1CAValue *value = node->m_value;
			if (value->m_filter.testTemplate(tmpl, 0, 0))
			{
				const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(*(const AsciiString *)value);
				if (upgrade != 0)
				{
					Object *target = *(Object **)((char *)this - 0x18);
					if (target->rva00290D2B(upgrade) == 0)
						goto next;
				}
				acc *= value->m_scale;
			}
		next:
			node = node->m_next;
		}
		while (node != holder->m_list);
	}
	return acc;
}
