// cl: /O1 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// BFME1 ba7ddda7 CommandSetLifetime.cpp supplies the override algorithm.
// Native 0x0031B05B..0x0031B0CE and WB 0x00C2DAD0 establish the target's
// constructor mode 0, named +0x10 string, override-copy guard, +0x08 byte,
// and original's +0x04 link. Reuse actual ctor/copy/base owners.
#include "ascii_string.h"
class Rva001E3624 {
public:
    virtual ~Rva001E3624();
    void markAsOverride() { m_override=true; }
    void setNextOverride(Rva001E3624 *next) { m_next=next; }
private:
    Rva001E3624 *m_next;
    bool m_override;
    int m_stale;
};
class Rva00409FFA : public Rva001E3624 {
public:
    Rva00409FFA(const AsciiString &,int);
    virtual ~Rva00409FFA();
    const AsciiString &getName() const { return m_name; }
private:
    AsciiString m_name;
    void *m_buttons[32];
    int m_count;
    int m_mode98;
};
class Rva0031AB7F { public: Rva0031AB7F &operator=(const Rva0031AB7F &); };
extern unsigned char g_00E01EA8;
class ControlBar { public: Rva00409FFA *rva0031B05B(Rva00409FFA *); };
Rva00409FFA *ControlBar::rva0031B05B(Rva00409FFA *original)
{
    if(!original) return 0;
    Rva00409FFA *set=new Rva00409FFA(original->getName(),0);
    g_00E01EA8=1;
    *((Rva0031AB7F *)set)=*((const Rva0031AB7F *)original);
    g_00E01EA8=0;
    set->markAsOverride();
    original->setNextOverride(set);
    return set;
}
