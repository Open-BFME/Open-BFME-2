// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0027F2D6@Rva0027F2D6@@QAEXH@Z @0x0027F2D6 52B
// Search pointer array at +0x578..+0x57C for entry whose target +0xC equals key then run rowed countdown with target+0x28.
// Evidence: same layout as sibling 0x0027F09F; callee rva0027D378 0x0027D378 rowed; caller 0x000ECADA unclaimed 936B.
class Rva0027D378
{
public:
	int rva0027D378(void *p, int amount);
};

struct Rva0027F2D6Target
{
	char m_pad00[0xc];
	int m_field0C;
	char m_pad10[0x18];
	int m_field28;
};

class Rva0027F2D6
{
public:
	void rva0027F2D6(int key);
private:
	char m_pad00[0x578];
	Rva0027F2D6Target **m_begin578;
	Rva0027F2D6Target **m_end57C;
};

void Rva0027F2D6::rva0027F2D6(int key)
{
	Rva0027F2D6Target **begin = m_begin578;
	Rva0027F2D6Target **end = m_end57C;
	if (begin >= end)
		return;
	Rva0027F2D6Target **it = begin;
	do
	{
		if ((*it)->m_field0C == key)
		{
			((Rva0027D378 *)this)->rva0027D378(*it, (*it)->m_field28);
			return;
		}
		++it;
	} while (it < end);
}
