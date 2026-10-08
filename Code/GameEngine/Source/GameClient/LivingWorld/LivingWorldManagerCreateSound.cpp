// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// WorldBuilder 0x00B5F3F0 identifies LivingWorldManager::CreateSound,
// its duplicate-name guard and insertion. Retail 0x0021399A..0x00213A0E
// supplies the +0x204 table, 0x34 allocation and actual constructor target
// (0x003FAE68). Preserve that provider's address-derived class and integer
// parameter spelling: its argument is the AsciiString reference's address,
// and this source makes no claim about the sound object's original type.
#include "ascii_string.h"

class Rva003FAE68Base
{
public:
    Rva003FAE68Base(int nameAddress);
    virtual void slot00();
private:
    char m_unrecovered[0x30];
};
class Rva00056F61;
struct Rva0041534BIter
{
    void *m_node;
    Rva00056F61 *m_table;
};
class Rva00056F61
{
public:
    Rva0041534BIter rva0041534B(const AsciiString *key);
    void *rva0021386C(const AsciiString *key);
};
class LivingWorldManager
{
public:
    Rva003FAE68Base *CreateSound(const AsciiString &name);
private:
    char m_unrecovered[0x204];
    Rva00056F61 m_sounds;
};

Rva003FAE68Base *LivingWorldManager::CreateSound(const AsciiString &name)
{
    Rva0041534BIter it = m_sounds.rva0041534B(&name);
    if (it.m_node != 0)
        return *(Rva003FAE68Base **)m_sounds.rva0021386C(&name);
    Rva003FAE68Base *sound = new Rva003FAE68Base((int)&name);
    *(Rva003FAE68Base **)m_sounds.rva0021386C(&name) = sound;
    return sound;
}
