// cl: /O1 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// BFME1 ba7ddda7 CommandSetLifetime.cpp supplies the override algorithm.
// Native 0x0031B05B..0x0031B0CE and WB 0x00C2DAD0 establish the target's
// constructor mode 0, named +0x10 string, override-copy guard, +0x08 byte,
// and original's +0x04 link. Reuse actual ctor/copy/base owners.
#include "ascii_string.h"
class Overridable {
public:
    virtual ~Overridable();
    void markAsOverride() { m_override=true; }
    void setNextOverride(Overridable *next) { m_next=next; }
private:
    Overridable *m_next;
    bool m_override;
    int m_stale;
};
class CommandSet : public Overridable {
public:
    CommandSet(const AsciiString &,int);
    virtual ~CommandSet();
    const AsciiString &getName() const { return m_name; }
private:
    AsciiString m_name;
    void *m_buttons[32];
    int m_count;
    int m_mode98;
};
class Rva0031AB7F { public: Rva0031AB7F &operator=(const Rva0031AB7F &); };
extern unsigned char g_00E01EA8;
typedef bool Bool;
#include "subsystem_interface.h"
#include "ControlBarMemberTypes.h"
class ControlBar : public SubsystemInterface { public: CommandSet *rva0031B05B(CommandSet *); };
CommandSet *ControlBar::rva0031B05B(CommandSet *original)
{
    if(!original) return 0;
    CommandSet *set=new CommandSet(original->getName(),0);
    g_00E01EA8=1;
    *((Rva0031AB7F *)set)=*((const Rva0031AB7F *)original);
    g_00E01EA8=0;
    set->markAsOverride();
    original->setNextOverride(set);
    return set;
}
