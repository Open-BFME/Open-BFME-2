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

// The scanner's expansion call targets the independently matched five-entity
// decoder at 5426DB. Its char/unsigned-char donor view uses the same pointer
// ABI and 0/1 AL result as the decoder's bool/unsigned-char view.
#pragma comment(linker, "/alternatename:?bfmeExpandEAN@BfmeLexEAN@@QAEDPAD@Z=?rva005426DB@Rva005426DB@@QAE_NPAE@Z")

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

// Donor1281192f68 BfmeConv2008.cpp /O1 supplies this complete107B body.
// Target Ghidra542459 and rowed scanner542791 establish the same lexer;
// source-line pointer+8 and state clears+0/+4/+8/+C are retail facts.
// The dead local line copy is preserved because the target emits it.
extern "C" __declspec(dllimport) char *__cdecl strncpy(
	char *destination, const char *source, unsigned int count);

int BfmeLexEAN::bfmeFailEAN(int code)
{
	BfmeLexEAN *self = this;
	char line[0x104];
	int length = 0;

	line[0] = 0;
	if (self->m_bfmeSourceEAN != 0)
	{
		char *cursor = self->m_bfmeSourceEAN;
		while (*cursor != 0 && *cursor != '\n')
		{
			++length;
			++cursor;
		}

		if (length != 0)
		{
			if (length >= 0x104)
				length = 0x103;
			strncpy(line, self->m_bfmeSourceEAN, length);
		}
	}

	self->m_bfmePosEAN = 0;
	self->m_bfmeLineNumberEAN = 0;
	self->m_bfmeSourceEAN = 0;
	self->m_bfmeLineEAN = 0;
	return code;
}

