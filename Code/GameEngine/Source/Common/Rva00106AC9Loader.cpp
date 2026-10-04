// ?rva00106AC9@Rva00106AC9@@QAE_NPBDH_N@Z
// cl: /Ireference/shims/bfme2_ascii /Os /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include "ascii_string.h"

// ?rva00106AC9@Rva00106AC9@@QAE_NPBDH_N@Z
// 0x00106AC9 256B: file-backed loader keyed by mode 1/2. Sets path, checks
// existence via TheFileSystem, opens (0x141/0x5a), reads size via File slot
// 0x2c, runs rva00106A5C check and invokeForMode. Caller at 0x00106CD6 and
// 0x000918E5. Prev/next are BfmeB996Range TUs with same flags.
class File
{
public:
	virtual ~File();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual int getSize();
};

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
	File *openFile(const char *filename, int access, int unk);
};

extern FileSystem *TheFileSystem;

class Rva007E3410Object
{
public:
	void invokeForMode();
};

class Rva00106874Host
{
public:
	bool rva00106874();
};

class BfmeB996Range
{
public:
	char rva00106A5C();
};

class Rva00106AC9
{
public:
	Rva00106AC9(const char *path, int mode, bool flag);
	bool rva00106AC9(const char *path, int mode, bool flag);
private:
	AsciiString m_path;
	File *m_file;
	int m_mode;
	int m_size;
};

__forceinline const char *GetStr00106AC9(const AsciiString &s)
{
	char *t = *(char * *)(const void *)&s;
	return t ? t + 8 : "";
}

// Native full extent 0x00106AC9..0x00106BC9; RET12.
// The original owner name is unknown. Offsets and modes below are target facts.
// Native branch at 106B52 skips the probe when flag is false; its success
// branch and false-flag branch share the invokeForMode call at 106B71.
// Combining the predicate preserves that join and its ECX reload under /Os.
bool Rva00106AC9::rva00106AC9(const char *path, int mode, bool flag)
{
	bool done = false;
	((StringBase<char> &)m_path).set(path);
	if (mode == 1) {
		const char *p = GetStr00106AC9(m_path);
		if (!TheFileSystem->doesFileExist(p)) {
			m_mode = 5;
		} else {
			p = GetStr00106AC9(m_path);
			File *f = TheFileSystem->openFile(p, 0x141, 0);
			m_file = f;
			int sz = f->getSize();
			m_size = sz;
			m_mode = 6;
			if (sz >= 8) {
                if (flag && !((BfmeB996Range *)this)->rva00106A5C()) {
                    m_mode = 3;
                    ((Rva00106874Host *)this)->rva00106874();
                } else {
                    ((Rva007E3410Object *)this)->invokeForMode();
                    done = true;
                }
			} else {
				m_mode = 3;
			}
		}
	} else if (mode == 2) {
		const char *p = GetStr00106AC9(m_path);
		File *f = TheFileSystem->openFile(p, 0x5a, 0);
		m_file = f;
		m_mode = 3;
		if (f != 0) {
			m_mode = 7;
			done = true;
		}
	}
	return done;
}

// Native 0x00106C9E..0x00106CEC RET12 constructs the same 16-byte owner.
// Its calls prove the StringBase(path, 1) initialization and loader binding;
// target stores establish file=0, mode=4, size=0 before the load.
// /EHsc preserves the native member-cleanup region on constructor failure.
Rva00106AC9::Rva00106AC9(const char *path, int mode, bool flag)
    : m_path(path, 1), m_file(0), m_mode(4), m_size(0)
{
    rva00106AC9(path, mode, flag);
}
