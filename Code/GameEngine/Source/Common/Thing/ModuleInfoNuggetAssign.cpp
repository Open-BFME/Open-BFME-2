// cl: /Ireference/shims/bfme2_ascii /O1
//
// ??4Nugget@ModuleInfo@@QAEAAU01@ABU01@@Z @0x002CEFCD 57B.
// ModuleInfo::Nugget copy assignment. Layout is the BFME1 donor
// (Code/GameEngine/Source/Common/Thing/ThingTemplate.cpp Rva0013E5D0Nugget:
// two AsciiStrings then ModuleData pointer then Int then two Bools for
// 0x14-byte records); ZH adds a third Bool which retail does not copy.
// Identity is pin-proven: per-element callee of the rowed 5-arg
// _STL::__copy_ptrs worker at 0x002CF0BE (ModuleInfoNuggetCopyPtrs.cpp).

#include "ascii_string.h"

#include "../../../Include/Common/ModuleData.h"

#include "../../../Include/Common/ModuleInfoClass.h"

ModuleInfo::Nugget &ModuleInfo::Nugget::operator=(const Nugget &other)
{
	first = other.first;
	m_moduleTag = other.m_moduleTag;
	second = other.second;
	interfaceMask = other.interfaceMask;
	copiedFromDefault = other.copiedFromDefault;
	inheritable = other.inheritable;
	return *this;
}
