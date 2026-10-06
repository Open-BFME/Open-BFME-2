// ?evaluateNumPlayersInGame@ScriptConditions@@IAE_NPAUCondA003E53C8@@PAUCondB003E53C8@@@Z
// retail 0x003E53C8, 114 bytes.
// Evidence: chain lane via rowed PlayerList::rva002A7C0B 0x002A7C0B; ThePlayerList 0x009FEEE8; two condition structs with int at +8; switch 0..5 to setl/setle/sete/setge/setg/setne.
// flags: region default (reverse/retail_inventory/flag_regions.csv)

class PlayerList
{
public:
	int rva002A7C0B(bool flag);
};

extern PlayerList *ThePlayerList;

struct CondA003E53C8
{
	char m_pad[8];
	int m_op;
};

struct CondB003E53C8
{
	char m_pad[8];
	int m_value;
};

class ScriptConditions
{
protected:
	bool evaluateNumPlayersInGame(CondA003E53C8 *a, CondB003E53C8 *b);
};

bool ScriptConditions::evaluateNumPlayersInGame(CondA003E53C8 *a, CondB003E53C8 *b)
{
	int count = ThePlayerList->rva002A7C0B(false);
	int op = a->m_op;
	bool result = false;

	switch (op)
	{
	case 0:
		result = count < b->m_value;
		break;
	case 1:
		result = count <= b->m_value;
		break;
	case 2:
		result = count == b->m_value;
		break;
	case 3:
		result = count >= b->m_value;
		break;
	case 4:
		result = count > b->m_value;
		break;
	case 5:
		result = count != b->m_value;
		break;
	default:
		break;
	}

	return result;
}
