// Target facts (game.dat 1.06; code addresses are RVAs, table addresses are VAs):
// 0x00689320 calls SubsystemInterface's 0x001B4E63, stores arguments at +0x0C/+0x10/+0x14 and installs 0x00CE4918 at +0. The derived constructor 0x00090781 calls it, then installs 0x00BC7EA8; its allocation at 0x0004C590 requests 0x1C bytes. The base constructor clears byte +4 and the AsciiString at +8; 0x001B4E74 destroys that string. 0x00689183 reads byte +0x18, 0x0068918F clears it and 0x004F5FA7 sets it. 0x00689596 calls the +0x0C cdecl string-return callback; 0x006899A7/+0x006899B0 test +0x14/+0x10, passed to SubtitleManager's 0x00688750 at 0x00689A34.
// 0x00689350 stores VideoPlayer's concrete 0x00CE4918, clears TheVideoPlayer when equal to this, then stores 0x00CE48A0 and jumps to 0x001B4E74. The rowed intermediate destructor 0x006892F0 stores only 0x00CE48A0 and takes the same jump. Both video tables have 29 slots: 0x00CE4914 is zero and 0x00CE498C begins a string. The intermediate has pure slots 1/9/10/14-28; slots 2-8/11-13 retain SubsystemInterface's fourteen-slot table 0x00BD77A0. The concrete table contains 0:006894E0, 1:006898D0, 2:001B5384, 3:000B3FD0, 4:005CB9FF, 5:0047A699, 6:000D43D0, 7:0047A69C, 8:000B3FD0, 9:00689180, 10:0069E440, 11:005CB9FF, 12:000B3FD0, 13:0047A69C, 14-16:0069E440, 17:006894D0, 18:006891A0, 19:006891B0, 20:00689FD0, 21:00689CE0, 22:006893D0, 23:00689400, 24:00689B10, 25:000907A1, 26:00180FD0, 27:006897B0, 28:004F5FA7. 0x006894E3 and 0x00091141 call the rowed VideoPlayer destructor out of line. First-stream and close are dispatched at +0x48/+0x1C by 0x006891B0; 0x00053371 dispatches provider notification at +0x68; 0x006885EB dispatches the subtitle query at +0x6C. Zero Hour VideoPlayer.h supplies the service names firstStream, deinit, loseFocus, regainFocus, getNumVideos, getVideo(int), getFieldParse and notifyVideoPlayerOfNewProvider; getVideo overloads are declared in donor order to place int at slot 23 with MSVC 7.1. Slot 9 is SubsystemInterface's reset (VideoPlayer's 0x00689180, rowed under the placeholder Rva00689180). The ledger supplies the other named VideoPlayer methods and the intermediate name Rva006892F0. Other slots and fields keep neutral names.

#pragma once
#ifndef BFME2_VIDEOPLAYERCLASS_H
#define BFME2_VIDEOPLAYERCLASS_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

struct Video;
struct FieldParse;
class VideoStreamInterface;
class SubtitleEntry;
class SubtitleManager;

typedef SubtitleEntry *(__cdecl *VideoPlayerSubtitleFactory)(AsciiString *, int,
    const AsciiString &, unsigned int, int, int, int, int, int);

class Rva006892F0 : public SubsystemInterface
{
public:
    virtual ~Rva006892F0();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual void init() = 0;
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
    virtual void reset() = 0;
    virtual void update() = 0;
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif
    virtual void deinit() = 0;
    virtual void loseFocus() = 0;
    virtual void regainFocus() = 0;
    virtual VideoStreamInterface *open(AsciiString title, unsigned int flags) = 0;
    virtual VideoStreamInterface *firstStream() = 0;
    virtual void closeAllStreams() = 0;
    virtual void addVideo(Video *video) = 0;
    virtual void removeVideo(Video *video) = 0;
    virtual int getNumVideos() = 0;
    virtual const Video *getVideo(AsciiString title) = 0;
    virtual const Video *getVideo(int index) = 0;
    virtual const FieldParse *getFieldParse() const = 0;
    virtual void notifyVideoPlayerOfNewProvider(unsigned char available) = 0;
    virtual SubtitleManager *getSubTitleMgrForVideo(const AsciiString &title) = 0;
    virtual void slot28() = 0;
};

class VideoPlayer : public Rva006892F0
{
public:
    virtual ~VideoPlayer();
    virtual void init();
    virtual void reset();
    virtual void update();
    virtual void deinit();
    virtual void loseFocus();
    virtual void regainFocus();
    virtual VideoStreamInterface *open(AsciiString title, unsigned int flags);
    virtual VideoStreamInterface *firstStream();
    virtual void closeAllStreams();
    virtual void addVideo(Video *video);
    virtual void removeVideo(Video *video);
    virtual int getNumVideos();
    virtual const Video *getVideo(AsciiString title);
    virtual const Video *getVideo(int index);
    virtual const FieldParse *getFieldParse() const;
    virtual void notifyVideoPlayerOfNewProvider(unsigned char available);
    virtual SubtitleManager *getSubTitleMgrForVideo(const AsciiString &title);
    virtual void slot28();

    void rva00689580(AsciiString &out);

private:
    AsciiString (__cdecl *m_field0C)();
    int m_field10;
    VideoPlayerSubtitleFactory m_field14;
    bool m_flag18;
};

typedef char VideoPlayerSizeCheck[(sizeof(VideoPlayer) == 0x1C) ? 1 : -1];

#endif
