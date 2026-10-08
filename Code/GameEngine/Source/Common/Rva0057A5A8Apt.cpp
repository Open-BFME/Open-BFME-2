// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?Rva0057A5A8Set@@YAXHPAPAURva0057A5A8Team@@H@Z @0x0057A5A8 221B.
// Free Apt TimeRemaining setter: team name lookup then format APT:_level%u.%s_TimeRemaining plus GameText STRATEGICHUD:TurnTimeRemaining fetch then minutes:seconds format then bfmeSetText false.
// Evidence: chain lane calls 0x0057A272 plus caller 0x0057A861 plus precedents Rva0057A51CApt Rva0057A685Apt plus globals TheGameText TheRva00222A8BTarget g_Rva0107301CEmptyString plus strings APT:_level%u.%s_TimeRemaining STRATEGICHUD:TurnTimeRemaining.
#include "ascii_string.h"
#include "unicode_string.h"

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};

class Rva00222A8BTarget
{
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;

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
extern unsigned short *Rva0057A272Get(void);

struct Rva0057A5A8Team
{
	char m_pad8[8];
	char m_name[1];
};

void Rva0057A5A8Set(int level, Rva0057A5A8Team **ppTeam, int totalSeconds)
{
	AsciiString key;
	Rva0057A5A8Team *team = *ppTeam;
	const char *mid = team ? team->m_name : "";
	key.format("APT:_level%u.%s_TimeRemaining", level, mid);
	UnicodeString value;
	bool exists;
	UnicodeString tmp = TheGameText->fetch("STRATEGICHUD:TurnTimeRemaining", &exists);
	if (exists) {
		value.format(tmp.str(), totalSeconds / 60, Rva0057A272Get(), totalSeconds % 60);
	}
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, value, false);
}
