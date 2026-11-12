// cl: /Ireference/shims/bfme2_ascii /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?getNthInList@ObjectTypes@@QBE?AVAsciiString@@I@Z @0x002041AC 53B: bounds-checked
// AsciiString getter over the pointer pair at +8/+0xc; out of range yields the
// exported AsciiString::TheEmptyString at 0x009E0878. Evidence: StringBase copy pin
// 0x000365F0; callers 0x00206011 0x003A17E6 0x003C2532 0x003C7511 0x003E826D 0x003E8351.
// Zero Hour's ObjectTypes::getNthInList: the list's names live in the
// vector at +8 (vptr and list name ahead of it).

#include "../../../Include/GameLogic/ObjectTypesClass.h"



AsciiString ObjectTypes::getNthInList(unsigned int index) const
{
    return index < m_objectTypes.size() ? m_objectTypes[index] : AsciiString::TheEmptyString;
}
