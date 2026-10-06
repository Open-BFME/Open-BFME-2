// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc

// ?Rva005DD6D5Apply@@YAXPAP8Rva005DE5B5@@AEXXZPAU1@1P81@AEXXZ@Z RVA 0x005DD6D5, 34B.
// Unlock lane: range-apply helper over 0x18-byte Rva005DE5B5 elements; calls
// the function pointer in ecx per element then stores it to the out slot.
// Indirect call needs no row; 0x18 stride is the Rva005DE5B5 size. Caller is
// 0x005DE96B which passes 0x005DE926 as the function; landing unblocks it.
// Free-function honest address name. Flags copy the next neighbour
// stlport_vector_stringrecord_5ddd40_allocate_copy.cpp (EBP frame, no EH).
struct Rva005DE5B5 {
	char m_data[0x18];
};
typedef void (Rva005DE5B5::*Rva005DE5B5Fn)();

void Rva005DD6D5Apply(Rva005DE5B5Fn *out, Rva005DE5B5 *first, Rva005DE5B5 *last, Rva005DE5B5Fn fn)
{
	for (; first != last; ++first)
		(first->*fn)();
	*out = fn;
}
