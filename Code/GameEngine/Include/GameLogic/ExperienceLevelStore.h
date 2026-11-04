// Target facts: ExperienceLevelStore's rowed retail API has no virtual functions or rowed constructor/destructor; its methods use direct calls. It is used as a plain API view of TheExperienceLevelSystem (VA 0x00DFECC4, read at RVA 0x005C3000). The owner's constructor 0x00289ABD and destructor 0x00289D7A both store table VA 0x00BFB8F4; no separate Store lifetime, vtable or complete sizeof is established.
// Target facts: 0x00288C34 reads the map pointer at +0x0C; 0x00288AF2 reads the scalar-vector bounds at +0x14/+0x18 and default table at +0x20; 0x002891DB clears the cache at +0x28. Those belong to the owner and are not a complete standalone Store layout. Out-of-line declarations below follow ledger RVAs 0x0028879C, 0x002887B8, 0x002887D1, 0x0028891F, 0x00288ABC, 0x00288AF2, 0x00288C34, 0x00288C68, 0x00288CA6, 0x00288D2F, 0x00288D88, 0x00288E21, 0x002891DB, 0x00289BE0, 0x0028A1AA, 0x0028A294 and 0x0028A473. The two-word handle ABI is visible at 0x00288ABC and 0x00288D2F. Zero Hour's ExperienceTracker.h does not declare this BFME-specific API.
// Target facts: VA 0x00BFB8F4 slots 0..13 target RVAs 0x00289E96, 0x000B3FD0, 0x001B5384, 0x000B3FD0, 0x00289812, 0x00289874, 0x000D43D0, 0x0047A69C, 0x002886A2, 0x00289180, 0x000B3FD0, 0x005CB9FF, 0x000B3FD0 and 0x0047A69C; the next word is non-code 0x454E4F42. None is a Store row. The owner table stores occur at RVAs 0x00289AE4/0x00289D8E; its SubsystemInterface constructor/destructor calls target 0x001B4E63/0x001B4E74, whose own table stores at 0x001B4E65/0x001B4E74 use VA 0x00BD77A0. The global load at 0x005C3029 precedes the direct IsValid call at 0x005C302F. The owner allocation observed at 0x0022F122 pushes 0x34 before the constructor call at 0x0022F137; it does not establish a separate Store object size.

#pragma once

#ifndef BFME2_EXPERIENCELEVELSTORE_H
#define BFME2_EXPERIENCELEVELSTORE_H

class AsciiString;
struct BfmePod264;
struct ExperienceLevelHandle;
class ExperienceLevelList;
class ExperienceLevelSystem;
class ExperienceScalarTable;
class ExperienceTracker;
class INI;
class Rva002894A2;
class ThingTemplate;

extern ExperienceLevelSystem *TheExperienceLevelSystem;

// The owner's scalar-table vector occupies +0x14..+0x1F. This pointer-only
// view needs no definition of the scalar-table element.
class ExperienceScalarTableVector
{
public:
    int size() const { return m_finish - m_start; }
    ExperienceScalarTable *operator[](unsigned int i) const { return m_start[i]; }

private:
    ExperienceScalarTable **m_start;
    ExperienceScalarTable **m_finish;
    ExperienceScalarTable **m_endOfStorage;
};

class ExperienceLevelStore
{
public:
    static ExperienceLevelStore *get() { return reinterpret_cast<ExperienceLevelStore *>(TheExperienceLevelSystem); }

    int GetLevelRank(ExperienceLevelHandle levelHandle) const;
    int GetRequiredExperience(ExperienceLevelHandle levelHandle) const;
    int GetExperienceAwardForLevel(ExperienceLevelHandle levelHandle) const;
    bool IsValid(ExperienceLevelHandle levelHandle) const;
    ExperienceLevelHandle GetNextLevel(ExperienceLevelHandle levelHandle) const;
    ExperienceScalarTable *FindExperienceScalarTableByName(const AsciiString &name) const;
    ExperienceLevelList *FindExperienceLevelList(const ExperienceTracker *tracker) const;
    ExperienceLevelList *rva00288C68(int object);
    int rva00288CA6(const ExperienceTracker *tracker, int rank, int *pastEnd) const;
    ExperienceLevelHandle FindCurrentLevel(const ExperienceTracker *tracker) const;
    ExperienceLevelHandle rva00288D88(int object, int limit);
    ExperienceLevelHandle rva00288E21(const ThingTemplate *object, int rank) const;
    void rva002891DB(const Rva002894A2 *level);
    int rva00289BE0(const ExperienceTracker *tracker, int *out);
    void AddExperienceLevel(void *map, const BfmePod264 *level);
    static void friend_parseExperienceLevelDefinition(INI *ini);
    bool CreateNewExpLevel(const AsciiString &source, const AsciiString &name, const AsciiString &target, const AsciiString &upgrades, const AsciiString &attributes);

private:
    // Proven owner prefix only, not the complete ExperienceLevelSystem size
    // or evidence of a separately constructed Store. Map implementations are
    // deliberately opaque here; the member bodies select their existing view.
    unsigned char m_pad00[0x0C];
    void *m_levelLists;                         // +0x0C
    void *m_reloadLevelLists;                   // +0x10, reload/parser paths
    ExperienceScalarTableVector m_scalarTables; // +0x14
    ExperienceScalarTable *m_defaultScalarTable; // +0x20
};

#endif
