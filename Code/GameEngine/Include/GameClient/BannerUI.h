// BannerUI: canonical declarations for the members 5 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BANNERUI_H
#define CANONICAL_BANNERUI_H

class AsciiString;

class BannerUI
{
public:
	const AsciiString &GetBannerIconImageName(const AsciiString &);
	void Hide(bool on);
	void SetBannerSlotXOffset(unsigned int index, float value);
};

#endif // CANONICAL_BANNERUI_H
