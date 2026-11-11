// cl: /DNDEBUG /MD
//
// Retail 0x0030BC94 (26 B, RET 4): forwards its argument to the 239-byte leaf
// 0x0053841C on the member at +0x68, then calls virtual slot 10 (+0x28). Same
// shape as the rowed 0x00330ABE (VtableSlotBodiesR4.cpp: container push on +0x08,
// then slot 12). The forwarder's owner is unrecovered; its names stay
// address-derived.

struct Rva0053841CArg;
class Matrix3D;

// The leaf is QuadStrip2D's transform (Rva0053841CTransform.cpp); the argument is its Matrix3D.
#include "../../Include/Common/QuadStrip2D.h"

class Rva0030BC94
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual void changed();	// slot 10

	void transform(const Rva0053841CArg *matrix);

private:
	char m_pad04[0x68 - 0x04];
	char m_member68[4];	// +0x68
};

void Rva0030BC94::transform(const Rva0053841CArg *matrix)
{
	((QuadStrip2D *)m_member68)->rva0053841C(*(const Matrix3D *)matrix);
	changed();
}
