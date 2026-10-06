// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?rva0029766B@Rva0029766B@@QAEXPBUCoord3D@@@Z 0x0029766B 25B evidence: runs 0x00291C20 on this, then Object teleport 0x0029660C with the position and 0; caller 0x004AFA6B
// 0x00291C20 is the status-0x33 refresh pinned as BfmeThingTFB::bfmeOneTFB (donor sweep), not
// SimpleObjectIterator::reset: that pin was read back from the refuted firstWithNumeric placement at
// 0x00291C84 (reverse/deleted_rows.csv). Matrix3D sibling: Object::rva00291C84 (ObjectRefreshThenSetTransform.cpp).
struct Coord3D;
class Object
{
public:
	void rva0029660C(const Coord3D *pos, int i);
};
// Donor-swept pin for 0x00291C20 (BFME 1 BfmeConv1312 placement).
class BfmeThingTFB
{
public:
	void bfmeOneTFB();
};
class Rva0029766B
{
public:
	void rva0029766B(const Coord3D *pos);
};
void Rva0029766B::rva0029766B(const Coord3D *pos)
{
	((BfmeThingTFB *)this)->bfmeOneTFB();
	((Object *)this)->rva0029660C(pos, 0);
}
