#pragma once
// Target WinInstanceData: ctor32225A installs C0D830; one virtual dtor slot.
// GameWindow member30..1D7 and last ctor word1A4 prove extent1A8.
// Unknown storage stays opaque. Lifetime bodies remain the matched owners.
class WinInstanceData
{
public:
 WinInstanceData();
 virtual ~WinInstanceData();
 unsigned char m_opaque04[8];
 unsigned int m_style; // +0C
 unsigned char m_opaque10[0x15C-0x10];
 int m_enabledColor, m_enabledBorderColor;
 int m_disabledColor, m_disabledBorderColor;
 int m_hiliteColor, m_hiliteBorderColor;
 int m_imecompositeColor, m_imecompositeBorderColor;
 unsigned char m_opaque17C[0x1A8-0x17C];
private:
 WinInstanceData(const WinInstanceData &);
 WinInstanceData &operator=(const WinInstanceData &);
};
typedef char Bfme2WinInstanceData_extent_1A8[(sizeof(WinInstanceData)==0x1A8)?1:-1];
