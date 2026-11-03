// Target facts (BFME2 RVAs): 0x00625884/0x0062588B and 0x006258B4/0x006258BB compare a float at +4; 0x00625A90 indexes eight-byte elements.
// 0x00625A9F..0x00625AAC and 0x00625BC3..0x00625BF7 copy both dwords at +0/+4 without vptr stores or member calls: no virtual functions or base storage. No constructor or destructor is rowed; copies and assignment remain trivial.
// The ledger's PAUS4SortElem8@@ spelling fixes struct. The +0 payload has no proven meaning or signedness; int is its four-byte carrier and the m_bfme labels are project placeholders. 0x005EC52E/0x005EC537 instead dereference +4 as a pointer and belong to the separate score family.

#pragma once

#ifndef BFME2_S4SORTELEM8_H
#define BFME2_S4SORTELEM8_H

struct S4SortElem8
{
	int m_bfmeA;
	float m_bfmeKey;
};

#endif
