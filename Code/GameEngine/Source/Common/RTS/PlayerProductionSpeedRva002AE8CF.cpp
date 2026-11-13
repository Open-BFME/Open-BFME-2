// cl: /O1 /arch:SSE /G7 /MD /Oy-
// Native Ghidra 002AE8CF..002AE930, 97B, RET12. Rowed
// ProductionSpeedBonus::doSpecialPower proves the Player receiver, string
// list entry, float bonus and duration arguments. Retail establishes the
// maps at +294/+2A8/+2BC: initialize a missing +2A8 float to zero, write
// the +2BC integer duration, then the +294 float bonus. Original names
// for this method and these fields remain unknown.
// Existing iterator/find and float-reference helpers retain their rowed
// interfaces. Native 002AE4C5 is121B RET4 and returns the integer payload
// address (+8 of a found node) after the same AsciiString-keyed lookup.
class AsciiString;
class Rva00056F61;
#include "../../../Include/GameClient/Rva0041534BIter.h"
#include "../../../Include/GameClient/Rva00056F61.h"
#include "../../../Include/Common/Rva001FDE3F.h"
class Rva002AE4C5
{
public:
    int &rva002AE4C5(const AsciiString *key);
};
#include "../../../Include/Common/Player.h"

void Player::rva002AE8CF(const AsciiString *name, float bonus, int frames)
{
    Rva00056F61 *starts = reinterpret_cast<Rva00056F61 *>(
        reinterpret_cast<char *>(this) + 0x2A8);
    Rva0041534BIter found = starts->rva0041534B(name);
    if (!found.m_node)
        reinterpret_cast<Rva001FDE3F *>(starts)->rva001FDE3F(*name) = 0.0f;
    reinterpret_cast<Rva002AE4C5 *>(reinterpret_cast<char *>(this) + 0x2BC)
        ->rva002AE4C5(name) = frames;
    reinterpret_cast<Rva001FDE3F *>(reinterpret_cast<char *>(this) + 0x294)
        ->rva001FDE3F(*name) = bonus;
}
