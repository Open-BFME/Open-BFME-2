// cl: /O1 /G7 /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// BFME1 9cbfb551fe20 RankInfoSkillPoints.cpp supplies the clean selection body.
// Native00200157..0020021A RET4 expands it to six BFME2 sides and shifts the
// seven override/default fields to18..30/14. Existing neutral config name is
// retained; constructor0020010B and lookup002000D7 establish its prefix.
#include "ascii_string.h"
class GameLogic;
extern GameLogic *TheGameLogic;
class Rva0023C6A4 { public: bool rva00200084(); };
struct Rva002000D7Config {
    int rva00200157(const AsciiString &);
    char unknown00[0x14]; int fallback,primary,men,elves,dwarves,isengard,mordor,wild;
};
int Rva002000D7Config::rva00200157(const AsciiString &side)
{
    Rva0023C6A4 *logic=reinterpret_cast<Rva0023C6A4 *>(TheGameLogic);
    if (logic && logic->rva00200084()) {
        if (primary!=-1) return primary;
    } else {
        const StringBase<char> &name=*reinterpret_cast<const StringBase<char> *>(&side);
        if (name.compare("Men")==0 && men!=-1) return men;
        if (name.compare("Elves")==0 && elves!=-1) return elves;
        if (name.compare("Dwarves")==0 && dwarves!=-1) return dwarves;
        if (name.compare("Isengard")==0 && isengard!=-1) return isengard;
        if (name.compare("Mordor")==0 && mordor!=-1) return mordor;
        if (name.compare("Wild")==0 && wild!=-1) return wild;
    }
    return fallback;
}
