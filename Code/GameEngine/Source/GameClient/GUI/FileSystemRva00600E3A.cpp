// cl: /Oy- /MD
// ?getFileInfo@FileSystem@@QBE_NPBDPAUFileInfo@@@Z @0x00600E3A 289B: FileSystem::getFileInfo(const char *, FileInfo *) via gate archive lang English local. Evidence: callers 0x00077BF8 (the AsciiString overload, forwarding ECX), 0x002E5D62 and 0x002E698B load TheFileSystem into ECX; the second argument is zeroed as 16 bytes, the size of ZH's FileInfo; callees rowed pinned; vtable offsets 0x28 0x10.
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *fmt, ...);

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

struct FileInfo;

class FileSystem
{
public:
	bool getFileInfo(const char *filename, FileInfo *fileInfo) const;
};

class FilePathGate
{
public:
	bool allow(const char *filename);
};

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual void A3();
	virtual void A4();
	virtual bool doesFileExist(const char *a, FileInfo *b) const;
	virtual void A6();
	virtual void A7();
	virtual void A8();
	virtual void A9();
	virtual bool doesFileExist2(const char *a, FileInfo *b) const;
};

class Rva0060061AHelper
{
public:
	virtual ~Rva0060061AHelper();
	virtual void H1();
	virtual void H2();
	virtual void H3();
	virtual bool doesFileExist(const char *a, FileInfo *b) const;
};

extern FilePathGate *TheFilePathGate;
extern bool BFME2PreferLocalFiles;
extern ArchiveFileSystem *TheArchiveFileSystem;
extern char TheLangDir[];
extern Rva0060061AHelper *G00A06E54;
char g_00DD509C[188] = "English";

bool FileSystem::getFileInfo(const char *a, FileInfo *b) const
{
	char buf[0x104];

	if (b == 0)
		return false;
	if (TheFilePathGate) {
		if (!TheFilePathGate->allow(a))
			return false;
	}
	ji_006291ae((void *)b, 0, 0x10);
	if (!BFME2PreferLocalFiles)
		goto try_local;
	if (TheArchiveFileSystem == 0)
		goto try_local;
	{
		int (__cdecl *sprintfImp)(char *, const char *, ...);
		sprintfImp = sprintf;
		if (TheLangDir[0]) {
			(*sprintfImp)(buf, "%s\\%s", TheLangDir, a);
			if (TheArchiveFileSystem->doesFileExist2(buf, b))
				return true;
		}
		if (g_00DD509C[0]) {
			(*sprintfImp)(buf, "lang\\%s\\%s", g_00DD509C, a);
			if (TheArchiveFileSystem->doesFileExist2(buf, b))
				return true;
		}
		if (TheArchiveFileSystem->doesFileExist2(a, b))
			return true;
	}
try_local:
	if (G00A06E54) {
		if (G00A06E54->doesFileExist(a, b))
			return true;
	}
	if (TheArchiveFileSystem != 0) {
		if (!BFME2PreferLocalFiles) {
			if (TheArchiveFileSystem->doesFileExist2(a, b))
				return true;
		}
	}
	return false;
}
