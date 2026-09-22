// ?j_0000ca59@Glo012F1024Item@@QAE_NXZ
// partial score=0.65 date=2026-09-22
// cl: /O1 /DNDEBUG /MD /EHsc

class Glo012F1024ItemBank
{
public:
	bool refreshCheck(void);
	char m_pad54[0x54];
	char *m_thirdBegin; // +0x54
	char *m_thirdEnd; // +0x58
	int m_unk5C;
	char *m_fourthBegin; // +0x60
	char *m_fourthEnd; // +0x64
	int m_unk68;
	char *m_secondBegin; // +0x6C
	char *m_secondEnd; // +0x70
	int m_unk74;
	char *m_firstBegin; // +0x78
	char *m_firstEnd; // +0x7C
};

bool Glo012F1024ItemBank::refreshCheck(void)
{
	char *cursor;
	int index;
	int total;

	cursor = m_firstBegin + 0x0C;
	index = 0;
	total = (m_firstEnd - m_firstBegin) >> 4;
	if (total == 0)
		goto second;
	do
	{
		if (*cursor)
			return true;
		index++;
		cursor += 0x10;
		total = (m_firstEnd - m_firstBegin) >> 4;
	} while (index < total);
second:
	cursor = m_secondBegin + 0x10;
	index = 0;
	total = (m_secondEnd - m_secondBegin) / 20;
	if (total == 0)
		goto third;
	do
	{
		if (*cursor)
			return true;
		index++;
		cursor += 0x14;
		total = (m_secondEnd - m_secondBegin) / 20;
	} while (index < total);
third:
	cursor = m_thirdBegin + 0x1C;
	index = 0;
	total = (m_thirdEnd - m_thirdBegin) >> 5;
	if (total == 0)
		goto fourth;
	do
	{
		if (*cursor)
			return true;
		index++;
		cursor += 0x20;
		total = (m_thirdEnd - m_thirdBegin) >> 5;
	} while (index < total);
fourth:
	cursor = m_fourthBegin + 8;
	index = 0;
	total = (m_fourthEnd - m_fourthBegin) / 24;
	if (total == 0)
		goto done;
	do
	{
		if (*cursor)
			return true;
		index++;
		cursor += 0x18;
		total = (m_fourthEnd - m_fourthBegin) / 24;
	} while (index < total);
done:
	return false;
}
