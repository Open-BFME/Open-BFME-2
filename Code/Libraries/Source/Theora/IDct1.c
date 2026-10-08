/*
 * IDct1 -- the DC-only inverse transform belonging to the On2 VP6 decoder
 * that game.dat links.  Retail body at RVA 0x001D6C60 (48 bytes): computes
 * (InputData[0] * QuantMatrix[0] + 15) >> 5 and stores it to all 64 output
 * samples (`rep stosd` over 64 shorts).  It sits in the codec's region of the
 * image, directly ahead of the codec's MMX block routines (0x001D6C90 ..
 * 0x001D7080) and the codec dispatch at 0x001D7200, above the rowed VP6
 * units (Code/Libraries/Source/VP6, 0x001B79E0 .. 0x001C6D20) and the
 * dequant/zigzag helpers between.  VP6 descends from On2's VP3, and this
 * helper is VP3-heritage text that On2 carried into VP6.
 *
 * Text donor: libtheora 1.0alpha2, lib/idct.c, IDct1 -- Xiph.org's
 * BSD-licensed copy of the same On2 VP3 text (Copyright (c) 2002, Xiph.org
 * Foundation; COPYING in this directory is the licence that covers the text).
 * The function is identical, whitespace apart, in every libtheora 1.0alpha
 * release (alpha2/alpha3/alpha4), so "1.0alpha2" names where the text was
 * taken from, not a detected library version.
 *
 * libtheora itself is NOT linked into game.dat.  Every libtheora release
 * embeds the vendor string "Xiph.Org libTheora I ..." from toplevel.c; the
 * retail image has no "Xiph", "theora", Ogg page sync ("OggS") or Vorbis
 * string (0 hits each).  The retail body is On2 VP6 decoder code, so the
 * ledger row carries no vendored= claim; the donor is named in its note.
 */
typedef short ogg_int16_t;
typedef int ogg_int32_t;
typedef short Q_LIST_ENTRY;

void IDct1(Q_LIST_ENTRY *InputData, ogg_int16_t *QuantMatrix,
	   ogg_int16_t *OutputData)
{
	int loop;
	ogg_int16_t OutD;

	OutD = (ogg_int16_t)((ogg_int32_t)(InputData[0] * QuantMatrix[0] + 15) >> 5);

	for (loop = 0; loop < 64; loop++)
		OutputData[loop] = OutD;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva009C6360@@YAXXZ=_IDct1")
