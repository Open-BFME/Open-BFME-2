// cl: /Ob0

struct BfmeTailF5
{
	void copyFrom(const BfmeTailF5 *src);
};

struct BfmeElemF5
{
	int m_00;
	int m_04;
	int m_08;
	BfmeTailF5 m_0C;
};

BfmeElemF5 *bfmeFillF5(BfmeElemF5 *dest, unsigned n, const BfmeElemF5 *src)
{
	unsigned k = n;
	BfmeElemF5 *destCursor = dest;
	if (k > 0)
	{
		unsigned remaining = k;
		do
		{
			if (destCursor)
			{
				destCursor->m_00 = src->m_00;
				destCursor->m_04 = src->m_04;
				destCursor->m_08 = src->m_08;
				destCursor->m_0C.copyFrom(&src->m_0C);
			}
			++destCursor;
		} while (--remaining);
	}
	return destCursor;
}
