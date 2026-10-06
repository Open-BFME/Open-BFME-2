// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004233F5@Rva004233F5@@QAEHPAURva00422544List@@M@Z, retail 0x004233F5, 144 bytes.
// __thiscall returning int, args (Rva00422544List*, float); early -1 when
// g_00DC84F5 clear, Find passthrough when this+0x2c above val, else
// lower_bound over global deque range with float key, deref hit or back().
// Evidence: chain lane, callees 0x00422544 0x00422FE6 0x004226AD rowed,
// globals 0x00DC84F5 0x00A031B8 0x00A031A8, caller 0x002A50D7.
// Structural inference: the lower_bound result is assigned and compared with
// end() inside one full expression; that keeps the call's return temporary
// and the end() temporary alive together, so they take two frame slots
// (retail frame 0x30) instead of sharing one (0x20 with the assignment and
// the comparison as separate statements).
#include <algorithm>
#include <deque>
struct BfmeE12 { int m_id; float m_key; float m_z; };
struct BfmeE12Cmp0042299E
{
	__forceinline bool operator()(const BfmeE12 &a, const float &b) const { return a.m_key < b; }
};
struct Rva00422544Elem { Rva00422544Elem *m_next; int m_unk04; int m_key; };
struct Rva00422544List { Rva00422544Elem *m_head; };
extern unsigned char g_00DC84F5;
extern _STL::deque<BfmeE12> g_00E031A8;
int __stdcall Rva00422544Find(Rva00422544List *list);
class Rva004233F5
{
public:
	unsigned char m_pad[44];
	float m_thresh;
	int rva004233F5(Rva00422544List *list, float val);
};
int Rva004233F5::rva004233F5(Rva00422544List *list, float val)
{
	if (g_00DC84F5 == 0)
		return -1;
	if (m_thresh > val)
		return Rva00422544Find(list);
	_STL::deque<BfmeE12>::iterator it;
	return (it = _STL::lower_bound(g_00E031A8.begin(), g_00E031A8.end(), val, BfmeE12Cmp0042299E())) == g_00E031A8.end() ? g_00E031A8.back().m_id : (*it).m_id;
}
