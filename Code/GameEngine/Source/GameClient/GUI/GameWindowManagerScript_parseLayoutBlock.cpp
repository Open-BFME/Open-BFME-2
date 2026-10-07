// cl: /Ireference/shims/sweep /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_namekey /Ireference/shims/functionlexicon_bfme2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/functionlexicon /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// ?parseLayoutBlock@@YA_NPAVFile@@PADIPAVWindowLayoutInfo@@@Z, retail
// 0x0031732D, 255 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseLayoutBlock): read the opening STARTLAYOUTBLOCK string, then walk
// LAYOUTINIT/UPDATE/SHUTDOWN/CLASS entries from layoutScriptTable until
// ENDLAYOUTBLOCK, dispatching each through the table's parse pointer.
// BFME2 facts (all retail-measured):
// - File's own vtable has scanString at slot 9 (offset 0x24); the sweep shim's
//   MemoryPoolObject adds one virtual ahead of File's, so this TU carries a
//   TU-local 17-slot File view copied from RAMFileRead.cpp.
// - strtok rides the msvcr71 import at 0xBBA5EC (dllimport decl -> the 6-byte
//   ff 15 indirect call).
// - strcpy is a plain extern decl (5-byte E8 to the 0x629176 slot).
// - AsciiString::compare is the out-of-line StringBase<char>::compare(const
//   char *) row at 0x000069B1; releaseBuffer is the row at 0x00036410.
// - __EH_prolog is pinned at 0x00629188.
// - readUntilSemicolon is the file-static at 0x00314DE8 (defined here verbatim
//   so MSVC keeps its register convention; its 90-byte body is also rowed).
// - layoutScriptTable lives at 0x00DBE318 (DIR32, masked by the byte gate).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE true
#endif

#ifndef FALSE
#define FALSE false
#endif

class WindowLayoutInfo;
class File;

enum
{
	WIN_BUFFER_LENGTH = 2048
};

struct LayoutScriptParse
{
	char *name;
	Bool (*parse)(char *token, char *buffer, UnsignedInt version, WindowLayoutInfo *info);
};

// Native table at RVA 0x009BE318: four named callbacks and a null entry.
extern LayoutScriptParse layoutScriptTable[];

class File
{
public:
	enum seekMode { START, CURRENT, END };

	virtual ~File();								// slot 0
	virtual bool open(const char *filename, int access = 0);	// slot 1
	virtual void close(void);						// slot 2
	virtual int read(void *buffer, int bytes);			// slot 3
	virtual int write(const void *buffer, int bytes);		// slot 4
	virtual int seek(int pos, seekMode mode);			// slot 5
	virtual void nextLine(char *buf, int bufSize);			// slot 6
	virtual bool scanInt(int &newInt);				// slot 7
	virtual bool scanReal(float &newReal);				// slot 8
	virtual bool scanString(void *newString);			// slot 9
	virtual bool print(const char *format, ...);			// slot 10
	virtual int size(void);						// slot 11
	virtual int position(void);					// slot 12
	virtual char *readEntireAndClose(void);				// slot 13
	virtual File *convertToRAMFile(void);				// slot 14
	virtual void lock(void);					// slot 15
	virtual void unlock(void);					// slot 16
};

#include "ascii_string.h"
#include "PreRTS.h"
#include "Common/FunctionLexicon.h"


extern "C" __declspec(dllimport) int __cdecl isspace(int c);
extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
extern "C" __declspec(dllimport) char *__cdecl strtok(char *str, const char *delimiters);

// readUntilSemicolon =========================================================
static void readUntilSemicolon(File *fp, char *buffer, int maxBufLen)
{
	int i = 0;
	Bool start = TRUE;

	while (i < maxBufLen)
	{
		// get next character
		fp->read(buffer + i, 1);

		// make all whitespace characters spaces
		if (isspace(buffer[i]))
		{
			if (start == FALSE)
				buffer[i++] = ' ';
		}
		else
		{
			start = FALSE;

			if (buffer[i] == ';')
			{
				// found end of data chunk
				buffer[i] = '\000';
				return;
			}

			i++;
		}
	}

	buffer[maxBufLen - 1] = '\000';
}

// ?parseLayoutBlock@@YA_NPAVFile@@PADIPAVWindowLayoutInfo@@@Z
Bool parseLayoutBlock(File *inFile, char *buffer, UnsignedInt version, WindowLayoutInfo *info)
{
	LayoutScriptParse *parse;
	char token[256];

	AsciiString asciitoken;
	if (inFile->scanString(&asciitoken) == FALSE)
	{
		return FALSE;
	}

	// better be the layout block
	if (asciitoken.compare("STARTLAYOUTBLOCK") != 0)
	{
		return FALSE;
	}

	while (TRUE)
	{
		// get next token
		inFile->scanString(&asciitoken);

		// check for end
		if (asciitoken.compare("ENDLAYOUTBLOCK") == 0)
		{
			break;
		}

		// search for token in the table
		for (parse = layoutScriptTable; parse && parse->name; parse++)
		{
			if (asciitoken.compare(parse->name) == 0)
			{
				char *c;

				// read from file
				readUntilSemicolon(inFile, buffer, WIN_BUFFER_LENGTH);

				// eat equals separator " = "
				c = strtok(buffer, " =");

				_mbscpy(token, asciitoken.str());

				// parse it
				if (parse->parse(token, c, version, info) == FALSE)
					return FALSE;

				break;	// exit for
			}
		}
	}

	return TRUE;
}

static const void *s_parseLayoutBlockAnchor = (const void *)parseLayoutBlock;

// Donor parseInit/Update/Shutdown: Open-BFME-1 968ca36c32,
// game/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp.
// Retail's four 68-byte callbacks prove the observed info prefix: function
// pointers +4/+8/+C/+10 and AsciiString names +14/+18/+1C/+20. The fourth
// LAYOUTCLASS callback uses lexicon table 11; its function signature is unknown.
struct BfmeLayoutInfoPrefix
{
    unsigned int unknown00;
    WindowLayoutInitFunc init;
    WindowLayoutUpdateFunc update;
    WindowLayoutShutdownFunc shutdown;
    void *classCallback;
    AsciiString initName;
    AsciiString updateName;
    AsciiString shutdownName;
    AsciiString className;
};
class Rva00DFF024Registry;
extern Rva00DFF024Registry *TheRva00DFF024Registry;

Bool parseInit(char *, char *buffer, UnsignedInt, WindowLayoutInfo *info)
{
    BfmeLayoutInfoPrefix *layout = reinterpret_cast<BfmeLayoutInfoPrefix *>(info);
    layout->initName = strtok(buffer, " \n\r\t");
    layout->init = reinterpret_cast<FunctionLexicon *>(TheRva00DFF024Registry)->winLayoutInitFunc(
        TheNameKeyGenerator->nameToKey(layout->initName));
    return TRUE;
}
Bool parseUpdate(char *, char *buffer, UnsignedInt, WindowLayoutInfo *info)
{
    BfmeLayoutInfoPrefix *layout = reinterpret_cast<BfmeLayoutInfoPrefix *>(info);
    layout->updateName = strtok(buffer, " \n\r\t");
    layout->update = reinterpret_cast<FunctionLexicon *>(TheRva00DFF024Registry)->winLayoutUpdateFunc(
        TheNameKeyGenerator->nameToKey(layout->updateName));
    return TRUE;
}
Bool parseShutdown(char *, char *buffer, UnsignedInt, WindowLayoutInfo *info)
{
    BfmeLayoutInfoPrefix *layout = reinterpret_cast<BfmeLayoutInfoPrefix *>(info);
    layout->shutdownName = strtok(buffer, " \n\r\t");
    layout->shutdown = reinterpret_cast<FunctionLexicon *>(TheRva00DFF024Registry)->winLayoutShutdownFunc(
        TheNameKeyGenerator->nameToKey(layout->shutdownName));
    return TRUE;
}
Bool parseLayoutClassRva003172E9(char *, char *buffer, UnsignedInt, WindowLayoutInfo *info)
{
    BfmeLayoutInfoPrefix *layout = reinterpret_cast<BfmeLayoutInfoPrefix *>(info);
    layout->className = strtok(buffer, " \n\r\t");
    // The shared inline getter only forwards to findFunction. Explicit slot
    // 11 preserves this lookup while the returned callback's type is unknown.
    layout->classCallback = reinterpret_cast<void *>(
        reinterpret_cast<FunctionLexicon *>(TheRva00DFF024Registry)->winLayoutShutdownFunc(
            TheNameKeyGenerator->nameToKey(layout->className), FunctionLexicon::TABLE_BFME_UNIDENTIFIED_11));
    return TRUE;
}

LayoutScriptParse layoutScriptTable[] = {
    {"LAYOUTINIT", parseInit},
    {"LAYOUTUPDATE", parseUpdate},
    {"LAYOUTSHUTDOWN", parseShutdown},
    {"LAYOUTCLASS", parseLayoutClassRva003172E9},
    {NULL, NULL}
};
