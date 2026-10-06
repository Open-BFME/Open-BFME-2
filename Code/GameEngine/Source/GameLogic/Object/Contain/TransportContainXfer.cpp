// cl: /DNDEBUG /MD /GX
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// TransportContain::xfer, ported from Zero Hour's GameEngine/Source/GameLogic/
// Object/Contain/TransportContain.cpp (GeneralsMD tree vendored under
// reference/open-bfme-1/inputs/reference). Slot 3 of ??_7TransportContain.
// BFME 2 writes the version before the OpenContain base xfer (slot 3 of
// OpenContain's vftable, 0x00465EF1) and has no light-CRC early-out. Its
// fields are m_extraSlotsInUse +0x100 (int), m_frameExitNotBusy +0x104
// (UnsignedInt) and m_payloadCreated +0x10C (Bool), transferred in that
// order. Offsets come from the bodies; the names are ZH's for the same
// three fields.

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

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class OpenContain
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
	char m_unrecovered04[ 0x100 - 0x04 ];
};

class TransportContain : public OpenContain
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	Int m_extraSlotsInUse;																										///< 0x100
	UnsignedInt m_frameExitNotBusy;																						///< 0x104
	char m_unrecovered108[ 0x10C - 0x108 ];
	Bool m_payloadCreated;																										///< 0x10C
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void TransportContain::xfer( Xfer *xfer )
{

	// version
	xfer->Version1();

	// extend base class
	OpenContain::xfer( xfer );

	// extra slots in use
	*xfer == m_extraSlotsInUse;

	// frame exit not busy
	*xfer == m_frameExitNotBusy;

	// payload created
	*xfer == m_payloadCreated;

}  // end xfer
