// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine

struct Rva00355640Key
{
	int m_pad;
	int m_index;
};

struct Rva003558C0Key
{
	int m_pad;
	int m_index;
	int m_value;
};

struct Rva00354400Elem
{
	char m_pad[0x0E];
	short m_0e;
	char m_tail[4];
};

struct Rva003558A0Elem
{
	char m_pad[0x10];
	int m_10;
};

class Rva003558C0Arr
{
public:
	bool matches(const Rva003558C0Key *key);

	char m_pad[0x18];
	Rva00354400Elem *m_items;
};

class Rva003558A0Arr
{
public:
	int get(const Rva00355640Key *key);

	char m_pad[0x18];
	Rva003558A0Elem *m_items;
};

class Rva00355950Arr
{
public:
	bool matches(const Rva003558C0Key *key);

	char m_pad[0x38];
	Rva00354400Elem *m_items;
};

class Rva00355930Arr
{
public:
	int get(const Rva00355640Key *key);

	char m_pad[0x38];
	Rva003558A0Elem *m_items;
};

struct Rva003412E0Node
{
	Rva003412E0Node *next;
	int index;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void applyNamed(void *obj, void *slot);
	void walkNamed(Rva00355950Arr *arr, Rva003412E0Node *node, bool filter);
	void walkChild(Rva003558C0Arr *arr, Rva003412E0Node *node);
};

void ScriptEngine::walkChild(Rva003558C0Arr *arr, Rva003412E0Node *node)
{
	Rva003412E0Node *cur = node;
	if (!cur)
		return;
	do
	{
		if (arr->matches((const Rva003558C0Key *)cur))
		{
			int obj = ((Rva003558A0Arr *)arr)->get((const Rva00355640Key *)cur);
			unsigned char *p = (unsigned char *)obj;
			if (p[0x0C] && !p[0x0D])
			{
				walkNamed((Rva00355950Arr *)arr, *(Rva003412E0Node **)(p + 8), true);
				walkChild(arr, *(Rva003412E0Node **)(p + 4));
			}
		}
		cur = cur->next;
	} while (cur);
}
