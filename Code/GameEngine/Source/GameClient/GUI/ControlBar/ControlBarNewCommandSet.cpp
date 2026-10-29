// cl: /O1 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// Native 0x0031E8D5..0x0031E92D and WB 0x00C2DA30: allocate a 0x9C-byte
// command set, construct from name and mode, put it in the +0x30 name map.
// BFME1 ba7ddda7 CommandSetLifetime.cpp guides the creation algorithm.
// The map replaces the donor's list, and layout comes from matched ctor
// 0x00409FFA and its rowed sibling methods rather than the donor.
#include "ascii_string.h"
class Overridable {
public:
    virtual ~Overridable();
private:
    Overridable *m_next;
    bool m_override;
    int m_stale;
};
class CommandSet : public Overridable {
public:
    CommandSet(const AsciiString &, int);
    virtual ~CommandSet();
private:
    AsciiString m_name;
    void *m_buttons[32];
    int m_count;
    int m_mode98;
};
class Rva000427195 { public: void **rva0031DB83(const AsciiString &); };
typedef bool Bool;
#include "subsystem_interface.h"
class ControlBar : public SubsystemInterface { public: CommandSet *rva0031E8D5(const AsciiString &,int); };
CommandSet *ControlBar::rva0031E8D5(const AsciiString &name,int mode)
{
    CommandSet *set=new CommandSet(name,mode);
    *((Rva000427195 *)((char *)this+0x30))->rva0031DB83(name)=set;
    return set;
}
