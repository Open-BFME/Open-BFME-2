// LargeGroupAudioGridCell: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_LARGEGROUPAUDIOGRIDCELL_H
#define CANONICAL_LARGEGROUPAUDIOGRIDCELL_H

struct Rva005C8876Grid;
struct Rva005C8876Position;

class LargeGroupAudioGridCell
{
public:
	void addToWeight(unsigned short weight);
	Rva005C8876Position getPreferredAudioPosition(Rva005C8876Grid *);
	void setOverlappedLocking(bool flag);
	void subtractFromWeight(unsigned short weight);
	void update(Rva005C8876Grid *);
};

#endif // CANONICAL_LARGEGROUPAUDIOGRIDCELL_H
