// ?doesFileExist@FileSystem@@QBE_NPBD@Z
// partial score=0.7 date=2026-09-10
// cl: /O2 /Oy- /MD
//
// FileSystem::doesFileExist, retail 0x00600D7D, 189 bytes.
// Dedicated TU. BFME2 checks a path gate, local (+0xC), archive (+0x14),
// then optional "%s\\%s" under TheLangDir and "lang\\%s\\%s" / English.

extern "C" int (__cdecl *__imp__sprintf)(char *, const char *, ...);

static int do_sprintf(char *buf, const char *fmt, const char *a, const char *b)
{
	return (*__imp__sprintf)(buf, fmt, a, b);
}

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
extern LocalFileSystem *TheLocalFileSystem;
extern ArchiveFileSystem *TheArchiveFileSystem;
extern char TheLangDir[];

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
};

bool FileSystem::doesFileExist(const char *filename) const
{
	char buf[0x200];

	if (TheFilePathGate) {
		if (!TheFilePathGate->allow(filename))
			return false;
	}

	if (TheLocalFileSystem->doesFileExist(filename))
		goto success;

	if (TheArchiveFileSystem->doesFileExist(filename))
		goto success;

	if (TheLangDir[0]) {
		(*__imp__sprintf)(buf, "%s\\%s", TheLangDir, filename);
		if (TheArchiveFileSystem->doesFileExist(buf))
			goto success;
	}

	(*__imp__sprintf)(buf, "lang\\%s\\%s", "English", filename);
	return TheArchiveFileSystem->doesFileExist(buf);

success:
	return true;
}
