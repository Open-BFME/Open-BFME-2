// Target facts (addresses are RVAs unless marked VA):
// 0x003A25B1 calls SubsystemInterface's constructor 0x001B4E63, stores Snapshot's VA 0x00BBB554 at +0xC, then installs TeamFactory's VA 0x00C1AE2C at +0 and VA 0x00C1AE1C at +0xC. The destructor 0x003A383A installs the same pair before restoring Snapshot's base table at 0x003A3880 and calling 0x001B4E74. These are two non-virtual bases, not competing class tables.
// VA 0x00C1AE2C contains 14 slots: 0 deleting destructor 0x003A398B, 1 init 0x003A3899, 2 inherited loadIniFilesFromLegend 0x001B5384, 3 0x000B3FD0, 4 0x005CB9FF, 5 0x0047A699, 6 0x000D43D0, 7 0x0047A69C, 8 0x000B3FD0, 9 reset 0x003A389E, 10 update 0x000B3FD0, 11 0x005CB9FF, 12 0x000B3FD0, 13 0x0047A69C. The TeamFactory literal starts immediately after slot 13 at VA 0x00C1AE64. Other slots retain the registered base's names or neutral vslotNN spellings.
// VA 0x00C1AE1C contains Snapshot's four slots: 0 thunk 0x003A2624 (subtracts 0xC then jumps to 0x003A398B), 1 loadPostProcess 0x0039F7A5, 2 GetSnapshotName 0x003A261E (returns VA 0x00C1AE64), 3 xfer 0x003A308A. TeamFactory adds no virtual slots.
// GameEngine::init pushes 0xC4 at 0x0022F59F, calls operator new 0x0002FDA0 and calls 0x003A25B1 at 0x0022F5B7: sizeof is 0xC4. The constructor clears +0x10..+0xAF, constructs the 12-byte map at +0xB0 through 0x0024613C and clears dwords +0xBC/+0xC0. 0x003A2FD4 indexes 40 TeamPrototype pointers at +0x10; 0x003A2F4C copies and clears the map and pointer array; 0x0039F7A5 recomputes the two IDs at +0xBC/+0xC0. The map representation remains opaque.
// Every non-virtual declaration below has a TeamFactory ledger row at its adjacent RVA. Constructor, destructor and methods stay out of line. Zero Hour Common/Team.h supplies the names m_prototypes, m_uniqueTeamPrototypeID and m_uniqueTeamID; the target bodies establish their offsets and roles. The pointer array has the neutral name m_field10. Snapshot's crc surface is a compatibility spelling of its retail name-getter slot.

#pragma once
#ifndef CANONICAL_TEAMFACTORY_H
#define CANONICAL_TEAMFACTORY_H

#ifndef CANONICAL_SUBSYSTEMINTERFACE_H
#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class AsciiString;
class Dict;
class Player;
class SidesList;
class Team;
class TeamPrototype;
class Xfer;
struct Rva003A2FD4Proto;

class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
    TeamFactory(); // 0x003A25B1
    virtual ~TeamFactory(); // 0x003A383A

    virtual void init(); // primary slot 1, 0x003A3899
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset(); // primary slot 9, 0x003A389E
    virtual void update(); // primary slot 10, 0x000B3FD0
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif

    void clear(); // 0x003A2F4C
    void initFromSides(SidesList *sides); // 0x003A4182
    void initTeam(const AsciiString &name, const AsciiString &owner, bool singleton, Dict *dict); // 0x003A404D
    TeamPrototype *findTeamPrototype(const AsciiString &name); // 0x003A2659
    TeamPrototype *findTeamPrototype(const AsciiString &owner, const AsciiString &name); // 0x0039FE6C
    TeamPrototype *findTeamPrototypeByID(unsigned int id); // 0x0039F72C
    Team *findTeamByID(unsigned int id); // 0x0039F761
    Team *createEmptyTeam(Player *player); // 0x003A3CD9
    Team *createInactiveTeam(const AsciiString &owner, const AsciiString &name); // 0x003A3B7E
    Team *createTeamOnPrototype(TeamPrototype *prototype, bool activate); // 0x003A3DBE
    Team *findTeam(const AsciiString &name); // 0x003A40F5
    Team *findTeam(const AsciiString &owner, const AsciiString &name); // 0x003A3E37
    void addTeamPrototypeToList(TeamPrototype *prototype); // 0x003A2B78
    void removeTeamPrototypeFromList(TeamPrototype *prototype); // 0x0039FE11
    void teamAboutToBeDeleted(Team *team); // 0x003A3048
    void markTeamDoneForTacticalAI(Team *team); // 0x0039FD98
    Rva003A2FD4Proto *initTeamForTacticalAI(const AsciiString &name, void *ownerName, int targetID, unsigned int tacticID); // 0x003A2FD4
    void rva003A262C(); // 0x003A262C

protected:
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
    virtual void LoadPostProcess();
#else
    virtual void loadPostProcess(); // Snapshot slot 1, 0x0039F7A5
#endif
#ifdef BFME_SNAPSHOT_NAME_SLOT
#ifdef BFME_SNAPSHOT_NONCONST_NAME_SLOT
    virtual const char *GetSnapshotName();
#else
    virtual const char *GetSnapshotName() const; // Snapshot slot 2, 0x003A261E
#endif
#else
    virtual void crc(Xfer *xfer);
#endif
#ifdef BFME_SNAPSHOT_CAPITALIZED_SLOTS
#ifdef BFME_SNAPSHOT_REFERENCE_XFER
    virtual void DoXfer(Xfer &xfer);
#else
    virtual void DoXfer(Xfer *xfer);
#endif
#else
    virtual void xfer(Xfer *xfer); // Snapshot slot 3, 0x003A308A
#endif

private:
    TeamPrototype *m_field10[40]; // +0x10
    unsigned char m_prototypes[0xC]; // +0xB0
    unsigned int m_uniqueTeamPrototypeID; // +0xBC
    unsigned int m_uniqueTeamID; // +0xC0
};

#endif
