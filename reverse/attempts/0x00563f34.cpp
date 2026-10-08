// ?rva00563F34@Rva00563F34@@QAEXXZ
// partial score=0.85 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc
// ?rva00563F34@Rva00563F34@@QAEXXZ 0x00563F34 84B. Fires one FX position per
// armed gate once the frame clock has advanced past the object's stamp by the
// gate's window; the pulse reads +0x58 on the object and sets +0x54 when the
// second flag is set. Helper is FXList::doFXPos (matched).
struct Coord3D;
class Matrix3D;
class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *pos, const Matrix3D *mtx, float a, float b);
};

class ClientFrameSubsystem
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual int slot7C();
};

extern ClientFrameSubsystem *TheGameClient;

struct Rva00563F34Stamp
{
	unsigned char m_pad00[0x1C];
	Coord3D *m_pos; // +0x1C (address taken)
};

class Rva00563F34
{
public:
	void rva00563F34();
private:
	unsigned char m_pad00;
	unsigned char m_flag0C; // +0x0C
	Rva00563F34Stamp *m_stamp; // +0x04
	unsigned char m_pad08[0x0C];
	unsigned int m_window; // +0x14
	FXList *m_fx; // +0x18
	unsigned char m_armed; // +0x1C
};

void Rva00563F34::rva00563F34()
{
	if (m_armed && m_fx)
	{
		Rva00563F34Stamp *stamp = m_stamp;
		int elapsed = TheGameClient->slot7C() - *(int *)((char *)stamp + 0x58);
		if ((unsigned int)elapsed >= m_window)
		{
			FXList::doFXPos(m_fx, (const Coord3D *)((char *)stamp + 0x1C), 0, 0.0f, 0);
			m_armed = 0;
			if (m_flag0C)
				*(int *)((char *)stamp + 0x54) = 1;
		}
	}
}
