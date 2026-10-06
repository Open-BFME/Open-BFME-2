// cl: /EHsc /MD
// ?rva0042C7B1@Rva0042C7B1@@QAEHPBURva0042C083Param@@H@Z @0x0042C7B1 47B via mouse-gated setter forward
// Evidence: TheMouse at 0x009FDCA0 field +0x4FA4 slot 0x4C plus call 0x0042C083 via +0x8; caller 0x0042C8C6; chain from 0x0042C083
class Mouse
{
public:
	virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
	virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
	virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
	virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
	virtual void m16(); virtual void m17(); virtual void m18();
	virtual void m19(int x);
	char m_pad[0x4FA0];
	int m_4FA4;
};
extern Mouse *TheMouse;

struct Rva0042C083Param
{
	int m_00;
	int m_04;
};
class Rva0042C083
{
public:
	void rva0042C083(const Rva0042C083Param *p);
};

class Rva0042C7B1
{
public:
	int rva0042C7B1(const Rva0042C083Param *p, int unused);
private:
	char m_pad00[8];
	Rva0042C083 *m_08;
};

int Rva0042C7B1::rva0042C7B1(const Rva0042C083Param *p, int unused)
{
	(void)unused;
	if (TheMouse && TheMouse->m_4FA4 != 2)
		TheMouse->m19(2);
	m_08->rva0042C083(p);
	return 0;
}
