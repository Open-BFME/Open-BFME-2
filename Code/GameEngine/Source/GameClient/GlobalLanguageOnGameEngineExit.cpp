// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?onGameEngineExit@GlobalLanguage@@QAEXXZ retail 0x001EA77F 473 bytes.
// GlobalLanguage local-font and temp-dir cleanup: counts m_localFonts at
// +0x138 via size then LoadLibraryA GDI32 plus GetProcAddress
// RemoveFontResourceExA to unhook each non-empty second string at node+0xC
// then assigns TheEmptyString at 0x009E0878 then clear via rowed 0x001EA529
// then GetTempPathA plus format plus FindFirstFileA lrf pattern plus
// DeleteFileA plus RemoveDirectoryA. BFME1 donor is
// GlobalLanguage_onGameEngineExit.cpp verbatim for imports and loop shape.
// BFME2 repairs retail-measured: list at +0x138 (not +0x134) of
// Rva001EA443 two-string records (not BfmeFontEntry) so clear resolves via
// rowed Rva clear; empty assignment via AsciiString operator= pin 0x000366F0
// (not clear); format via rowed const-char 0x00038150; font dir global at
// 0x009B8F94; isEmpty via rowed StringBase bool 0x00001E2F. Identity: same
// class as rowed adjustFontSize dtor and deleting dtor plus vtable Language
// string plus caller at 0x0022D7E8.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


typedef int Bool;
typedef unsigned long DWORD;
typedef void *HANDLE;
typedef void *HMODULE;
typedef const char *LPCSTR;
typedef char *LPSTR;

#define NULL 0
#define MAX_PATH 260
#define INVALID_HANDLE_VALUE ((HANDLE)-1)

extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR);
extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(HMODULE, LPCSTR);
extern "C" __declspec(dllimport) Bool __stdcall FreeLibrary(HMODULE);
extern "C" __declspec(dllimport) DWORD __stdcall GetTempPathA(DWORD, LPSTR);
extern "C" __declspec(dllimport) HANDLE __stdcall FindFirstFileA(LPCSTR, void *);
extern "C" __declspec(dllimport) Bool __stdcall FindNextFileA(HANDLE, void *);
extern "C" __declspec(dllimport) Bool __stdcall FindClose(HANDLE);
extern "C" __declspec(dllimport) Bool __stdcall DeleteFileA(LPCSTR);
extern "C" __declspec(dllimport) Bool __stdcall RemoveDirectoryA(LPCSTR);

#include "ascii_string.h"
extern const char *BfmeFontExtractionDirectory;

struct BfmeStringView
{
	char *m_data;
};


struct Rva001EA443
{
	AsciiString m_text0;
	AsciiString m_text1;
	Rva001EA443();
	Rva001EA443(const Rva001EA443 &);
	~Rva001EA443();
};

inline bool operator==(const Rva001EA443 &x, const Rva001EA443 &y) { return false; }
inline bool operator<(const Rva001EA443 &x, const Rva001EA443 &y) { return false; }

struct BfmeFindData
{
	unsigned char header[44];
	char fileName[MAX_PATH];
	char alternateFileName[14];
	unsigned short padding;
};

class GlobalLanguage
{
public:
	void onGameEngineExit();
private:
	typedef _STL::list<Rva001EA443, _STL::allocator<Rva001EA443> > StringList;
	typedef StringList::iterator StringListIt;
	unsigned char m_unmodelled00[0x138];
	StringList m_localFonts;
};

void GlobalLanguage::onGameEngineExit()
{
	if (m_localFonts.size()) {
		HMODULE library = LoadLibraryA("GDI32.DLL");
		if (library) {
			typedef Bool(__stdcall *RemoveFontResourceExProc)(LPCSTR, DWORD, void *);
			RemoveFontResourceExProc removeFontResourceEx = (RemoveFontResourceExProc)GetProcAddress(library, "RemoveFontResourceExA");
			if (removeFontResourceEx) {
				for (StringListIt it = m_localFonts.begin(); it != m_localFonts.end(); ++it) {
					AsciiString &val = (*it).m_text1;
					if (!val.isEmpty()) {
						removeFontResourceEx(val.str(), 0x30, NULL);
						val = AsciiString::TheEmptyString;
					}
				}
			}
			FreeLibrary(library);
		}
		m_localFonts.clear();
	}
	char tempPath[MAX_PATH];
	if (GetTempPathA(MAX_PATH, tempPath)) {
		AsciiString fontDirectory;
		fontDirectory.format("%s\\%s", tempPath, BfmeFontExtractionDirectory);
		AsciiString searchPath;
		searchPath.format("%s\\lrf*.*", fontDirectory.str());
		BfmeFindData findData;
		HANDLE findHandle = FindFirstFileA(searchPath.str(), &findData);
		while (findHandle != INVALID_HANDLE_VALUE) {
			AsciiString fontPath;
			fontPath.format("%s\\%s", fontDirectory.str(), findData.fileName);
			DeleteFileA(fontPath.str());
			if (!FindNextFileA(findHandle, &findData)) {
				FindClose(findHandle);
				findHandle = INVALID_HANDLE_VALUE;
			}
		}
		RemoveDirectoryA(fontDirectory.str());
	}
}
