// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?restoreObjectToWorld@Object@@QAEXPBUCoord3D@@@Z 0x0029766B 25B. WB confirms
// restoreObjectToWorld; retail runs the internal restore then teleport(pos, 0).
// 0x00291C20 is the status-0x33 refresh pinned as BfmeThingTFB::bfmeOneTFB (donor sweep), not
// SimpleObjectIterator::reset: that pin was read back from the refuted firstWithNumeric placement at
// 0x00291C84 (reverse/deleted_rows.csv). Matrix3D sibling: Object::rva00291C84 (ObjectRefreshThenSetTransform.cpp).
struct Coord3D;
class Object
{
public:
	void rva0029660C(const Coord3D *pos, int i);
	void restoreObjectToWorld(const Coord3D *pos);
};
// Donor-swept pin for 0x00291C20 (BFME 1 BfmeConv1312 placement).
class BfmeThingTFB
{
public:
	void bfmeOneTFB();
};
void Object::restoreObjectToWorld(const Coord3D *pos)
{
	((BfmeThingTFB *)this)->bfmeOneTFB();
	((Object *)this)->rva0029660C(pos, 0);
}
