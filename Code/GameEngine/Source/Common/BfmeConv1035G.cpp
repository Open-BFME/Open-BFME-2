// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// retail 0x00131C40, 35 bytes. Donor game/GameEngine/Source/Common/BfmeConv1035.cpp
// recompiled /Os emits this body byte-identically on unclaimed .text. Dedicated
// TU holding the preamble and this one body; the donor's other five bodies
// (bfmeGo1035A, bfmeGo1035B, bfmeGo1035C, bfmeGo1035E and bfmeGo1035F) are
// omitted -- bfmeGo1035C is recovered in its own TU.
class BfmeG1035;

extern char g_bfmeCh1035;
extern char g_bfmeLit1035[];
void bfmeFix1035(char **slot, char *lit, BfmeG1035 *o);

class BfmeG1035
{
public:
	char *bfmeGo1035G(void);

	char m_bfmePad[0x18];
	char *m_bfmeName;
};

char *BfmeG1035::bfmeGo1035G(void)
{
	if (*m_bfmeName == g_bfmeCh1035)
		bfmeFix1035(&m_bfmeName, g_bfmeLit1035, this);

	return m_bfmeName;
}
