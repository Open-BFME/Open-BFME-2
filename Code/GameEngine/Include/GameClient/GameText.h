// GameTextInterface: canonical BFME2 abstract text subsystem.
// Target facts (code addresses are RVAs; table addresses are VAs):
// Constructor 0x002E55FF calls SubsystemInterface's 0x001B4E63 at 0x002E5602, then stores 0x00C04E90 at 0x002E5607. Destructor 0x002E55D8 restores that table and tail-calls the parent destructor 0x001B4E74. These bodies retain the ledger's Rva002E55D8 name; lifetime methods are declared out of line.
// Table 0x00C04E90 has 22 slots: 0 is the deleting destructor 0x002E55E3; slots 1-13 equal the parent's 0x00BD77A0; slots 14-21 are __purecall (0x0003B810). The next word at 0x00C04EE8 is text. This class is polymorphic and adds eight pure virtual methods to the parent's fourteen slots.
// GameTextManager's constructor 0x002E63AA calls the parent constructor at 0x002E63BD and stores 0x00C04FA8 at 0x002E63CF. Its destructor 0x002E66F2 stores that table at 0x002E6703, then restores the interface table at 0x002E6733 before calling the parent destructor at 0x002E6739. The tables describe successive class lifetimes, not alternative interface layouts. Unwind paths 0x00778D11 and 0x00778D49 call the interface destructor 0x002E55D8.
// SubsystemInterface's constructor clears byte +4 and the AsciiString pointer +8. The interface constructor adds no fields; GameTextManager uses +0xC onward for its own state. The interface therefore occupies the parent's 0xC bytes. The factory 0x002E651F allocates 0x44 bytes at 0x002E652A for the manager, not the interface.
// Manager table 0x00C04FA8 names slots 14/15 as fetch(AsciiString const&,bool*) at 0x002E573C and fetch(char const*,bool*) at 0x002E5719; slots 16/17 as fetchPtr(AsciiString const&,bool*) at 0x002E5770 and fetchPtr(char const*,bool*) at 0x002E65B1. MSVC reverses each introducing overload group. Retail callers 0x00433CC2 and 0x00583241 dispatch fetch at +0x38 and +0x3C respectively.
// Manager slots 18/19/20 are the rowed getStringsWithLabelPrefix 0x002E67EA, initMapStringFile 0x002E6A38 and setTranslateMode 0x002E640B. Slot 21 is 0x005C4AF5, a dword getter at +0x40; its text-subsystem name is unproved and stays vslot21. Manager-only slot 22 is the rowed deinit 0x002E6551. Zero Hour GameText.h independently supplies the fetch, prefix-query and map-file method names; its by-value AsciiString parameters differ from BFME2's rowed reference parameters.
#ifndef BFME2_GAMETEXT_H
#define BFME2_GAMETEXT_H

#if defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#error Include GameText.h before the short SubsystemInterface definition.
#endif
#ifndef BFME_SUBSYSTEM_SLOTS
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class UnicodeString;
namespace _STL {
template <class T> class allocator;
template <class T, class Alloc> class vector;
}

class GameTextInterface : public SubsystemInterface {
public:
    GameTextInterface();
    virtual ~GameTextInterface();

    virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
    virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
    virtual UnicodeString *fetchPtr(const char *label, bool *exists = 0) = 0;
    virtual UnicodeString *fetchPtr(const AsciiString &label, bool *exists = 0) = 0;
    virtual _STL::vector<AsciiString, _STL::allocator<AsciiString> > &getStringsWithLabelPrefix(const AsciiString &label) = 0;
    virtual void initMapStringFile(const AsciiString &filename) = 0;
    virtual void setTranslateMode(int mode) = 0;
    virtual int vslot21() = 0;
};

extern GameTextInterface *TheGameText;
GameTextInterface *CreateGameTextInterface();

#endif
