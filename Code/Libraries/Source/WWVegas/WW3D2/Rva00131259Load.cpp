// cl: /DNDEBUG /MD
// ?rva00131259@Rva00131259@@QAEX PBD@Z, retail 0x00131259, 212 bytes.
// Chain via 0x000787BA opener: copies name to 260B buffer via _mbscpy thunk,
// finds extension via strrchr IAT, tries .dds .tga .jpg into +0x10 and .png
// into +0x1C, sets byte +0xD on opened Files. Evidence: chain lane, caller
// pushes at 0x00131C9E 0x00131D76, .dds/.tga/.jpg/.png literals.

extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
extern "C" __declspec(dllimport) char *__cdecl strrchr(const char *s, int c);

class File
{
public:
	char m_pad[0xD];
	unsigned char m_flag0D;
};

File *__cdecl Rva000787BAOpen(const char *filename);

class Rva00131259
{
public:
	void rva00131259(const char *name);

	char m_pad00[0x10];
	File *m_file10;
	char m_pad14[8];
	File *m_file1C;
};

void Rva00131259::rva00131259(const char *name)
{
	char buf[0x104];
	_mbscpy(buf, name);
	char *dot = strrchr(buf, '.');
	if (dot != 0) {
		_mbscpy(dot, ".dds");
		m_file10 = Rva000787BAOpen(buf);
		if (m_file10 == 0) {
			_mbscpy(dot, ".tga");
			m_file10 = Rva000787BAOpen(buf);
			if (m_file10 == 0) {
				_mbscpy(dot, ".jpg");
				m_file10 = Rva000787BAOpen(buf);
				if (m_file10 == 0)
					goto check;
				_mbscpy(dot, ".png");
				m_file1C = Rva000787BAOpen(buf);
				goto check;
			}
			goto check;
		}
		goto check;
	}
check:
	if (m_file10 != 0)
		m_file10->m_flag0D = 1;
	if (m_file1C != 0)
		m_file1C->m_flag0D = 1;
}
