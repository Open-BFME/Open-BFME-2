// cl: /MD -GR- -EHsc- /Ireference/shims/bfme2_ascii
// ?OnMyPowerRollOver@Manager@AptCreateAHero@@QAEXPAD@Z @0x005B5B39 89B: digit-string slot apply.
// Null-guarded string must start with a digit (imported isdigit) and atoi
// to 1..10 (imported atoi, minus one); a value already current returns,
// else the +0x27C sub-object resolves it through the pinned 1-arg callee
// and the (K, K, pointer) triple runs through the rowed cdecl callee before
// stamping +0x24. K is AsciiString::TheEmptyString (VA 0x00DE0878).
// Targets from retail REL32; imports declared dllimport explicitly.
#include <ctype.h>
#include <stdlib.h>
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"

class CommandButton;
#include "../../Include/Common/CreateAHeroHero.h"

#include "../../Include/Common/AptCreateAHero.h"

struct AptCreateAHero::Manager
{
	char pad[4];
	void *m_4;
	char pad2[0x24 - 8];
	int m_24;

	void OnMyPowerRollOver(char *s);
};

void Rva005B23D7HeroPowersDescription(void *button, const AsciiString &a, const AsciiString &b);	// 0x005B23D7

void AptCreateAHero::Manager::OnMyPowerRollOver(char *s)
{
	if (s == 0)
		return;
	if (!isdigit(s[0]))
		return;
	int v = atoi(s) - 1;
	if (v < 0 || v >= 10 || v == m_24)
		return;
	const CommandButton *commandButton = ((CreateAHeroHero *)((char *)m_4 + 0x27c))->GetButtonForLevel(v);
	Rva005B23D7HeroPowersDescription((void *)commandButton, AsciiString::TheEmptyString, AsciiString::TheEmptyString);
	m_24 = v;
}
