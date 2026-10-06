// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?OnSelectAward@Manager@AptCreateAHero@@QAEXPBD@Z @0x005B5E2D 257B
// Chain of just-landed 0x00406E8F: atoi arg then holder+0x27c forward then
// vector g_00E02F74 lookup then TheGameText fetch at slot 0x38 then
// bfmeSetText; fallback builds wide from g_00BC26DC. Callers none.
// Honest-address method.
#include "ascii_string.h"
#include "unicode_string.h"

extern "C" __declspec(dllimport) int __cdecl atoi(const char *s);

class Rva00222A8BTarget
{
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;

typedef bool Bool;
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
    virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
    virtual UnicodeString fetch(const AsciiString &label, Bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class BfmeAptWindowManager
{
public:
    void bfmeSetText(const AsciiString &a, const UnicodeString &u, bool b);
};

struct BfmePod40
{
    int a[10];
};
class Rva0040AAD5
{
public:
    BfmePod40 *rva0040AAD5(int key);
};
extern Rva0040AAD5 *g_00E02F74;
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
class AptCreateAHero
{
public:
	class Manager;
};

class AptCreateAHero::Manager
{
    char m_pad[4];
    Holder *m_holder;
public:
    void OnSelectAward(const char *arg);
};
void AptCreateAHero::Manager::OnSelectAward(const char *arg)
{
    if (!TheRva00222A8BTarget)
        return;
    int idx = atoi(arg);
    BfmePod40 *found = 0;
    if (idx >= 0)
    {
        int v = m_holder->m_obj.rva00406E8F((unsigned int)idx);
        found = g_00E02F74->rva0040AAD5(v);
    }
    if (found)
    {
        AsciiString key("Cah:SelectedAwardDesc");
        ((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, TheGameText->fetch(*(const AsciiString *)((char *)found + 0x14), (Bool *)0), false);
        return;
    }
    UnicodeString uw((const wchar_t *)g_00BC26DC);
    AsciiString key("Cah:SelectedAwardDesc");
    ((BfmeAptWindowManager *)TheRva00222A8BTarget)->bfmeSetText(key, uw, false);
}
