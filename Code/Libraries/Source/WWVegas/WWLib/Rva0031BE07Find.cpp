// cl: /Ireference/shims/bfme2_ascii /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0031BE07@Rva0031BE07@@QAEPAXABV?$StringBase@D@@@Z @0x0031BE07 53B
// Unlocks 0x0031BE58/153 and 0x001DAF81/255; LINK BONUS via 0x0031BE3C.
// String-keyed node search at this+0x2C via rowed StringBase::compare 0x000069D6
// and pinned getFinalOverride 0x001E35DF (pin ?getFinalOverride@Overridable@@QBEPBV1@XZ); callers at 0x001DAFB7 0x0031BE40 0x0031BE85 0x0031BEC0
// pass StringBase temps (0x0031BE58 builds from Command_* literals).
// Donor: none; honest Rva class; layout from retail offsets.
#include "ascii_string.h"

class Overridable
{
public:
    const Overridable *getFinalOverride() const;
};

struct Rva0031BE07Node
{
    void *m_unk00;
    Overridable *m_nextOverride;
    unsigned char m_pad08[8];
    StringBase<char> m_name;
    unsigned char m_pad14[4];
    Rva0031BE07Node *m_next;
};

struct Rva0031BE07
{
    unsigned char m_pad[0x2c];
    Rva0031BE07Node *m_head;
    void *rva0031BE07(const StringBase<char> &key);
    void rva0031BE58(const class ModuleData *data);
};

void *Rva0031BE07::rva0031BE07(const StringBase<char> &key)
{
    Rva0031BE07Node *node = m_head;
    while (node) {
        if (node->m_name.compare(key) == 0) {
            if (node->m_nextOverride != 0)
                return (void *)node->m_nextOverride->getFinalOverride();
            return node;
        }
        node = node->m_next;
    }
    return 0;
}

// ?rva0031BE58@Rva0031BE07@@QAEXPBVModuleData@@@Z @0x0031BE58 153B
// Chain from 0x0031BE07; two StringBase temps from Command_StructureExit and
// Command_TransportExit literals; each find result pushed via 0x0035B750.
// Evidence: callers at 0x0031BE85 0x0031BEC0 are this body; caller 0x0031ED9E.
class ModuleData
{
};

class Rva0035B750
{
public:
    void rva0035B750(const ModuleData *arg);
};

void Rva0031BE07::rva0031BE58(const ModuleData *data)
{
    if (data == 0)
        return;
    void *found;
    {
        AsciiString name1("Command_StructureExit");
        found = rva0031BE07(*(const StringBase<char> *)&name1);
    }
    if (found != 0)
        ((Rva0035B750 *)found)->rva0035B750(data);
    {
        AsciiString name2("Command_TransportExit");
        found = rva0031BE07(*(const StringBase<char> *)&name2);
    }
    if (found != 0)
        ((Rva0035B750 *)found)->rva0035B750(data);
}

// ?findCommandButton@ControlBar@@QAEPBVCommandButton@@ABVAsciiString@@@Z @0x0031BE3C 28B
// LINK BONUS: 1 matched file waits for this name. Donor BFME1 ControlBar.cpp
// findCommandButton calls findNonConst (here 0x0031BE07) then final-override
// hop via pinned 0x001E35DF (?getFinalOverride@Overridable@@QBEPBV1@XZ).
// Evidence: 40+ callers; retail forwards ecx to 0x0031BE07 and hops via +4.
class CommandButton
{
};

class ControlBar
{
public:
    const CommandButton *findCommandButton(const AsciiString &name);
};

const CommandButton *ControlBar::findCommandButton(const AsciiString &name)
{
    void *btn = ((Rva0031BE07 *)this)->rva0031BE07(*(const StringBase<char> *)&name);
    if (btn == 0)
        return 0;
    const Overridable *over = *(const Overridable *const *)((const char *)btn + 4);
    if (over == 0)
        return (const CommandButton *)btn;
    return (const CommandButton *)over->getFinalOverride();
}
