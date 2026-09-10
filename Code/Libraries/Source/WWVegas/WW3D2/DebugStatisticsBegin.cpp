// cl: /O2 /DNDEBUG /MD
//
// Debug_Statistics::Begin_Statistics, retail 0x0012A400, 67 bytes. Eleven
// dword counters zeroed, then two helpers. /O2 tail-jumps the second.

int g_stat0;
int g_stat1;
int g_stat2;
int g_stat3;
int g_stat4;
int g_stat5;
int g_stat6;
int g_stat7;
int g_stat8;
int g_stat9;
int g_stat10;

void Record_Texture_Begin();

class DX8Wrapper
{
public:
	static void Begin_Statistics();
};

namespace Debug_Statistics
{
	void Begin_Statistics();
}

void Debug_Statistics::Begin_Statistics()
{
	g_stat0 = 0;
	g_stat1 = 0;
	g_stat2 = 0;
	g_stat3 = 0;
	g_stat4 = 0;
	g_stat5 = 0;
	g_stat6 = 0;
	g_stat7 = 0;
	g_stat8 = 0;
	g_stat9 = 0;
	g_stat10 = 0;
	Record_Texture_Begin();
	DX8Wrapper::Begin_Statistics();
}
