// The six forwarding bodies load the RegionAwardMovieClip::Impl pointer at
// offset 4. The preceding word is opaque in this view.
#ifndef CANONICAL_RVA005ED976_H
#define CANONICAL_RVA005ED976_H

#include "RegionAwardMovieClip.h"

class Image;
class UnicodeString;

class Rva005ED976
{
public:
	void SetRegionBonusText(int index, const UnicodeString &text);
	void SetUnitCount(int index, int value);
	void rva005ED5BB(int index, const Image *image);
	void rva005ED5EB();
	void rva005ED849(int index, int color);
	void rva005ED851(int index, int value);
	void rva005ED976(const UnicodeString &text);
	void selectPlayer(int xfer);
	void setPlayerName(int index, const UnicodeString &name);

private:
	char m_prefix[4];
	StrategicHUD::RegionAwardMovieClip::Impl *m_impl;
};

typedef char Rva005ED976SizeCheck[sizeof(Rva005ED976) == 8 ? 1 : -1];

#endif // CANONICAL_RVA005ED976_H
