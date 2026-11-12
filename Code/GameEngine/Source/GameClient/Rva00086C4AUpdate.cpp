// ?rva00086C4A@Rva00086C4A@@QAEXXZ @0x00086C4A 144B
// cl: /MD /DNDEBUG
// Leaf camera-path updater: ParabolicEase ratio plus Matrix3D::Lerp plus view slot 0x54 plus TheAudio slot 0x58 plus mode clear at 0x2354. Evidence: callees 0x0030E5D1 0x00713AB0 rowed; TheAudio extern in use; offsets 0x104 0x13C 0x16C 0x19C 0x1A0 0x1A4 0x2354; prev 0x00086B2C next 0x00086CDA.
typedef float Real;

#include "../../Include/Common/ParabolicEase.h"

#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"

class Rva00086C4AView
{
public:
	virtual void _v00();
	virtual void _v01();
	virtual void _v02();
	virtual void _v03();
	virtual void _v04();
	virtual void _v05();
	virtual void _v06();
	virtual void _v07();
	virtual void _v08();
	virtual void _v09();
	virtual void _v10();
	virtual void _v11();
	virtual void _v12();
	virtual void _v13();
	virtual void _v14();
	virtual void _v15();
	virtual void _v16();
	virtual void _v17();
	virtual void _v18();
	virtual void _v19();
	virtual void _v20();
	virtual void _v21(Matrix3D *m);
};

#include "../../Include/Common/GameAudio.h"

extern AudioManager *TheAudio;

class Rva00086C4A
{
public:
	void rva00086C4A();
private:
	char m_pad0[0x104];
	Rva00086C4AView *m_view;
	char m_pad108[0x13C - 0x108];
	Matrix3D m_a;
	Matrix3D m_b;
	int m_total;
	int m_cur;
	ParabolicEase m_ease;
	char m_pad1AC[0x2354 - 0x1AC];
	int m_mode;
};

void Rva00086C4A::rva00086C4A()
{
	if (m_cur <= m_total) {
		float denom = (float)m_total;
		float num = (float)m_cur;
		float ratio = m_ease(num / denom);
		Matrix3D tmp;
		Matrix3D::Lerp(m_a, m_b, ratio, tmp);
		m_view->_v21(&tmp);
		++m_cur;
		if (TheAudio != 0)
			TheAudio->slot22();
	}
	if (m_cur >= m_total)
		m_mode = 0;
}
