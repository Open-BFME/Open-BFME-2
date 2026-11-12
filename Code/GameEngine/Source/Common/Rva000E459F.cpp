// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva000E459F@Rva000E459F@@QAE_NXZ retail 0x000E459F 315B
// Evidence: chain from 0x00272C9E Drawable::rva00272C9E plus pin getTransformMatrix; callers 0x000E5B57; matrix at +0x50 floats +0x84 +0x88 flag +0x98 Drawable +0x2C
#include "../../../Libraries/Source/WWVegas/WWMath/Matrix3DData.h"
static __forceinline float &matrixComponent(Matrix3D &m,int row,int col) { return (&m.Row[row].X)[col]; }
static __forceinline const float &matrixComponent(const Matrix3D &matrix,int row,int col) { return (&matrix.Row[row].X)[col]; }


#include "../../Include/GameClient/Drawable.h"

#include "ascii_string.h"

#include "../../Include/Common/Rva0055A88BDwordField.h"

class Rva000E459F
{
public:
	bool rva000E459F();
	void rva000E46DA(Drawable *d, const AsciiString &a1, const AsciiString &secondName, bool b82, bool b81);
private:
	char m_pad00[0x2C];
	Drawable *m_2C;
	char m_pad30[0x1C];
	int m_4C;
	Matrix3D m_50;
	bool m_80;
	bool m_81;
	bool m_82;
	char m_pad83[1];
	float m_84;
	float m_88;
	AsciiString m_8C;
	AsciiString m_90;
	char m_pad94[4];
	int m_98;
	bool m_9C;
};

bool Rva000E459F::rva000E459F()
{
	if (!m_2C || m_98 != 1)
		return false;
	bool changed = false;
	float level;
	if (m_88 != 0.0f) {
		level = m_84 + m_88;
		if (level < 0.0f)
			level = 0.0f;
		if (level > 1.0f)
			level = 1.0f;
	} else {
		level = m_2C->rva00272C9E(0);
		const Matrix3D *matrix3D = m_2C->getTransformMatrix();
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (matrixComponent(m_50,i,j) != matrixComponent(*matrix3D,i,j))
					goto copy_mat;
			}
		}
		goto have_v;
	copy_mat: {
		const int *s = (const int *)m_2C->getTransformMatrix();
		int *d = (int *)&m_50;
		d[0] = s[0];
		d[1] = s[1];
		d[2] = s[2];
		d[3] = s[3];
		d[4] = s[4];
		d[5] = s[5];
		d[6] = s[6];
		d[7] = s[7];
		d[8] = s[8];
		d[9] = s[9];
		d[10] = s[10];
		d[11] = s[11];
		changed = true;
	}
	have_v:;
	}
	if (m_84 != level) {
		m_84 = level;
		changed = true;
	}
	return changed;
}

void Rva000E459F::rva000E46DA(Drawable *drawable, const AsciiString &asciiString, const AsciiString &secondName, bool b82, bool b81)
{
	m_2C = drawable;
	int fieldValue;
	if (drawable)
		fieldValue = ((Rva0055A88BDwordField *)drawable)->get();
	else
		fieldValue = 0;
	m_4C = fieldValue;
	m_8C = asciiString;
	m_90 = secondName;
	m_80 = (drawable != 0);
	m_81 = b81;
	m_82 = b82;
	m_9C = 0;
}
