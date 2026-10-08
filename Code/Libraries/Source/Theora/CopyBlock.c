/*
 * CopyBlock -- an 8x8 block copy belonging to the On2 VP6 decoder that
 * game.dat links.  Retail body at RVA 0x001B7F30 (142 bytes): copies eight
 * rows of eight bytes using the supplied source/destination stride, fully
 * unrolled.  It sits in the codec's region of the image, between the rowed
 * VP6 units (Code/Libraries/Source/VP6, 0x001B79E0 GetQuantizedCoeffsMSE_RD
 * .. 0x001C6D20 VP6_EncodeValue) and the VP6 four-tap filter at 0x001B8050,
 * with the 12x12 block copy at 0x001B7FC0 next to it.  VP6 descends from
 * On2's VP3, and this helper is VP3-heritage text that On2 carried into VP6.
 *
 * Text donor: libtheora 1.0alpha2, lib/dct_decode.c, CopyBlock -- Xiph.org's
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
typedef unsigned int ogg_uint32_t;

void CopyBlock(unsigned char *src, unsigned char *dest, unsigned int srcstride)
{
	unsigned char *s = src;
	unsigned char *d = dest;
	unsigned int stride = srcstride;
	int j;

	for (j = 0; j < 8; j++) {
		((ogg_uint32_t *)d)[0] = ((ogg_uint32_t *)s)[0];
		((ogg_uint32_t *)d)[1] = ((ogg_uint32_t *)s)[1];
		s += stride;
		d += stride;
	}
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva009A74D0@@YAXXZ=_CopyBlock")
