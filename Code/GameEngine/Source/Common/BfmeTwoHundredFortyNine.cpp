// cl: /Od

struct BfmeThingOL
{
	unsigned char m_bfmeHead[0xcc];
	int m_bfmeKind;
};

int bfmeGroupOL(const BfmeThingOL *what)
{
	if (what->m_bfmeKind == 2 || what->m_bfmeKind == 3)
		return 2;

	if (what->m_bfmeKind == 1 || what->m_bfmeKind == 7)
		return 1;

	if (what->m_bfmeKind == 4 || what->m_bfmeKind == 5)
		return 3;

	return 4;
}
