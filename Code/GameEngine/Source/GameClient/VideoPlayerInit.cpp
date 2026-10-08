// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O2 /Ob2
// Clean donor: Open-BFME-1 34f59164f6d1efd413c5fd37f4894ec834c3c0fe
// game/GameEngine/Source/Common/BfmeMoviePathAB.cpp and GameClient/VideoPlayerInit.cpp.
// Native 689580..6895F2 formats Data/%s/Movies/ from a cdecl callback at +C.
// The purpose and accessed offsets follow retail; the original helper name
// is unknown. BFME1 supplies the path-building semantics. BFME2's callback
// is +C rather than +8 and the formatter takes a const char* format directly.
#include <new.h>
#include "../../Include/GameClient/BfmeVideoRecord.h"
#include "../../Include/GameClient/BfmeVideoTable.h"
class SubtitleEntry;
typedef SubtitleEntry *(__cdecl *CreateSubtitleEntry)(AsciiString *, int,
 const AsciiString &, unsigned int, int, int, int, int, int);
class VideoPlayer
{
public:
 virtual void init();
 void rva00689580(AsciiString &out);
 char m_unknown04[8];
 AsciiString (__cdecl *m_movieName)();
 int m_second;
 CreateSubtitleEntry m_createSubtitleEntry;
};
void VideoPlayer::rva00689580(AsciiString &out)
{
 if(m_movieName != 0)
  out.format("Data/%s/Movies/", m_movieName().str());
}

// Native 6898D0..689B0E is 574B, including the final stack release/RET.
// The old inventory's 567B extent ended inside that epilogue.
// Clean BF1 VideoPlayerInit.cpp supplies the initialization semantics.
// Retail independently establishes INI width87C (locals+20/+89C),
// receiver fields+10/+14, the28B Video stride and native callbacks75A4DC/
// 6885B0. The initialized byte is read before callee saves and set once at
// the end; its original source name and the +10 field label remain unknown.
class Xfer;
enum INILoadType { INI_LOAD_INVALID=0, INI_LOAD_OVERWRITE=1 };
class INI
{
public:
 INI();
 ~INI();
 void load(AsciiString,INILoadType,Xfer*,void (__cdecl *)(INI*));
 static void parseVideoDefinition(INI*);
private:
 char storage[0x87c];
};
extern void parseSubtitle(INI*,void*,void*,const void*);
class SubtitleManager
{
public:
 SubtitleManager(CreateSubtitleEntry,int,const AsciiString&);
private:
 char storage[0x64];
};
// Only the shared string allocation header is viewed here; the canonical
// AsciiString owns construction and teardown through the verified workers.
struct BfmeStringHeader
{
 int m_refCount;
 unsigned short m_length,m_capacity;
 char m_text[1];
};
struct BfmeStringObject { BfmeStringHeader *m_data; };
#define g_bfmeVideoTableBegin ((Video*)g_bfmeVideoTableStorage.begin)
#define g_bfmeVideoTableEnd ((Video*)g_bfmeVideoTableStorage.end)
static unsigned char s_videoPlayerInitialised;

void VideoPlayer::init(void)
{
	if (s_videoPlayerInitialised == 0)
	{
		INI ini;
		ini.load(AsciiString("Data\\INI\\Default\\Video.ini"),
			INI_LOAD_OVERWRITE, 0, INI::parseVideoDefinition);
		ini.load(AsciiString("Data\\INI\\Video.ini"),
			INI_LOAD_OVERWRITE, 0, INI::parseVideoDefinition);

		for (unsigned int index = 0;
			index < (unsigned int)(g_bfmeVideoTableEnd - g_bfmeVideoTableBegin);
			index++)
		{
			Video *video = g_bfmeVideoTableBegin + index;
			if (video->m_hasSubtitles)
			{
				if (m_createSubtitleEntry != 0 && m_second != 0)
				{
					AsciiString path;
					rva00689580(path);

					const BfmeStringObject *name =
						(const BfmeStringObject *)&video->m_internalName;
					int length = name->m_data ? name->m_data->m_length : 0;
					const char *text = name->m_data
						? name->m_data->m_text : "";
					((StringBase<char> *)&path)->concat(text, length);
					((StringBase<char> *)&path)->concat(".ini", 4);

					video->m_subtitleManager =
						new SubtitleManager(m_createSubtitleEntry, m_second, path);

					{
						INI subtitleIni;
						subtitleIni.load(path, INI_LOAD_OVERWRITE, 0,
							(void (__cdecl *)(INI *))parseSubtitle);
					}
				}
			}
		}

		s_videoPlayerInitialised = 1;
	}
}
