// cl: /Ireference/shims/bfmealloc_alloconly /Ireference/shims/iniexception /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB
// NON-RETAIL shim for the allocator family (P78), a labelled step and not a recovered form. This unit's kept STL copies
// allocate from the game's table, so they must free there too, and /D_CRTIMP= would also rebind the imports its rows
// need. While the STL headers parse, free names a local inline to that table; those copies call it directly where
// retail's call _free. Retired when the real allocator headers give this unit retail's _free binding, or when these
// copies are no longer kept from this unit (P75). If anything odd happens under the STL headers, look here first.
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
extern "C" void (__cdecl *__gameMemFreePtr)(void *, int);
inline void bfmeGameFree(void *block) { __gameMemFreePtr(block, 3); }
#define free bfmeGameFree
// stlport
// ?addSubtitle@SubtitleManager@@QAEXABVAsciiString@@IHHHHH@Z, retail 0x00688AA0 (105B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/SubtitleManagerAccessors.cpp
// (BFME1 0x0081DDD0). Creates the entry through the manager's factory hook and
// pushes it on the entry vector. The donor defines 7 further siblings the sweep
// did not place, so only the placed body is defined here; the rest stay
// declared-only.

#include <stdlib.h>
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

#include "ascii_string.h"
// Preserve the visible null initialization without a competing wide-base copy.
template <> __declspec(dllimport) __forceinline
StringBase<unsigned short>::StringBase() : m_data(0) {}
// The empty Unicode wrapper has the native six-byte size profile.
#pragma optimize("s", on)
#include "unicode_string.h"
#pragma optimize("", on)
template<> inline bool StringBase<unsigned short>::isEmpty() const throw() { return m_data == 0 || m_data->length == 0; }
// Keep __node_alloc<true,0>::allocate inline-only: every call here is inlined,
// and this TU's COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void * _STLP_CALL __node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}


union SubtitleEntryBulk
{
	int words[10];
	struct
	{
		unsigned int color;
		char middle[0x14];
		bool displayed;
		char rest[0x0B];
	} fields;
};

class SubtitleEntry
{
public:
	SubtitleEntry(const SubtitleEntry &that);
	AsciiString getText() const;
	SubtitleEntry &operator=(const SubtitleEntry &that)
	{
		m_text = that.m_text;
		m_label = that.m_label;
		m_bulk = that.m_bulk;
		m_tailFirst = that.m_tailFirst;
		m_tailSecond = that.m_tailSecond;
		return *this;
	}

	AsciiString m_text;
	AsciiString m_label;
	SubtitleEntryBulk m_bulk;
	int m_tailFirst;
	int m_tailSecond;
};

typedef SubtitleEntry *(__cdecl *CreateSubtitleEntry)(AsciiString *, int,
	const AsciiString &, unsigned int, int, int, int, int, int);

class INI;
class SubtitleManager
{
 friend void parseSubtitleText(INI*,void*,void*,const void*);
public:
	SubtitleManager(CreateSubtitleEntry createEntry, int second, const AsciiString &name);
	void addSubtitle(const AsciiString &label, unsigned int color, int style,
		int alignment, int line, int startFrame, int endFrame);
	bool hasBeenDisplayed(int index) const;
	AsciiString getText(int index) const;
	void setDisplayedStats(int index);
	unsigned int getColor(int index) const;
	int getStartFrame(int index) const;
private:
	CreateSubtitleEntry m_createEntry;
	int m_second;
	AsciiString m_name;
	AsciiString m_secondaryName;
	int m_count;
	_STL::vector<SubtitleEntry *> m_entries;
	int m_startFrame;
	int m_state[15];
	bool m_enabled;
};

void SubtitleManager::addSubtitle(const AsciiString &label, unsigned int color,
	int style, int alignment, int line, int startFrame, int endFrame)
{
	SubtitleEntry *entry = m_createEntry(&m_secondaryName, m_count, label, color,
		style, alignment, line, startFrame, endFrame);
	m_entries.push_back(entry);
}

// ??0SubtitleManager@@QAE@P6APAVSubtitleEntry@@PAVAsciiString@@HABV2@IHHHHH@ZH1@Z
// retail 0x00688750 (107B). Placed by masked whole-.text search of the compiled
// donor body (single hit on unclaimed ground).
SubtitleManager::SubtitleManager(CreateSubtitleEntry createEntry, int second,
	const AsciiString &name) :
	m_createEntry(createEntry),
	m_second(second),
	m_name(name),
	m_secondaryName(),
	m_count(0),
	m_entries(),
	m_enabled(false)
{
	m_startFrame = 0x7FFFFFFF;
	// Keep the sentinel visible before the remaining state is cleared, as retail does.
	_ReadWriteBarrier();
	m_state[0] = 0;
	m_state[1] = 0;
	m_state[2] = 0;
	m_state[3] = 0;
	m_state[4] = 0;
	m_state[5] = 0;
	m_state[6] = 0;
	m_state[7] = 0;
	m_state[8] = 0;
	m_state[9] = 0;
	m_state[10] = 0;
	m_state[11] = 0;
	m_state[12] = 0;
	m_state[13] = 0;
	m_state[14] = 0;
}

typedef int Int;
typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

#include "../../Include/Common/INI/INI.h"
// Preserve the retail inlined accessors in this TU.
inline const char *INI::getSeps() const { return m_seps; }
inline const char *INI::getSepsColon() const { return m_sepsColon; }

class VideoPlayerInterface
{
public:
	virtual ~VideoPlayerInterface();
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
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void *getVideo(const AsciiString &title) = 0;
};

extern VideoPlayerInterface *TheVideoPlayer;

#include "Common/INIException.h"
#undef free


static const char *const subtitleStyles[] = {
	"TRANSPARENT", "TRANSPARENT_FADE", "OUTLINED", "OUTLINED_FADE",
	"SOLID", "SOLID_FADE", 0
};

static const char *const subtitleAlignments[] = {
	"CENTER", "LEFT", "RIGHT", 0
};

// ?parseSubtitleText@@YAXPAVINI@@PAX1PBX@Z, retail 0x00688B10 (1578B). INI field
// parser for one subtitle entry (Label/Color/Style/Align/Line/StartFrame/EndFrame),
// adding it to the video's SubtitleManager. Semantic lead: Open-BFME-1
// Rva0081DE40ParseSubTitleEntry.cpp. The separator reads go through INI's inline
// getters as in the donor; raw member reads rotate the scratch registers.
void parseSubtitleText( INI *ini, void *, void *store, const void * )
{
	void *target = store;
	SubtitleManager *manager = (SubtitleManager *)TheVideoPlayer->getVideo( ini->getFilename() );
	if ( manager != 0 && target != 0 )
	{
	UnicodeString text;
	unsigned int color = 0;
	int style = 0x7fffffff;
	int align = 0x7fffffff;
	int line = 0x7fffffff;
	int startFrame = 0x7fffffff;
	int endFrame = 0x7fffffff;
	for ( const char *token = ini->getNextTokenOrNull( ini->getSepsColon() ); token != 0;
		token = ini->getNextTokenOrNull( ini->getSepsColon() ) )
	{
		if ( _strcmpi( token, "Label" ) == 0 && text.isEmpty() )
		{
			const char *label = ini->getNextTokenOrNull( ini->getSeps() );
			if ( label == 0 || !text.isEmpty() || !((Bool (__cdecl *)(const char *,UnicodeString *))manager->m_second)(label, &text) )
			{
				throw INIException( 8, "Invalid text label while parsing %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else if ( _strcmpi( token, "Color" ) == 0 && color == 0 )
		{
			const char *names[ 3 ] = { "R", "G", "B" };
			for ( int i = 0; i < 3; ++i )
			{
				int value = ini->scanInt( ini->getNextSubToken( names[ i ] ) );
				if ( value < 0 || value > 255 )
				{
					throw INIException( 3, "color value %s=%i out of range (0..255) in %s on line %d",
						names[ i ], value, ini->getFilename(), ini->getLineNum() );
				}
				color = ( color << 8 ) | value;
			}
			color |= 0xff000000;
		}
		else if ( _strcmpi( token, "Style" ) == 0 && style == 0x7fffffff )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value == 0 )
			{
				throw INIException( 8, "Expected subtitle style type not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
			style = ini->scanIndexList( value, subtitleStyles );
		}
		else if ( _strcmpi( token, "Align" ) == 0 && align == 0x7fffffff )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value == 0 )
			{
				throw INIException( 8, "Expected subtitle alignment type not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
			align = ini->scanIndexList( value, subtitleAlignments );
		}
		else if ( _strcmpi( token, "Line" ) == 0 && line == 0x7fffffff )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value != 0 )
			{
				line = ini->scanInt( value ) - 1;
				if ( line < 0 || line >= 15 )
				{
					throw INIException( 3, "Subtitle Line value %d out of range (%d..%d) in %s on line %d",
						line, 1, 15, ini->getFilename(), ini->getLineNum() );
				}
			}
			else
			{
				throw INIException( 8, "Expected subtitle line value for Line: not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else if ( _strcmpi( token, "StartFrame" ) == 0 && startFrame == 0x7fffffff )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value != 0 )
			{
				startFrame = ini->scanInt( value );
				if ( startFrame < 0 )
				{
					throw INIException( 3, "Subtitle StartFrame must be greater than 0 in %s on line %d",
						ini->getFilename(), ini->getLineNum() );
				}
			}
			else
			{
				throw INIException( 8, "Expected subtitle StartFrame value for StartFrame: not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else if ( _strcmpi( token, "EndFrame" ) == 0 && endFrame == 0x7fffffff )
		{
			const char *value = ini->getNextTokenOrNull( ini->getSepsColon() );
			if ( value != 0 )
			{
				endFrame = ini->scanInt( value );
				if ( endFrame < 0 )
				{
					throw INIException( 3, "Subtitle EndFrame must be greater than 0 in %s on line %d",
						ini->getFilename(), ini->getLineNum() );
				}
			}
			else
			{
				throw INIException( 8, "Expected subtitle EndFrame value for EndFrame: not found in %s on line %d",
					ini->getFilename(), ini->getLineNum() );
			}
		}
		else
		{
			throw INIException( 3, "bad colon spacing, or unexpected token in TransitionDamageFXModuleData::NeighborIDSubobjectNameDataAppend" );
		}
	}
	// The ledger types addSubtitle's first argument as AsciiString; retail
	// passes this UnicodeString.
	manager->addSubtitle( *(const AsciiString *)&text, color, style, align, line, startFrame, endFrame );
	}
	else
	{
		throw INIException( 9, "Could not locate SubTitleManager for %s", ini->getFilename() );
	}
}
