// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0027F09F@Rva0027F09F@@QAEXHH@Z @0x0027F09F 52B
// Search pointer array at +0x578..+0x57C for entry whose target +0xC equals key then run rowed countdown on same this.
// Evidence: callees rva0027D378 0x0027D378 rowed; caller 0x00288227 unclaimed 1599B; array step 4 element deref +0xC compare.
class Rva0027D378
{
public:
	int rva0027D378(void *p, int amount);
};

struct Rva0027F09FTarget
{
	char m_pad00[0xc];
	int m_field0C;
};

class Rva0027F09F
{
public:
	void rva0027F09F(int key, int amount);
private:
	char m_pad00[0x578];
	Rva0027F09FTarget **m_begin578;
	Rva0027F09FTarget **m_end57C;
};

void Rva0027F09F::rva0027F09F(int key, int amount)
{
	Rva0027F09FTarget **begin = m_begin578;
	Rva0027F09FTarget **end = m_end57C;
	if (begin == end)
		return;
	Rva0027F09FTarget **it = begin;
	do
	{
		if ((*it)->m_field0C == key)
		{
			((Rva0027D378 *)this)->rva0027D378(*it, amount);
			return;
		}
		++it;
	} while (it != end);
}
