// cl: /O1 /arch:SSE /G7 /EHs-c- /ICode/Libraries/Include
// ?rva0030BE41@Rva0030BE41@@QAEXXZ @0x0030BE41 28B
// Clear QuadStrip2D at +0x68 when non-empty then virtual slot 0x28.
// Evidence: callee 0x00538931 row ?rva00538931@QuadStrip2D@@QAEXXZ erases whole vector; member QuadStrip2D at +0x68 same as callers 0x0030BC39 0x0030BC53 0x0030BC84; virtual jmp [eax+0x28] is v10 same as Rva0030BDEE precedent; no callers.
struct BfmePod16
{
	int a[4];
};

struct BfmeFloat4Record00469C61 { float x, y, z, w; };
class W3DAnimationInfo;

class QuadStrip2D
{
public:
	void rva00538931();
	void rva005389D9(const BfmeFloat4Record00469C61 &);
	void rva005389ED(int, const W3DAnimationInfo &);
	void rva00538768(int);
	void rva00538383(float);
	BfmePod16 *m_start;
	BfmePod16 *m_finish;
	BfmePod16 *m_end;
};

class Rva0030BE41
{
public:
	virtual ~Rva0030BE41();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	void rva0030BE41();
	void rva0030BC11(const BfmeFloat4Record00469C61 &);
	void rva0030BC2B(int, const W3DAnimationInfo &);
	void rva0030BC49(int);
	void rva0030BC63(float);
private:
	char m_pad[0x64];
	QuadStrip2D m_68;
};

void Rva0030BE41::rva0030BE41()
{
	QuadStrip2D &q = m_68;
	if (q.m_start != q.m_finish)
	{
		q.rva00538931();
		v10();
	}
}

// Native boundaries 30BC11..30BC2B, 30BC2B..30BC49 and 30BC49..30BC63
// each end in RET before the next entry. Each forwards to its existing
// QuadStrip2D operation at receiver+68 and then calls virtual slot+28.
// The river importer 329339 supplies the 16-byte four-float strip to the
// first wrapper; provider rows independently fix all three argument ABIs.
// Rva0030BE41 remains an opaque receiver view, not an asserted EA class.
void Rva0030BE41::rva0030BC11(const BfmeFloat4Record00469C61 &strip)
{
    m_68.rva005389D9(strip);
    v10();
}
void Rva0030BE41::rva0030BC2B(int index, const W3DAnimationInfo &strip)
{
    m_68.rva005389ED(index, strip);
    v10();
}
void Rva0030BE41::rva0030BC49(int index)
{
    m_68.rva00538768(index);
    v10();
}

// Native 30BC63..30BC94 tests scale against 1.0 before the established
// QuadStrip2D scale operation and the same slot+28 notification.
// The SSE unordered comparison also takes the update path for NaN.
void Rva0030BE41::rva0030BC63(float scale)
{
    if (scale != 1.0f)
    {
        m_68.rva00538383(scale);
        v10();
    }
}
