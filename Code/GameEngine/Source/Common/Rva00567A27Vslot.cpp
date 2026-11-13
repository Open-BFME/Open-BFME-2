// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?OnMouseOver@Rva00567960@@QAEXXZ @0x00567A27 66B
// vslot 2 of 0x0086CEF0 (+8 of Rva00567960): BfmeMsgDN msg(holder+0x14, this+0xc) then ControlBar::bfmeShowDN via g_bfmeWorldRV.
// Evidence: ret no args thiscall; pin ?bfmeShowDN@ControlBar@@QAEXPAUBfmeMsgDN@@@Z 0x00405C04; global g_bfmeWorldRV ?g_bfmeWorldRV@@3PAUBfmeWorldRV@@A; this+8 deref +0x14 and this+0xc; donor BfmeConv1941 BfmeMsgDN virtual dtor plus 2-int inline ctor.
// BfmeMsgDN is the class of table 0x00C6CED8 (ledger Rva00567847), below the
// root of table 0x00BE5838 (target facts): that root table is [??_G
// 0x00215E42, five __purecall slots]; slot 0 of 0x00C6CED8 is the shared
// deleting dtor 0x00406B1D, which calls 0x004059AC: mov [ecx],0x00BE5838 /
// ret. With the empty base destructor expanded, the own table store dies and
// only the root's remains; the funclet 0x0079A0EE calls that body for the
// local below. The copy ctor 0x00567CA6 shows one more step between them, the
// vtable-only base copy 0x00567860 storing 0x00C6CEB4 (Rva00567860); its store
// dies too, and it is not modelled here because Rva00567860Copy.cpp's view of
// that table (a pure slot 0) would make the two units' COMDATs differ.
// The root takes InGameUICreateMouseoverHint.cpp's spelling, which binds
// the same table and passes its derived record to the same bfmeShowDN 0x00405C04;
// C01's Rva00215E42 defines its ctor and dtor out of line, so an inline
// view under that name would duplicate them.
#include "../../Include/Common/TooltipBase.h"

struct BfmeMsgDN : public TooltipBase
{
	BfmeMsgDN(int a, int b)
	{
		m_04 = a;
		m_08 = b;
	}
	virtual ~BfmeMsgDN() {}
	int m_04;
	int m_08;
};

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

class BfmeThingGX;
#include "../../Include/Common/Rva00405A50.h"

struct Rva00567A27Holder
{
	char m_pad[20];
	int m_14;
};

class Rva00567960
{
public:
	void OnMouseOver();
private:
	char m_pad00[8];
	Rva00567A27Holder *m_08;
	int m_0c;
};

void Rva00567960::OnMouseOver()
{
	BfmeMsgDN msg(m_08->m_14, m_0c);
	((Rva00405A50 *)((BfmeWorldRV *)TheControlBar))->rva00405C04((BfmeThingGX *)&msg);
}
