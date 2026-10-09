// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /Oy- /MD /EHsc
// ?rva00528C65@Rva00528C65@@QBE?AVAsciiString@@XZ retail 0x00528C65 32B
// Evidence: EBP frame; copy [ecx+4]+0x12C via StringBase copy 0x365F0 into hidden return; caller 0x00529224
#include "ascii_string.h"

struct Rva00528C65Mid
{
	char m_pad[0x118];
	void *m_filter;
	char m_pad11c[0xC];
	unsigned char m_percent;
	char m_pad129[3];
	AsciiString m_str;
};

class Player { public: float getProductionCostChangeBasedOnUpgradeDiscount(AsciiString) const; int getProductionCostChangeByObjectFilterID(void *); };
class Rva00528C65
{
public:
	AsciiString rva00528C65() const;
	int rva00528C85(Player *);
private:
	char m_pad04[4];
	Rva00528C65Mid *m_ptr;
};

AsciiString Rva00528C65::rva00528C65() const
{
	return m_ptr->m_str;
}

extern "C" __declspec(dllimport) double __cdecl floor(double);
// Native 528C85..528CE6 RET4: module data+128 selects percent vs filter.
// WB 13CA0F0 and the rowed Player providers identify both queries. Original
// helper spelling and module-data class remain unknown; offsets are target facts.
// Same x87 rounding operation as the independently matched Player cost query.
// MSVC casts otherwise call __ftol2; retail 528CC9/528CCC use FLD/FISTP.
int Rva00528C65::rva00528C85(Player *player)
{
    if (m_ptr->m_percent != 0)
    {
        long rounded;
        float value = (float)floor(player->getProductionCostChangeBasedOnUpgradeDiscount(AsciiString::TheEmptyString) * 100.0f + 0.5f);
        __asm {
            fld [value]
            fistp [rounded]
        }
        return rounded;
    }
    return player->getProductionCostChangeByObjectFilterID(m_ptr->m_filter);
}
