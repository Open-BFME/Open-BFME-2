// ?loadDirectory@INI@@QAE_NVAsciiString@@_NW4INILoadType@@PAVXfer@@H@Z
// Native2E63B..2E850 includes the shared throw block after RET20.
// The matched find44B implementation is a byte-identical select-any copy;
// keeping its definition visible supplies MSVC call-result information and
// reproduces four TEST EAX,EAX sites that a declaration alone changes to CMP.
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /O1 /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
//
// BFME1 9cbfb551 GeneralsMD INI.cpp supplies the two-pass load algorithm.
// Native2E63B..2E850 establishes the byte result, filter and complete extent.
// The main return ends2E846; the following shared throw block is part of
// this compiled body and matches through2E850. The adjacent parser begins2E850.

#include "ascii_string.h"
#include <set>

template<> inline void StringBase<char>::concat(char c) { concat(&c, 1); }

// ?StringBase<char>::find present-unmatched
template<> __declspec(noinline) inline const char*StringBase<char>::find(char c)const{
 const char*p=m_data?&m_data->data[0]:""; const char*end=p+(m_data?m_data->length:0);
 while(p!=end){if(*p==c)return p;++p;}return 0;
}
class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID,
	INI_LOAD_OVERWRITE,
	INI_LOAD_CREATE_OVERRIDES,
	INI_LOAD_MULTIFILE
};

class INI
{
public:
	unsigned char loadFile(AsciiString filename, INILoadType loadType, Xfer *pXfer);
	bool loadDirectory(AsciiString dirName, bool subdirs, INILoadType loadType,
		Xfer *pXfer, int fileFilter);

	void rva0002C0F5(AsciiString &filename);

protected:
	bool prepFile(const AsciiString &filename, INILoadType loadType);
	void unPrepFile();
	void readLine();

private:
	void *m_file;                    // +0x000
	AsciiString m_filename;          // +0x004
	char m_pad08[0x14 - 0x08];
	char m_buffer[0x418 - 0x14];     // +0x014
	const char *m_seps;              // +0x418
	char m_pad41c[0x430 - 0x41c];
	bool m_endOfFile;                // +0x430
	char m_curBlockStart[0x404];     // +0x431
	char m_pad835[0x87C - 0x835];
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int m_argCount;
	INIException(const INIException &that);
	~INIException();
};

extern void setFPMode();
extern void *g_00DDF57C; // s_xfer, provider INI_readLine.cpp

// Donor: GeneralsMD Code/GameEngine/Source/Common/INI/INI.cpp at BFME1
// revision 6583b3c1. Its loadDirectory has the same two-pass sorted INI load:
// root files first, then nested paths. Retail evidence supports this identity:
// the INI load subsystem calls this body at 0x0002E63B, with the same dirName,
// subdirs, INILoadType and Xfer arguments used by the donor. BFME2's target
// returns whether any loadFile succeeded and checks its fifth, opaque argument
// only for nested paths; the target's call at 0x0002E7D3 passes the current
// AsciiString and that argument to the address-derived list predicate below.
// The donor appends a trailing backslash unconditionally; BFME2 first uses the
// matched endsWith worker at 0x0002BEC1. The filter's element meaning is
// unresolved; its list walk and string-prefix compare are supported by the
// 0x0002C5E6 disassembly and matched startsWithNoCase at 0x0002C42F.
struct BfmeStringNoCaseLess
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};

typedef std::set<AsciiString, BfmeStringNoCaseLess> FilenameList;

class FileSystem
{
public:
// The donor API is FileSystem::getFileListInDirectory. The third argument
// is passed by address at retail. BFME1's FilenameList uses
// rts::less_than_nocase; BFME2's call to the set constructor at 0x000D3A71 and
// cleanup through the rowed no-case tree dtor at 0x0002CC38 support this local
// BFME2 FilenameList comparator view.
	void getFileListInDirectory(const AsciiString &directory,
		const AsciiString &searchName, FilenameList &filenameList, bool searchSubdirectories) const;
};

extern FileSystem *TheFileSystem;

// Address-derived target helper. Retail's caller passes the current list item
// and the opaque argument on the stack; the 59-byte callee walks +0/+4 as a
// four-byte element range, compares each element through 0x0002C42F, and
// returns whether it found a match. Its original name and filter semantics are
// not established.
struct Rva0002C5E6Range { const StringBase<char>*first,*last; };
extern bool __cdecl Rva0002C5E6(const StringBase<char>&candidate,const Rva0002C5E6Range*filter);

bool INI::loadDirectory(AsciiString dirName, bool subdirs, INILoadType loadType,
	Xfer *pXfer, int fileFilter)
{
	if (dirName.isEmpty())
		throw INIException(0, 0);

	bool didLoad = false;
	try
	{
		FilenameList filenameList;
		if (!dirName.endsWith("\\"))
			dirName.concat('\\');
		TheFileSystem->getFileListInDirectory(dirName, AsciiString("*.ini"),
			filenameList, true);

		AsciiString tempname;
		FilenameList::const_iterator it = filenameList.begin();
		while (it != filenameList.end())
		{
			tempname = (*it).str() + dirName.getLength();
			if (!tempname.find('\\') && !tempname.find('/'))
			{
				if (loadFile(*it, loadType, pXfer))
					didLoad = true;
			}
			++it;
		}

		if (subdirs)
		{
			it = filenameList.begin();
			while (it != filenameList.end())
			{
				tempname = (*it).str() + dirName.getLength();
				if (tempname.find('\\') || tempname.find('/'))
				{
					if (!Rva0002C5E6(*(const StringBase<char>*)&*it,(const Rva0002C5E6Range*)fileFilter)
						&& loadFile(*it, loadType, pXfer))
						didLoad = true;
				}
				++it;
			}
		}
	}
	catch (...)
	{
		throw;
	}

	return didLoad;
}
