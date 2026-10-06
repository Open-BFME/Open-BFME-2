// cl: /Oy- /DNDEBUG /MD /GX
// ?rva0056C7F1@Rva0056C7F1@@QAEXPAUFloatPair@@00@Z @0x0056C7F1 170B: thiscall
// with 3 stack args (ret 0xC). Scales this+0x30/+0x34 int pairs (+0x24/+0x28)
// by the float pair from the TheRva00222A8BTarget virtual at +0x3C into a and
// b (zero when the source is null), then stores the componentwise max into
// out. Callers at 0x0056CAAF/0x0056CD00 pass three stack FloatPairs.
// Structural inference: the max is written b > a ? b : a, which keeps b's
// operand first in comiss and selects with cmovbe as retail does.
struct FloatPair
{
	float x;
	float y;
};
struct IntPair
{
	int pad[9];
	int v24;
	int v28;
};
struct ScalePair
{
	float x;
	float y;
};
class Rva00222A8BTarget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual ScalePair *v15();
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
class Rva0056C7F1
{
public:
	void rva0056C7F1(FloatPair *a, FloatPair *b, FloatPair *out);
	char m_pad[0x30];
	IntPair *m_30;
	IntPair *m_34;
};
void Rva0056C7F1::rva0056C7F1(FloatPair *a, FloatPair *b, FloatPair *out)
{
	ScalePair *scale = TheRva00222A8BTarget->v15();
	if (m_30 != 0) {
		a->x = (float)m_30->v24 * scale->x;
		a->y = (float)m_30->v28 * scale->y;
	} else {
		a->x = 0.0f;
		a->y = 0.0f;
	}
	if (m_34 != 0) {
		b->x = (float)m_34->v24 * scale->x;
		b->y = (float)m_34->v28 * scale->y;
	} else {
		b->x = 0.0f;
		b->y = 0.0f;
	}
	float *px;
	if (b->x > a->x)
		px = &b->x;
	else
		px = &a->x;
	out->x = *px;
	float *py;
	if (b->y > a->y)
		py = &b->y;
	else
		py = &a->y;
	out->y = *py;
}
