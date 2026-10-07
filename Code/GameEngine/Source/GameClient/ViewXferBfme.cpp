// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD -ICode/Libraries/Include/Lib
// BFME2 View::xfer, retail RVA 0x0025F020 (749 bytes).
// Target evidence: View vftable 0x00BF6178 slot 3 (inherited at 0x00BC7568
// slot 3); slots 0x54/0xFC/0x100/0x118 are the rowed View::lookAt,
// View::setAngle, the angle getter and View::getPosition; XferObjectID and
// XferDrawableID are rowed callees; list nodes are 0x30 bytes and serialize
// through the rowed Rva0025ECFC::rva0025ECFC.
// Donor: BFME1 1399ad37 game/GameEngine/Source/GameClient/ViewXferBfme.cpp
// (version 3 layout through View+0xB0); Zero Hour View::xfer supplies the
// angle/position/lookAt prologue. Field and Xfer slot names are donor labels
// or slot offsets, not target facts.
typedef unsigned char UnsignedByte;

struct XferVersionInfo
{
	XferVersionInfo(UnsignedByte v, UnsignedByte c) : version(v), currentVersion(c) {}
	UnsignedByte version;
	UnsignedByte currentVersion;
};

#include "Coord3D.h"

enum ObjectID { INVALID_ID = 0 };

class Xfer
{
public:
	virtual void slot00();
	virtual bool isLoading();
	virtual void slot08();
	virtual bool isLightCRC();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void xferUser(void *data, int size);
	virtual void xferVersion(XferVersionInfo *version);
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void xferSlot50(void *value);
	virtual void slot54();
	virtual void slot58();
	virtual void xferSlot5C(void *value);
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void xferReal(float *value);
	virtual void slot74();
	virtual void slot78();
	virtual void xferInt(int *value);
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void xferBool(bool *value);
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);
void XferDrawableID(Xfer *xfer, int *value);

struct BigIface0025ECFC;

class Rva0025ECFC
{
public:
	Rva0025ECFC() : m_next(0), m_04(0) {}
	void rva0025ECFC(BigIface0025ECFC *iface);

	Rva0025ECFC *m_next;
	int m_04;
	int m_08;
	char m_0C[0x14 - 0x0C];
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
};

class View
{
public:
	virtual ~View();
	virtual void crc(Xfer *xfer);
	virtual void slot08();
protected:
	virtual void xfer(Xfer *xfer);
public:
	virtual void loadPostProcess();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void lookAt(const Coord3D *o);
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual void slotC0();
	virtual void slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void slotD4();
	virtual void slotD8();
	virtual void slotDC();
	virtual void slotE0();
	virtual void slotE4();
	virtual void slotE8();
	virtual void slotEC();
	virtual void slotF0();
	virtual void slotF4();
	virtual void slotF8();
	virtual void setAngle(float angle);
	virtual float getAngle();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10C();
	virtual void slot110();
	virtual void slot114();
	virtual void getPosition(Coord3D *pos);

	unsigned char m_padding04[0x14];
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	float m_bfme28;
	float m_bfme2c;
	float m_bfme30;
	float m_bfme34;
	float m_bfme38;
	float m_bfme3c;
	float m_bfme40;
	bool m_bfme44;
	unsigned char m_padding45[3];
	float m_bfme48;
	float m_bfme4c;
	float m_bfme50;
	float m_bfme54;
	ObjectID m_bfme58;
	int m_bfme5c;
	int m_bfme60;
	float m_bfme64;
	float m_bfme68;
	float m_bfme6c;
	float m_bfme70;
	bool m_bfme74;
	bool m_bfme75;
	bool m_bfme76;
	unsigned char m_padding77;
	int m_bfme78[2];
	Rva0025ECFC *m_bfme80;
	bool m_bfme84;
	unsigned char m_padding85[3];
	ObjectID m_bfme88;
	int m_bfme8c[3];
	float m_bfme98;
	float m_bfme9c;
	float m_bfmea0;
	float m_bfmea4;
	float m_bfmea8;
	float m_bfmeac;
	float m_bfmeb0;
};

void View::xfer(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersionInfo version(1, 3);
	xfer->xferVersion(&version);

	float angle = getAngle();
	xfer->xferReal(&angle);
	setAngle(angle);

	Coord3D viewPos;
	getPosition(&viewPos);
	xfer->xferReal(&viewPos.x);
	xfer->xferReal(&viewPos.y);
	xfer->xferReal(&viewPos.z);
	lookAt(&viewPos);

	if (version.currentVersion < 3)
	{
		xfer->xferInt(&m_bfme18);
		xfer->xferInt(&m_bfme1c);
		xfer->xferInt(&m_bfme20);
		xfer->xferInt(&m_bfme24);
	}

	if (version.currentVersion >= 2)
	{
		xfer->xferReal(&m_bfme28);
	}

	xfer->xferReal(&m_bfme2c);
	xfer->xferReal(&m_bfme30);
	xfer->xferReal(&m_bfme34);
	xfer->xferReal(&m_bfme38);
	xfer->xferReal(&m_bfme40);
	xfer->xferBool(&m_bfme44);
	xfer->xferReal(&m_bfme48);
	xfer->xferReal(&m_bfme4c);
	xfer->xferReal(&m_bfme50);
	xfer->xferReal(&m_bfme54);

	XferObjectID(xfer, &m_bfme58);
	XferDrawableID(xfer, &m_bfme5c);
	xfer->xferUser(&m_bfme60, 4);
	xfer->xferReal(&m_bfme64);
	xfer->xferReal(&m_bfme68);

	if (version.currentVersion < 3)
	{
		xfer->xferReal(&m_bfme6c);
	}
	xfer->xferReal(&m_bfme70);
	xfer->xferBool(&m_bfme74);
	xfer->xferBool(&m_bfme75);
	xfer->xferBool(&m_bfme76);
	xfer->xferSlot50(&m_bfme78[0]);

	int count = 0;
	Rva0025ECFC *node;
	for (node = m_bfme80; node != 0; node = node->m_next)
		++count;
	xfer->xferInt(&count);
	if (xfer->isLoading())
	{
		for (int index = 0; index < count; ++index)
		{
			node = new Rva0025ECFC;
			node->rva0025ECFC((BigIface0025ECFC *)xfer);
			node->m_next = m_bfme80;
			m_bfme80 = node;
		}
	}
	else
	{
		for (node = m_bfme80; node != 0; node = node->m_next)
			node->rva0025ECFC((BigIface0025ECFC *)xfer);
	}
	xfer->xferBool(&m_bfme84);
	XferObjectID(xfer, &m_bfme88);
	xfer->xferSlot5C(&m_bfme8c[0]);
	xfer->xferReal(&m_bfme98);
	xfer->xferReal(&m_bfme9c);
	xfer->xferReal(&m_bfmea0);
	xfer->xferReal(&m_bfmea4);
	xfer->xferReal(&m_bfmea8);
	xfer->xferReal(&m_bfmeac);
	xfer->xferReal(&m_bfmeb0);
}
