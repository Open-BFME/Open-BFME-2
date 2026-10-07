// 36-byte copy walk, retail 0x00161150, 45 bytes.
//
// Bounded-by-end-pointer walk handing each 36-byte slot to the helper at
// 0x001610F0 (unmatched; pinned here under an address-derived name). Both
// cursors advance by the retail step 0x24; the returned value is the
// advanced dest cursor. Element identity is not recovered -- Elem36 is a
// stride-sized stand-in in the ElementStrideWalks donor's own convention.

struct Elem36
{
	char m_bytes[36];
};

void gen001610F0(Elem36 *slot, const Elem36 *source);

Elem36 *rva00161150CopyWalk(Elem36 *first, Elem36 *last, Elem36 *dest)
{
	Elem36 *cursor = dest;
	for ( ; first != last; ++first)
	{
		gen001610F0(cursor, first);
		++cursor;
	}
	return cursor;
}

// 28-byte copy walk, retail 0x00689750, 45 bytes.
//
// Same shape as the Elem36 walk above: bounded-by-end-pointer walk handing
// each 28-byte slot to the helper at 0x006896F0 (rowed 66-byte pair
// construct body; pinned here under an address-derived name). Both cursors
// advance by the retail step 0x1c; the returned value is the advanced dest
// cursor. Element identity is not recovered -- Elem28 is a stride-sized
// stand-in in the ElementStrideWalks donor's own convention.

struct Elem28
{
	char m_bytes[28];
};

void gen006896F0(Elem28 *slot, const Elem28 *source);

Elem28 *rva00689750CopyWalk(Elem28 *first, Elem28 *last, Elem28 *dest)
{
	Elem28 *cursor = dest;
	for ( ; first != last; ++first)
	{
		gen006896F0(cursor, first);
		++cursor;
	}
	return cursor;
}
