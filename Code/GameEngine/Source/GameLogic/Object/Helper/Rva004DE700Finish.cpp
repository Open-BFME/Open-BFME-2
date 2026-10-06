// ?framesUntilNext@ObjectSMCHelper@@AAEHXZ
// cl: /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfmelist
// stlport
//
// ?framesUntilNext@ObjectSMCHelper@@AAEHXZ, retail 0x004DE700, 77 bytes.
// Private timer helper behind ObjectSMCHelper::update (0x004DE85F caller
// tail-jumps here): 0x3fffffff for an empty timer list, else the smallest
// queued wake frame minus the current frame, clamped to at least 1.
// The separate empty()/begin()/end() list calls keep retail's two m_node
// loads and its duplicate empty check; the min is a cmovb, which needs
// /arch:SSE (the P6 instruction set) on top of the TU's /O1. Donor:
// BFME1 ObjectSMCHelperFramesUntilNext.cpp with ObjectSMCHelperUpdate.cpp.

struct Rva004DE700FrameSource
{
	unsigned char m_padding[0x40];
	unsigned int m_frame;
};
class GameLogic;
extern GameLogic *TheGameLogic;

struct Rva004DE700TimerValue
{
	unsigned int m_condition;
	unsigned int m_frame;
};
struct Rva004DE700TimerNode
{
	Rva004DE700TimerNode *m_next;
	Rva004DE700TimerNode *m_previous;
	Rva004DE700TimerValue m_value;
};
struct Rva004DE700TimerList
{
	Rva004DE700TimerNode *m_node;
	bool empty() const { return m_node->m_next == m_node; }
	Rva004DE700TimerNode *begin() const { return m_node->m_next; }
	Rva004DE700TimerNode *end() const { return m_node; }
};

class ObjectSMCHelper
{
private:
	int framesUntilNext();
	unsigned char m_padding[0x20];
	Rva004DE700TimerList m_timers;
};

int ObjectSMCHelper::framesUntilNext()
{
	if (m_timers.empty())
		return 0x3fffffff;

	unsigned int frame = ((Rva004DE700FrameSource *)TheGameLogic)->m_frame;
	unsigned int best = 99999999;
	Rva004DE700TimerNode *n = m_timers.begin();
	if (n != m_timers.end())
	{
		do
		{
			Rva004DE700TimerValue value = n->m_value;
			unsigned int f = value.m_frame;
			n = n->m_next;
			if (f < best)
				best = f;
		} while (n != m_timers.end());
	}
	int delta = best - frame;
	if (delta > 0)
		return delta;
	return 1;
}
