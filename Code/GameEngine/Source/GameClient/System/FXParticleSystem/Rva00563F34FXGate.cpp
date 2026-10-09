// cl: /ICode/Libraries/Include /DNDEBUG /MD /EHsc /O1
// Recovered from the V2 bank (score 0.95): the bank declared the fifth
// doFXPos parameter as int; the rowed helper 0x00094C29 is mangled
// ...PBVMatrix3D@@M1@Z, whose 1 back-reference is const Coord3D* (ZH
// secondary position), and a null pointer pushes the same 0.
// ?rva00563F34@Rva00563F34@@QAEXXZ 0x00563F34 84B. Fires one FX position per
// armed gate once the frame clock has advanced past the object's stamp by the
// gate's window; the pulse reads +0x58 on the object and sets +0x54 when the
// second flag is set. Helper is FXList::doFXPos (matched).
#include "Lib/Coord3D.h"
class Matrix3D;
class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *pos, const Matrix3D *mtx, float primarySpeed, const Coord3D *secondary);
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
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual unsigned int getFrame();
};

// The real GameClient singleton uses this primary-vtable frame accessor at +0x7C.
class GameClient;
extern GameClient *TheGameClient;

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
	unsigned char m_pad00[4];
	Rva00563F34Stamp *m_stamp; // +0x04
	unsigned char m_pad08[4];
	unsigned char m_flag0C; // +0x0C
	unsigned char m_pad0D[7];
	unsigned int m_window; // +0x14
	FXList *m_fx; // +0x18
	unsigned char m_armed; // +0x1C
};

void Rva00563F34::rva00563F34()
{
	if (m_armed && m_fx)
	{
		Rva00563F34Stamp *stamp = m_stamp;
		unsigned int elapsed = reinterpret_cast<ClientFrameSubsystem *>(TheGameClient)->getFrame()
			- (unsigned int)*(int *)((char *)stamp + 0x58);
		if (elapsed >= m_window)
		{
			char *pos = (char *)stamp;
			pos += 0x1C;
			FXList::doFXPos(m_fx, (const Coord3D *)pos, 0, 0.0f, 0);
			m_armed = 0;
			if (m_flag0C)
				*(int *)((char *)m_stamp + 0x54) = 1;
		}
	}
}

// The particle-system modules below keep their system at +0x04 and fall back
// to the rowed null-system factory 0x001FCBD7 when it is unset (retail inlines
// that test at every use). The system's position copy is rowed 0x001F385A; its
// +0x124 is the frame stamp and +0x128 the fired flag.
class ParticleSystem;
ParticleSystem *Make001FCBD7();

class Rva001F385A
{
public:
	void rva001F385A(void *out);
};

struct Rva0056405CSystemView
{
	unsigned char m_pad000[0x124];
	unsigned int m_stamp; // +0x124
	int m_fired; // +0x128
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual float getGroundHeight(float x, float y, Coord3D *normal) const;
};

extern TerrainLogic *TheTerrainLogic;

// ?rva0056405C@Rva0056405C@@QAEXXZ 0x0056405C 144B: the frame-window pulse.
// Fires once the frame clock has advanced past the system's stamp by +0x38.
class Rva0056405C
{
public:
	void rva0056405C();

private:
	ParticleSystem *system() { return m_system == 0 ? Make001FCBD7() : m_system; }

	unsigned char m_pad00[4];
	ParticleSystem *m_system; // +0x04
	unsigned char m_pad08[0x1D - 0x08];
	unsigned char m_resetSystem; // +0x1D
	unsigned char m_pad1E[0x34 - 0x1E];
	FXList *m_fx; // +0x34
	unsigned int m_window; // +0x38
	unsigned char m_armed; // +0x3C
};

void Rva0056405C::rva0056405C()
{
	if (m_armed && m_fx)
	{
		unsigned int stamp = ((Rva0056405CSystemView *)system())->m_stamp;
		if (reinterpret_cast<ClientFrameSubsystem *>(TheGameClient)->getFrame() - stamp >= m_window)
		{
			Coord3D pos;
			((Rva001F385A *)system())->rva001F385A(&pos);
			FXList::doFXPos(m_fx, &pos, 0, 0.0f, 0);
			m_armed = 0;
			if (m_resetSystem)
				((Rva0056405CSystemView *)system())->m_fired = 1;
		}
	}
}

// ?rva005645FE@Rva005645FE@@QAEXXZ 0x005645FE 144B: the ground-contact pulse.
// Fires once the system's position is at or below TheTerrainLogic's ground
// height (slot 0x18) at its x/y.
class Rva005645FE
{
public:
	void rva005645FE();

private:
	ParticleSystem *system() { return m_system == 0 ? Make001FCBD7() : m_system; }

	unsigned char m_pad00[4];
	ParticleSystem *m_system; // +0x04
	unsigned char m_pad08[0x1D - 0x08];
	unsigned char m_resetSystem; // +0x1D
	unsigned char m_pad1E[0x38 - 0x1E];
	FXList *m_fx; // +0x38
	unsigned char m_pad3C[0x40 - 0x3C];
	unsigned char m_armed; // +0x40
};

void Rva005645FE::rva005645FE()
{
	Coord3D pos;
	((Rva001F385A *)system())->rva001F385A(&pos);
	if (m_armed && m_fx)
	{
		if (pos.z <= TheTerrainLogic->getGroundHeight(pos.x, pos.y, 0))
		{
			FXList::doFXPos(m_fx, &pos, 0, 0.0f, 0);
			m_armed = 0;
			if (m_resetSystem)
				((Rva0056405CSystemView *)system())->m_fired = 1;
		}
	}
}
