/* Target facts (code addresses are RVAs; tables are VAs): HotKeyManager is polymorphic. GameClient::init pushes 0x30 at 0x0023A89E for operator new 0x0002FDA0, calls constructor 0x0035973D at 0x0023A8B3, stores the result in TheHotKeyManager (VA 0x00E01E28) at 0x0023A8C1 and calls slot 1 at 0x0023A8CC. The constructor is rowed as Rva00359290: it calls SubsystemInterface's constructor 0x001B4E63 at 0x0035974E, installs 0x00C15398 at +0 at 0x0035975A and constructs three 0x0C-byte map objects at +0x0C/+0x18/+0x24 through 0x0033C432. Destructor 0x00359290 restores the same table at 0x003592A1, destroys those members in reverse order through 0x00358F44/0x00359231/0x00359231 and calls ~SubsystemInterface at 0x003592D4. The parent constructor/destructor install 0x00BD77A0 at 0x001B4E65/0x001B4E74; these are the base subobject's lifetime tables. The parent clears byte +4 and the AsciiString pointer +8 at 0x001B4E6F/0x001B4E6B and destroys the string through 0x00036410 at 0x001B4E7D.
   Table 0x00C15398 has fourteen slots, ending at non-code word 0x00C153D0: 0=0035978C (deleting destructor calling 00359290); 1=003592E6 (init); 2=001B5384 (loadIniFilesFromLegend); 3/8/10/12=000B3FD0 (ret); 4/11=005CB9FF (false, ret 4); 5=0047A699 (false); 6=000D43D0 (zero); 7/13=0047A69C (ret 4); 9=003592FA (reset). Slots 2-8/11-13 equal the registered parent's 0x00BD77A0 table. The parent's full slot form supplies the inherited order. Zero Hour GeneralsMD HotKey.h supplies the class name, base and init/reset/update names; its one-map layout and action API do not describe BFME2. The three map representations remain opaque: 0x00359316/0x0035931B select +0x18/+0x0C, and 0x003597B1/0x003593DD select +0x24.
   Out-of-line method spellings follow ledger rows: searchHotKey(AsciiString) 0x00358CCD, searchHotKey(UnicodeString) 0x00358B9E, addHotKey 0x00359302, addMessageAction 0x003597A8, removeMessageAction 0x003593D8, executeHotKey 0x003593E8, translate 0x00359556, rva00358A53 0x00358A53 and rva00358ACB 0x00358ACB. Their reference, bool, result and enum types follow those rows. The lifetime, init and reset rows retain placeholder owners, so their canonical declarations require provider identity reconciliation before direct calls can resolve. */
#pragma once

#ifndef BFME2_HOTKEYMANAGER_H
#define BFME2_HOTKEYMANAGER_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class UnicodeString;
class GameMessage;
enum GameMessageDisposition;
struct TreeHintRef00217D4C;
struct Rva00359302Result;

class HotKeyManager : public SubsystemInterface
{
public:
    HotKeyManager();
    virtual ~HotKeyManager();
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

    AsciiString searchHotKey(const AsciiString &label);
    AsciiString searchHotKey(const UnicodeString &text);
    Rva00359302Result addHotKey(const TreeHintRef00217D4C &action, const AsciiString &key, bool alternate);
    void addMessageAction(const TreeHintRef00217D4C &action, int messageType);
    unsigned int removeMessageAction(int messageType);
    bool executeHotKey(const AsciiString &key, bool shift);
    GameMessageDisposition translate(const GameMessage *message);
    void rva00358A53();
    void rva00358ACB();

private:
    unsigned char m_storage0C[0x0C];
    unsigned char m_storage18[0x0C];
    unsigned char m_storage24[0x0C];
};

extern HotKeyManager *TheHotKeyManager;

#endif
