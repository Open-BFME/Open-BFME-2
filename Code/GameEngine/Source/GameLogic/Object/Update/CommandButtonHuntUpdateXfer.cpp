// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
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

// CommandButtonHuntUpdate::xfer, ported from Zero Hour's GameEngine/Source/
// GameLogic/Object/Update/CommandButtonHuntUpdate.cpp (GeneralsMD tree vendored
// under reference/open-bfme-1/inputs/reference). Slot 3 of
// ??_7CommandButtonHuntUpdate. BFME 2 Xfer spelling: UpdateModule::xfer first,
// the light-CRC early-out, Version1, then the button name (+0x20) through
// operator==(AsciiString&). On load the button pointer (+0x24) is
// re-resolved from the object's command set; a BFME 2 command set holds 32
// buttons. Callees are ZH's: Object::getCommandSetString (0x00290E67),
// ControlBar::findCommandSet (0x0031D5F8) and CommandSet::getCommandButton
// (0x00409EE8). CommandButton keeps its name at +0x10.

#include "ascii_string.h"

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

class CommandButton
{
public:
	const AsciiString &getName( void ) const { return m_name; }
private:
	char m_unrecovered00[ 0x10 ];
	AsciiString m_name;																												///< 0x10
};

enum { MAX_COMMANDS_PER_SET = 32 };

class CommandSet
{
public:
	const CommandButton *getCommandButton( Int i ) const;
};

// ControlBar::findCommandSet (0x0031D5F8) is rowed as Rva0031D5F8::rva0031D5F8.
class Rva0031D5F8
{
public:
	void *rva0031D5F8( const AsciiString *name );
};
class ControlBar;
extern ControlBar *TheControlBar;

class Object
{
public:
	const AsciiString *rva00290E67( void ) const;	// getCommandSetString, rowed by address
};

class UpdateModule
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer( Xfer *xfer );
protected:
	Object *getObject( void ) const { return m_object; }
private:
	void *m_moduleData;																												///< 0x04
	Object *m_object;																													///< 0x08
	char m_unrecovered0C[ 0x20 - 0x0C ];
};

class CommandButtonHuntUpdate : public UpdateModule
{
protected:
	virtual void xfer( Xfer *xfer );
private:
	AsciiString m_commandButtonName;																					///< 0x20
	const CommandButton *m_commandButton;																			///< 0x24
};

// ------------------------------------------------------------------------------------------------
/** Xfer method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
void CommandButtonHuntUpdate::xfer( Xfer *xfer )
{

	// extend base class
	UpdateModule::xfer( xfer );

	if( xfer->IsLightCRC() )
		return;

	// version
	xfer->Version1();

	// command button name
	*xfer == m_commandButtonName;

	// command button
	if( xfer->IsLoading() )
	{

		m_commandButton = 0;
		// BFME 2 keeps the out-of-line StringBase<char>::isEmpty call here
		if( ((const StringBase<char> *)&m_commandButtonName)->isEmpty() == false )
		{
			const CommandSet *commandSet = (const CommandSet *)((Rva0031D5F8 *)TheControlBar)->rva0031D5F8( getObject()->rva00290E67() );
			if( commandSet )
			{
				for( Int i = 0; i < MAX_COMMANDS_PER_SET; i++ )
				{
					const CommandButton *commandButton = commandSet->getCommandButton(i);
					if( commandButton && commandButton->getName() == m_commandButtonName )
					{
						m_commandButton = commandButton;
						break;
					}
				}
			}
		}

	}  // end if

}  // end xfer
