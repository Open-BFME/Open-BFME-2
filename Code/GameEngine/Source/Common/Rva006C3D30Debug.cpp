// cl: /O2 /arch:SSE /DNDEBUG /MD
// platformsdk
//
// ?rva006C3D30@GeneralAllocatorDebug@@QAE_NPAURva006C2270Record@@PAX_N@Z @ 0x006C3D30 903B, ret 0xC
//
// Writes the debug data a freshly allocated block carries, from the record
// 0x006C2270 sized for it: (record, block, fill-new flag). The usable size is
// the chunk size field masked to 0x7FFFFFF8, plus four unless bit 1 is set.
// With the flag set and the new-fill byte (+0x50A) not 1, the block is
// filled with that byte over its reported size (0x00032A20). The 16-bit
// trailer word ten bytes before the usable end is cleared and the block is
// registered with the external-record table (0x006C39F0, given the record's
// external total); failure returns false. When either record total exceeds
// the two-byte header, every field with a nonzero slot total is stored
// through the setter 0x006C3AB0 with the slot's length and location:
// 1 the allocator, 2 the requested size, 3 record+0xB8, 4 record+0xBC alone
// or paired with record+0xC0 when that is nonzero, 5 the +0x51C text or an
// empty string, 6 record+0xC4, 7 the captured call stack, 8 a zero word,
// 9 the +0x568 member, 10 GetTickCount() in seconds, 12 the slack between
// usable and requested size, 13 the +0x52C member, and last 11, a field the
// setter only reserves: it is filled with the guard byte (+0x50B) and, when
// the gap between requested size and field is 1..0x4000 bytes, that gap is
// filled too and folded into the field's length word and the trailer word.
//
// Evidence: retail body, the record layout 0x006C2270 writes, and the rowed
// or pinned callees. Field roles beyond the bytes are not established; the
// name is address-derived.
// Codegen: retail re-reads record->inlineTotal and slots[3].total instead of
// keeping them in registers; the two reads go through a volatile reference
// helper (the unit's only deviation from plain C++).

#include <windows.h>
#include <string.h>
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}

struct Rva006C2270Slot {unsigned total,length,mode;};
struct Rva006C2270Record {
	unsigned initial;Rva006C2270Slot slots[14];
	unsigned inlineTotal,externalTotal,requestedSize,arg2,arg3,arg4,word520,word524;
	void*stack[24];
};

#include "../../Include/Common/GeneralAllocator.h"
namespace EA { namespace Allocator {
} }

#include "../../Include/Common/Rva006C39F0Owner.h"

class GeneralAllocatorDebug
{
public:
	bool rva006C3D30(Rva006C2270Record *record, void *block, bool fill);
	void *rva006C3AB0(void *block, unsigned short id, const void *data, unsigned length, int location);
private:
	unsigned char m_pad0[0x50a];
	unsigned char m_fillNew;
	unsigned char m_fillGuard;
	unsigned char m_pad1[0x51c - 0x50c];
	const char *m_name;
	unsigned char m_pad2[0x52c - 0x520];
	unsigned m_52c;
	unsigned char m_pad3[0x568 - 0x530];
	unsigned m_568[2];
};

bool GeneralAllocatorDebug::rva006C3D30(Rva006C2270Record *r, void *block, bool fill)
{
	unsigned n = ((unsigned *)block)[-1];
	unsigned usable = !(n & 2) ? (n & 0x7ffffff8) + 4 : (n & 0x7ffffff8);

	if (fill && m_fillNew != 1)
		memset(block, m_fillNew, ((EA::Allocator::GeneralAllocator *)this)->rva00032A20(block));

	unsigned short *trailer = (unsigned short *)((char *)block + usable - 10);
	for (int i = 0; i < 2; ++i)
		((char *)trailer)[i] = 0;

	if (((Rva006C39F0Owner *)this)->rva006C39F0((unsigned)block, r->externalTotal, 0, 0)) {
	if (__vref(r->inlineTotal) > 2 || r->externalTotal > 2) {
		if (r->slots[1].total)
			rva006C3AB0(block, 1, this, r->slots[1].length, r->slots[1].mode);
		if (r->slots[2].total)
			rva006C3AB0(block, 2, &r->requestedSize, r->slots[2].length, r->slots[2].mode);
		if (__vref(r->slots[3]).total)
			rva006C3AB0(block, 3, &r->arg2, r->slots[3].length, r->slots[3].mode);
		if (r->slots[4].total) {
			if (r->arg4) {
				unsigned pair[2];
				pair[0] = r->arg3;
				pair[1] = r->arg4;
				rva006C3AB0(block, 4, pair, r->slots[4].length, r->slots[4].mode);
			} else
				rva006C3AB0(block, 4, &r->arg3, r->slots[4].length, r->slots[4].mode);
		}
		if (r->slots[5].total) {
			if (m_name)
				rva006C3AB0(block, 5, m_name, r->slots[5].length, r->slots[5].mode);
			else {
				char empty = 0;
				rva006C3AB0(block, 5, &empty, 1, r->slots[5].mode);
			}
		}
		if (r->slots[6].total)
			rva006C3AB0(block, 6, &r->word520, r->slots[6].length, r->slots[6].mode);
		if (r->slots[7].total)
			rva006C3AB0(block, 7, r->stack, r->slots[7].length, r->slots[7].mode);
		if (r->slots[8].total) {
			unsigned zero = 0;
			rva006C3AB0(block, 8, &zero, r->slots[8].length, r->slots[8].mode);
		}
		if (r->slots[9].total)
			rva006C3AB0(block, 9, m_568, r->slots[9].length, r->slots[9].mode);
		if (r->slots[10].total) {
			unsigned seconds = GetTickCount() / 1000;
			rva006C3AB0(block, 10, &seconds, r->slots[10].length, r->slots[10].mode);
		}
		if (r->slots[12].total) {
			unsigned slack = usable - r->requestedSize - 4;
			rva006C3AB0(block, 12, &slack, r->slots[12].length, r->slots[12].mode);
		}
		if (r->slots[13].total)
			rva006C3AB0(block, 13, &m_52c, r->slots[13].length, r->slots[13].mode);
		if (r->slots[11].total) {
			char *field = (char *)rva006C3AB0(block, 11, 0, r->slots[11].length, r->slots[11].mode);
			if (field) {
				memset(field, m_fillGuard, r->slots[11].length);
				unsigned short gap = (unsigned short)(field - (char *)block - r->requestedSize);
				if ((unsigned)(gap - 1) < 0x4000) {
					memset((char *)block + r->requestedSize, m_fillGuard, gap);
					*(unsigned short *)(field + r->slots[11].length + 2) = (unsigned short)r->slots[11].length + gap;
					*trailer += gap;
				}
			}
		}
	}
	return true;
	}
	return false;
}
