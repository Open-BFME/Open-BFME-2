// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -EHsc -MD
// stlport
// ??1ControlBarScheme@@QAE@XZ, retail 0x0032002C, 105 bytes. Dtor of ControlBarScheme: body calls reset 0x31FAF0 then destroys list at +0x170 and array at +0x158 and two AsciiStrings at +0xC/+0x0.
// Evidence: deleting-dtor caller at 0x0032013C; offsets match the ControlBarScheme reset TU (Rva0031FAF0.cpp); callees rowed List_base 0x004EC395 vector-dtor 0x00629110 releaseBuffer 0x00036410.
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
class Image;
typedef int Color;


#include <list>

// The list teardown stays the rowed STLport int-list body at 0x004EC395
// (clear 0x0023DAA5 then free), so the member teardown is declared here.
namespace _STL { template <> _List_base<int, allocator<int> >::~_List_base(); }

class Rva00200667 : public _STL::_List_base<int, _STL::allocator<int> >
{
public:
	~Rva00200667() {}
};

class ControlBarScheme
{
public:
    ControlBarScheme();
    ~ControlBarScheme();
    void init();
    void update();
    void reset();

	AsciiString m_name;
	ICoord2D m_ScreenCreationRes;
	AsciiString m_side;
	Image *m_buttonQueueImage;
	Image *m_rightHUDImage;					///< +0x14
	Color m_buildUpClockColor;				///< +0x18
	Color m_borderBuildColor;				///< +0x1c
	Color m_borderActionColor;
	Color m_borderUpgradeColor;
	Color m_borderSystemColor;
	Color m_bfmeBorderFifthColor;			///< +0x2c
	Color m_commandBarBorderColor;			///< +0x30
	Image *m_optionsButtonEnable;			///< +0x34
	Image *m_optionsButtonHightlited;
	Image *m_optionsButtonPushed;
	Image *m_optionsButtonDisabled;
	Image *m_idleWorkerButtonEnable;		///< +0x44
	Image *m_idleWorkerButtonHightlited;
	Image *m_idleWorkerButtonPushed;
	Image *m_idleWorkerButtonDisabled;
	Image *m_buddyButtonEnable;				///< +0x54
	Image *m_buddyButtonHightlited;
	Image *m_buddyButtonPushed;
	Image *m_buddyButtonDisabled;
	Image *m_beaconButtonEnable;			///< +0x64
	Image *m_beaconButtonHightlited;
	Image *m_beaconButtonPushed;
	Image *m_beaconButtonDisabled;
	Image *m_genBarButtonIn;				///< +0x74
	Image *m_genBarButtonOn;
	Image *m_toggleButtonUpIn;				///< +0x7c
	Image *m_toggleButtonUpOn;
	Image *m_toggleButtonUpPushed;
	Image *m_toggleButtonDownIn;
	Image *m_toggleButtonDownOn;
	Image *m_toggleButtonDownPushed;
	Image *m_generalButtonEnable;			///< +0x94
	Image *m_generalButtonHightlited;
	Image *m_generalButtonPushed;
	Image *m_generalButtonDisabled;
	Image *m_uAttackButtonEnable;			///< +0xa4
	Image *m_uAttackButtonHightlited;
	Image *m_uAttackButtonPushed;
	Image *m_minMaxButtonEnable;			///< +0xb0
	Image *m_minMaxButtonHightlited;
	Image *m_minMaxButtonPushed;
	Image *m_genArrow;						///< +0xbc
	ICoord2D m_moneyUL;						///< +0xc0
	ICoord2D m_moneyLR;
	ICoord2D m_minMaxUL;
	ICoord2D m_minMaxLR;
	ICoord2D m_generalUL;
	ICoord2D m_generalLR;
	ICoord2D m_uAttackUL;					///< +0xf0
	ICoord2D m_uAttackLR;
	ICoord2D m_optionsUL;
	ICoord2D m_optionsLR;
	ICoord2D m_workerUL;
	ICoord2D m_workerLR;
	ICoord2D m_chatUL;						///< +0x120
	ICoord2D m_chatLR;
	ICoord2D m_beaconUL;
	ICoord2D m_beaconLR;
	ICoord2D m_powerBarUL;
	ICoord2D m_powerBarLR;
	Image *m_expBarForeground;				///< +0x150
	Image *m_commandMarkerImage;			///< +0x154
    Rva00200667 m_lists[6];
    // Native EH calls the complete five-byte list wrapper at200667;
    // the normal path inlines it and calls the23-byte base at4EC395.
    // The node payload is not established by these destruction paths.
    Rva00200667 m_list170;
};

ControlBarScheme::~ControlBarScheme()
{
	reset();
}
