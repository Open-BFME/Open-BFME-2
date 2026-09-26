// cl: /O1 /Oy- /MD
//
// ?openFile@FileSystem@@QAEPAVFile@@PBDHH@Z, retail 0x00600C34, 329 bytes.
// BFME2 lang-aware open: gate, archive lang "%s\%s" + "lang\%s\%s"/English,
// local (+0x8), archive (+0xC); File+4 setName via StringBase<char>::set.
// Evidence: pin ?openFile@FileSystem@@QAEPAVFile@@PBDHH@Z; callers via
// LanguageFilterInit 0x38873F; vtable offsets from sibling doesFileExist
// 0x00600D7D (local +0xC, archive +0x14); donor BFME1 FileSystem_openFile.

extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *fmt, ...);

template <typename T> class StringBase
{
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};
	Header *m_data;
public:
	void set(const T *str);
};

class File
{
public:
	virtual void dummy();
	void setName(const char *name) { m_name.set(name); }
private:
	StringBase<char> m_name;
};

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
	virtual File *openFile(const char *filename, int access, int unk);
	virtual bool doesFileExist(const char *filename) const;
};

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual File *openFile(const char *filename, int access, int unk);
	virtual void A4();
	virtual bool doesFileExist(const char *filename) const;
};

extern FilePathGate *TheFilePathGate;
extern LocalFileSystem *TheLocalFileSystem;
extern ArchiveFileSystem *TheArchiveFileSystem;
extern char TheLangDir[];
extern bool ArchiveOrderFlag;

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int unk);
};

File *FileSystem::openFile(const char *filename, int access, int unk)
{
	char buf[0x200];

	if (TheFilePathGate) {
		if ((access & 8) == 0) {
			if (!TheFilePathGate->allow(filename))
				return 0;
		}
	}

	File *file = 0;

	if (!ArchiveOrderFlag)
		goto try_local;
	if (!TheArchiveFileSystem)
		goto try_local;
	if (access & 8)
		goto try_archive_direct;
	{
		int (__cdecl *sprintfImp)(char *, const char *, ...);
		sprintfImp = sprintf;
		if (TheLangDir[0]) {
			(*sprintfImp)(buf, "%s\\%s", TheLangDir, filename);
			file = TheArchiveFileSystem->openFile(buf, access, unk);
			if (file)
				file->setName(filename);
		}
		(*sprintfImp)(buf, "lang\\%s\\%s", "English", filename);
		if (file)
			goto done;
		file = TheArchiveFileSystem->openFile(buf, access, unk);
		if (file) {
			file->setName(filename);
			goto done;
		}
	}
try_archive_direct:
	file = TheArchiveFileSystem->openFile(filename, access, unk);
	if (file)
		goto done;
try_local:
	if ((access & 8) == 0) {
		if (TheLocalFileSystem) {
			file = TheLocalFileSystem->openFile(filename, access, unk);
			if (file)
				goto done;
		}
	}
	if (ArchiveOrderFlag)
		goto done;
	file = TheArchiveFileSystem->openFile(filename, access, unk);
done:
	return file;
}
