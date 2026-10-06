// cl: /Ob0

struct BfmeShapeE15
{
	char m[0x24];
};

// g_bfmeBadE15: VA 0x00DDBFF0 (.data); preserve the exact opaque 36-byte
// retail payload. The local type proves extent only; member meanings are not asserted.
BfmeShapeE15 g_bfmeBadE15 = {{
	0, 0, 0, 0, 0, 0, -128, 63, 0, 0, -128, 63,
	0, 0, -128, 63, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0
}};

class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(int i);
	char m_00[0x2C];
	BfmeShapeE15 *volatile m_start;
	BfmeShapeE15 *m_finish;
};

BfmeShapeE15 *BfmeObjE15::bfmeAtE15(int i)
{
	if (i >= 0)
	{
		if ((unsigned)i < (unsigned)(m_finish - m_start))
			return m_start + i;
	}
	return &g_bfmeBadE15;
}
