// GameWindowManager: target ABI view, VA BC7C90 and base constructor RVA 2C5334.
// Slots 0-13 are SubsystemInterface's 14-slot form (base table VA BFF658: init 1, reset 9, update 10).
// Unknown slots from 14 on are private opaque declarations that only reserve proven positions.
// Member names follow the ZH donor except target-identified m_windowList/m_keyboardFocus.
// Retail new at RVA 4C4C7 proves size0x40; ctor2C5334 proves the base and field offsets.
#pragma once
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
class GameWindow;
class GameFont;
class UnicodeString;
struct Rva0047EDE0CreateInfo;
enum WindowMsgHandledType;
class WindowLayout;
class GadgetCreateView;
struct _ListboxData;
struct _EntryData;
struct _ComboBoxData;
class Rva0031763A;
struct ICoord2D;
class Image;
class ModalWindow;
enum GameWindowMessage;
enum WinInputReturnCode;
class GameWindowManager : public SubsystemInterface {
public:
    GameWindowManager();
    virtual ~GameWindowManager();
#ifndef BFME_SUBSYSTEM_SLOTS
    // The unit sees SubsystemInterface's short form: its slots 1-13 are declared here.
    virtual void init(); // slot 1
    virtual bool loadIniFilesFromLegend(); // slot 2
    virtual void postProcessLoad(); // slot 3
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
    virtual void reset(); // slot 9
    virtual void update(); // slot 10
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#else
    virtual void init(); // slot 1
    virtual void reset(); // slot 9
    virtual void update(); // slot 10
#endif
    virtual int slot14(); // slot 14
    virtual GameWindow *slot15(Rva0047EDE0CreateInfo *info); // slot 15
private:
    virtual void slot16(); // slot 16
public:
    // MSVC places overloads in reverse declaration order: the bool form is slot 17.
    virtual GameWindow *gogoMessageBox(int, int, int, int, unsigned short, UnicodeString, UnicodeString, void (*)(), void (*)(), void (*)(), void (*)()); // slot 18
    virtual GameWindow *gogoMessageBox(int, int, int, int, unsigned short, UnicodeString, UnicodeString, void (*)(), void (*)(), void (*)(), void (*)(), bool); // slot 17
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
    virtual GameWindow *gogoGadgetListBox(GadgetCreateView *, _ListboxData *, GameFont *, bool); // slot 24
private:
    virtual void slot25(); // slot 25
public:
private:
    virtual void slot26(); // slot 26
public:
private:
    virtual void slot27(); // slot 27
public:
    virtual GameWindow *gogoGadgetTextEntry(GadgetCreateView *, _EntryData *, GameFont *, bool); // slot 28
    virtual GameWindow *gogoGadgetComboBox(GadgetCreateView *, _ComboBoxData *, GameFont *, bool); // slot 29
    virtual void assignDefaultGadgetLook(GameWindow *, GameFont *, bool); // slot 30
    virtual GameWindow *winCreateFromScript(AsciiString, Rva0031763A *, GameWindow *); // slot 31
    virtual WindowLayout *winCreateLayout(AsciiString); // slot 32
    virtual void freeStaticStrings(); // slot 33
private:
    virtual void slot34(); // slot 34
public:
    virtual int winDestroy(GameWindow *); // slot 35
    virtual int winDestroyAll(); // slot 36
    virtual GameWindow *winGetWindowList(); // slot 37
    virtual void hideWindowsInRange(GameWindow *, int, int, bool); // slot 38
    virtual void enableWindowsInRange(GameWindow *, int, int, bool); // slot 39
    virtual void windowHiding(GameWindow *); // slot 40
private:
    virtual void slot41(); // slot 41
public:
    virtual void winNextTab(GameWindow *); // slot 42
    virtual void winPrevTab(GameWindow *); // slot 43
private:
    virtual void slot44(); // slot 44
public:
    virtual void clearTabList(); // slot 45
    virtual WinInputReturnCode winProcessMouseEvent(GameWindowMessage, ICoord2D *, void *); // slot 46
    virtual int rva002C0F68(bool, bool); // slot 47
    virtual GameWindow *winGetFocus(); // slot 48
    virtual int winSetFocus(GameWindow *); // slot 49
private:
    virtual void slot50(); // slot 50
public:
    virtual GameWindow *winGetGrabWindow(); // slot 51
    virtual void winSetLoneWindow(GameWindow *); // slot 52
    virtual GameWindow *slot53(); // slot 53: returns m_loneWindow
    virtual bool isEnabled(GameWindow *); // slot 54
    virtual bool isHidden(GameWindow *); // slot 55
    virtual void addWindowToParent(GameWindow *, GameWindow *); // slot 56
    virtual void addWindowToParentAtEnd(GameWindow *, GameWindow *); // slot 57
    virtual WindowMsgHandledType winSendSystemMsg(GameWindow *, unsigned int, unsigned int, unsigned int); // slot 58
    virtual WindowMsgHandledType winSendInputMsg(GameWindow *, unsigned int, unsigned int, unsigned int); // slot 59
    virtual GameWindow *winGetWindowFromId(GameWindow *, int); // slot 60
    virtual int winCapture(GameWindow *); // slot 61
    virtual int winRelease(GameWindow *); // slot 62
    virtual GameWindow *winGetCapture(); // slot 63
    virtual int winSetModal(GameWindow *); // slot 64
    virtual int winUnsetModal(GameWindow *); // slot 65
    virtual void winDrawImage(const Image *, int, int, int, int, int = 0xFFFFFFFF); // slot 66
    virtual void winFillRect(int, float, int, int, int, int); // slot 67
    virtual void winOpenRect(int, float, int, int, int, int); // slot 68
private:
    virtual void slot69(); // slot 69
public:
    virtual int winMakeColor(unsigned char, unsigned char, unsigned char, unsigned char); // slot 70
    virtual const Image *winFindImage(const char *); // slot 71
    virtual int winFontHeight(GameFont *); // slot 72
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
    virtual GameWindow *getWindowUnderCursor(int, int, bool); // slot 77
    GameWindow *winCreate(Rva0047EDE0CreateInfo *);
    GameFont *winFindFont(AsciiString, int, bool);
    UnicodeString winTextLabelToText(AsciiString);
    void winGetTextSize(GameFont *, UnicodeString, int *, int *, int);
    void linkWindow(GameWindow *);
    void unlinkWindow(GameWindow *);
    void unlinkChildWindow(GameWindow *);
    void insertWindowAheadOf(GameWindow *, GameWindow *);
    GameWindow *duplicateGadget(GameWindow *, int);
    void rva002C5761(GameWindow *);
protected:
    void processDestroyList();
    int drawWindow(GameWindow *);
    void dumpWindow(GameWindow *);
    GameWindow *m_windowList; // +0x0C: link/dump owners
    GameWindow *m_windowTail;
    GameWindow *m_destroyList;
    GameWindow *m_currMouseRgn;
    GameWindow *m_mouseCaptor;
    GameWindow *m_keyboardFocus; // +0x20: set-focus and parent-chain owners
    ModalWindow *m_modalHead;
    GameWindow *m_grabWindow;
    GameWindow *m_loneWindow;
    unsigned char m_unrecovered30[4]; // native list base at +0x30, not typed/adopted here
    unsigned int m_unrecovered34;
    unsigned int m_unrecovered38;
    int m_unrecovered3C; // native constructor initializes -1
};
typedef char GameWindowManagerRetailSize[sizeof(GameWindowManager)==0x40 ? 1 : -1];
