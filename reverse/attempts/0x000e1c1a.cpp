// ?rva000E1C1A@Rva000E1C1A@@QAEXPAH000000@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// @0x000E1C1A 311B. Find *key in the int span at +0x38B4, then walk the
// 0xD4 grid and expand four out-rects by 16 unless the element rejects it.

class Rva000E0EDD
{
public:
	bool rva000E0EDD(int index);
	void rva0011580A(int *key, int *arg1, int *arg6);
	char m_pad[0x64];
	float m_at64;
};

class Rva000E1C1A
{
public:
	void rva000E1C1A(int *key, int *arg1, int *minX, int *maxX, int *minY, int *maxY, int *arg6);

	char m_pad0[0x3888];
	char *m_base;
	int m_at388C;
	int m_cols;
	int m_rows;
	char m_pad3898[0x10];
	unsigned char m_flag;
	char m_pad38A9[3];
	int m_at38AC;
	float m_thresh;
	int *m_begin;
	int *m_end;
};

void Rva000E1C1A::rva000E1C1A(int *key, int *arg1, int *minX, int *maxX, int *minY, int *maxY, int *arg6)
{
	int found = -1;
	int i = 0;
	int zero = 0;
	if ((((char *)m_end - (char *)m_begin) & ~3) > 0)
	{
		int want = *key;
		int *p = m_begin;
		do
		{
			if (*p == want)
			{
				found = i;
				break;
			}
			++i;
			++p;
		} while (i < (m_end - m_begin));
	}
	int x = zero;
	if (m_cols > 0)
	{
		int xCoord = zero;
		for (; x < m_cols; ++x)
		{
			int y = zero;
			if (m_rows > 0)
			{
				int yCoord = zero;
				for (; y < m_rows; ++y)
				{
					Rva000E0EDD *el =
						(Rva000E0EDD *)(m_base + (y * m_cols + x) * 0xD4);
					if (!el->rva000E0EDD(found))
					{
						if (!(m_flag != 0 && m_at38AC < m_at388C && el->m_at64 > m_thresh))
						{
							el->rva0011580A(key, arg1, arg6);
							if (xCoord < *minX)
								*minX = xCoord;
							if (yCoord < *minY)
								*minY = yCoord;
							if (xCoord + 0x10 > *maxX)
								*maxX = xCoord + 0x10;
							if (yCoord + 0x10 > *maxY)
								*maxY = yCoord + 0x10;
						}
					}
					yCoord += 0x10;
				}
			}
			xCoord += 0x10;
		}
	}
}
