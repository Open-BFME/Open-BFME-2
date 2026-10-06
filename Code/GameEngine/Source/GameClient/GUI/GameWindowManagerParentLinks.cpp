// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
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
// stlport
#include "PreRTS.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindow.h"

// Clean BFME1 GameWindowManager donor6d943426; native hierarchy view only.
// Manager class declarations come from shared reference headers. Native33/33/58
// and independent GameWindow leaf walkers prove status8 and links1F8/1FC/200/204.
struct BfmeManagerWindowLinks { char opaque00[8]; unsigned status; char opaque0C[0x1EC]; BfmeManagerWindowLinks *next,*prev,*parent,*child; };
Bool GameWindowManager::isEnabled(GameWindow *win)
{
 BfmeManagerWindowLinks *w=(BfmeManagerWindowLinks *)win;
 if(w==0) return false;
 do { if((w->status&8)==0) return false; w=w->parent; } while(w);
 return true;
}
Bool GameWindowManager::isHidden(GameWindow *win)
{
 BfmeManagerWindowLinks *w=(BfmeManagerWindowLinks *)win;
 if(w==0) return true;
 do { if(w->status&0x10) return true; w=w->parent; } while(w);
 return false;
}
void GameWindowManager::addWindowToParent(GameWindow *window,GameWindow *parent)
{
 BfmeManagerWindowLinks *w=(BfmeManagerWindowLinks *)window;
 BfmeManagerWindowLinks *p=(BfmeManagerWindowLinks *)parent;
 if(p) { w->prev=0; w->next=p->child; if(p->child) p->child->prev=w; p->child=w; w->parent=p; }
}
