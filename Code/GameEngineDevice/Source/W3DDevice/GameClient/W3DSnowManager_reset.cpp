// cl: /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// ?reset@W3DSnowManager@@UAEXXZ @0x00093B3F (28B):
// W3DSnowManager reset slot 9 of vtable 0x007C8144: base SnowManager::reset
// 0x00201134, then copy helper 0x00093457, then zero m_a8 and m_50.
// Evidence: vslot, caller none, LINK none, prev 0x00093457 same flags.
#include "W3DSnowResourceView.h"
void W3DSnowManager::reset()
{
	SnowManager::reset();
	rva00093457();
	m_A8 = 0;
	m_50 = false;
}
