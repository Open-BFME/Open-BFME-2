// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /D_CRTIMP= /Ireference/shims/bfme2_ascii
//
// ??1Rva005EEF2F@@MAE@XZ @ 0x005EEF2F (99B).
// Dtor with two vptrs (+0/+4), unregister via +0x30 slot 0, members
// +0x20/+0x14 through rowed 0x005242D7/0x0052413E. Evidence: vtable stores
// 0x008787D4/0x008787D0 then 0x007FBC9C/0x007C6F20; virtual on +0x30 with
// this pushed; caller 0x005EF165 is the ??_G; neighbours share /O1.

#include "RegionArmyIconSlotView.h"

// ?Rva005EEF2FBase0dtor present-unmatched
Rva005EEF2FBase0::~Rva005EEF2FBase0()
{
}

// ?Rva005EEF2FBase4dtor present-unmatched
Rva005EEF2FBase4::~Rva005EEF2FBase4()
{
}

Rva005EEF2F::~Rva005EEF2F()
{
	if (m_listener)
		m_listener->v00(this);
}

// Native005EF669..005EF8BB RET8 and WB01616450; three icon callback names
// append the decimal slot index after the prefix/name/event expression.
Rva005EEF2F::Rva005EEF2F(StrategicHUD::RegionDetailsArmiesMovieClip::Impl *p,int n)
 : owner(reinterpret_cast<RegionSlotOwnerView *>(p)),index(n),m_rolledOver(false),m_listener(0),a(0),b(0),c(0) {
 AsciiString prefix; prefix.format("_level%u.",owner->level);
 AsciiString number; number.format("%d",index);
 commands.AddCommandMapBinding(prefix + owner->name + "_OnIconSlotClicked" + number,FunctorBinding(this,&Rva005EEF2F::OnIconSlotClicked));
 commands.AddCommandMapBinding(prefix + owner->name + "_OnIconSlotRollOver" + number,FunctorBinding(this,&Rva005EEF2F::OnIconSlotRollOver));
 commands.AddCommandMapBinding(prefix + owner->name + "_OnIconSlotRollOut" + number,FunctorBinding(this,&Rva005EEF2F::OnIconSlotRollOut));
}
