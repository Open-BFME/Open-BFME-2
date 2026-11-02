/* Target facts (code addresses are RVAs, tables are VAs): Shell is polymorphic. Constructor 0x0035BFBC calls SubsystemInterface's constructor 0x001B4E63 at 0x0035BFD0, then installs 0x00C16208 at +0 at 0x0035BFDA. Destructor 0x0035C087 installs the same table at 0x0035C099 and calls the parent's destructor 0x001B4E74 at 0x0035C157. The parent's 0x00BD77A0 stores at 0x001B4E65/0x001B4E74 belong to the base lifetime. Deleting destructor 0x0035C54A calls 0x0035C087. Allocation 0x00239891 pushes 0x78 before operator new 0x0002FDA0 and constructor call 0x002398A5; the constructor writes through +0x74, establishing sizeof 0x78 with the 0x0C-byte parent.
   Table 0x00C16208 has fourteen slots, ending at text at 0x00C16240: 0=35C54A, 1=35BD00, 2=1B5384, 3/8/12=0B3FD0, 4/11=5CB9FF, 5=47A699, 6=0D43D0, 7/13=47A69C, 9=35C16A, 10=35C566. Slots 2-8/11-13 equal the registered parent's table. Zero Hour Shell.h names init/reset/update; reset/update have ledger rows and slot 1 reads +0x64 then tail-calls the scheme manager. Constructor 0x0035BFED..0x0035BFF0 clears sixteen pointers at +0x0C; top 0x0035BD7E reads count +0x4C and indexes that array. Constructor stores prove bytes +50/+51/+52/+53/+54, string +58, bytes +5C/+5D, pointers +60/+64, word +68, bytes +6C/+6D and layout pointers +70/+74. Destructor 0x0035C146..0x0035C14C destroys the +58 string; loadScheme 0x0035C49C uses +64, animation methods 0x0035BE23/0x0035BEAA use +60, and layout getters 0x0035C4E6/0x0035C518 use +70/+74.
   Member spellings and signatures follow reverse/functions.csv's Shell rows at 35BD7E, 35BD8B, 35BDA5, 35BDC2, 35BE23, 35BE55, 35BE8F, 35BEAA, 35BEC7, 35BF0E, 35BF4C, 35C194, 35C2B9, 35C3C3, 35C445, 35C49C, 35C4E6, 35C518, 35C6B4, 35C74A and 35C7CF. hide(bool) is the existing spelling proved by the direct call at 0x005128ED to 0x0035BF4C. Zero Hour's Shell.h supplies the stack, pending-operation, active/map, manager and layout field names and accessor names; BFME2-only storage retains offset names. Rowed lifetimes and methods are declared out of line. */
#ifndef BFME2_SHELL_H
#define BFME2_SHELL_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
class WindowLayout;
class AnimateWindowManager;
class ShellMenuSchemeManager;
class GameWindow;
enum AnimTypes;

class Shell : public SubsystemInterface
{
public:
    Shell();
    virtual ~Shell();
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

    bool showShellMap(bool useShellMap, bool restartShellGame);
    void hide(bool shutdownImmediate);
    void push(AsciiString filename, bool shutdownImmediate = false);
    void pop();
    void popImmediate();
    void showShell(bool runInit = true);
    WindowLayout *top();
    void shutdownComplete(WindowLayout *layout, bool impendingPush = false);
    WindowLayout *findScreenByFilename(AsciiString filename);
    bool isShellActive() const { return m_isShellActive; }
    int getScreenCount() const { return m_screenCount; }
    void registerWithAnimateManager(GameWindow *win, AnimTypes animType,
        bool needsToFinish, unsigned int delayMS = 0);
    bool isAnimFinished();
    void reverseAnimatewindow();
    bool isAnimReversed();
    void loadScheme(AsciiString name);
    ShellMenuSchemeManager *getShellMenuSchemeManager() { return m_schemeManager; }
    WindowLayout *getSaveLoadMenuLayout();
    WindowLayout *getPopupReplayLayout();
    bool rva0035BD5D();
    void rva0035C2B9();
    void rva0035BF4C(bool shutdownImmediate);

protected:
    void linkScreen(WindowLayout *screen);
    void unlinkScreen(WindowLayout *screen);
    void doPush(AsciiString layoutFile);
    void doPop(bool impendingPush);

public:
    enum { MAX_SHELL_STACK = 16 };
    WindowLayout *m_screenStack[MAX_SHELL_STACK];
    int m_screenCount;
    bool m_pendingPush;
    bool m_pendingPop;
    bool m_byte52;
    bool m_byte53;
    bool m_clearBackground;
    unsigned char m_pad55[3];
    AsciiString m_pendingPushName;
    bool m_isShellActive;
    bool m_shellMapOn;
    unsigned char m_pad5E[2];
    AnimateWindowManager *m_animateWindowManager;
    ShellMenuSchemeManager *m_schemeManager;
    unsigned int m_word68;
    bool m_byte6C;
    bool m_byte6D;
    unsigned char m_pad6E[2];
    WindowLayout *m_saveLoadMenuLayout;
    WindowLayout *m_popupReplayLayout;
};

extern Shell *TheShell;

#endif
