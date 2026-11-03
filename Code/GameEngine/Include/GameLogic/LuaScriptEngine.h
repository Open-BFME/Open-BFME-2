/* Target facts (code addresses are RVAs; table addresses are VAs): Constructor 0x003379FD calls SubsystemInterface 0x001B4E63 at 0x00337A10, installs 0x00C0E390 at +0 at 0x00337A27, and clears pointers +0x0C/+0x10/+0x9C, byte +0xAC, dword +0xD4, byte +0xD8 and dword +0xDC. Allocation 0x0022F558 requests 0xE0 bytes through operator new 0x0002FDA0 and calls this constructor at 0x0022F570; the final constructor store reaches the same extent. SubsystemInterface occupies +0..+0x0B: 0x001B4E63 installs 0x00BD77A0 and clears byte +4 and AsciiString +8; 0x001B4E74 restores that table and destroys +8. Destructor 0x00337AA8 restores LuaScriptEngine's same 0x00C0E390 at 0x00337AB9, then calls the parent destructor at 0x00337B3A. The two lifetime tables belong to the derived and base subobjects, respectively.
Table 0x00C0E390 has exactly seventeen code pointers before its name string at 0x00C0E3D4. Slots 0/1/9/15/16 are deleting destructor 0x00337C70, init 0x00335D5B, reset 0x00337C8C, GetSnapshotName 0x00337AA2 and DoXfer 0x00306A9B. Slot 0 calls destructor 0x00337AA8. Slots 2-8/11-13 equal SubsystemInterface's fourteen-slot table: 2=loadIniFilesFromLegend 0x001B5384; 3/8/12=ret 0x000B3FD0; 4/11=false-ret-4 0x005CB9FF; 5=false-ret 0x0047A699; 6=zero-ret 0x000D43D0; 7/13=ret-4 0x0047A69C. Slots 10 and 14 are also 0x000B3FD0. The registered parent's BFME_SUBSYSTEM_SLOTS form supplies slots 0-13; fourteen inherited slots, not the eleven of a private view, precede slot14. LuaScriptEngine is polymorphic with one base at +0 and no observed secondary table or virtual base.
Constructor 0x00337A15..0x00337A33 builds seventeen eight-byte entries at +0x14 using constructor 0x00332AEF, which initializes a name key at entry +0 through 0x00326BE6 and clears byte +4. InitializeInternalEvents 0x00332B7A addresses the same seventeen entries and stores the OnDestroyed name key at +0xDC (0x00332BAD); ProcessInternalEvent 0x00332C7A compares entry keys at +0x14+8*i and sets byte +0x18+8*i at 0x00332CD1. Its setter at 0x003316BA is rowed as EventFlagEntry::setKeyFromName; 0x003316C7 calls NameKeyGenerator::nameToKey and 0x003316CC stores its result at entry +0. Constructor calls 0x00211E58 at receivers +0xA0/+0xB0/+0xBC/+0xC8 establish four twelve-byte vector headers; reset 0x00337C8C passes their start/finish pairs to erasers 0x00532803/0x0033790F/0x00335C62/0x00335C88. Element spellings and ownership wrappers remain opaque. Lua states +0x0C/+0x10 are passed to lua_close 0x0074DF60 by the destructor. Buffer execution 0x00334133 uses state +0x10 and context +0x9C. Field names below are neutral placeholders.
Out-of-line declarations follow ledger rows: InitializeInternalEvents 0x00332B7A; ProcessInternalEvent 0x00332C7A; PushObjectTable 0x00334003; ExecuteChunk 0x003340C1; rva00334133 0x00334133; LoadScripts 0x003345BE; DispatchEvent 0x00334634; DispatchSpyEvent 0x00334860; ObjectDescription 0x00334DDF; ObjectModifyUpgrade 0x003354D6; HordeBroadcastEventToMembers 0x00335A61; ProcessScriptedEvent 0x00336BE4; rva002E9680ParseModelConditionEvent 0x00336C5D; rva002E9AA0ParseObjectStatusEvent 0x00336EB0; ProcessEventsElement 0x003371F4; rva00337DEF 0x00337DEF; ProcessEventList 0x00337EAA; ProcessSageElement 0x003381C4; LoadXML 0x00338241; rva00338317RegisterScriptFunctions 0x00338317; rva003387DC 0x003387DC. All lifecycle and rowed method bodies remain out of line. No Zero Hour declaration supplies this class's layout or names. */
#pragma once
#ifndef BFME2_LUASCRIPTENGINE_H
#define BFME2_LUASCRIPTENGINE_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class BfmeLexEAN;
class Object;
class XmlNameSlotList;
class Xfer;
struct lua_State;
struct Rva00334133Context;
struct Rva00336283Element;

struct EventFlagEntry
{
    void setKeyFromName(const char *name);

    int field00;
    unsigned char field04;
    unsigned char padding05[3];
};

class LuaScriptEngine : public SubsystemInterface
{
public:
    LuaScriptEngine();
    virtual ~LuaScriptEngine();
    virtual void init();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset();
    virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif
    virtual void slot14();
#ifdef BFME_SNAPSHOT_NAME_SLOT
    virtual const char *GetSnapshotName() const;
#else
    virtual void crc(Xfer *xfer);
#endif
    virtual void DoXfer(Xfer *xfer);

    void InitializeInternalEvents();
    void ProcessInternalEvent(XmlNameSlotList *xml);
    void PushObjectTable(lua_State *state, Object *object);
    void ExecuteChunk(char *buffer, int size, const AsciiString &chunk);
    AsciiString rva00334133(const char *buffer, unsigned long size, Rva00334133Context *context);
    void LoadScripts(const char *filename);
    void DispatchEvent(int *event, Object *object, void *parameters);
    void DispatchSpyEvent(int event, void *object, void *spy, void *parameters);
    static int ObjectDescription(lua_State *state);
    static int ObjectModifyUpgrade(lua_State *state, bool grant);
    static int HordeBroadcastEventToMembers(lua_State *state);
    void ProcessScriptedEvent(XmlNameSlotList *xml);
    void rva002E9680ParseModelConditionEvent(BfmeLexEAN *parser);
    void rva002E9AA0ParseObjectStatusEvent(BfmeLexEAN *parser);
    void ProcessEventsElement(BfmeLexEAN *parser);
    Rva00336283Element *rva00337DEF(const AsciiString &name);
    void ProcessEventList(BfmeLexEAN *parser);
    void ProcessSageElement(BfmeLexEAN *parser);
    void LoadXML(const char *filename, bool keepOpen);
    void rva00338317RegisterScriptFunctions();
    void rva003387DC(const AsciiString &mapName);

    lua_State *field0C;
    lua_State *field10;
    EventFlagEntry field14[17];
    void *field9C;
    unsigned char fieldA0[12];
    bool fieldAC;
    unsigned char paddingAD[3];
    unsigned char fieldB0[12];
    unsigned char fieldBC[12];
    unsigned char fieldC8[12];
    int fieldD4;
    unsigned char fieldD8;
    unsigned char paddingD9[3];
    int fieldDC;
};

typedef char Bfme2LuaScriptEngineSize[sizeof(LuaScriptEngine) == 0xE0 ? 1 : -1];
typedef char Bfme2EventFlagEntrySize[sizeof(EventFlagEntry) == 8 ? 1 : -1];

#endif
