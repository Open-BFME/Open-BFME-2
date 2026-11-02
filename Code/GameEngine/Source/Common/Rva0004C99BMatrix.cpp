// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ?rva0004C99B@Rva0004C99B@@QAEXXZ @0x0004C99B 102B
// Matrix setup: initializes a 12-float buffer (identity-ish, 1.0 at
// 0/5/10) then runs the 0x00713290 matrix method on a second buffer and
// the same-this 0x0023A1BB helper.
// Row spellings: 0x00713290 is Matrix3D::Get_Inverse(Matrix3D &) const and
// 0x0023A1BB is the virtual GameClient::init (called directly).
class Matrix3D
{
public:
	void Get_Inverse(Matrix3D &inverse) const;
};
#include "../../Include/GameClient/GameClientClass.h"
class Rva0004C99B
{
public:
	void rva0004C99B();
private:
	char m_pad[0];
};
void Rva0004C99B::rva0004C99B()
{
	float buf1[12];
	float buf2[12];
	buf1[0] = 1.0f;
	buf1[1] = 0.0f;
	buf1[2] = 0.0f;
	buf1[3] = 0.0f;
	buf1[4] = 0.0f;
	buf1[5] = 1.0f;
	buf1[6] = 0.0f;
	buf1[7] = 0.0f;
	buf1[8] = 0.0f;
	buf1[9] = 0.0f;
	buf1[10] = 1.0f;
	buf1[11] = 0.0f;
	((const Matrix3D *)buf2)->Get_Inverse(*(Matrix3D *)buf1);
	((GameClient *)this)->GameClient::init();
}
