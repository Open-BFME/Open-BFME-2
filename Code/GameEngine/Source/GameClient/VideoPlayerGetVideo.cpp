// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Retail 0x00689B10 (338B). VideoPlayer::getVideo linear scan over the
// 28-byte Video table: copy/compare each internal name case-insensitively.
// Transferred from the BFME1 reconstruction (VideoPlayerQueries.cpp); only
// getVideo is claimed here. AsciiString carries no user copy/dtor so both
// implicit members emit the shared StringBase base calls retail makes
// (ctor 0x365F0, teardown 0x36410, both via public-spelling pins); trim
// resolves to 0x37CF0.

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *, const void *, unsigned int);

#include "../../Include/GameClient/BfmeVideoRecord.h"
#include "../../Include/GameClient/BfmeVideoTable.h"



#define g_bfmeVideoTableBegin ((Video *)g_bfmeVideoTableStorage.begin)
#define g_bfmeVideoTableEnd ((Video *)g_bfmeVideoTableStorage.end)

// Read-only view of the canonical StringBase allocation header: refcount+0,
// length+4, capacity+6, text+8. The Video name comparison inlines these reads.
struct VideoNameBufferView
{
    int m_refCount;
    unsigned short m_length;
    unsigned short m_capacity;
    char m_text[1];
};

struct VideoStringStorageView
{
    VideoNameBufferView *m_data;
};

// ?compareVideoNames@@YAHABVAsciiString@@0@Z absent-from-retail
inline int compareVideoNames(const AsciiString &left, const AsciiString &right)
{
    const VideoStringStorageView *self = (const VideoStringStorageView *)&left;
    const VideoStringStorageView *that = (const VideoStringStorageView *)&right;
    int thatLength = that->m_data ? that->m_data->m_length : 0;
    const char *thatText = that->m_data ? that->m_data->m_text : "";
    int selfLength = self->m_data ? self->m_data->m_length : 0;
    const char *selfText = self->m_data ? self->m_data->m_text : "";
    int count = selfLength < thatLength ? selfLength : thatLength;
    int result = _memicmp(selfText, thatText, count);
    if (result != 0)
        return result;
    return selfLength - thatLength;
}

class VideoPlayer
{
public:
	virtual const Video *getVideo(AsciiString movieTitle);
};

// ?getVideo@VideoPlayer@@UAEPBUVideo@@VAsciiString@@@Z
const Video *VideoPlayer::getVideo(AsciiString movieTitle)
{
	AsciiString title(movieTitle);
	((StringBase<char> *)&title)->trim();

	Video *it = g_bfmeVideoTableBegin;
	for (; it != g_bfmeVideoTableEnd; ++it)
	{
		AsciiString name(it->m_internalName);
		((StringBase<char> *)&name)->trim();
		if (compareVideoNames(name, title) == 0)
			return it;
	}
	return 0;
}

// One definition for all readers and the mutable native vector view.
BfmeVideoTableStorage g_bfmeVideoTableStorage = { 0, 0, 0 };
