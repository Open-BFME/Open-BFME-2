// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: forwarder at 0x1E702E (37B). Forwards (obj,b,c) with
// this to 0x1E685F, then runs obj->setTransformMatrix on the +0x68 member.
// Address-derived names; 0x1E685F types unproven.

class Matrix3D;
class Thing
{
public:
	void setTransformMatrix(const Matrix3D *m);
};
class Rva001E685F
{
public:
	void rva001E685F(int a, int b, int c);
};
class Rva001E702E
{
public:
	void rva001E702E(Thing *o, int b, int c);
private:
	char m_pad[0x68];
	char m_mat[64];
};

// ?rva001E702E@Rva001E702E@@QAEXPAVThing@@HH@Z
void Rva001E702E::rva001E702E(Thing *o, int b, int c)
{
	((Rva001E685F *)this)->rva001E685F((int)o, b, c);
	o->setTransformMatrix((const Matrix3D *)&m_mat);
}
