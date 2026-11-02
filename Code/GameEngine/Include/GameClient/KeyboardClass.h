// Keyboard: canonical BFME2 keyboard interface and layout.
// Target facts (addresses are RVAs unless explicitly marked VA):
// - Constructor 0x00232920 calls SubsystemInterface 0x001B4E63 at +0,
//   installs VA 0x00BE81F0 at 0x00232932, and constructs the vector at +0x10.
//   The base constructor writes its vptr at +0, a byte at +4 and a dword at +8;
//   its destructor 0x001B4E74 restores VA 0x00BD77A0 and destroys +8.
//   Thus the base occupies 12 bytes, not the 8 of some private views.
// - Destructor 0x00232976 restores VA 0x00BE81F0 at 0x00232987, frees +0x10,
//   then calls the base destructor. The base table belongs to the base's
//   lifetime; VA 0x00BC8688, installed by 0x00098B55/0x00098B8B, belongs to
//   DirectInputKeyboard. Neither replaces Keyboard's own 17-slot table.
// - VA 0x00BE81F0 has slot 0 deleting destructor 0x002329B7, slot 1 init
//   0x0023260F, inherited slots 2-13 (reset slot 9 is the empty 0x000B3FD0,
//   update slot 10 is 0x00232BC7), pure slot 14, slot 15 createStreamMessages
//   0x002326FB and pure slot 16, followed by zero at VA 0x00BE8234.
//   Shared slots: 2 = 0x001B5384; 3/8/12 = 0x000B3FD0;
//   4/11 = 0x005CB9FF; 5 = 0x0047A699; 6 = 0x000D43D0;
//   7/13 = 0x0047A69C. The base has pure slots 1/9/10 instead.
//   The inherited signatures agree with the registered base's full slot view.
//   DirectInputKeyboard fills slot 14 with 0x00098BC8 (caps-lock query) and
//   slot 16 with 0x00098AAC (KeyboardIO output); 0x00232BA7 calls slot 16.
// - Constructor stores prove a word at +0x0C, a byte at +0x0E, a 0x800-byte
//   status array at +0x1C, a 0x600-byte names array at +0x81C and a dword at
//   +0xE1C. Status accessors 0x00232620/0x0023262C/0x00232654 use stride 8,
//   status byte +1, state word +2 and sequence dword +4. 0x002326AE reads
//   three 16-bit names per key. 0x002326FB reads vector begin/end +0x10/+0x14.
//   Vector constructor 0x00211E58 clears +0/+4 and constructs +8 through
//   0x0014F3C4; its three pointer-sized storage fields occupy +0x10..+0x1B.
//   DirectInputKeyboard begins its own pointers at +0xE20/+0xE24; factory
//   0x0004C6DF allocates 0xE28. Keyboard's complete data extent is 0xE20.
// - Out-of-line rows: initKeyNames 0x002306B8, getKeyStatusData 0x00232620,
//   rva00232643 0x00232643, isShift 0x00232683, isCtrl 0x00232696,
//   isAlt 0x002326A2,
//   getPrintableKey 0x002326AE, translateKey 0x00232763, checkKeyRepeat
//   0x002329D3, rva00232A42 0x00232A42, rva00232AE8 0x00232AE8,
//   rva00232B7B 0x00232B7B and resetKeys 0x00232BDD retain their ledger ABI.
// Donor facts: Zero Hour Keyboard.h names getCapsState, getKey, the modifier
// getter and the data members. Its fixed key array is replaced in BFME2 by
// the three vector pointers. getModifierFlags returns the +0x0C word, as the
// retail GadgetHorizontalSliderInput tests at 0x00321C40..0x00321C4B.

#pragma once
#ifndef CANONICAL_KEYBOARDCLASS_H
#define CANONICAL_KEYBOARDCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

struct KeyboardIO
{
    enum StatusType { STATUS_UNUSED = 0, STATUS_USED = 1 };
    unsigned char key;
    unsigned char status;
    unsigned short state;
    unsigned int sequence;
};

class Keyboard : public SubsystemInterface
{
public:
    Keyboard();
    virtual ~Keyboard();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual bool getCapsState() = 0;
    virtual void createStreamMessages();

    bool isShift();
    bool isCtrl();
    bool isAlt();
    int getModifierFlags() { return m_modifiers; }
    void resetKeys();
    unsigned short translateKey(unsigned short keyCode);
    unsigned short getPrintableKey(unsigned char key, int state);
    unsigned char getKeyStatusData(unsigned char key);
    bool rva00232643(unsigned char key);
    void initKeyNames();
    void rva00232A42();
    void rva00232B7B();
    enum { MAX_KEY_STATES = 3, KEY_NAMES_COUNT = 256 };

protected:
    virtual void getKey(KeyboardIO *key) = 0;
    bool checkKeyRepeat();

private:
    void rva00232AE8();

public:
    unsigned short m_modifiers;
    unsigned char m_shift2Key;
    KeyboardIO *field10;
    KeyboardIO *field14;
    KeyboardIO *field18;
    KeyboardIO m_keyStatus[256];
    struct
    {
        unsigned short stdKey;
        unsigned short shifted;
        unsigned short shifted2;
    } m_keyNames[256];
    unsigned int m_inputFrame;
};

#endif
