// FILE: DynamicPortalLink.h
// Target facts (BFME2 RVAs): DynamicPortalLink has no virtual functions or vptr. Range destruction 0x003F29F8 calls 0x0007FAB3 at 0x003F2A01 and advances by 0x0C at 0x003F2A06; push_back advances by the same size at 0x00461691. Destructor 0x0007FAB3 reads the owned pointer at +0 and conditionally calls free (0x00030830), with no table store. Thus sizeof is 0x0C, and +0 is data, not a vptr.
// Target layout: resize 0x003F3B28 builds the value through 0x00211E58 at 0x003F3B3B; that constructor clears dwords +0/+4 (0x00211E65/67) and +8 through 0x0014F3C4 (store 0x0014F3CA). Placement copy 0x00460F18 calls the scalar-vector copy 0x002CFAB9 at 0x00460F34; its +0/+4 range is copied in four-byte elements. m_owned describes only the observed ownership; m_second and m_third are positional placeholders. No class-specific table or Snapshot name is present in these lifetime paths. The nonvirtual destructor stays out of line, as the range-destruction call proves.

#pragma once

struct DynamicPortalLink
{
	~DynamicPortalLink();

	void *m_owned;
	int m_second;
	int m_third;
};
