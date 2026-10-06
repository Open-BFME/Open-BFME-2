// cl: /DNDEBUG /MD

// ?GadgetButtonGetData@@YAPAXPAVGameWindow@@@Z, retail 0x00327D56 (24B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetPushButton.cpp
// (BFME1 0x004BBEE0). PushButtonData keeps its ZH field order up to userData;
// winGetUserData resolves through the ledger (no new pins). Trimmed to the
// placed getter; the 11 siblings are declared-only here.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int Color;

struct PushButtonData
{
	UnsignedByte drawClock;
	Int percentClock;
	Color colorClock;
	Bool drawBorder;
	Color colorBorder;
	void *userData;
};

class WinInstanceData
{
public:
	unsigned char m_pad[8];
	unsigned int m_state;
};

class GameWindow
{
public:
	void *winGetUserData();
	WinInstanceData *winGetInstanceData();
	unsigned int winSetStatus(unsigned int);
	unsigned int winClearStatus(unsigned int);
};

#ifndef NULL
#define NULL 0
#endif

// ?GadgetButtonGetData@@YAPAXPAVGameWindow@@@Z
void *GadgetButtonGetData(GameWindow *button)
{
	if (button == NULL)
		return NULL;

	PushButtonData *buttonData = (PushButtonData *)button->winGetUserData();
	if (buttonData == NULL)
		return NULL;

	return buttonData->userData;
}

// ?GadgetCheckLikeButtonIsChecked@@YA_NPAVGameWindow@@@Z, retail 0x00327C9B (30B).
// Selected state is bit 2 of WinInstanceData::m_state (+0x08).
Bool GadgetCheckLikeButtonIsChecked(GameWindow *button)
{
	if (button == NULL)
		return 0;

	WinInstanceData *instData = button->winGetInstanceData();
	if (instData == NULL)
		return 0;

	return (instData->m_state >> 2) & 1;
}

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

// Clean BFME1 donor6d9434269164392c5ba62aaa7c15a86b5b020d76.
// Native327CB9/69 calls rowed instance/status methods and changes state+8 bit4;
// donor supplies the check-like semantic names. Status mask80000 is native.
void GadgetButtonEnableCheckLike( GameWindow *g, Bool makeCheckLike, Bool initiallyChecked )
{

	// sanity
	if( g == NULL )
		return;

	// get inst data
	WinInstanceData *instData = g->winGetInstanceData();
	if( instData == NULL )
		return;

	// make it check like
	if( makeCheckLike )
		g->winSetStatus( 0x00080000 );
	else
		g->winClearStatus( 0x00080000 );

	// set the initially checked "state"
	if( initiallyChecked )
		instData->m_state |= 4;
	else
		instData->m_state &= ~4;

}  // end GadgetButtonEnableCheckLike
