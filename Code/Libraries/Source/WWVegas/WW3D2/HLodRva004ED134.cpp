// cl: /Ireference/shims/bfmevector /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?isTeamIdle@AITactic@@QAE_NH@Z @0x004ED134 53B
// HLod threshold check: find node via rowed 0x004ECF05 then compare its +0x10 int as float against LogicFramesPerSecond scaled by global +0x874.
// Evidence: chain via 0x004ECF05; callees all rowed; globals g_Va00DBA4E4 g_00DFEEF8; SSE cvtsi2ss mulss comiss need /arch:SSE plus /G7 per sibling HLodRva004ECECD.
extern int g_Va00DBA4E4;
class Rva002A8F24;
extern Rva002A8F24 *g_00DFEEF8;
struct Rva004ECECDNode
{
	void *m_model;
	char m_pad0[0xC];
	int m_10;
};
class AITactic
{
public:
	Rva004ECECDNode *rva004ECF05(int id);
	bool isTeamIdle(int id);
};
bool AITactic::isTeamIdle(int id)
{
	Rva004ECECDNode *node = rva004ECF05(id);
	if (node != 0)
	{
		float a = (float)node->m_10;
		float b = (float)g_Va00DBA4E4 * *(float *)((char *)g_00DFEEF8 + 0x874);
		if (a >= b)
			return true;
		return false;
	}
	return true;
}
