// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005FF450@Rva005FF450@@QAEXHPBDABVUnicodeString@@@Z @ 0x005FF450 (109B).
// Apt Unit text setter; formats APT:_level%u.%s_Unit%s%d from m_level at +4 and team name at +8.
// Team pointer null uses g_Rva0107301CEmptyString; manager via TheRva00222A8BTarget.
// Evidence: format row 0x00038150; bfmeSetText pin 0x00225301; releaseBuffer 0x00036410;
// globals 0x009FE4CC 0x007BAC1C; callers 0x005FF593 0x005FFA3C; precedent AptPlayerNameSet 0x005FB770.
#include "ascii_string.h"
#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &key, const UnicodeString &value, bool b);
};

class Rva00222A8BTarget
{
	char m_pad;
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];

struct Rva005FF450Team
{
	char m_pad[8];
	char m_name[1];
};

struct BfmePod8
{
	int a[2];
};

class BfmePod8Vector
{
public:
	void resize(unsigned int n, BfmePod8 x);
	BfmePod8 *m_begin;
	BfmePod8 *m_end;
private:
	void *m_alloc;
};

int __cdecl Rva0052519DFire(void *a1, void *a2, const char *a3, const char *a4, int *a5);

class Rva005FF450
{
public:
	void rva005FF450(int count, const char *kind, const UnicodeString &text);
	void rva005FF3E9(const UnicodeString &text);
	void rva005FF9D8(int count);
private:
	char m_pad[4];
	unsigned int m_level;
	Rva005FF450Team *m_team;
	char m_padC[36];
	BfmePod8Vector m_icons;
};

void Rva005FF450::rva005FF450(int count, const char *kind, const UnicodeString &text)
{
	AsciiString key;
	const char *team = m_team ? m_team->m_name : g_Rva0107301CEmptyString;
	key.format("APT:_level%u.%s_Unit%s%d", m_level, team, kind, count);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, true);
}

// ?rva005FF3E9@Rva005FF450@@QAEXABVUnicodeString@@@Z @ 0x005FF3E9 (103B).
// Apt Army name setter; formats APT:_level%u.%s_ArmyName from m_level at +4 and team name at +8.
// Same layout and globals as rva005FF450 above; team null uses empty string.
// Evidence: format row 0x00038150; bfmeSetText pin 0x00225301; releaseBuffer 0x00036410;
// globals 0x009FE4CC 0x007BAC1C; callers 0x005FF5DB 0x005FF8D4.
void Rva005FF450::rva005FF3E9(const UnicodeString &text)
{
	AsciiString key;
	const char *team = m_team ? m_team->m_name : g_Rva0107301CEmptyString;
	key.format("APT:_level%u.%s_ArmyName", m_level, team);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, text, true);
}

// ?rva005FF9D8@Rva005FF450@@QAEXH@Z @ 0x005FF9D8 118B
// SetUnitIconCount via rowed Rva0052519DFire then BfmePod8 resize to count with fill {0,-1}
// then Quantity text per new index via own rva005FF450 with UnicodeString::TheEmptyString.
// Evidence: callees rowed 0x0052519D 0x005FF96A 0x005FF450; globals TheRva00222A8BTarget
// g_Rva0107301CEmptyString TheEmptyString; strings SetUnitIconCount Quantity; layout +4 level
// +8 team +0x30 icons; caller jmp 0x005FFA51; precedent Rva0035ABC0Resize.
void Rva005FF450::rva005FF9D8(int count)
{
	BfmePod8Vector *vec = &m_icons;
	int cur = vec->m_end - vec->m_begin;
	if (count == cur)
		return;
	const char *team = m_team ? m_team->m_name : g_Rva0107301CEmptyString;
	Rva0052519DFire(TheRva00222A8BTarget, (void *)m_level, team, "SetUnitIconCount", &count);
	BfmePod8 fill;
	fill.a[0] = 0;
	fill.a[1] = -1;
	vec->resize((unsigned int)count, fill);
	for (int i = cur; i < count; ++i)
		rva005FF450(i, "Quantity", UnicodeString::TheEmptyString);
}
