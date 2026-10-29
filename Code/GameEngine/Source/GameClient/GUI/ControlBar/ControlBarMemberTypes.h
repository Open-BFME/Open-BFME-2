#pragma once
// What every ControlBar.cpp view needs to declare ControlBar's members (the
// TU's files share one ControlBar layout): the array bounds and the types of
// the members held by value.
//
// +0x30: the ctor (0x0031E94C) builds it through hash_map<int, T>() rowed at
// 0x0031E92D, which calls the hashtable constructor rowed at 0x0031DBFC; reset
// (0x0031E09E) walks and clears it. The int key and the eight-byte mapped type
// are the STL sweep rows' spelling (structural); ControlBarReloadNotice views
// the same map keyed by AsciiString, so the real key is still open.
//
// +0x2A4: the holder reset and update release through clear (0x000AD6F4); the
// ctor nulls its pointer in member order (an inline default ctor). Its pointee
// type is unknown.
#include <hash_map>
#include <vector>
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

// m_currentControlBarStage (+0x24): the stage setters store 1 (0x0031ADAE),
// 2 (setLowControlBarConfig) and 3 (setHiddenControlBar); toggle 0x0031BAB1
// switches between 0 and 2.
enum ControlBarStages
{
	CONTROL_BAR_STAGE_DEFAULT,
	CONTROL_BAR_STAGE_SQUISHED,
	CONTROL_BAR_STAGE_LOW,
	CONTROL_BAR_STAGE_HIDDEN
};

// m_contextParent holds NUM_CONTEXT_PARENTS + 1 windows (+0x48..+0x6C).
enum ControlBarParentWindowType
{
	CP_MASTER,
	CP_COMMAND,
	CP_BUILD_QUEUE,
	CP_BEACON,
	CP_UNDER_CONSTRUCTION,
	CP_OBSERVER_INFO,
	CP_OBSERVER_LIST,
	CP_OCL_TIMER,
	NUM_CONTEXT_PARENTS
};

enum
{
	MAX_COMMANDS_PER_SET = 32,			// m_commandWindows, +0xDC..+0x15C
	MAX_RIGHT_HUD_UPGRADE_CAMEOS = 5	// m_rightHUDUpgradeCameos, +0x8C..+0xA0
};

struct Rva0031DBFCElement
{
	Rva0031DBFCElement();
	Rva0031DBFCElement(const Rva0031DBFCElement &);
	Rva0031DBFCElement &operator=(const Rva0031DBFCElement &);
	~Rva0031DBFCElement() {}
	char m_data[8];
};

class Rva000AD6F4
{
public:
	Rva000AD6F4() : m_ptr(0) {}
	~Rva000AD6F4();
	void clear();
private:
	void *m_ptr; // +0x00
};
