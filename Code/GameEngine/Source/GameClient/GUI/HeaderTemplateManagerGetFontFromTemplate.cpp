#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
// stlport
// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Bodies ported from Open-BFME-1's GameEngine/Source/GameClient/GUI/HeaderTemp
// lateManagerGetFontFromTemplate.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// HeaderTemplateManager::getFontFromTemplate 0x00201A84 (78B). Callee
// addresses are read off retail's call sites (reverse/symbols.csv). Only the
// placed bodies are carried; the donor's other definitions are omitted.
//
// ?getFontFromTemplate@HeaderTemplateManager@@QAEPAVGameFont@@VAsciiString@@@Z
//
// The retail manager keeps a circular list at this+0x00.  Each list node
// links at +0x00 and stores its HeaderTemplate at +0x08; the template keeps
// its GameFont pointer at +0x00 and its inline AsciiString name at +0x04.
// The typed lookup at BFME2 0x00201A33 compares canonical AsciiString names
// and returns the matching template; its list and template layouts are shared.

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "HeaderTemplateView.h"

class GameFont;

GameFont *HeaderTemplateManager::getFontFromTemplate( AsciiString name )
{
	HeaderTemplate *header = findHeaderTemplate( name );
	if (!header)
		return 0;
	return header->m_font;
}
