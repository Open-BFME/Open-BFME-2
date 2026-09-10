// cl: /O2 /DNDEBUG /MD
//
// Debug_Statistics::End_Statistics, retail 0x0012A450, 122 bytes. Snapshot
// last-frame counters then tail-jump DX8Wrapper::End_Statistics.

extern int g_stat0;
extern int g_stat1;
extern int g_stat2;
extern int g_stat3;
extern int g_stat4;
extern int g_stat5;
extern int g_stat6;
extern int g_stat7;
extern int g_stat8;
extern int g_stat9;

int g_last0;
int g_last1;
int g_last2;
int g_last3;
int g_last4;
int g_last5;
int g_last6;
int g_last7;
int g_last8;
int g_last9;

void Record_Texture_End();

class DX8Wrapper
{
public:
	static void End_Statistics();
};

namespace Debug_Statistics
{
	void End_Statistics();
}

void Debug_Statistics::End_Statistics()
{
	Record_Texture_End();
	g_last2 = g_stat2;
	g_last3 = g_stat3;
	g_last5 = g_stat5;
	g_last4 = g_stat4;
	g_last0 = g_stat0;
	g_last1 = g_stat1;
	g_last6 = g_stat6;
	g_last7 = g_stat7;
	g_last8 = g_stat8;
	g_last9 = g_stat9;
	DX8Wrapper::End_Statistics();
}
