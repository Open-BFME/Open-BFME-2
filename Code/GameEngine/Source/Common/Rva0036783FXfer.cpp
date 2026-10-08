// cl: /MD /Ireference/shims/moduledata
//
// ?xfer@GiantBirdAttackMoveToState@@MAEXPAVXfer@@@Z, retail 0x0036788E, 72 bytes.
//
// Slot 3 (offset 0xC) of vtable 0x00817548 (GiantBirdAttackMoveToState; dtor in
// Rva0036783FDtor.cpp). Version1 via rowed 0x000053EE then base
// Rva0055CA8A::xfer via rowed 0x0055CA8A then IsLightCRC guard then int at
// +0x2C via Xfer slot 0x7C then Snapshot at +0x28 via slot 0x30 then
// CommandSourceType at +0x24 via rowed XferCommandSourceType 0x00305C02.
// Layout: State base 0x20 plus bool at +0x20 (base xfer) plus ints at +0x24
// and +0x2C plus Snapshot pointer at +0x28. Precedent Rva00367647Xfer.cpp
// (int 0x7C bool 0x90) and Rva0055CA8AXfer.cpp (State plus m_20).
class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class DamageInfo;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

#include "Common/Snapshot.h"

class StateMachine;

class State
{
public:
	State(StateMachine *machine, unsigned int hash);
	virtual ~State();

	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitionsFirst;
	void *m_transitionsLast;
	StateMachine *m_machine;
	bool m_tail1C;
	char m_pad1D[0x20 - 0x1D];
};

class Rva0055CA8A : public State
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	bool m_20;
};

class GiantBirdAttackMoveToState : public Rva0055CA8A
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_24;
	Snapshot *m_28;
	int m_2C;
};

void XferCommandSourceType(Xfer *xfer, int *value);

void GiantBirdAttackMoveToState::xfer(Xfer *xfer)
{
	xfer->Version1();
	Rva0055CA8A::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_2C;
	*xfer == *m_28;
	XferCommandSourceType(xfer, &m_24);
}
