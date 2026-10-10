// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ?load@WindowLayoutInfo@@QAE_NVAsciiString@@@Z, retail 0x0031742C, 159 bytes
// (native 0x0031742C..0x003174CB, WorldBuilder 0x013A7380). Dedicated TU, so
// the AptPlayer::WinCreate reference (0x00223263, unrowed) cannot hold the
// linked parseLayoutBlock unit out of the link.
//
// Semantic donor: Open-BFME-1 WindowLayoutInfoLoad.cpp (BFME 1 retail
// 0x00487870): an empty name fails; a ".apt" extension goes to the Apt
// player, anything else to the window manager's script loader; on success
// the name is kept in the info.
// BFME 2 facts (retail-measured):
// - the extension is found with the out-of-line StringBase<char>::find(char);
//   the compare is the msvcr71 _strcmpi import against ".apt";
// - the Apt branch calls AptPlayer::WinCreate (0x00223263, pinned) on the
//   global at 0x009FE4CC with a pointer to the name and this info;
// - the script branch is GameWindowManager vtable slot 31 (+0x7C) with
//   (filename by value, this, NULL) and RET 12 in the callee;
// - the filename lives at +0x24, after the 0x24-byte callback/name prefix the
//   parseInit/Update/Shutdown/LayoutClass rows measure.

#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class GameWindow;
class WindowLayoutInfo;

// Observed layout view of the info handed to AptPlayer::WinCreate.
struct AptLayoutInfoView;

class AptPlayer
{
public:
	GameWindow *WinCreate(const AsciiString *filename, AptLayoutInfoView *info);
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class GameWindowManager
{
public:
#define SLOT(n) virtual void slot##n();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09)
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
#undef SLOT
	virtual GameWindow *winCreateFromScript(AsciiString filename, WindowLayoutInfo *info, void *parent);	// slot 31
};
extern GameWindowManager *TheWindowManager;

class WindowLayoutInfo
{
public:
	bool load(AsciiString filename);

	unsigned int m_version;			// +0x00
	void *m_init;					// +0x04
	void *m_update;					// +0x08
	void *m_shutdown;				// +0x0C
	void *m_classCallback;			// +0x10
	AsciiString m_initName;			// +0x14
	AsciiString m_updateName;		// +0x18
	AsciiString m_shutdownName;		// +0x1C
	AsciiString m_className;		// +0x20
	AsciiString m_filename;			// +0x24
	void *m_windowList;				// +0x28 list<GameWindow *> node (44-byte info, ctor 0x0031763A)
};

bool WindowLayoutInfo::load(AsciiString filename)
{
	if (filename.isEmpty())
		return false;

	const char *extension = reinterpret_cast<const StringBase<char> *>(&filename)->find('.');
	GameWindow *result;
	if (extension && _strcmpi(extension, ".apt") == 0)
		result = reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->WinCreate(
			&filename, reinterpret_cast<AptLayoutInfoView *>(this));
	else
		result = TheWindowManager->winCreateFromScript(filename, this, 0);

	if (!result)
		return false;

	m_filename = filename;
	return true;
}
