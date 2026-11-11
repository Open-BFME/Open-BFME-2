// Rva005ED976: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA005ED976_H
#define CANONICAL_RVA005ED976_H

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
};

#endif // CANONICAL_RVA005ED976_H
