// Adapted from BFME1 7a8a034afa7d game/GameEngine/Source/GameClient/window_layout.h.
// Donor interface projection retained for the admitted BFME2 WindowLayout rows;
// the obsolete BFME1-only manager view is replaced by the shared BFME2 header.
// Donor table addresses below are BFME1 facts, not BFME2 placement claims.
#pragma once
// WindowLayout (GameClient/WindowLayout.h in Generals). BFME made the layout
// methods virtual; the declaration order below reproduces the vtable read from
// the binary at 0x10f7514 (runInit, dtor, runUpdate, runShutdown, hide,
// bringForward, addWindow, removeWindow, destroyWindows). Generals' inline
// run* accessors stayed inline (their bodies land in COMDAT space at 0x4706xx,
// away from the WindowLayout.obj region at 0x497axx).

class GameWindow;
class WindowLayout;

// GameWindow layout-chain accessors (Generals GameWindow.h). Addresses come
// from targets/game/reverse/symbols.csv, derived from the binary's call sites.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow {
public:
    GameWindow *winGetNextInLayout(void);
    GameWindow *winGetPrevInLayout(void);
    int winSetNextInLayout(GameWindow *next);
    int winSetPrevInLayout(GameWindow *prev);
    int winSetLayout(WindowLayout *layout);
    int winHide(int hide);
    int winBringToTop(void);
};

// Partial GameWindowManager: only the slot used here is meaningful.
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
#include "GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

// Stands in for BFME's AsciiString member (StringBase<char> family). The
// out-of-line set/dtor resolve to the matched StringBase<char> functions via
// targets/game/reverse/symbols.csv until AsciiString/StringBase headers unify.
class LayoutFilename {
public:
    LayoutFilename() : m_data(0) {}
    void set(const char *str, int len);
    ~LayoutFilename();

private:
    void *m_data;
};

typedef void (*WindowLayoutFunc)(void *layout, void *userData);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout {
public:
    WindowLayout(void);

    virtual void runInit(void *userData) { if (m_init) m_init(this, userData); }            // slot 0
    virtual ~WindowLayout();                                                                 // slot 1
    virtual void runUpdate(void *userData) { if (m_update) m_update(this, userData); }       // slot 2
    virtual void runShutdown(void *userData) { if (m_shutdown) m_shutdown(this, userData); } // slot 3
    virtual void hide(int hide);                                                             // slot 4
    virtual void bringForward(void);                                                         // slot 5
    virtual void addWindow(GameWindow *window);                                              // slot 6
    virtual void removeWindow(GameWindow *window);                                           // slot 7
    virtual void destroyWindows(void);                                                       // slot 8

    GameWindow *getFirstWindow(void) { return m_windowList; }

private:
    GameWindow *findWindow(GameWindow *window);

    LayoutFilename m_filenameString;  // +0x04
    GameWindow *m_windowList;         // +0x08
    GameWindow *m_windowTail;         // +0x0c
    int m_windowCount;                // +0x10
    char m_hidden;                    // +0x14
    WindowLayoutFunc m_init;          // +0x18
    WindowLayoutFunc m_update;        // +0x1c
    WindowLayoutFunc m_shutdown;      // +0x20
};
