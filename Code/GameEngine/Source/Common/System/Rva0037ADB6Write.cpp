// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0037ADB6@Rva0037ADB6@@QAEXXZ @0x0037ADB6 152B: recorder file patch via ftell fseek fwrite rows plus globals g_00DBC800 and TheGameLogic+0x40 into members +0xe60 +0xe64. Evidence: null FILE at +0x10 early out plus IAT ftell fseek fwrite plus fixed offsets 0x14 0x18 plus restore ftell pos; same FILE+0x10 family as Rva0037B287Write; caller 0x00240225.
struct FILE;
extern "C" __declspec(dllimport) long __cdecl ftell(FILE *stream);
extern "C" __declspec(dllimport) int __cdecl fseek(FILE *stream, long offset, int origin);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *buf, unsigned int size, unsigned int count, FILE *stream);

extern unsigned int g_00DBC800;

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_40;
};
extern GameLogic *TheGameLogic; // ?TheGameLogic@@3PAVGameLogic@@A

class Rva0037ADB6
{
public:
	void rva0037ADB6();
private:
	char m_pad00[0x10];
	FILE *m_file10; // +0x10
	char m_pad14[0xe60 - 0x14];
	int m_e60; // +0xe60
	int m_e64; // +0xe64
};

void Rva0037ADB6::rva0037ADB6()
{
	if (m_file10 == 0)
		return;
	m_e60 = (int)g_00DBC800;
	m_e64 = TheGameLogic->m_40;
	long pos = ftell(m_file10);
	if (fseek(m_file10, 0x14, 0) == 0)
		fwrite(&m_e60, 4, 1, m_file10);
	if (fseek(m_file10, 0x18, 0) == 0)
		fwrite(&m_e64, 4, 1, m_file10);
	fseek(m_file10, pos, 0);
}
