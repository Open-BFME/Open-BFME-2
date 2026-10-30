// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// platformsdk
// stlport
//
// ?rva0021F5F8@CreateAHeroManager@@QAEXXZ, retail 0x0021F5F8..0x0021F797
// (415 bytes, EH, RET 0; caller the screen destructor 0x00513BAB; WB twin
// 0x00B7F190, unnamed): reconciles the hero save files with the manager's
// heroes. For each listed file (the 0x0021F19B file list, destroyed through
// its rowed destructor 0x0021DB35) whose suffix-stripped name (0x0021C12F)
// the hero list at +0x174 does not know (0x0040A5CF), it deletes that save
// file: the save directory (0x002DC267) plus the file name, joined by the
// wide concat materializer 0x0021C3F7, passed to kernel32 DeleteFileW (IAT
// 0xBBA324). Then each hero (0x0040A32F) that is not a system hero (+0x48,
// unless the 0x009FE34C flag is set) and has a name (+0x4C) is saved under
// its file name (0x0021A651) through 0x004098BE.
//
// Codegen evidence: both containers are STLport vectors (8-byte file
// entries, CreateAHeroData pointers); with real vectors and the WB twin's
// inline hero accessors (its isSystem/getName temporaries) cl gives retail's
// this/EBX, iterator/hero EDI allocation, which the hand-written views and
// direct member reads mirrored. Owner class and method names are unknown.
#include <vector>
#include <stdlib.h>
#include <windows.h>
#include "ascii_string.h"
#include "unicode_string.h"

class GameState;
extern GameState *TheGameState;

// The game state's save directory (0x002DC267), rowed under its own spelling.
class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
};

extern unsigned char g_rva005B5C02Flag;

class CreateAHeroData;
class Rva0040A3F9
{
public:
	__forceinline ~Rva0040A3F9() { if (m_begin) free(m_begin); }
	CreateAHeroData **m_begin;
	CreateAHeroData **m_end;
	CreateAHeroData **m_capacity;
	bool m_flag;
	unsigned int size() const { return m_end - m_begin; }
	CreateAHeroData *rva0040A32F(int index);
	CreateAHeroData *rva0040A5CF(const AsciiString &name);
};

struct Rva0021F5F8Hero
{
	unsigned char m_pad00[0x48];
	bool m_system;					// +0x48
	unsigned char m_pad49[0x4c - 0x49];
	AsciiString m_name;				// +0x4C
	bool isSystem() const { return m_system; }
	const AsciiString &getName() const { return m_name; }
};
class CreateAHeroHero
{
public:
	int GetBlingCount(int blingKey) const; // 0x004079F4
	int GetBlingId(int blingKey, unsigned int index) const; // 0x00407A29
	bool rva004098BE(const AsciiString &file, bool system);
};
AsciiString Rva0021A651Filename(const AsciiString &name);
AsciiString Rva0021C12FStripName(const AsciiString &file);

struct CreateAHeroFileEntry
{
	AsciiString filename;
	bool system;
};
struct Rva0021DB35
{
    Rva0021DB35(); // native21F19B fills a vector of file-name / flag pairs
    ~Rva0021DB35();
    CreateAHeroFileEntry *m_begin;
    CreateAHeroFileEntry *m_end;
    CreateAHeroFileEntry *m_capacity;
};

class BFME2WideConcatPair
{
public:
	__forceinline BFME2WideConcatPair(const UnicodeString &left, const UnicodeString &right) { m_right = &right; m_left = &left; }
	operator UnicodeString();			// 0x0021C3F7 (pinned UnicodeString spelling)
	const UnicodeString *m_left;
	const UnicodeString *m_right;
};

class CreateAHeroData
{
public:
	CreateAHeroData(int, int, int, const UnicodeString &, int, int, int);
	virtual ~CreateAHeroData();
	bool rva00408A55();
	bool rva004099CA(AsciiString *filename, bool mode);
	char m_storage04[0x130];
	unsigned int m_crc;
	unsigned char m_pad138[8];
};

struct BfmePod216 { int a[54]; };

struct Rva0021DA18
{
	~Rva0021DA18();
	char m_storage[12];
};

struct Rva0021DA57
{
	~Rva0021DA57();
	char m_storage[12];
};

class Rva0040A530 : public Rva0040A3F9
{
public:
	Rva0040A530(bool flag);
	__declspec(noinline) ~Rva0040A530();
};

typedef bool Bool;

#include "../../../../reference/shims/subsystem_bfme2/subsystem_interface.h"

class CreateAHeroManager : public SubsystemInterface
{
public:
	// The named, independently rowed 00219C1F accessor views the same 32B class
	// record and its 216B subclass range. Keep the existing container spelling.
	class CreateAHeroClass
	{
	public:
		int GetAwardCount(unsigned int subClassIndex);
		CreateAHeroClass(const CreateAHeroClass &);
		~CreateAHeroClass();
		AsciiString m_strings[5];
		_STL::vector<BfmePod216> m_subclasses;
	};

	virtual ~CreateAHeroManager();
	virtual void init();
	virtual Bool loadIniFilesFromLegend();
	virtual void reset();
	virtual void update();
	CreateAHeroClass *rva0022020C(CreateAHeroClass &entry);
	void LoadMyHeroList();
	void rva0021F5F8();
private:
	CreateAHeroData m_hero0C;
	_STL::vector<CreateAHeroClass> m_vector14C;
	int m_158;
	Rva0021DA18 m_vector15C;
	Rva0021DA57 m_vector168;
	Rva0040A530 m_tree174;
	char m_pad180[4]; // +184; the pointer-vector view includes its +180 flag.
	AsciiString m_text188, m_text18C, m_text190;
	char m_pad194[0x30];
	AsciiString m_text1C4, m_text1C8, m_text1CC;
	int m_1D0;
	unsigned int m_maxAwards1D4;
	bool m_1D8;
	unsigned char m_pad1D9[3];
	AsciiString m_text1DC;
	int m_state1E0;
	int m_1E4;
	AsciiString m_text1E8, m_text1EC;
	unsigned int m_systemHeroCRC;
};

void CreateAHeroManager::rva0021F5F8()
{
	Rva0021DB35 files;
	for (_STL::vector<CreateAHeroFileEntry>::iterator it = files.m_begin; it != files.m_end; ++it)
	{
		AsciiString name = Rva0021C12FStripName(it->filename);
		if (!m_tree174.rva0040A5CF(name))
		{
			UnicodeString path = BFME2WideConcatPair(((const Rva002DC267 *)TheGameState)->rva002DC267(),
				UnicodeString(it->filename));
			DeleteFileW(path.str());
		}
	}
	unsigned int count = m_tree174.size();
	for (unsigned int i = 0; i < count; ++i)
	{
		Rva0021F5F8Hero *hero = (Rva0021F5F8Hero *)m_tree174.rva0040A32F(i);
		if (hero && (!hero->isSystem() || g_rva005B5C02Flag) && !hero->getName().isEmpty())
		{
			AsciiString file = Rva0021A651Filename(hero->getName());
			((CreateAHeroHero *)hero)->rva004098BE(file, hero->isSystem() || g_rva005B5C02Flag);
		}
	}
}
