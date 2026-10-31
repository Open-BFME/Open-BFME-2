// GameWindowManager: target ABI view, VA BC7C90 and base constructor RVA 2C5334.
// Unknown virtual slots are opaque declarations, never named as recovered methods.
// Opaque slots are private and have no callable signature claim; they only reserve proven positions.
// Member names follow the ZH donor except target-identified m_windowList/m_keyboardFocus.
// Retail new at RVA 4C4C7 proves size0x40; ctor2C5334 proves the base and field offsets.
#pragma once
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
class GameWindow;
class GameFont;
struct Rva0047EDE0CreateInfo;
enum WindowMsgHandledType;
class GameWindowManager : public SubsystemInterface {
public:
    GameWindowManager();
    virtual ~GameWindowManager();
private:
    virtual void slot01(); // slot 1
public:
private:
    virtual void slot02(); // slot 2
public:
private:
    virtual void slot03(); // slot 3
public:
private:
    virtual void slot04(); // slot 4
public:
private:
    virtual void slot05(); // slot 5
public:
private:
    virtual void slot06(); // slot 6
public:
private:
    virtual void slot07(); // slot 7
public:
    virtual void init(); // slot 8
    virtual void reset(); // slot 9
    virtual void update(); // slot 10
private:
    virtual void slot11(); // slot 11
public:
private:
    virtual void slot12(); // slot 12
public:
private:
    virtual void slot13(); // slot 13
public:
    virtual int slot14(); // slot 14
    virtual GameWindow *slot15(Rva0047EDE0CreateInfo *info); // slot 15
private:
    virtual void slot16(); // slot 16
public:
private:
    virtual void slot17(); // slot 17
public:
private:
    virtual void slot18(); // slot 18
public:
private:
    virtual void slot19(); // slot 19
public:
private:
    virtual void slot20(); // slot 20
public:
private:
    virtual void slot21(); // slot 21
public:
private:
    virtual void slot22(); // slot 22
public:
private:
    virtual void slot23(); // slot 23
public:
private:
    virtual void slot24(); // slot 24
public:
private:
    virtual void slot25(); // slot 25
public:
private:
    virtual void slot26(); // slot 26
public:
private:
    virtual void slot27(); // slot 27
public:
private:
    virtual void slot28(); // slot 28
public:
private:
    virtual void slot29(); // slot 29
public:
private:
    virtual void slot30(); // slot 30
public:
private:
    virtual void slot31(); // slot 31
public:
private:
    virtual void slot32(); // slot 32
public:
    virtual void freeStaticStrings(); // slot 33
private:
    virtual void slot34(); // slot 34
public:
    virtual int winDestroy(GameWindow *); // slot 35
    virtual int winDestroyAll(); // slot 36
private:
    virtual void slot37(); // slot 37
public:
    virtual void hideWindowsInRange(GameWindow *, int, int, bool); // slot 38
    virtual void enableWindowsInRange(GameWindow *, int, int, bool); // slot 39
private:
    virtual void slot40(); // slot 40
public:
private:
    virtual void slot41(); // slot 41
public:
private:
    virtual void slot42(); // slot 42
public:
private:
    virtual void slot43(); // slot 43
public:
private:
    virtual void slot44(); // slot 44
public:
private:
    virtual void slot45(); // slot 45
public:
private:
    virtual void slot46(); // slot 46
public:
    virtual int rva002C0F68(bool, bool); // slot 47
private:
    virtual void slot48(); // slot 48
public:
private:
    virtual void slot49(); // slot 49
public:
private:
    virtual void slot50(); // slot 50
public:
private:
    virtual void slot51(); // slot 51
public:
private:
    virtual void slot52(); // slot 52
public:
private:
    virtual void slot53(); // slot 53
public:
private:
    virtual void slot54(); // slot 54
public:
private:
    virtual void slot55(); // slot 55
public:
    virtual void addWindowToParent(GameWindow *, GameWindow *); // slot 56
    virtual void addWindowToParentAtEnd(GameWindow *, GameWindow *); // slot 57
    virtual WindowMsgHandledType winSendSystemMsg(GameWindow *, unsigned int, unsigned int, unsigned int); // slot 58
    virtual WindowMsgHandledType winSendInputMsg(GameWindow *, unsigned int, unsigned int, unsigned int); // slot 59
    virtual GameWindow *winGetWindowFromId(GameWindow *, int); // slot 60
private:
    virtual void slot61(); // slot 61
public:
private:
    virtual void slot62(); // slot 62
public:
private:
    virtual void slot63(); // slot 63
public:
private:
    virtual void slot64(); // slot 64
public:
private:
    virtual void slot65(); // slot 65
public:
private:
    virtual void slot66(); // slot 66
public:
private:
    virtual void slot67(); // slot 67
public:
private:
    virtual void slot68(); // slot 68
public:
private:
    virtual void slot69(); // slot 69
public:
private:
    virtual void slot70(); // slot 70
public:
private:
    virtual void slot71(); // slot 71
public:
private:
    virtual void slot72(); // slot 72
public:
private:
    virtual void slot73(); // slot 73
public:
private:
    virtual void slot74(); // slot 74
public:
private:
    virtual void slot75(); // slot 75
public:
    virtual GameFont *slot76(AsciiString, int, bool); // slot 76
private:
    virtual void slot77(); // slot 77
public:
    GameWindow *winCreate(Rva0047EDE0CreateInfo *);
    GameFont *winFindFont(AsciiString, int, bool);
    void linkWindow(GameWindow *);
protected:
    void dumpWindow(GameWindow *);
    GameWindow *m_windowList; // +0x0C: link/dump owners
    GameWindow *m_windowTail;
    GameWindow *m_destroyList;
    GameWindow *m_currMouseRgn;
    GameWindow *m_mouseCaptor;
    GameWindow *m_keyboardFocus; // +0x20: set-focus and parent-chain owners
    void *m_modalHead;
    GameWindow *m_grabWindow;
    GameWindow *m_loneWindow;
    unsigned char m_unrecovered30[4]; // native list base at +0x30, not typed/adopted here
    unsigned int m_unrecovered34;
    unsigned int m_unrecovered38;
    int m_unrecovered3C; // native constructor initializes -1
};
typedef char GameWindowManagerRetailSize[sizeof(GameWindowManager)==0x40 ? 1 : -1];
