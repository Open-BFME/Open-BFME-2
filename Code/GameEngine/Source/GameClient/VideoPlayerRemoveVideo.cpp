// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Native RVA 0x00689CE0, 195 bytes. Operation/control flow follow BFME1
// 10af19f44a game/GameEngine/Source/GameClient/VideoPlayerRemoveVideo.cpp.
// Target table VA 0x00BC7EBC slot 16 follows addVideo and shares getVideo's
// 28-byte global table at VA 0x00E0ABB4. String comparison, vector erasure,
// and the destructor calls are checked against this target body.
// The typed vector-copy helper reproduces all 125 bytes of the already-held
// bfmeCopyVIA body at 0x00689450, including its three string assignments.
// Field names and the VideoPlayer operation name retain donor provenance.
// The canonical AsciiString wrapper calls out of line; retail inlines the
// null/length/text comparison, using the same view as the verified addVideo.

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

// ?compareVideoNamesForRemoval@@YAHABVAsciiString@@0@Z absent-from-retail
__forceinline int compareVideoNamesForRemoval(const AsciiString &self, const AsciiString &other)
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
// Video::~Video and the held element destructor share the verified ABI.
#pragma comment(linker, "/alternatename:??1Video@@QAE@XZ=??1Rva001D28F0Element@@QAE@XZ")

#include "../../Include/GameClient/VideoPlayerClass.h"

void VideoPlayer::removeVideo(Video *video)
{
    _STL::vector<Video> &videoTable = *(_STL::vector<Video> *)&g_videoTable;
    for (_STL::vector<Video>::iterator it = videoTable.begin();
         it != videoTable.end(); ++it)
    {
        if (compareVideoNamesForRemoval(it->m_internalName, video->m_internalName) == 0)
        {
            videoTable.erase(it);
            return;
        }
    }
}
