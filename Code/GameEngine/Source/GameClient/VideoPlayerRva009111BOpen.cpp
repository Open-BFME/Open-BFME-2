// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?open@Rva009111B@@UAEPAVVideoStreamInterface@@VAsciiString@@H@Z retail
// 0x0009151D..0x00091763 (582 bytes): slot 17 of the VP6 video player's
// vftable 0x007C7EA8 (the class the ledger names Rva009111B; slots 18-24 are
// VideoPlayer's firstStream closeAllStreams addVideo removeVideo
// getNumVideos and the two getVideo overloads, as in Zero Hour's
// VideoPlayerInterface where open follows regainFocus).
// Unless the global-data flag +0x9AD is set it resolves the title through
// getVideo (slot 24), builds "<dir><file>.vp6" for each enabled entry of the
// three 0x145-byte search directories g_Va00DE44A8 until the file system
// finds one, then constructs the rowed 0x64-byte stream 0x000907C1 and opens
// it (stream slot 19); an opened stream is linked by 0x00689230, a failed one
// is destroyed. A missing video or file reports through the debug crash path
// (SkipNext / CrashBegin / operator<< / CrashDone(2)); the file case formats
// with the rowed Debug::Format 0x000386E0. WorldBuilder has no twin.
#include "ascii_string.h"
#include "../../Include/GameClient/BfmeVideoRecord.h"

class GlobalData
{
public:
	unsigned char m_pad000[0x9AD];
	bool m_bfme9AD; // +0x9AD
};

extern GlobalData *TheWritableGlobalData;

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

// The three video search directories (see Rva007AC13CEntryArrayInit.cpp).
struct Rva007AC13CEntry
{
	bool m_00;
	char m_path[0x104]; // +0x01
	bool m_105;
	char m_106[0x3F];
};

extern Rva007AC13CEntry g_Va00DE44A8[3];

bool bfmeRva000387C0();
void _bfme_debugRecordCallsite(int kind);

class Debug
{
public:
	class Format
	{
	public:
		explicit Format(const char *format, ...);
		char m_buffer[0x200];
	};

	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);

	Debug &operator<<(const Format &format) { operator<<(format.m_buffer); return *this; }
};

extern Debug *theDebug;

class VideoStreamInterface
{
public:
	virtual ~VideoStreamInterface();
};

class Rva007E3C20Vp6Stream : public VideoStreamInterface
{
public:
	Rva007E3C20Vp6Stream(int video, int player);
	virtual ~Rva007E3C20Vp6Stream();
	virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08();
	virtual void s09(); virtual void s10(); virtual void s11(); virtual void s12();
	virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
	virtual void s17(); virtual void s18();
	virtual bool open(const AsciiString &path, const Video *video, bool preload); // slot 19

private:
	unsigned char m_pad04[0x64 - 0x04];
};

class VideoPlayer
{
public:
	virtual ~VideoPlayer();
	virtual void s01(); virtual void s02(); virtual void s03(); virtual void s04();
	virtual void s05(); virtual void s06(); virtual void s07(); virtual void s08();
	virtual void s09(); virtual void s10(); virtual void s11(); virtual void s12();
	virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
	virtual VideoStreamInterface *open(AsciiString movieTitle, int flags) = 0; // slot 17
	virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
	virtual void s22(); virtual void s23();
	virtual const Video *getVideo(AsciiString movieTitle); // slot 24

	// 0x00689230: links a stream into the player's stream list.
	void rva00689230(VideoStreamInterface *stream);
};

class Rva009111B : public VideoPlayer
{
public:
	virtual VideoStreamInterface *open(AsciiString movieTitle, int flags);
};

VideoStreamInterface *Rva009111B::open(AsciiString movieTitle, int flags)
{
	if (TheWritableGlobalData->m_bfme9AD)
		return 0;

	const Video *pVideo = getVideo(movieTitle);
	VideoStreamInterface *stream = 0;
	if (pVideo)
	{
		AsciiString filePath;
		int i;
		for (i = 0; i < 3; ++i)
		{
			if (g_Va00DE44A8[i].m_00)
			{
				filePath.format("%s%s.%s", g_Va00DE44A8[i].m_path, pVideo->m_filename.str(), "vp6");
				if (TheFileSystem->doesFileExist(filePath.str()))
					break;
			}
		}
		if (i >= 3)
		{
			if (bfmeRva000387C0())
			{
				_bfme_debugRecordCallsite(1);
				theDebug->SkipNext();
				const char *file = pVideo->m_filename.str();
				const char *title = movieTitle.str();
				Debug &dbg = theDebug->CrashBegin(0, 0, 0);
				(dbg << Debug::Format("Could not open VP6 video file for %s - %s.", title, file)).CrashDone(2);
			}
			return 0;
		}
		Rva007E3C20Vp6Stream *vp6 = new Rva007E3C20Vp6Stream((int)pVideo, (int)this);
		bool preload = (flags | 0x40) != 0;
		if (vp6->open(filePath, pVideo, preload))
		{
			rva00689230(vp6);
			stream = vp6;
		}
		else
		{
			::delete vp6;
			stream = 0;
		}
	}
	else
	{
		if (bfmeRva000387C0())
		{
			_bfme_debugRecordCallsite(1);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "A movie named '" << movieTitle.str() << "' was requested but can't be found.\n").CrashDone(2);
		}
	}
	return stream;
}
