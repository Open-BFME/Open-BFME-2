// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva0057A685Set@@YAXHPAPAURva0057A685Team@@H@Z @0x0057A685 195B.
// Free Apt PhaseTitle setter: GameText table lookup then format APT:_level%u.%s_PhaseTitle then bfmeSetText.
// Evidence: unlock lane plus callers 0x0057ABBD 0x0057B917 plus precedents Rva005F6220Apt Rva005FF450Apt GameSlotSetState fetch slot 0x3C plus globals TheGameText TheRva00222A8BTarget g_Rva0107301CEmptyString plus string APT:_level%u.%s_PhaseTitle.
#include "ascii_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

struct Rva0057A685Team
{
	char m_pad8[8];
	char m_name[1];
};

struct Rva0057A685Entry
{
	int m_id;
	const char *m_label;
};

static const Rva0057A685Entry s_table[3] = {
	{ 0, "A" },
	{ 1, "B" },
	{ 2, "C" },
};

void Rva0057A685Set(int level, Rva0057A685Team **ppTeam, int phase)
{
	UnicodeString value;
	for (unsigned i = 0; i < 3; ++i) {
		if (s_table[i].m_id == phase) {
			value.set(TheGameText->fetch(s_table[i].m_label));
			break;
		}
	}
	AsciiString key;
	Rva0057A685Team *team = *ppTeam;
	const char *mid = team ? team->m_name : "";
	key.format("APT:_level%u.%s_PhaseTitle", level, mid);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, value, true);
}
