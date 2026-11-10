// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ?addVideo@VideoPlayer@@UAEXPAUVideo@@@Z
// Native RVA 0x00689FD0, 270 bytes. Clean C++ donor Open-BFME-1
// 10af19f44a89ab7ecc23195bb9a842ceafbc02c9,
// game/GameEngine/Source/GameClient/VideoPlayerAddVideo.cpp (B1 0x0081D2C0).
// Native callback table VA 0x00BC7EBC has add/remove at slots 15/16 and the
// already-matched getVideo at slot 19. Those neighbors and the shared 28-byte
// table support the donor's operation/class interpretation; original symbols
// are unknown. Replacement stores verify three strings and fields C/10/14/18.
//
// Keep canonical AsciiString. Its frozen compare wrapper calls out of line;
// the native loop inlines the donor's null/length/text comparison, spelled
// below through the existing allocation-header layout rather than a new class.
// Use the already-verified vector family's compiler/allocator settings.
// Construct call 0x0068A060 reaches 0x006896F0; that 66-byte SEH wrapper calls
// the copy constructor 0x00689650 at 0x0068971E. This TU reproduces that
// constructor's full 122 bytes. Overflow at 0x0068A0D1 reaches 0x00689E60;
// its full 300 bytes match with the established family flags and typed pins.
// Destructor 0x00689500 is the existing verified 119-byte element destructor;
// its owned-pointer teardown and three string releases fit this same layout.

#include "../../Include/GameClient/BfmeVideoRecord.h"
#include "../../Include/GameClient/BfmeVideoTable.h"
#include <vector>

struct VideoNameHeaderView
{
    int refCount;
    unsigned short length;
    unsigned short capacity;
    char text[1];
};
struct VideoNameStorageView { VideoNameHeaderView *data; };

// ?compareVideoNamesExact@@YAHABVAsciiString@@0@Z absent-from-retail
__forceinline int compareVideoNamesExact(const AsciiString &self, const AsciiString &other)
{
    const VideoNameStorageView *left = (const VideoNameStorageView *)&self;
    const VideoNameStorageView *right = (const VideoNameStorageView *)&other;
    int rightLength = right->data ? right->data->length : 0;
    const char *rightText = right->data ? right->data->text : "";
    int leftLength = left->data ? left->data->length : 0;
    const char *leftText = left->data ? left->data->text : "";
    int result = memcmp(leftText, rightText, leftLength < rightLength ? leftLength : rightLength);
    return result != 0 ? result : leftLength - rightLength;
}

typedef char BfmeVideoVectorWidth[(sizeof(_STL::vector<Video>) == 12) ? 1 : -1];
// Both names reach native 0x00689500; reuse its verified kept definition.

#include "../../Include/GameClient/VideoPlayerClass.h"

void VideoPlayer::addVideo(Video *video)
{
    _STL::vector<Video> &videoTable = *(_STL::vector<Video> *)&g_videoTable;
    for (_STL::vector<Video>::iterator it = videoTable.begin();
         it != videoTable.end(); ++it)
    {
        if (compareVideoNamesExact(it->m_internalName, video->m_internalName) == 0)
        {
            *it = *video;
            return;
        }
    }

    videoTable.push_back(*video);
}
