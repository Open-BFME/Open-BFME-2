// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /G7 /arch:SSE /O1
// ?PopulateAwards@Manager@AptCreateAHero@@QAEXXZ
// ?OnSelectAward@Manager@AptCreateAHero@@QAEXPBD@Z @0x005B5E2D 257B
// Chain of just-landed 0x00406E8F: atoi arg then holder+0x27c forward then
// vector TheAwardSystemManager lookup then TheGameText fetch at slot 0x38 then
// bfmeSetText; fallback builds wide from g_00BC26DC. Callers none.
// Honest-address method.
#include <stdlib.h>
#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../../../Include/Common/Rva00222A8BTarget.h"
int Rva0043DB23(Rva00222A8BTarget *, void *, const char *);
extern Rva00222A8BTarget *TheRva00222A8BTarget;

typedef bool Bool;
#include "../../../../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

#include "../../../../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

struct BfmePod40
{
    int a[10];
};
#include "../../../../../Include/GameClient/Rva0040AAD5.h"
extern Rva0040AAD5 *TheAwardSystemManager;
extern const unsigned short g_00BC26DC[];

class Rva00406E8F
{
public:
    int rva00406E8F(unsigned int i);
};
#include "../../../../../Include/Common/Rva00406E7D.h"
struct Holder
{
    char m_pad[0x274];
    void *m_movie;
    char m_pad278[4];
    Rva00406E8F m_obj;
    __forceinline void *movie() const { return m_movie; }
};
#include "../../../../../Include/Common/AptCreateAHero.h"

class AptCreateAHero::Manager
{
    char m_pad[4];
    Holder *m_holder;
public:
    void OnSelectAward(const char *arg);
    void PopulateAwards();
};
// OnSelectAward's row (257B @0x005B5E2D) lives in Rva005B5E2D.cpp; the
// duplicate definition here LNK2005-collided with it, so only the
// declaration above remains. Nothing in this TU calls it.

// Retail 005B6052..005B6166; WB 0157E340 names PopulateAwards.
// Lookup retains its existing opaque return type. Only the independently
// witnessed string fields are read through this view, as in CaHAwardNumber.
struct Rva005B6052AwardView
{
    char m_pad00[0x10];
    AsciiString m_name;
    AsciiString m_description;
    AsciiString m_image;
};
void AptCreateAHero::Manager::PopulateAwards()
{
    Rva0043DB23(TheRva00222A8BTarget, (m_holder?m_holder:m_holder)->movie(), "UpdateAwards");
    unsigned int count = reinterpret_cast<Rva00406E7D *>(&m_holder->m_obj)->rva00406E7D();
    for (unsigned int i = 0; i < count; ++i)
    {
        Rva005B6052AwardView *award = reinterpret_cast<Rva005B6052AwardView *>(
            TheAwardSystemManager->rva0040AAD5(m_holder->m_obj.rva00406E8F(i)));
        if (award)
        {
            AsciiString key;
            key.format("CahAward:Image_%d", i);
            TheRva00222A8BTarget->rva002239FA(key, award->m_image);
            key.format("CahAward:Name_%d", i);
            reinterpret_cast<BfmeAptWindowManager *>(TheRva00222A8BTarget)->bfmeSetText(
                key, TheGameText->fetch(award->m_name, 0), false);
        }
    }
}
