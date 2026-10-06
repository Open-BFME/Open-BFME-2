// cl: /MD
// ?rva0029A407@Rva0029A407@@QAEXXZ @0x0029A407 19B
// Guarded virtual slot2 clear like release-then-null; callers at 0x0029B53F
// 0x0029D9EB and jmp at 0x0029B346; unlocks 0x0029D9CA 0x0029B53C.
struct Freeable0029A407
{
	virtual ~Freeable0029A407() {}
	virtual void unk0();
	virtual void slot2();
};
class Rva0029A407
{
public:
	void rva0029A407();
	void *rva0029B53C(unsigned int flag);
private:
	Freeable0029A407 *m_0;
};
void Rva0029A407::rva0029A407()
{
	if (m_0 != 0) {
		m_0->slot2();
		m_0 = 0;
	}
}
void *Rva0029A407::rva0029B53C(unsigned int flag)
{
	rva0029A407();
	if (flag & 1)
		delete this;
	return this;
}

class RGBColor
{
public:
	int getAsInt() const;
};

class Shadow
{
public:
	void rva00330995(int color);
};

class Rva0029A41A
{
public:
	void rva0029A41A(RGBColor *color);
private:
	Shadow *m_shadow;
};

void Rva0029A41A::rva0029A41A(RGBColor *color)
{
	Shadow *shadow = m_shadow;
	if (shadow != 0) {
		int asInt = color->getAsInt();
		shadow->rva00330995(asInt);
	}
}
