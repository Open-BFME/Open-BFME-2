// cl: /O1 /DNDEBUG /MD /EHsc
// ?rva002E7482@Rva002E7482@@QAEMH@Z @0x002E7482 42B
// Float getter: if Rva001E3679(idx) is false return BfmeZeroRange else return
// (float)item[idx].m_val where items start at +0x9C with stride 64.
// Evidence: calls rowed ?Rva001E3679@@YA_NH@Z; uses extern BfmeZeroRange
// ?BfmeZeroRange@@3MB; callers at 0x00062D68 0x002EF82D 0x002EF846 0x002EF8E0.

bool __cdecl Rva001E3679(int index);
extern const float BfmeZeroRange;

struct Rva002E7482Item
{
	int m_val;
	char m_pad[60];
};

class Rva002E7482
{
public:
	float rva002E7482(int index);

private:
	char m_pad[0x9C];
	Rva002E7482Item m_items[16];
};

float Rva002E7482::rva002E7482(int index)
{
	if (!Rva001E3679(index))
		return BfmeZeroRange;
	return (float)m_items[index].m_val;
}
