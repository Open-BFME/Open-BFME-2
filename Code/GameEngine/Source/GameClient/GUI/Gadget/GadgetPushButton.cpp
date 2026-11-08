// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// platformsdk

// ?GadgetButtonGetData@@YAPAXPAVGameWindow@@@Z, retail 0x00327D56 (24B).
// Ported from Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/Gadget/GadgetPushButton.cpp
// (BFME1 0x004BBEE0). PushButtonData keeps its ZH field order up to userData;
// winGetUserData resolves through the ledger. The native display-string
// toggle below extends the same PushButtonData view through +0x30.

#include <windows.h>

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int Color;

class DisplayString;
#include "../../../../Include/GameClient/DisplayStringManager.h"
extern DisplayStringManager *TheDisplayStringManager;

struct PushButtonData
{
	UnsignedByte drawClock;
	Int percentClock;
	Color colorClock;
	Bool drawBorder;
	Color colorBorder;
	void *userData;
	char pad18[0x28-0x18];
	bool flag28;
	int value2C;
	DisplayString *displayString30;
};

#include "../../../../Include/GameClient/Bfme2GameWindow.h"


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
void GadgetButtonEnableCheckLike( GameWindow *gameWindow, Bool makeCheckLike, Bool initiallyChecked )
{

	// sanity
	if( gameWindow == NULL )
		return;

	// get inst data
	WinInstanceData *instData = gameWindow->winGetInstanceData();
	if( instData == NULL )
		return;

	// make it check like
	if( makeCheckLike )
		gameWindow->winSetStatus( 0x00080000 );
	else
		gameWindow->winClearStatus( 0x00080000 );

	// set the initially checked "state"
	if( initiallyChecked )
		instData->m_state |= 4;
	else
		instData->m_state &= ~4;

}  // end GadgetButtonEnableCheckLike

// Native327D86..327DD8 and WB1122D00..1122D8B agree on both guards,
// flag28/value2C stores and the manager factory/free slots38/3C. Native
// PushButton destruction328639 frees the same display string at30.
// The method name and flag semantics are unknown; retain the RVA spelling.
void Rva00327D86Update(GameWindow *button,bool enabled)
{
 if (!button) return;
 PushButtonData *data=(PushButtonData *)button->winGetUserData();
 if (!data) return;
 data->flag28=enabled;
 data->value2C=0;
 if(enabled) {
  if(!data->displayString30) data->displayString30=TheDisplayStringManager->newDisplayString();
 } else {
  if(data->displayString30) {
   TheDisplayStringManager->freeDisplayString(data->displayString30);
   data->displayString30=0;
  }
 }
}
