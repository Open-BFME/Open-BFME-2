// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// ?rva00052F1E@MilesAudioManager@@QAEHPAX@Z @0x00052F1E 46B.
// Same this+0x10 table as MilesAudioManagerRva00052F4C (ReverbTable at +0x10)
// and Rva000535CC (+0x10+0x78, /arch:SSE). Arg is outer struct with inner
// pointer at +8; inner has float at +0x1c, int at +0x44, flag byte at +0x48.
// Callers 0x0005C54D/0x0005D444. Returns 1 when flag bit 3 set, int==4, or
// float >= table+0xB8, else 0.
struct SettingsB8
{
	char m_pad[0xb8];
	float m_fB8;
};

struct Inner52F1E
{
	char m_pad0[0x1c];
	float m_f1C;
	char m_pad20[0x44 - 0x20];
	int m_i44;
	unsigned char m_b48;
};

struct OuterArg
{
	char m_pad0[8];
	Inner52F1E *m_inner;
};

class MilesAudioManager
{
public:
	int rva00052F1E(void *p);
private:
	char m_pad0[0x10];
	SettingsB8 *m_settings;
};

int MilesAudioManager::rva00052F1E(void *p)
{
	Inner52F1E *q = ((OuterArg *)p)->m_inner;
	if ((q->m_b48 & 8) || (q->m_i44 == 4) || (q->m_f1C >= m_settings->m_fB8))
		return 1;
	return 0;
}
