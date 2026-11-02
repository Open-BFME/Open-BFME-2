// Target facts (code addresses are RVAs; tables are VAs): ctor 0x0053F85C calls SubsystemInterface 0x001B4E63 at +0, constructs the rowed hash_map through 0x0053F83D at +0x0C, installs 0x00C694A4 and clears bytes +0x20/+0x21. Dtor 0x0053F45C restores the same table, destroys the map at +0x0C and calls base dtor 0x001B4E74, which installs 0x00BD77A0 and releases the string at +8. The base ctor installs 0x00BD77A0 and clears byte +4 and dword +8. These are base and derived lifetimes, not competing WindowVideoManager tables. Allocation 0x0031CFCD requests 0x24 bytes via 0x0002FDA0 and calls this ctor at 0x0031CFE2: sizeof 0x24, with a 0x0C-byte base and no intervening gap.
// Target facts: 0x00C694A4 has fourteen slots before the next table at 0x00C694DC (stored at 0x0053FAC7): 0 deleting dtor 0x0053F821; 1 init 0x0053F2A4; 2 loadIniFilesFromLegend 0x001B5384; 3/8/12 ret 0x000B3FD0; 4/11 false-ret-4 0x005CB9FF; 5 false 0x0047A699; 6 zero 0x000D43D0; 7/13 ret-4 0x0047A69C; 9 reset 0x0053F4E4; 10 update 0x0053F53C. The registered parent's BFME_SUBSYSTEM_SLOTS form supplies this order. Map ctor 0x0053F7E1 puts its bucket vector at +4 and count at +0x10, so the map occupies +0x0C..+0x1F. field0C preserves that map's opaque storage; the declared lifecycle bodies construct and destroy it. stopAllMovies 0x0053F721 sets byte +0x20; pauseAllMovies 0x0053F761 sets byte +0x21; update tests both. All lifecycle and movie methods below are declared out of line.
// Target facts: ledger rows prove playMovie 0x0053F63D, hideMovie 0x0053F2DD, pauseMovie 0x0053F2B9, resumeMovie 0x0053F301, stopMovie 0x0053F331, stopAndRemoveMovie 0x0053F3FF, stopAllMovies 0x0053F721, pauseAllMovies 0x0053F761, resumeAllMovies 0x0053F7A1 and getWinState 0x0053F355, including their signatures and the nested hash type in map ctor 0x0053F83D. Rehash 0x0053F255 loads the raw pointer key from node +4 and divides it by bucket count, proving the identity hash. Donor facts: Zero Hour GeneralsMD GameClient/WindowVideoManager.h names the map, flags and hash, with its by-value pointer argument. The donor supplies names and source spelling, not BFME2 layout evidence.

#pragma once
#ifndef CANONICAL_WINDOWVIDEOMANAGERCLASS_H
#define CANONICAL_WINDOWVIDEOMANAGERCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include <stddef.h>

class GameWindow;
class WindowVideo;
enum WindowVideoPlayType;

class WindowVideoManager : public SubsystemInterface
{
public:
    WindowVideoManager();
    virtual ~WindowVideoManager();
    virtual void init();
    virtual void reset();
    virtual void update();

    void playMovie(GameWindow *win, AsciiString movieName, WindowVideoPlayType playType);
    void hideMovie(GameWindow *win);
    void pauseMovie(GameWindow *win);
    void resumeMovie(GameWindow *win);
    void stopMovie(GameWindow *win);
    void stopAndRemoveMovie(GameWindow *win);
    void stopAllMovies();
    void pauseAllMovies();
    void resumeAllMovies();
    int getWinState(GameWindow *win);

    typedef const GameWindow *ConstGameWindowPtr;
    struct hashConstGameWindowPtr
    {
        size_t operator()(ConstGameWindowPtr p) const { return (unsigned int)p; }
    };

private:
    char field0C[0x14];
    bool m_stopAllMovies;
    bool m_pauseAllMovies;
};

#endif
