// cl: /MD /EHsc /DNDEBUG
//
// ??1Rva00508E87@@UAE@XZ retail 0x00508E87 56B
// Novtable derived of Rva00507823 base rowed at 0x00507823. Destroys
// 12B vector at +0x128 via pinned ??1RvaVecAscii at 0x0002CC70 EH state
// 0 then calls base dtor. No derived vptr store novtable same as
// Rva00508CF7 0x00508CF7 precedent. Evidence: chain from base plus
// caller deleting 0x00508E6B.
class RvaVecAscii
{
public:
	~RvaVecAscii();
private:
	int m_x[3];
};

class Rva00507823
{
public:
	virtual ~Rva00507823();
private:
	unsigned char m_pad[0x128 - 4];
};

class __declspec(novtable) Rva00508E87 : public Rva00507823
{
public:
	virtual ~Rva00508E87();
private:
	RvaVecAscii m_vec128;
};

Rva00508E87::~Rva00508E87()
{
}
