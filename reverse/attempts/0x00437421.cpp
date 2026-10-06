// ?Rva00437421@@YAXXZ
// partial score=0.66 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
//
// Retail 0x00437421 is called at the end of LAN lobby initialization. Its
// target evidence clears the TreeHint map, enumerates the WotR multiplayer
// save extension under the save directory, parses each file's 0xDE8-byte
// metadata subobject, and stores nonzero MD5 records under their hex digest.
// The application owner and metadata parser's semantic name remain uncertain.

// stlport
#include <map>
#include <new>
#include <set>

#include "ascii_string.h"
#include "unicode_string.h"

extern "C" void MD5Print(unsigned char digest[16], char output[33]);
extern "C" int __cdecl strcmp(const char *left, const char *right);

class GameState;
extern GameState *TheGameState;
class FileSystem;
extern FileSystem *TheFileSystem;
extern unsigned g_Va00E032EC;

class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
};

void *__stdcall Rva002DBC97Get(int id);

struct BfmeSubobject0022CE19
{
	virtual ~BfmeSubobject0022CE19();
	unsigned char m_opaque[0xDE4];
	BfmeSubobject0022CE19();
	BfmeSubobject0022CE19 &operator=(const BfmeSubobject0022CE19 &);
};

struct TreeHintOpaque0043671B
{
	UnicodeString m_text;
	BfmeSubobject0022CE19 m_subobject;
	unsigned int m_wordDEC;
	unsigned int m_wordDF0;
	TreeHintOpaque0043671B();
	TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
	TreeHintOpaque0043671B &operator=(const TreeHintOpaque0043671B &);
	~TreeHintOpaque0043671B();
};

typedef _STL::pair<const AsciiString, TreeHintOpaque0043671B> TreeHintPair0043671B;
typedef _STL::map<AsciiString, TreeHintOpaque0043671B,
	_STL::less<AsciiString>, _STL::allocator<TreeHintPair0043671B> > TreeHintMap0043671B;
typedef _STL::set<AsciiString> SetConstructorAlias00437421;
typedef _STL::set<UnicodeString,
	_STL::less<UnicodeString>, _STL::allocator<UnicodeString> > UnicodePathSet00437421;

class Rva0021C459
{
public:
	~Rva0021C459();
};

struct LocalUnicodePathSet00437421
{
	char m_storage[sizeof(SetConstructorAlias00437421)];

	__forceinline LocalUnicodePathSet00437421()
	{
		new (m_storage) SetConstructorAlias00437421;
	}
	__forceinline ~LocalUnicodePathSet00437421()
	{
		((Rva0021C459 *)m_storage)->~Rva0021C459();
	}
};

class Rva006007DA
{
public:
	void rva006007DA(const UnicodeString &directory,
		const UnicodeString &pattern, void *files, int recursive) const;
};

class Rva002DEEC3
{
public:
	bool rva002DEEC3(UnicodeString filename, BfmeSubobject0022CE19 *metadata);
};

void Rva00437421()
{
	if (TheGameState == 0)
		return;

	TreeHintMap0043671B *hints = (TreeHintMap0043671B *)&g_Va00E032EC;
	hints->clear();

	AsciiString star("*");
	UnicodeString pattern(star);
	pattern += (const unsigned short *)Rva002DBC97Get(6);

	LocalUnicodePathSet00437421 files;
	UnicodeString directory = ((Rva002DC267 *)TheGameState)->rva002DC267();
	((Rva006007DA *)TheFileSystem)->rva006007DA(directory, pattern, &files, 1);

	UnicodePathSet00437421 &wideFiles = *(UnicodePathSet00437421 *)&files;
	for (UnicodePathSet00437421::iterator it = wideFiles.begin(); it != wideFiles.end(); ++it) {
		BfmeSubobject0022CE19 metadata;
		if (!((Rva002DEEC3 *)TheGameState)->rva002DEEC3(*it, &metadata))
			continue;

		char printedDigest[33];
		MD5Print((unsigned char *)&metadata + 0xDA8, printedDigest);
		if (strcmp(printedDigest, "00000000000000000000000000000000") == 0)
			continue;

		TreeHintOpaque0043671B hint;
		hint.m_subobject = metadata;
		hint.m_text = *it;
		(*hints)[AsciiString(printedDigest)] = hint;
	}
}
