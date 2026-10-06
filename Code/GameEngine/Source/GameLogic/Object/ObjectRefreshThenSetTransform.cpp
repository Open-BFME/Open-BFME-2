// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00291C84@Object@@QAEXPBVMatrix3D@@@Z at retail 0x00291C84 (23B).
// Target evidence: the body runs 0x00291C20 on this (that callee opens with
// Object::testStatus(0x33) on its this and clears the same status through
// Object::setStatus at its end) and then Object::setTransformMatrix 0x0028D412
// (whose body opens with the rowed Thing::setTransformMatrix on this) with the
// stack argument. It is the Matrix3D sibling of 0x0029766B, which runs the
// same 0x00291C20 and then 0x0029660C with a position. Name by address; no
// direct caller or pointer to it in the image.
// First rowed as ?firstWithNumeric@SimpleObjectIterator@@QAEPAVObject@@PAM@Z
// by a masked shape search (see reverse/deleted_rows.csv): the reset/next
// pins that placement read back are Object methods, not iterator ones.
class Matrix3D;

// Donor-swept pin for 0x00291C20 (BFME 1 BfmeConv1312 placement).
class BfmeThingTFB
{
public:
	void bfmeOneTFB();
};

class Object
{
public:
	void setTransformMatrix(const Matrix3D *mtx);
	void rva00291C84(const Matrix3D *mtx);
};

void Object::rva00291C84(const Matrix3D *mtx)
{
	((BfmeThingTFB *)this)->bfmeOneTFB();
	setTransformMatrix(mtx);
}
