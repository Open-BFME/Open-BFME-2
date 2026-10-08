// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0049D244@Rva0049D244@@QAEMPBVThingTemplate@@@Z @0x0049D244 122B ret 4.
// Same product as 0x0049D1CA. The counted float sits at value+0xC.

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

struct Rva0049D244Value
{
	char m_name[4];
	ObjectFilter m_filter;
	char m_gap[4];
	float m_scale;
};

struct Rva0049D244Node
{
	Rva0049D244Node *m_next;
	Rva0049D244Node *m_prev;
	Rva0049D244Value *m_value;
};

struct Rva0049D244Holder
{
	char m_pad[0x3C];
	Rva0049D244Node *m_list;
};

class Rva0049D244
{
public:
	float rva0049D244(const ThingTemplate *tmpl);
};

float Rva0049D244::rva0049D244(const ThingTemplate *tmpl)
{
	float acc = 1.0f;
	Rva0049D244Holder *holder = *(Rva0049D244Holder **)((char *)this - 0x1C);
	Rva0049D244Node *head = holder->m_list;
	Rva0049D244Node *node = head->m_next;
	if (node != head)
	{
		do
		{
			Rva0049D244Value *value = node->m_value;
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
