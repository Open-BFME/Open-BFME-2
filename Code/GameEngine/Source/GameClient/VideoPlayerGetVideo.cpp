// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /DNDEBUG /MD /EHsc /O2 /Ob2
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
    virtual SubtitleManager *getSubTitleMgrForVideo(const AsciiString &title);
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

// Restore the banked BFME1 subtitle query after repairing the unrelated
// Snapshot vtable gate blocker. Donor: Open-BFME-1 34f59164f6,
// game/GameEngine/Source/GameClient/VideoPlayerQueries.cpp.
// Native 6897B0..6898C8 is 280 bytes; manager+8 is its string name.
class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(void *first, void *second, void *third);
};

class Debug;
extern Debug *theDebug;
#define TheBfmeAwakenDebug (reinterpret_cast<BfmeAwakenDebug*>(theDebug))


extern void _bfme_debugRecordCallsite(int kind);


// Exact native diagnostic at VACE499C names this method.
// parseSubtitle6885B0 uses the primary VideoPlayer interface slot+6C; the
// callback-table view startingBC7EBC lists this address at its own slot22.
// Those are different origins within the interface table, not interchangeable
// slot numbers. Return record+18 is the same manager initialized by6898D0.
// ?getSubTitleMgrForVideo@VideoPlayer@@UAEPAVSubtitleManager@@ABVAsciiString@@@Z
SubtitleManager *VideoPlayer::getSubTitleMgrForVideo(const AsciiString &title)
{
	unsigned int index = 0;
	if ((unsigned int)(g_bfmeVideoTableEnd - g_bfmeVideoTableBegin) != 0)
	{
		unsigned int offset = 0;
		do
		{
			Video *record = (Video *)((char *)g_bfmeVideoTableBegin + offset);
			SubtitleManager *manager = record->m_subtitleManager;
			if (manager != 0 && compareVideoNames(title, *(AsciiString *)((char *)manager + 8)) == 0)
				return record->m_subtitleManager;
			++index;
			offset += sizeof(Video);
		} while (index < (unsigned int)(g_bfmeVideoTableEnd - g_bfmeVideoTableBegin));
	}

	_bfme_debugRecordCallsite(1);
	TheBfmeAwakenDebug->slot60();
	BfmeAwakenLog *report = TheBfmeAwakenDebug->slot6C(0, 0, 0);
	report->slot38("VideoPlayer::getSubTitleMgrForVideo should not FAIL!")->slot4C(1);
	return 0;
}
