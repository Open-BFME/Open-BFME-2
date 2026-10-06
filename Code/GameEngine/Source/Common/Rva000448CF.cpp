// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva000448CF@Rva000448CF@@QAEXMMMMMK@Z @ 0x000448CF (89B).
// Table-slot forwarder that draws a line via Render2DClass::Add_Line.
// Evidence: ref table slot 0x007C3D5C with forwarder neighbours, ecx+0x168
// target like VslotSizedDirectForwarders (prev 0x000448C4 same +0x168),
// ret 0x18 six stack args, float/int annotation (movss/fld/push), callee
// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MK@Z pin at 0x00042A4D taking
// (Vector2,Vector2,float,width ulong color), byte flag at target+0x48.
class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

class Render2DClass
{
public:
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, unsigned long color);
	char m_pad[0x48];
	unsigned char m_ready;
};

class Rva000448CF
{
public:
	void rva000448CF(float x1, float y1, float x2, float y2, float width, unsigned long color);
private:
	char m_lead[0x168];
	Render2DClass *m_target;
};

void Rva000448CF::rva000448CF(float x1, float y1, float x2, float y2, float width, unsigned long color)
{
	m_target->m_ready = 0;
	m_target->Add_Line(Vector2(x1, y1), Vector2(x2, y2), width, color);
}
