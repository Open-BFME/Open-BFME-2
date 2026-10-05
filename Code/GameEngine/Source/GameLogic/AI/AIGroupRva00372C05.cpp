// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva00372C05@AIGroup@@QAEXXZ, retail 0x00372C05, 29 bytes.
// Idle guard then two-pass work: rowed AIGroup::isIdle on our own this,
// rowed AIGroup::rva0036DF92, then the pinned AIGroup 0x003705C2 tail call
// on the same this. Evidence: caller chain noted on the rva0036DF92 TU
// (isIdle, then this, then 0x003705C2, same this); pop-esi then jmp tail.
class AIGroup
{
public:
	bool isIdle() const;
	void rva0036DF92();
	void rva003705C2();
	void rva00372C05();
};

void AIGroup::rva00372C05()
{
	if (isIdle())
		return;
	rva0036DF92();
	rva003705C2();
}
