// cl: /Ireference/shims/bfmevector /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// ?rva004ED169@AITactic@@QAEEXZ @0x004ED169 56B
// HLod all-nodes check: count is (m_end-m_begin) stride 0x14 then require every isTeamIdle(i) true.
// Evidence: chain via 0x004ED134; prev 0x004ED134 next 0x004ED1A1 same flags; stride 0x14 matches ModelNode loop.
struct Rva004ECECDNode
{
	void *m_model;
	char m_pad0[0xC];
	int m_10;
};
class AITactic
{
public:
	bool isTeamIdle(int id);
	unsigned char rva004ED169();
private:
	char m_pad00[0x14];
	Rva004ECECDNode *m_begin;
	Rva004ECECDNode *m_end;
};
unsigned char AITactic::rva004ED169()
{
	unsigned int count = (unsigned int)(m_end - m_begin);
	unsigned int matched = 0;
	for (unsigned int i = 0; i < count; ++i)
	{
		if (isTeamIdle((int)i))
			++matched;
	}
	return matched == count;
}
