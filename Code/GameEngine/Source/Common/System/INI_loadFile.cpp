// ?prepFile@INI@@IAE_NABVAsciiString@@W4INILoadType@@@Z
// cl: /O1 /arch:SSE /G7 /Ireference/shims/iniexception /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?prepFile@INI@@IAE_NABVAsciiString@@W4INILoadType@@@Z @0x0002D2C1, 936B.
//
// W7-ASTRA recovery: native 0x0002D2C1..0x0002D669 RET8, 936 bytes.
// WB 0x6D0530 INI::prepFile preserves the character scan as a guarded loop.
// Putting *p in the for condition (rather than an infinite loop + break)
// reproduces the shared exception tail at the duplicate-name path and all
// late-error block ordering. The helper receives File*, the record loop ends
// on the first non-define, and the macro counter stores saved-start+1.
// The insertion record is {node,table,flag} (12B), corroborated by its rowed
// provider. Canonical INIException is 8B. The local insertion adapter keeps
// target pair-copy, insertion, pair destruction and factory destruction order.
// Integrated beside the existing 195B loadFile caller, whose access-level
// declarations and layout remain the verified target forms.
//
// Name/signature are carried from the clean BFME1 INI.cpp prepFile donor;
// this target body is substantially different. Target evidence: all three
// matched INI load entries pass (&filename, loadType) and branch on AL; the
// body opens/records the file, runs the +0x838 helper, closes the file,
// scans the helper's 12-byte records, and handles #define rows through the
// global macro table. The table's constructor at 0x2DC3C initializes a
// hash_map at +0 and set at +0x14; target calls 0x2CD2F with ECX=0xDDF58C and
// 0x2CB98 with that same base. Its target class name remains structural.
// The helper record/name views follow 0x6018B6, 0x5D5847 and the independent
// readLine consumer; the macro value is the pair's second StringBase at node
// +8, confirmed by target compare/assignment calls 0x69D6/0x366F0.
// GeneralsMD Common/INI/INI.cpp prepFile supplies only the open/save-file
// semantic lead. Target-specific timestamp gating, macro parsing, error
// messages, and duplicate replacement follow retail bytes and strings.

#include "ascii_string.h"

// Keep the vector member declaration out of the implementation header. The
// target calls its separately emitted size body at 0x5D5847.
namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	unsigned int size() const;
	T *m_start;
	T *m_finish;
	T *m_end;
};

template <class First, class Second> struct pair
{
	First first;
	Second second;
	pair(const pair &that);
	~pair();
};
}

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE,
	INI_LOAD_UNK4,
	INI_LOAD_UNK5
};

#include "../../../Include/Common/File.h"

#include "../../../Include/Common/FileSystem.h"

extern FileSystem *TheFileSystem;
// Native 2DC3C constructs the 20-byte macro hash and 12-byte file set.
// The adjacent generation words are separately owned by the timestamp updater.
// These descriptive identifiers record proven roles; original names are unknown.
// Retail builds both objects in the INI unit's .text$yc run: 0x007ABBB3 runs the rowed
// constructor 0x0002DC3C on the macro table and registers 0x007B6A6E (the destructor
// 0x0002CD7B), then 0x007ABBC9 calls the out-of-line AsciiString() 0x00326BE6 on the
// current file name and registers 0x007B6A5A. INI.cpp's view spells the same struct.
struct INIMacroTable
{
	INIMacroTable();
	~INIMacroTable();
	unsigned m_storage[8];
};
INIMacroTable BfmeINIMacroTableStorage;
#pragma inline_depth( 0 )
AsciiString BfmeINICurrentFilename;
#pragma inline_depth()
extern int BfmeINIMacroGeneration;
extern int BfmeINISavedMacroGeneration;

typedef unsigned short WORD;

#include "../../../Include/Common/SaveDate.h"
extern SaveDate BfmeINIReadTimestamp;

// <windows.h>'s SYSTEMTIME (isFileNewer.cpp).
struct _SYSTEMTIME;
bool isFileNewer(const AsciiString &filename, const _SYSTEMTIME *date);

class Rva0002CB98
{
	unsigned char m_pad[0x14];
public:
	bool rva0002CB98(const AsciiString &filename) const;
};

struct Out0002CA72
{
	void *first;
	void *iteratorOwner;
	unsigned char second;
	unsigned char pad[3];
};
struct Pair0002CA72;
class Rva0002CD2F
{
	char m_pad[16];
	unsigned int m_count;
public:
	Out0002CA72 *rva0002CD2F(Out0002CA72 *out, const Pair0002CA72 *value);
};

struct BfmeE12
{
	float x;
	float y;
	float z;
};

struct INIFileRecord
{
	unsigned int fileId;
	int line;
	int nameIndex;
};
struct INIFileRecordTable
{
	INIFileRecord *begin;
	INIFileRecord *end;
	unsigned int reserved;
	AsciiString *names;
};
class INIFileTable
{
public:
	int getFileId(int index) const;
private:
	unsigned int reserved;
	INIFileRecordTable records;
};

class Rva00601BBCHelper
{
public:
	virtual ~Rva00601BBCHelper();
	bool rva00602072(void *outer);
private:
	char m_04[0x18];
	_STL::vector<int> m_1C;
	_STL::vector<int> m_28;
};

class Xfer;
class INI
{
public:
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);
	void parseLine(AsciiString &filename);
	protected:
	void unPrepFile();
	void readLine();
	bool prepFile(const AsciiString &filename, INILoadType loadType);

	private:
	File *m_file;
	AsciiString m_filename;
	INILoadType m_loadType;
	int m_0C;
	int m_10;
	char m_buffer[0x418 - 0x14];
	const char *m_seps;
	char m_pad41C[0x430 - 0x41C];
	bool m_endOfFile;
	char m_pad431[0x838 - 0x431];
	Rva00601BBCHelper m_helper;
	char m_tail86C[0x87C - 0x86C];
};

#include "Common/INIException.h"

typedef _STL::pair<const AsciiString, AsciiString> MacroPair;
typedef char InsertResultSizeCheck[sizeof(Out0002CA72) == 12 ? 1 : -1];
typedef char ExceptionSizeCheck[sizeof(INIException) == 8 ? 1 : -1];
typedef char MacroPairSizeCheck[sizeof(MacroPair) == 8 ? 1 : -1];

// The lifted return record is two StringBase-sized words. Its mangling is
// retained as BfmePairEL; the pair base supplies the target-proven copy/dtor
// behavior at 0x2C574/0x2C0C0 without assigning that donor spelling to data.
class BfmeWordEL
{
	void *m_stringStorage;
};
struct BfmePairEL;
BfmePairEL __cdecl bfmeMakePairEL(const BfmeWordEL &first, const BfmeWordEL &second);

static __forceinline void insertMacroPair(Out0002CA72 *inserted, const MacroPair &factoryPair)
{
	MacroPair pair(factoryPair);
	((Rva0002CD2F *)&BfmeINIMacroTableStorage)->rva0002CD2F(inserted, (const Pair0002CA72 *)&pair);
}

// ?prepFile@INI@@IAE_NABVAsciiString@@W4INILoadType@@@Z
bool INI::prepFile(const AsciiString &filename, INILoadType loadType)
{
	if (m_file != 0)
	{
		throw INIException(6,
			"INI::load, cannot open file '%s', file already open\n", filename.str());
	}

	if (loadType == INI_LOAD_UNK5)
	{
		if (BfmeINISavedMacroGeneration == BfmeINIMacroGeneration)
		{
			if (!isFileNewer(filename, (const _SYSTEMTIME *)&BfmeINIReadTimestamp))
				return false;
		}
		else if (((Rva0002CB98 *)&BfmeINIMacroTableStorage)->rva0002CB98(filename) == false)
		{
			return false;
		}
	}

	m_file = TheFileSystem->openFile(filename.str(), 1, 0);
	*(AsciiString *)&BfmeINICurrentFilename = filename;
	if (m_file == 0)
	{
		throw INIException(7, "INI::load, cannot open file '%s'\n", filename.str());
	}

	m_helper.rva00602072(m_file);
	m_file->close();
	m_file = 0;

	int macroCount = BfmeINIMacroGeneration;
	_STL::vector<BfmeE12> *records = (_STL::vector<BfmeE12> *)((char *)&m_helper + 4);
	INIFileTable *fileTable = (INIFileTable *)&m_helper;
	for (int index = 0; index < (int)records->size(); ++index)
	{
		char *rawLine = (char *)fileTable->getFileId(index);
		AsciiString line(rawLine);
		if (line.startsWith("#define"))
		{
			*rawLine = 0;
			AsciiString value;
			line.nextToken(&value, 0);
			AsciiString name;
			line.nextToken(&name, 0);

			if (filename.endsWith("map.ini"))
			{
				throw INIException(8,
					"%s:\nMACROs not allowed in map.ini.\n%s.", filename.str(), name.str());
			}

			for (const char *p = name.str(); *p; ++p)
			{
				char ch = *p;
				if (ch > 'a' && ch < 'z')
				{
					throw INIException(8,
						"%s:\nMACRO names must use UPPERCASE letters.\n%s.", filename.str(), name.str());
				}
			}

			line.nextToken(&value, 0);
			AsciiString part;
			while (line.nextToken(&part, 0))
			{
				value += " ";
				value += part;
			}
			if (value.isEmpty())
			{
				throw INIException(8,
					"%s:\nError parsing MACRO.\n%s has no value", filename.str(), name.str());
			}

			Out0002CA72 inserted;
			typedef MacroPair (__cdecl *MakeMacroPair)(const BfmeWordEL &, const BfmeWordEL &);
			MakeMacroPair makePair=reinterpret_cast<MakeMacroPair>(&bfmeMakePairEL);
			insertMacroPair(&inserted, makePair(
				(const BfmeWordEL &)name, (const BfmeWordEL &)value));


			bool duplicate = inserted.second == 0;
			if (loadType != INI_LOAD_UNK5)
			{
				if (duplicate)
				{
					throw INIException(8,
						"%s:\nDuplicate MACRO names.\n%s.", filename.str(), name.str());
				}
			}
			else if (duplicate)
			{
				AsciiString *existingValue = (AsciiString *)((char *)inserted.first + 8);
				if (existingValue->compare(value) != 0)
				{
					*existingValue = value;
					BfmeINIMacroGeneration = macroCount + 1;
				}
			}
		}
		else
			break;
	}

	m_filename = filename;
	m_loadType = loadType;
	return true;
}

extern void setFPMode();
extern void *g_00DDF57C;
unsigned char INI::loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer)
{
	setFPMode();
	g_00DDF57C = pXfer;
	if (!prepFile(filename, loadType))
		return 0;

	try
	{
		while (m_endOfFile == false)
		{
			readLine();
			parseLine(filename);
		}
	}
	catch (INIException &iNIException)
	{
		throw INIException(iNIException.m_argCount, iNIException.mFailureMessage);
	}
	catch (...)
	{
		unPrepFile();
		throw;
	}

	unPrepFile();
	return 1;
}
