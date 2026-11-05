// cl: /MD -GR- -EHsc-
// ?OnMyPowerRollOver@Manager@AptCreateAHero@@QAEXPAD@Z @0x005B5B39 89B: digit-string slot apply.
// Null-guarded string must start with a digit (imported isdigit) and atoi
// to 1..10 (imported atoi, minus one); a value already current returns,
// else the +0x27C sub-object resolves it through the pinned 1-arg callee
// and the (K, K, pointer) triple runs through the rowed cdecl callee before
// stamping +0x24. K recomposed as in the 0x5B5AC3 unit (runtime constant).
// Targets from retail REL32; imports declared dllimport explicitly.
#include <ctype.h>
#include <stdlib.h>

enum Rva005B5B39Const
{
	Rva005B5B39_K = 0xDE0000 + 0x878
};

class CommandButton;
class CreateAHeroHero
{
public:
	const CommandButton *GetButtonForLevel(int level);	// 0x00406ED7
};
class AsciiString;

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
	Rva005B23D7HeroPowersDescription((void *)commandButton, *(const AsciiString *)Rva005B5B39_K, *(const AsciiString *)Rva005B5B39_K);
	m_24 = v;
}
