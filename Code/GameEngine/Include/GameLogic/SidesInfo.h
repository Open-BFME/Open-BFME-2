// Target facts (BFME2 1.06, code addresses are RVAs and table addresses are VAs): SidesInfo has no virtual functions, vptr, vbptr or base classes. Constructor 0x0032C667 clears the BuildListInfo pointer at +0, calls Dict(0) at +4 (0x0032C681 -> 0x00313581), ScriptList at +8 (0x0032C68D -> 0x003B7720), and the empty vector constructor at +0x54 (0x0032C699 -> 0x00211E58). Copy constructor 0x0032C6AD copies Dict's pointer at +4 and increments its 16-bit reference count, calls ScriptList's copy at +8 (0x0032C6E3 -> 0x003B88DA), copies the vector at +0x54 (0x0032C6F3 -> 0x000BC07E), and deep-copies the BuildListInfo chain through 0x00329DE6. Destructor 0x0032D4C0 calls init(0), then destroys the vector at +0x54, ScriptList at +8 and Dict at +4. Neither SidesInfo constructor nor its destructor installs a table. ScriptList's 0x00C1FAAC and its Snapshot base's 0x00BBB554 belong to the embedded member: ScriptList copy 0x003B88DA installs Snapshot then ScriptList; destructor 0x003B774B restores them in reverse order. They are not SidesInfo tables.
// Target extent and members: SidesList constructor 0x0032EE24 passes SidesInfo constructor/destructor 0x0032C667/0x0032D4C0 with count 20 and stride 0x60 at 0x0032EE89..0x0032EEA1 and 0x0032EEAD..0x0032EEBE. Getters 0x002035BA and 0x002A98D1 independently scale side indices by 0x60. Dict occupies +4..+7, ScriptList occupies +8..+0x53, and the trailing vector occupies +0x54..+0x5F. The trailing vector is bounded storage here; its original member name is unproved. init 0x0032CDAA clears the build list, Dict, ScriptList and vector; swap 0x0032B070 exchanges those same members. Assignment 0x0032D510 constructs a 0x60-byte copy, calls swap and destroys it. All lifetime members and rowed methods remain declared out of line.
// Target method rows: clear 0x0032D4AD calls init(0); setScriptList 0x003297F3 adjusts this by +8 and tail-jumps to ScriptList::swap 0x003B58DF; addToBuildList 0x003297FB, removeFromBuildList 0x0032983F and reorderInBuildList 0x00329F3F operate on the +0 chain. Donor names: Zero Hour GeneralsMD GameLogic/SidesList.h supplies SidesInfo, m_pBuildList, m_dict, m_scripts, getDict, getBuildList, releaseBuildList and getScriptList. Retail changes m_scripts from a pointer to a by-value ScriptList, as the constructor, destructor and setter prove. Registered Dict.h and ScriptList.h supply the member layouts.

#pragma once

#ifndef BFME2_SIDESINFO_H
#define BFME2_SIDESINFO_H

#include "../Common/Dict.h"
#include "ScriptList.h"

class BuildListInfo;

class SidesInfo
{
public:
    SidesInfo();
    SidesInfo(const SidesInfo &that);
    ~SidesInfo();
    SidesInfo &operator=(const SidesInfo &that);

    void init(const Dict *dict);
    void clear();
    void swap(SidesInfo *other);
    void addToBuildList(BuildListInfo *buildList, int position);
    int removeFromBuildList(BuildListInfo *buildList);
    void reorderInBuildList(BuildListInfo *buildList, int position);
    void setScriptList(ScriptList *scripts);

    Dict *getDict() { return &m_dict; }
    BuildListInfo *getBuildList() { return m_pBuildList; }
    void releaseBuildList() { m_pBuildList = 0; }
    ScriptList *getScriptList() { return &m_scripts; }
    const ScriptList *getScriptList() const { return &m_scripts; }

    BuildListInfo *m_pBuildList;
    Dict m_dict;
    ScriptList m_scripts;
    unsigned char m_tail[0x0C];
};

#endif
