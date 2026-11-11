// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?OnSelectAward@Manager@AptCreateAHero@@QAEXPBD@Z @0x005B5E2D 257B
// Chain of just-landed 0x00406E8F: atoi arg then holder+0x27c forward then
// vector TheAwardSystemManager lookup then TheGameText fetch at slot 0x38 then
// bfmeSetText; fallback builds wide from g_00BC26DC. Callers none.
// Honest-address method.
#include <stdlib.h>
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../Include/Common/Rva00222A8BTarget.h"
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

typedef bool Bool;
#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

struct BfmePod40
{
    int a[10];
};
#include "../../Include/GameClient/Rva0040AAD5.h"
extern Rva0040AAD5 *TheAwardSystemManager;
extern const unsigned short g_00BC26DC[];

class Rva00406E8F
{
public:
    int rva00406E8F(unsigned int i);
};
struct Holder
{
    char m_pad[0x27C];
    Rva00406E8F m_obj;
};
#include "../../Include/Common/AptCreateAHero.h"

class AptCreateAHero::Manager
{
    char m_pad[4];
    Holder *m_holder;
public:
    void OnSelectAward(const char *arg);
};
void AptCreateAHero::Manager::OnSelectAward(const char *arg)
{
    if (!((Rva00222A8BTarget *)g_bfmeAptWindowManager))
        return;
    int idx = atoi(arg);
    BfmePod40 *found = 0;
    if (idx >= 0)
    {
        int v = m_holder->m_obj.rva00406E8F((unsigned int)idx);
        found = TheAwardSystemManager->rva0040AAD5(v);
    }
    if (found)
    {
        AsciiString key("Cah:SelectedAwardDesc");
        g_bfmeAptWindowManager->bfmeSetText(key, TheGameText->fetch(*(const AsciiString *)((char *)found + 0x14), (Bool *)0), false);
        return;
    }
    UnicodeString uw((const wchar_t *)g_00BC26DC);
    AsciiString key("Cah:SelectedAwardDesc");
    g_bfmeAptWindowManager->bfmeSetText(key, uw, false);
}
