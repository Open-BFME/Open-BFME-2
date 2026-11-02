// Target facts: ctor RVA 0x00356FDC and dtor 0x0035822E (ledger Rva0034C5E0) store table VA 0x00C150E4 at +0; the dtor restores Snapshot's 0x00BBB554, and ctor unwind 0x0077D6C0 calls ~Snapshot 0x0049B47C. The class is polymorphic with one Snapshot base. ScriptEngine ctor 0x0020843E..0x0020845A passes ctor/dtor, count 256 and stride 0x10 to the array constructor, proving sizeof 0x10.
// Target facts: table 0x00C150E4 has four slots: deleting dtor 0x00358317 (calls 0x0035822E), empty loadPostProcess 0x000B3FD0, name getter 0x0035701F (returns "AttackPriorityInfo" at 0x00C150F4), and xfer 0x003583A7; the string immediately follows the table. Ctor stores string +4 = 0, priority +8 = 1, map +0xC = 0; dtor releases string +4 via 0x00036410 and deletes map +0xC via 0x00357C6A/0x0002FD60. getPriority 0x00357CDE reads +8/+0xC; setPriority 0x00358333 allocates the map; xfer 0x003583A7 transfers +4/+8 and pointer-key/int-value map entries. Nonvirtual row 0x00357025 proves the float combat-chain helper ABI.
// Donor facts: Zero Hour GeneralsMD GameLogic/ScriptEngine.h names m_name, m_defaultPriority, m_priorityMap and AttackPriorityMap, and declares friend_setName, friend_setDefaultPriority and getName; its ScriptEngine.cpp supplies the constructor/destructor semantics. BFME2's Snapshot slot 2 is the name getter, rather than Zero Hour's crc. Constructors, destructor and rowed methods stay out of line.
#pragma once

#ifndef CANONICAL_ATTACKPRIORITYINFO_H
#define CANONICAL_ATTACKPRIORITYINFO_H

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class Object;
class ThingTemplate;

namespace _STL {
template <class First, class Second> struct pair;
template <class Type> struct less;
template <class Type> class allocator;
template <class Key, class Value, class Compare, class Allocator> class map;
}
typedef _STL::map<const ThingTemplate *, int, _STL::less<const ThingTemplate *>,
    _STL::allocator<_STL::pair<const ThingTemplate * const, int> > > AttackPriorityMap;

class AttackPriorityInfo : public Snapshot
{
public:
    AttackPriorityInfo();
    virtual ~AttackPriorityInfo();

    void setPriority(const ThingTemplate *thing, int priority);
    float getPriority(const Object *hunter, const Object *target, bool adjust) const;
    float doModPriorityByCombatChain(float priority, const Object *hunter, const Object *target) const;

    AsciiString getName() const { return m_name; }
    void friend_setName(const AsciiString &name) { m_name = name; }
    void friend_setDefaultPriority(int priority) { m_defaultPriority = priority; }

protected:
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

public:
    AsciiString m_name;
    int m_defaultPriority;
    AttackPriorityMap *m_priorityMap;
};

typedef char AttackPriorityInfoRetailSize[(sizeof(AttackPriorityInfo) == 0x10) ? 1 : -1];

#endif
