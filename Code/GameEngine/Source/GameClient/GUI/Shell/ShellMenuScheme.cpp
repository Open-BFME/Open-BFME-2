// cl: /O1 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/open-bfme-1/inputs/reference/shims/stlp_nodealloc /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/Shell

// draw: BFME 1 donor 6583b3c1ff21db4a561285717028fdafc780b7db,
// game/GameEngine/Source/GameClient/GUI/Shell/ShellMenuScheme.cpp; ZH source identity.
// Target 0x00200506 (216B) traverses image/line lists at +4/+8, agreeing with
// the matched scheme constructor/destructor. Retail calls the existing BFME 2
// W3DDisplay wrappers at 0x0004D6B3 and 0x0004D664; no donor vtable slots assumed.
// Line constructor 0x002004A5 (30B) retains its previously verified store order.

// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "Common/INI.h"
#include "GameClient/ShellMenuScheme.h"
#include "GameClient/Display.h"
class W3DDisplay
{
public:
    void rva0004D6B3(Image *, float, float, float, float, int = -1, int = 2);
    void rva0004D664(float, float, float, float, float, int);
};
// ?draw@ShellMenuScheme@@QAEXXZ
void ShellMenuScheme::draw( void )
{

	ShellMenuSchemeImageListIt imageIt = m_imageList.begin();
	while(imageIt != m_imageList.end())
	{
		ShellMenuSchemeImage *image = *imageIt;
		if(image && image->m_image)
		{
			((W3DDisplay *)TheDisplay)->rva0004D6B3(image->m_image, image->m_position.x, image->m_position.y,
														image->m_position.x + image->m_size.x , image->m_position.y + image->m_size.y);
		}
		++imageIt;
	}

	ShellMenuSchemeLineListIt it = m_lineList.begin();
	while(it != m_lineList.end())
	{
		ShellMenuSchemeLine *line = *it;
		
		if(line)
		{
			((W3DDisplay *)TheDisplay)->rva0004D664(line->m_startPos.x, line->m_startPos.y, line->m_endPos.x,
														line->m_endPos.y,line->m_width, line->m_color);
		}
		++it;
	}


}

// ??0ShellMenuSchemeLine@@QAE@XZ, retail 0x002004A5 (30B).
ShellMenuSchemeLine::ShellMenuSchemeLine(void)
{
	m_startPos.y = 0;
	m_startPos.x = 0;
	m_endPos.y = 0;
	m_endPos.x = 0;
	m_color = GAME_COLOR_UNDEFINED;
	m_width = 1;
}
