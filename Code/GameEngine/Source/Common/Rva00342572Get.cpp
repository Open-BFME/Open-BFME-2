// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00342572@Rva00342572@@QAEHXZ, retail 0x00342572, 46 bytes.
// Chain from 0x0033F8D4 (AIUpdateInterface::rva0033F8D4 FLT_MAX check).
// Gets AIUpdateInterface via this+0x18->+0x14->+0x258, calls the predicate;
// when false returns -1, when true copies its +0x1A0 int to +0x20 and
// returns 0. Callers none (leaf). Layout is pad to +0x18 plus pointer plus
// int at +0x20. Identity stays honest Rva.

class AIUpdateInterface
{
public:
	bool rva0033F8D4() const;

	char m_pad00[0x1A0];
	int m_1A0;
};

struct Mid00342572_14
{
	char m_pad00[0x258];
	AIUpdateInterface *m_258;
};

struct Mid00342572_18
{
	char m_pad00[0x14];
	Mid00342572_14 *m_14;
};

class Rva00342572
{
public:
	int rva00342572();

private:
	char m_pad00[0x18];
	Mid00342572_18 *m_18;
	char m_pad1C[0x20 - 0x1C];
	int m_20;
};

int Rva00342572::rva00342572()
{
	Mid00342572_14 *mid14 = m_18->m_14;
	AIUpdateInterface *ai = mid14->m_258;
	if (!ai->rva0033F8D4()) {
		return -1;
	}
	m_20 = ai->m_1A0;
	return 0;
}
