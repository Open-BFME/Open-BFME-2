// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// WorldBuilder 0x00B5F3F0 identifies LivingWorldManager::CreateSound,
// its duplicate-name guard and insertion. Retail 0x0021399A..0x00213A0E
// supplies the +0x204 table, 0x34 allocation and actual constructor target
// (0x003FAE68), rowed as Rva003FAFB9(const AsciiString &) in
// LivingWorldSound.cpp. The return type keeps the row's address-derived
// spelling; this source makes no claim about the sound object's original type.
#include "ascii_string.h"

class Rva003FAE68Base;
class Rva003FAFB9
{
public:
    Rva003FAFB9(const AsciiString &name);
    virtual void slot00();
private:
    char m_unrecovered[0x30];
};
class Rva00056F61;
#include "../../../Include/GameClient/Rva0041534BIter.h"
#include "../../../Include/GameClient/Rva00056F61.h"
#include "../../../Include/GameLogic/LivingWorldManager.h"

Rva003FAE68Base *LivingWorldManager::CreateSound(const AsciiString &name)
{
    Rva0041534BIter it = m_sounds.rva0041534B(&name);
    if (it.m_node != 0)
        return *(Rva003FAE68Base **)m_sounds.rva0021386C(&name);
    Rva003FAE68Base *sound = (Rva003FAE68Base *)new Rva003FAFB9(name);
    *(Rva003FAE68Base **)m_sounds.rva0021386C(&name) = sound;
    return sound;
}
