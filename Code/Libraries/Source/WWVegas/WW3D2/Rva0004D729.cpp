// cl: /DNDEBUG /MD
// ?rva0004D729@Rva0004D729@@QAEPAV1@PAXPAPAXPAHHHHH@Z @0x0004D729 43B
// Lock-rect helper: stores surf at +0, calls rowed 0x001166E0 with
// pitchOut/left/top/right/bottom, stores bits to *bitsOut, returns this.
// Evidence: push 0x20/0x1c/0x18/0x14/0x10 call 0x1166E0 / mov [ecx] eax /
// mov eax esi / ret 0x1c; callers in unclaimed; neighbours prove TU flags.
class Rva001166E0;
class Rva001166E0
{
public:
	void *rva001166E0(int *pitchOut, int left, int top, int right, int bottom);
};
class Member0C00739C70
{
public:
	void clear();
};
class Rva0004D729
{
public:
	Rva0004D729 *rva0004D729(void *surf, void **bitsOut, int *pitchOut, int left, int top, int right, int bottom);
	~Rva0004D729();
private:
	void *m_surf;
};
Rva0004D729 *Rva0004D729::rva0004D729(void *surf, void **bitsOut, int *pitchOut, int left, int top, int right, int bottom)
{
	m_surf = surf;
	void *bits = ((Rva001166E0 *)surf)->rva001166E0(pitchOut, left, top, right, bottom);
	*bitsOut = bits;
	return this;
}

Rva0004D729::~Rva0004D729()
{
	((Member0C00739C70 *)m_surf)->clear();
}
