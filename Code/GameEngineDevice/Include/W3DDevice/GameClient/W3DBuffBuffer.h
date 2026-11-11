// W3DBuffBuffer: canonical declarations for the members 4 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_W3DBUFFBUFFER_H
#define CANONICAL_W3DBUFFBUFFER_H

struct BuffInfoView;
class Drawable;
class RenderInfoClass;
class TBuff;

class W3DBuffBuffer
{
public:
	TBuff *addBuff(Drawable *draw, const BuffInfoView *info);
	void allocateBuffBuffers();
	void rva000D28FA(RenderInfoClass &rinfo, bool flag);
};

#endif // CANONICAL_W3DBUFFBUFFER_H
