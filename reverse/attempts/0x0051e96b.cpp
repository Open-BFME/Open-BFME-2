// ?Rva0051E96B@Holder0051E96B@@QAEMH@Z
// partial score=0.75 date=2026-10-06
// cl: /O1 /MD
// Range-27 strided table float lookup.
// ?Rva0051E96B@Holder0051E96B@@QAEMH@Z @0x0051E96B 103B
// Thiscall float lookup: this+4 points at a range descriptor whose
// +0x14/+0x18 bound a 20-byte-stride table. An index below 0 or above
// the element count answers BfmeZeroRange (0.0 at 0x00BBAEAC). Otherwise
// this+8 selects the field: 0/1 short at +0xC/+0xE, 2 int at +4, 4/5
// float at +8 (x87 fild/fld); any other mode answers BfmeZeroRange.
extern const float BfmeZeroRange;

struct Data0051E96B
{
	char m_pad[0x14];
	int m_14;
	int m_18;
};

struct Holder0051E96B
{
	char m_pad[4];
	Data0051E96B *m_4;
	int m_8;
	float Rva0051E96B(int index);
};

float Holder0051E96B::Rva0051E96B(int index)
{
	if (index >= 0)
	{
		unsigned count = (unsigned)((m_4->m_18 - m_4->m_14) / 20);
		if ((unsigned)index <= count)
		{
			int mode = m_8;
			index *= 20;
			index += m_4->m_14;
			char *elem = (char *)index;
			switch (mode)
			{
			case 0:
				return (float)*(short *)(elem + 0xC);
			case 1:
				return (float)*(short *)(elem + 0xE);
			case 2:
				return (float)*(int *)(elem + 4);
			case 4:
				return *(float *)(elem + 8);
			default:
				break;
			}
		}
	}
	return BfmeZeroRange;
}
