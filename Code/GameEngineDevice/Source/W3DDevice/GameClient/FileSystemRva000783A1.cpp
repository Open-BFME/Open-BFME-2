// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// ?rva000783A1@FileSystem@@QAEPAVFile@@PBDHHH@Z, retail 0x000783A1, 36 bytes.
// FileSystem 4-arg openFile wrapper in W3DFileSystem.cpp gap (prev 0x78393
// W3D dtor next 0x783C5 GameFileClass dtor same // cl:). Packs trailing
// two ints into 8-byte local and passes its address as unk int to rowed
// 3-arg openFile 0x600C34 (File::READ|BINARY 0x41 path via caller 0x7882F
// TheFileSystem in ecx passthrough). Caller 0x7882F plus 0x2895B4 etc prove
// FileSystem class via TheFileSystem global at 0xA06A48.

class File;

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unk);
	File *rva000783A1(const char *filename, int access, int a, int b);
};

struct TwoInts
{
	int a;
	int b;
};

File *FileSystem::rva000783A1(const char *filename, int access, int a, int b)
{
	TwoInts tmp;
	tmp.a = a;
	tmp.b = b;
	return openFile(filename, access, (int)&tmp);
}
