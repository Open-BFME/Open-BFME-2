// cl: /DNDEBUG /MD
//
// 8-byte vector copy pair, retail 0x00254D65 (47 bytes, rowed as
// ?dup_00254D65) plus its 0x00255CFA forwarder (29 bytes, rowed as
// ?dup_00255CFA). The loop has a single E8 caller (the forwarder); the
// forwarder has 6 callers image-wide (0x1D9BE4/0x1DA0C0/0x1DA0DE/0x207F21/
// 0x317F1D/0x317F3B), including the StructureCollapseUpdateModuleData ctor
// 0x257A5E via 0x207F0D. Element type unproven: the per-element call folds
// to the same bytes as FXBoneInfo::operator= (rowed at 0x1D9990), whose
// spelling this TU reuses for resolution with zero new pins; the dup labels
// claim the bytes and assert no identity. Shape levers: while-loop (not
// do-while) homes the counter late (push esi after the jle), and the two
// trailing dummy args (tag pointer plus zero) ride dead above the frame.

struct FXBoneInfo
{
	int m_a;
	int m_b;
	FXBoneInfo &operator=(const FXBoneInfo &other);
};

FXBoneInfo *copyEightByteRange(FXBoneInfo *first, FXBoneInfo *last, FXBoneInfo *dest, void *tag, int extra)
{
	int count = (int)((char *)last - (char *)first) >> 3;
	while (count > 0) {
		*dest = *first;
		++first;
		++dest;
		--count;
	}
	return dest;
}

FXBoneInfo *forwardEightByteRange(FXBoneInfo *first, FXBoneInfo *last, FXBoneInfo *dest, void *ignored)
{
	char tag;
	return copyEightByteRange(first, last, dest, &tag, 0);
}
