// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva0049D33D@Rva0049D33D@@QAEME@Z @0x0049D33D 127B ret 4.
// Same gate as 0x0049D2BE. The counted float sits at value+0xC.

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

struct Rva0049D33DValue
{
	char m_name[4];
	char m_pad[8];
	float m_scale;
	unsigned char m_10;
	unsigned char m_11;
};

struct Rva0049D33DNode
{
	Rva0049D33DNode *m_next;
	Rva0049D33DNode *m_prev;
	Rva0049D33DValue *m_value;
};

struct Rva0049D33DHolder
{
	char m_pad[0x3C];
	Rva0049D33DNode *m_list;
};

class Rva0049D33D
{
public:
	float rva0049D33D(unsigned char flag);
};

float Rva0049D33D::rva0049D33D(unsigned char flag)
{
	float acc = 1.0f;
	Rva0049D33DHolder *holder = *(Rva0049D33DHolder **)((char *)this - 0x1C);
	Rva0049D33DNode *head = holder->m_list;
	Rva0049D33DNode *node = head->m_next;
	if (node != head)
	{
		do
		{
			Rva0049D33DValue *value = node->m_value;
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
