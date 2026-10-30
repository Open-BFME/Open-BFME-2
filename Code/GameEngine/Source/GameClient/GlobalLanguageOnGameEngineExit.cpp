// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// platformsdk
// stlport
// ?onGameEngineExit@GlobalLanguage@@QAEXXZ retail 0x001EA77F 473 bytes.
// GlobalLanguage local-font and temp-dir cleanup: counts localFonts at
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

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


typedef bool Bool;

#include <windows.h>
#include "ascii_string.h"
#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"
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

struct FontDesc
{
public:
	FontDesc();
	AsciiString name; // +0x00
	int size; // +0x04
	bool bold; // +0x08
	char m_pad09[0x3];
};

class GlobalLanguage : public SubsystemInterface
{
public:
	GlobalLanguage();
	virtual ~GlobalLanguage();
	virtual void init();
	int adjustFontSize(int theFontSize);
	void onGameEngineExit();
	static void parseFontDesc(class INI *ini, void *instance, void *store, const void *userData);

private:
	AsciiString m_s00C;
	AsciiString m_s010;
	AsciiString m_s014;
	AsciiString m_s018;
	AsciiString m_s01C;
	AsciiString m_language;
	bool m_useHardWrap;
	int m_militaryCaptionSpeed;
	FontDesc m_f02C;
	FontDesc m_f038;
	FontDesc m_f044;
	FontDesc m_f050;
	FontDesc m_f05C;
	FontDesc m_f068;
	FontDesc m_f074;
	FontDesc m_f080;
	FontDesc m_f08C;
	FontDesc m_f098;
	FontDesc m_f0A4;
	FontDesc m_f0B0;
	FontDesc m_f0BC;
	FontDesc m_f0C8;
	FontDesc m_f0D4;
	FontDesc m_f0E0;
	FontDesc m_f0EC;
	FontDesc m_f0F8;
	FontDesc m_f104;
	FontDesc m_f110;
	FontDesc m_f11C;
	FontDesc m_f128;
	float m_res134;
	_STL::list<Rva001EA443> localFonts;
};

void GlobalLanguage::onGameEngineExit()
{
	if (localFonts.size()) {
		HMODULE library = LoadLibraryA("GDI32.DLL");
		if (library) {
			typedef BOOL(__stdcall *RemoveFontResourceExProc)(LPCSTR, DWORD, void *);
			RemoveFontResourceExProc removeFontResourceEx = (RemoveFontResourceExProc)GetProcAddress(library, "RemoveFontResourceExA");
			if (removeFontResourceEx) {
				for (_STL::list<Rva001EA443>::iterator it = localFonts.begin(); it != localFonts.end(); ++it) {
					AsciiString &val = (*it).m_text1;
					if (!val.isEmpty()) {
						removeFontResourceEx(val.str(), 0x30, NULL);
						val = AsciiString::TheEmptyString;
					}
				}
			}
			FreeLibrary(library);
		}
		localFonts.clear();
	}
	char tempPath[MAX_PATH];
	if (GetTempPathA(MAX_PATH, tempPath)) {
		AsciiString fontDirectory;
		fontDirectory.format("%s\\%s", tempPath, BfmeFontExtractionDirectory);
		AsciiString searchPath;
		searchPath.format("%s\\lrf*.*", fontDirectory.str());
		WIN32_FIND_DATAA findData;
		HANDLE findHandle = FindFirstFileA(searchPath.str(), &findData);
		while (findHandle != INVALID_HANDLE_VALUE) {
			AsciiString fontPath;
			fontPath.format("%s\\%s", fontDirectory.str(), findData.cFileName);
			DeleteFileA(fontPath.str());
			if (!FindNextFileA(findHandle, &findData)) {
				FindClose(findHandle);
				findHandle = INVALID_HANDLE_VALUE;
			}
		}
		RemoveDirectoryA(fontDirectory.str());
	}
}
