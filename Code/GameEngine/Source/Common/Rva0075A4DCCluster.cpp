// cl: /O1 /arch:SSE2 /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?parseVideoDefinition@INI@@SAXPAV1@@Z @0x0075A4DC (179B). INI field-parse
// callback for a Video definition. Donor identity is the original GeneralsMD
// INIVideo.cpp INI::parseVideoDefinition (static member, INI* only) plus the
// BFME1 default-video inheritance the open-bfme-1 donor reconstruction
// carries: read the token, default-construct a Video, copy the
// TheVideoPlayer->getVideo(AsciiString("DefaultVideoData")) record into it,
// clear its IsDefault flag, set the internal name from the token, parse the
// remaining fields through getFieldParse() and register it with addVideo().
// The Video layout, default ctor and three-string-plus-POD assignment match
// Video.h (volume 1.0f at +0x10, IsDefault at +0x14). Retail uses the
// one-argument StringBase<char>::set at 0x000055F5, not the (text,len)
// overload the donor reconstruction spelled. /O1 because the body opens with
// the __EH_prolog helper at 0x00629188.

#include "ascii_string.h"

// class-gate: allow Video retail calls the out-of-line operator= at 0x00689380; the shared BfmeVideoRecord.h view forceinlines it, so this TU needs the proved codegen view

struct FieldParse;

#include "../../Include/Common/INI/INI.h"

class Video
{
public:
	AsciiString m_filename;
	AsciiString m_internalName;
	AsciiString m_commentForWB;
	unsigned char m_hasSubtitles;
	float m_volume;
	unsigned char m_isDefault;
	void *m_subtitleManager;

	Video()
		: m_hasSubtitles(0), m_volume(1.0f), m_isDefault(0), m_subtitleManager(0)
	{
	}

	~Video();
	Video &operator=(const Video &other);
};

// The BFME2 VideoPlayerInterface vtable places addVideo at +0x50, the
// AsciiString getVideo at +0x60 and getFieldParse at +0x64. Only the ordinals
// matter to codegen; the slots between carry no target evidence here.
class VideoPlayerInterface
{
public:
	virtual ~VideoPlayerInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void addVideo(Video *video) = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual const Video *getVideo(AsciiString title) = 0;
	virtual const FieldParse *getFieldParse() const = 0;
};

extern VideoPlayerInterface *TheVideoPlayer;

// ?parseVideoDefinition@INI@@SAXPAV1@@Z
void INI::parseVideoDefinition(INI *ini)
{
	const char *c = ini->getNextToken();

	Video video;
	const Video *defaultVideo =
		TheVideoPlayer->getVideo(AsciiString("DefaultVideoData"));
	if (defaultVideo != 0)
	{
		video = *defaultVideo;
		video.m_isDefault = 0;
	}
	((StringBase<char> *)&video.m_internalName)->set(c);

	ini->initFromINI(&video, TheVideoPlayer->getFieldParse());
	TheVideoPlayer->addVideo(&video);
}
