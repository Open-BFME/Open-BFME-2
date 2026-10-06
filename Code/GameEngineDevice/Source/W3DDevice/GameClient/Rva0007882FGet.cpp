// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// ?GetGameFilePart@@YAPAVFile@@PBDHH@Z, retail 0x0007882F, 128 bytes.
// Chain from 0x000783A1 landing: free File* opener (filename plus 2 ints)
// via GameFileClass 0x220 stack object plus rowed FileSystem 4-arg wrapper.
// Returns null unless globals at 0x9E1FAC and TheFileSystem at 0xA06A48 are
// set and GameFileClass+8 exists flag is set; filename for wrapper is
// GameFileClass+9 filePath and access is 0x41 READ|BINARY. Callers at
// 0x14D0C9 0x17FDF0 0x180166 0x1802D5 0x1808FC 0x180D87 become ready.

class File;

class FileSystem
{
public:
	File *rva000783A1(const char *filename, int access, int a, int b);
};

extern int g_009E1FAC;
// ?g_009E1FAC@@3HA: the global at this VA is ?TheW3DFileSystem@@3PAVW3DFileSystem@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_009E1FAC@@3HA=?TheW3DFileSystem@@3PAVW3DFileSystem@@A")
extern FileSystem *TheFileSystem;

class GameFileClass
{
public:
	GameFileClass(const char *filename);
	virtual ~GameFileClass();
	File *m_theFile;
	bool m_fileExists;
	char m_filePath[0x214 - 9];
};

File *GetGameFilePart(const char *filename, int a, int b)
{
	if (g_009E1FAC == 0)
		return 0;
	if (TheFileSystem == 0)
		return 0;
	GameFileClass obj(filename);
	if (!obj.m_fileExists)
		return 0;
	return TheFileSystem->rva000783A1(obj.m_filePath, 0x41, a, b);
}
