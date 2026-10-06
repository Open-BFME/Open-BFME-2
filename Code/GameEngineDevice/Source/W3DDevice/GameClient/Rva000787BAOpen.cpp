// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// ?Rva000787BAOpen@@YAPAVFile@@PBD@Z, retail 0x000787BA, 117 bytes.
// Free File opener via GameFileClass 0x214 plus rowed 3-arg openFile with
// 0x41/0. Zero in ebx for all null compares plus unk push plus exists byte
// plus return across dtor (saves 4 vs imm plus esi). Globals TheW3D at
// 0x9E1FAC and TheFileSystem at 0xA06A48. Callers at 0x1312A3 etc.

class File;

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unk);
};

class W3DFileSystem
{
};

extern W3DFileSystem *TheW3DFileSystem;
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

File *__cdecl Rva000787BAOpen(const char *filename)
{
	int zero = 0;
	if ((int)TheW3DFileSystem == zero)
		return 0;
	if ((int)TheFileSystem == zero)
		return 0;
	GameFileClass obj(filename);
	if (obj.m_fileExists == (bool)zero)
		return 0;
	return TheFileSystem->openFile(obj.m_filePath, 0x41, zero);
}
