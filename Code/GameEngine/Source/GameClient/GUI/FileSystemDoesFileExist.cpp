// cl: /Oy- /MD
//
// ?doesFileExist@FileSystem@@QBE_NPBD@Z, retail 0x00600D7D, 189 bytes.
// Dedicated TU. BFME2 checks a path gate, local (+0xC), archive (+0x14),
// then optional "%s\%s" under TheLangDir and "lang\%s\%s" / English.

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *fmt, ...);

class FilePathGate
{
public:
	bool allow(const char *filename);
};

class LocalFileSystem
{
public:
	virtual ~LocalFileSystem();
	virtual void L1();
	virtual void L2();
	virtual bool doesFileExist(const char *filename) const;
};

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual void A3();
	virtual void A4();
	virtual bool doesFileExist(const char *filename) const;
};

extern FilePathGate *TheFilePathGate;
// TheFilePathGate: matched references place it at VA 0xe06a4c (zero-filled .bss).
FilePathGate * TheFilePathGate;
extern LocalFileSystem *TheLocalFileSystem;
extern ArchiveFileSystem *TheArchiveFileSystem;
// TheLangDir (VA 0xe06948) is defined in FileSystemOpenFile.cpp.
extern char TheLangDir[256];

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
};

// ?doesFileExist@FileSystem@@QBE_NPBD@Z
bool FileSystem::doesFileExist(const char *filename) const
{
	char buf[0x200];

	if (TheFilePathGate) {
		if (!TheFilePathGate->allow(filename))
			return false;
	}

	if (TheLocalFileSystem->doesFileExist(filename))
		return true;
	else {
		if (TheArchiveFileSystem->doesFileExist(filename))
			return true;

		int (__cdecl *sprintfImp)(char *, const char *, ...);
		sprintfImp = sprintf;

		if (TheLangDir[0]) {
			(*sprintfImp)(buf, "%s\\%s", TheLangDir, filename);
			if (TheArchiveFileSystem->doesFileExist(buf))
				return true;
		}

		(*sprintfImp)(buf, "lang\\%s\\%s", "English", filename);
		return TheArchiveFileSystem->doesFileExist(buf) ? true : false;
	}
}
