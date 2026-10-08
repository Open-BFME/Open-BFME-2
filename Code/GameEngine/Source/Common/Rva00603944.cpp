// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?init@Win32BIGFileSystem@@UAEX_N@Z @0x00603944 188B: vslot 1 of vtable 0x0087A94C (class of ??0Win32BIGFileSystem@@QAE@XZ). Loads lang big files. Evidence: vtable slot 1; strings "%s*.big" "lang\" "lang\%sAudio.big" "EnglishAudio.big" "*.big" "apt\"; global TheArchiveFileSystem; buffers g_00DD509C g_Rva0107301CEmptyString.
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *fmt, ...);

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

extern ArchiveFileSystem *TheArchiveFileSystem;
extern char g_00DD509C[];

class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();
	virtual void init(bool flag);
	virtual void V2();
	virtual void V3();
	virtual void V4();
	virtual void V5();
	virtual void V6();
	virtual void V7();
	virtual void S8(const char *a, const char *b, int c);
};

void Win32BIGFileSystem::init(bool flag)
{
	char buf[0x104];

	if (TheArchiveFileSystem == 0)
		return;
	if (!flag)
		return;

	int (__cdecl *sprintfImp)(char *, const char *, ...);
	sprintfImp = sprintf;

	sprintfImp(buf, "%s*.big", g_00DD509C);
	S8("lang\\", buf, 1);

	sprintfImp(buf, "lang\\%sAudio.big", g_00DD509C);
	if (!TheArchiveFileSystem->doesFileExist(buf)) {
		S8("lang\\", "EnglishAudio.big", 0);
	}

	const char *pat = "*.big";
	S8("", pat, 0);
	S8("apt\\", pat, 0);
}
