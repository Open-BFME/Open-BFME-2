// Target facts (game.dat, RVAs unless marked VA): constructors 0x003769F9 and 0x00376A1F store the four-slot table VA 0x00C18630 at +0; slots are the deleting destructor 0x00376AC3 (calls destructor 0x00376ADF), empty loadPostProcess 0x000B3FD0, the const name getter 0x00376A19, and xfer 0x00376B70. The following bytes at VA 0x00C18640 spell "ObjectTypes", so there is no fifth slot. Destructor 0x00376ADF destroys vector +8 and string +4, then stores Snapshot's table VA 0x00BBB554 at 0x00376B0E; that is the base teardown table, not ObjectTypes' table.
// Target facts: allocation 0x003BA810 and constructor call 0x003BA825, plus allocation 0x003582A3 and constructor call 0x003582BA, establish sizeof 0x14. Constructors initialize AsciiString +4 and vector +8; vector constructor 0x00211E58 initializes its three words at +0/+4/+8. Assignment 0x00376A9C calls string assignment on +4 and vector assignment on +8. getNthInList 0x002041AC and maintenance 0x003582F2 read begin +8 and end +0x0C with four-byte elements. Other out-of-line methods: isInSet 0x00376A62, addObjectType 0x00376B50, remove 0x00376B1E, canBuildAny 0x00376988, prepForPlayerCounting 0x00376C50 (called at 0x003E9823). The ThingTemplate test 0x00376A84 checks null, then passes the string at +0x64 to 0x00376A62; its ledger owner has an opaque class name.
// Donor facts: Zero Hour ObjectTypes.h and ObjectTypes.cpp supply m_listName, m_objectTypes, getListSize, prepForPlayerCounting and isInSet names. The registered Snapshot header supplies the slot names and its name-slot surface; retail has no ObjectTypes crc slot. The ledger still spells the slot-2 getter as nonvirtual name(), which is declared separately without emitting another body.

#pragma once

#ifndef __BFME2_OBJECTTYPESCLASS_H_
#define __BFME2_OBJECTTYPESCLASS_H_

#if !defined(__SNAPSHOT_H_) && !defined(BFME_SNAPSHOT_NAME_SLOT)
#define BFME_SNAPSHOT_NAME_SLOT
#endif
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <vector>

#if !defined(BFME_SNAPSHOT_NAME_SLOT) || defined(BFME_SNAPSHOT_NONCONST_NAME_SLOT) || defined(BFME_SNAPSHOT_CAPITALIZED_SLOTS)
#error ObjectTypes requires Snapshot's const name slot and lowercase transfer surface.
#endif

class Player;
class ThingTemplate;

class ObjectTypes : public Snapshot
{
public:
    ObjectTypes();
    ObjectTypes(const AsciiString &listName);
    ObjectTypes &operator=(const ObjectTypes &that);
    virtual ~ObjectTypes();

    void addObjectType(const AsciiString &objectType);
    void remove(const AsciiString &objectType);
    bool isInSet(const AsciiString &objectType) const;
    bool isInSet(const ThingTemplate *objectType) const;
    bool canBuildAny(Player *player);
    unsigned int getListSize() const { return m_objectTypes.size(); }
    AsciiString getNthInList(unsigned int index) const;
    int prepForPlayerCounting(_STL::vector<const ThingTemplate *> &templates, _STL::vector<int> &counts);
    const char *name() const;

protected:
    using Snapshot::GetSnapshotName;
    virtual void loadPostProcess();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void xfer(Xfer *xfer);

private:
    AsciiString m_listName;
    _STL::vector<AsciiString> m_objectTypes;
};

#endif
