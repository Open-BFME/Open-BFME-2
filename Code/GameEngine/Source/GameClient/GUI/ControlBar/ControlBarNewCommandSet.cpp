// cl: /O1 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
// Native 0x0031E8D5..0x0031E92D and WB 0x00C2DA30: allocate a 0x9C-byte
// command set, construct from name and mode, put it in the +0x30 name map.
// BFME1 ba7ddda7 CommandSetLifetime.cpp guides the creation algorithm.
// The map replaces the donor's list, and layout comes from matched ctor
// 0x00409FFA and its rowed sibling methods rather than the donor.
#include "ascii_string.h"
class Rva001E3624 {
public:
    virtual ~Rva001E3624();
private:
    Rva001E3624 *m_next;
    bool m_override;
    int m_stale;
};
class Rva00409FFA : public Rva001E3624 {
public:
    Rva00409FFA(const AsciiString &, int);
    virtual ~Rva00409FFA();
private:
    AsciiString m_name;
    void *m_buttons[32];
    int m_count;
    int m_mode98;
};
class Rva000427195 { public: void **rva0031DB83(const AsciiString &); };
class ControlBar { public: Rva00409FFA *rva0031E8D5(const AsciiString &,int); };
Rva00409FFA *ControlBar::rva0031E8D5(const AsciiString &name,int mode)
{
    Rva00409FFA *set=new Rva00409FFA(name,mode);
    *((Rva000427195 *)((char *)this+0x30))->rva0031DB83(name)=set;
    return set;
}
