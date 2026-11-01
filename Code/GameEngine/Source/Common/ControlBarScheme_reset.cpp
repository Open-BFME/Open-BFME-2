// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// stlport
// ?reset@ControlBarScheme@@QAEXXZ @0x0031FAF0 280B chain: clears 6 lists at +0x158 plus one at +0x170 then releases two strings and zeroes ints.
// Evidence: calls rowed dtors 0x2004FD and 0x31F831 plus delete 0x2FD60 and List_base clear 0x23DAA5 and releaseBuffer 0x36410; callers at 0x320044 and 0x32056F; prev/next flags /O1 /EHsc /MD.
#include "ascii_string.h"
#include "../../../Libraries/Include/Lib/ICoord2D.h"
class Image;
typedef int Color;


class Rva002004FD
{
public:
	~Rva002004FD();
};

class Rva0031F831
{
public:
    ~Rva0031F831();
    StringBase<char> m_str;
    char m_pad[4];
    int m_8;
};

#include <list>

// The clear stays the rowed STLport int-list body at 0x0023DAA5.
namespace _STL { template <> void _List_base<int, allocator<int> >::clear(); }

struct NodeA
{
	NodeA *m_next;
	NodeA *m_prev;
	Rva002004FD *m_obj;
};

struct ListA
{
	NodeA *m_header;
};

struct NodeB
{
	NodeB *m_next;
	NodeB *m_prev;
	Rva0031F831 *m_obj;
};

struct ListB
{
	NodeB *m_header;
};

// ControlBarScheme::reset: ZH's newControlBarScheme (0x0032053E) calls it at 0x0032056F, and
// the scheme destructor 0x0032002C calls it first, as ZH's ~ControlBarScheme does.
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

void ControlBarScheme::reset()
{
	ListA *listA = (ListA *)m_lists;
	int n = 6;
	do
	{
		NodeA *cur = listA->m_header->m_next;
		while (cur != listA->m_header)
		{
			Rva002004FD *obj = cur->m_obj;
			if (obj)
				delete obj;
			cur = cur->m_next;
		}
		(( _STL::_List_base<int, _STL::allocator<int> > *)listA)->clear();
		++listA;
		--n;
	} while (n != 0);

	NodeB *curB = ((ListB *)&m_list170)->m_header->m_next;
	while (curB != ((ListB *)&m_list170)->m_header)
	{
		Rva0031F831 *obj = curB->m_obj;
		if (obj)
		{
			obj->m_8 = 0;
			delete obj;
		}
		curB = curB->m_next;
	}
	(( _STL::_List_base<int, _STL::allocator<int> > *)&m_list170)->clear();

	m_name.clear();
	m_ScreenCreationRes.y = 0;
	m_ScreenCreationRes.x = 0;
	m_side.clear();
	m_buttonQueueImage = 0;
	m_rightHUDImage = 0;
	m_optionsButtonEnable = 0;
	m_optionsButtonHightlited = 0;
	m_optionsButtonPushed = 0;
	m_optionsButtonDisabled = 0;
	m_idleWorkerButtonEnable = 0;
	m_idleWorkerButtonHightlited = 0;
	m_idleWorkerButtonPushed = 0;
	m_idleWorkerButtonDisabled = 0;
	m_buddyButtonEnable = 0;
	m_buddyButtonHightlited = 0;
	m_buddyButtonPushed = 0;
	m_buddyButtonDisabled = 0;
	m_beaconButtonEnable = 0;
	m_beaconButtonHightlited = 0;
	m_beaconButtonPushed = 0;
	m_beaconButtonDisabled = 0;
	m_genBarButtonIn = 0;
	m_genBarButtonOn = 0;
	m_toggleButtonUpIn = 0;
	m_toggleButtonUpOn = 0;
	m_toggleButtonUpPushed = 0;
	m_toggleButtonDownIn = 0;
	m_toggleButtonDownOn = 0;
	m_toggleButtonDownPushed = 0;
	m_commandMarkerImage = 0;
	m_expBarForeground = 0;
}
