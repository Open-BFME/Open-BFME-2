// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ?rva00085FA8@Rva00085FA8@@QAEXPAM@Z 0x00085FA8 178B: thiscall projects two points via Camera at +0x104 and writes screen delta to out; caller 0x00087E4C
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};
class CameraClass
{
public:
	enum ProjectionResType
	{
		INSIDE_FRUSTUM,
		OUTSIDE_FRUSTUM,
		OUTSIDE_NEAR_CLIP,
		OUTSIDE_FAR_CLIP
	};
	ProjectionResType Project(Vector3 &dest, const Vector3 &ws_point) const;
};
class Rva00085FA8
{
public:
	char m_pad0[0xC];
	float m_C;
	float m_10;
	char m_pad14[0xF0];
	class CameraClass *m_104;
	char m_pad108[0x22EC];
	float m_23F4;
	float m_23F8;
	char m_pad23FC[0xC];
	float m_2408;
	void rva00085FA8(float *out);
};

void Rva00085FA8::rva00085FA8(float *out)
{
	out[0] = 0.0f;
	out[1] = 0.0f;
	Vector3 in1;
	Vector3 out1;
	in1.X = m_23F4;
	in1.Y = m_23F8;
	in1.Z = m_2408;
	if (m_104->Project(out1, in1) != 0)
		return;
	Vector3 in2;
	Vector3 out2;
	in2.X = m_C;
	in2.Y = m_10;
	in2.Z = m_2408;
	if (m_104->Project(out2, in2) != 0)
		return;
	out[0] = out2.X - out1.X;
	out[1] = out2.Y - out1.Y;
}
