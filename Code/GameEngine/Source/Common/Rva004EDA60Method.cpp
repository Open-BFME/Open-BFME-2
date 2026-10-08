// ?rva004EDA60@AITactic@@QAEXXZ
// cl: /MD
// ?rva004EDA60@AITactic@@QAEXXZ at 0x004EDA60 (44B).
// AITactic guard: early-out if +0x50 set or [ +0x20 ]+4 == 1, else
// rva004ED372(&m_44), set +0x50=1, end(0 0).
// Evidence: same this calls pinned AITactic members 0x004ED372(PAX)
// and 0x004ED748(HH); offsets +0x20/+0x44/+0x50 match 0x004ED748 body;
// caller jmp at 0x004EDDCC in 0x004EDDAA; unblocks 0x004EDDAA.
class AITactic
{
public:
	void rva004ED372(void *p);
	void end(bool a, bool b);
	void rva004EDA60();
private:
	char m_pad00[0x20]; // +0
	struct Sub
	{
		int m_00;
		int m_04;
	};
	Sub *m_20; // +0x20
	char m_pad24[0x44 - 0x24]; // +0x24
	int m_44; // +0x44
	char m_pad48[0x50 - 0x48]; // +0x48
	unsigned char m_50; // +0x50
};

void AITactic::rva004EDA60()
{
	if (m_50 != 0)
		return;
	if (m_20->m_04 == 1)
		return;
	rva004ED372(&m_44);
	m_50 = 1;
	end(0, 0);
}
