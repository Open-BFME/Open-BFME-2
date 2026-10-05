// cl: /Os /DNDEBUG /MD
// ?parseWindow@GameWindowTransitionsHandler@@SAXPAVINI@@PAX1PBX@Z, retail 0x001DCB2F, 53 bytes.
// Static INI field callback for the Window entry of the outer table at RVA 0x7DBBCC (VA 0xBDBBCC).
// Target evidence: outer slot Window->VA 0x5DCB2F (retail rdata decode at 0x7DBBCC: Window->0x5DCB2F,
// FireOnce->parseBool 0x42E850 off 16, terminator), caller parseWindowTransitions 0x1DC66F (rowed 112B,
// INIWindowTransition TU), 53B span 0x1DCB2F..0x1DCB64, ret 0 (cdecl, caller cleans).
// Sub-table is the typed 3-entry provider defined below as function-local myFieldParse
// (retail RVA 0x7DBDB0, VA 0xBDBDB0; ZH GeneralsMD parseWindow local-static pattern):
//   WinName    -> INI::parseAsciiString (rowed 0x2F11E, 60B)               off 0 (AsciiString at +0)
//   Transition -> INI::Rva001DCAED_ParseTransition (rowed 0x1DCAED, 66B)    off 0 (dispatch, ignores offset)
//   FrameDelay -> INI::parseInt (rowed 0x2EF56, 28B)                      off 4 (int at +4)
//   terminator {0,0,0,0}.
// Retail decode via build.read_target_bytes at 0x7DBDB0: entry0 tokVA 0xBDBDA4="WinName"
// parseVA 0x42F11E ud 0 off 0; entry1 tokVA 0xBDAE54="Transition" parseVA 0x5DCAED ud 0 off 0;
// entry2 tokVA 0xBDBD98="FrameDelay" parseVA 0x42EF56 ud 0 off 4; entry3 all zero.
// userData all zero, offsets match the 0x18 TransitionWindow (AsciiString +0, int +4;
// proven by GroupTotalFrames 0x1DC1FD 85B matched + Rva00489BC0 22B zero-fill ctor rowed 0x1DBC61 + ZH header).
// Reference via myFieldParse emits push-DIR32 (masked, copied from retail's 68 B0 BD BD 00),
// still byte-exact; table contents are data (not text-verified) with string bytes equal to retail rdata.
// Donors (shape only): ZH GeneralsMD GameWindowTransitions.cpp parseWindow (NEW+initFromINI+addWindow,
// local static table; BFME2 replaces Style-lookup with Transition dispatch) and BFME1 6583b3c1
// game/GameEngine/Source/GameClient/GUI/GameWindowTransitions_parseWindow.cpp (same shape, // cl /DNDEBUG /MD).
// Layout: TransitionWindow 0x18 (AsciiString m_winName + int m_frameDelay + NameKeyType m_winID
// + GameWindow* m_win + Transition* m_transition + int m_currentFrameDelay), zero-fill constructible;
// its zeroing ctor is the rowed ??0Rva00489BC0 at 0x1DBC61 (22B out-of-order dword zeros, no subcalls).
// Providers independently established: new 0x2FDA0 (??2@YAPAXI@Z mem_ops.cpp, matched),
// ctor 0x1DBC61 (??0Rva00489BC0 R3ScalarFieldConstructors1.cpp, matched BFME1 donor),
// initFromINI 0x2DE78 (?initFromINI@INI@@QAEXPAXPBUFieldParse@@@Z INI_initFromINI.cpp, matched),
// addWindow 0x1DC19F (rowed 20B ?addWindow@TransitionGroup, r6 land), table parsers all rowed (see above).
// No new class view: reuses HandlerGroups/GroupTotalFrames 0x18 TransitionWindow and TransitionGroup views;
// AsciiString canonical untouched (no private copy; offsets hardcoded per ControlBar g_0080D720 precedent).
// TU-scoped shims only, no shared-header edits. Single-local esi, nothrow ctor to avoid EH/ebp frame.
void *__cdecl operator new(unsigned int size) throw();

typedef void (*INIFieldParseProc)(class INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void Rva001DCAED_ParseTransition(INI *ini, void *instance, void *store, const void *userData);
};

class Rva00489BC0
{
public:
	Rva00489BC0() throw();
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
};

class TransitionWindow;

class TransitionGroup
{
public:
	void addWindow(TransitionWindow *window);
};

class GameWindowTransitionsHandler
{
public:
	static void parseWindow(INI *ini, void *instance, void *store, const void *userData);
};

// ?parseWindow@GameWindowTransitionsHandler@@SAXPAVINI@@PAX1PBX@Z
void GameWindowTransitionsHandler::parseWindow(INI *ini, void *instance, void *store, const void *userData)
{
	static const FieldParse myFieldParse[] = {
		{ "WinName", &INI::parseAsciiString, 0, 0 },
		{ "Transition", &INI::Rva001DCAED_ParseTransition, 0, 0 },
		{ "FrameDelay", &INI::parseInt, 0, 4 },
		{ 0, 0, 0, 0 }
	};
	TransitionWindow *transWin = (TransitionWindow *)new Rva00489BC0;
	ini->initFromINI(transWin, myFieldParse);
	((TransitionGroup *)instance)->addWindow(transWin);
}
