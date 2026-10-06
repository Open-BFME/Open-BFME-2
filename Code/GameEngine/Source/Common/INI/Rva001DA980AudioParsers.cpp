// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// Five INI audio-block parse helpers: each builds a Default-name
// AsciiString temporary and hands it, with a kind index and the event
// name, to the shared cdecl parser at 0x001DA770 (pinned from each
// body's own REL32). StringBase ctor/dtor resolve through the existing
// 0x00037BA0/0x00036410 pins; the literals byte-match their VAs.
// 0x001DA980: DefaultMusicTrack/MusicTrack kind 0.
// 0x001DA9CA: DefaultSoundEffect/AudioEvent kind 2.
// 0x001DAA14: DefaultDialog/DialogEvent kind 1.
// 0x001DAA5E: DefaultAmbientStream/AmbientStream kind 3.
// 0x001DAAA8: DefaultStreamedSound/StreamedSound kind 4.

#include "ascii_string.h"

class INI;

void __cdecl helper001DA770(INI *ini, int kind, AsciiString *def, const char *name);

// ?Rva001DA980Parse@@YAXPAVINI@@@Z
void __cdecl Rva001DA980Parse(INI *ini)
{
	AsciiString def("DefaultMusicTrack");
	helper001DA770(ini, 0, &def, "MusicTrack");
}

// ?Rva001DA9CAParse@@YAXPAVINI@@@Z
void __cdecl Rva001DA9CAParse(INI *ini)
{
	AsciiString def("DefaultSoundEffect");
	helper001DA770(ini, 2, &def, "AudioEvent");
}

// ?Rva001DAA14Parse@@YAXPAVINI@@@Z
void __cdecl Rva001DAA14Parse(INI *ini)
{
	AsciiString def("DefaultDialog");
	helper001DA770(ini, 1, &def, "DialogEvent");
}

// ?Rva001DAA5EParse@@YAXPAVINI@@@Z
void __cdecl Rva001DAA5EParse(INI *ini)
{
	AsciiString def("DefaultAmbientStream");
	helper001DA770(ini, 3, &def, "AmbientStream");
}

// ?Rva001DAAA8Parse@@YAXPAVINI@@@Z
void __cdecl Rva001DAAA8Parse(INI *ini)
{
	AsciiString def("DefaultStreamedSound");
	helper001DA770(ini, 4, &def, "StreamedSound");
}
