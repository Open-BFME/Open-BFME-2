// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0049D2BE@Rva0049D2BE@@QAEME@Z @0x0049D2BE 127B ret 4.
// Same product as 0x0049D1CA. A node counts when flag selects byte +0x11
// and flag is set, or byte +0x10 and flag is clear. Scale is at +8.

class AsciiString;
class UpgradeTemplate;

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

struct Rva0049D2BEValue
{
	char m_name[4];
	char m_pad[4];
	float m_scale;
	char m_gap[4];
	unsigned char m_10;
	unsigned char m_11;
};

struct Rva0049D2BENode
{
	Rva0049D2BENode *m_next;
	Rva0049D2BENode *m_prev;
	Rva0049D2BEValue *m_value;
};

struct Rva0049D2BEHolder
{
	char m_pad[0x3C];
	Rva0049D2BENode *m_list;
};

class Rva0049D2BE
{
public:
	float rva0049D2BE(unsigned char flag);
};

float Rva0049D2BE::rva0049D2BE(unsigned char flag)
{
	float acc = 1.0f;
	Rva0049D2BEHolder *holder = *(Rva0049D2BEHolder **)((char *)this - 0x1C);
	Rva0049D2BENode *head = holder->m_list;
	Rva0049D2BENode *node = head->m_next;
	if (node != head)
	{
		do
		{
			Rva0049D2BEValue *value = node->m_value;
			if (value->m_11 != 0 && flag != 0)
				goto accept;
			if (value->m_10 == 0 || flag != 0)
				goto next;
		accept:
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
