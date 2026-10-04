// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
class BfmeLexEAN
{
public:
	BfmeLexEAN(char *text, char *buffer, int limit);
	int bfmeScanEAN();
	char bfmeExpandEAN(char *out);
	int bfmeFailEAN(int code);

	char *m_bfmePosEAN;
	char *m_bfmeLineEAN;
	char *m_bfmeSourceEAN;
	int m_bfmeLineNumberEAN;
	int m_bfmeTagEAN;
	char *m_bfmeBufEAN;
	int m_bfmeLimitEAN;
	char *m_bfmeTailEAN;
	int m_bfmeDepthEAN;
	unsigned char m_bfmeSeenEAN;
	int m_bfmeMarkEAN;
	int m_bfmeStackEAN[0x61];
};

int BfmeLexEAN::bfmeScanEAN()
{
	int n = 0;

	for (;;)
	{
		char c = *m_bfmePosEAN;

		if (c == 0x26)
		{
			if (!bfmeExpandEAN(m_bfmeBufEAN + n))
				return bfmeFailEAN(-1);
		}
		else
		{
			m_bfmeBufEAN[n] = c;
		}

		c = *m_bfmePosEAN;

		if (c == 0x3c || c == 0)
			break;

		m_bfmePosEAN++;

		if (*m_bfmePosEAN == 0)
			return bfmeFailEAN(-1);

		if (n <= m_bfmeLimitEAN)
			n++;
	}

	m_bfmeBufEAN[n] = 0;

	m_bfmeTailEAN = m_bfmeBufEAN;

	return 3;
}
