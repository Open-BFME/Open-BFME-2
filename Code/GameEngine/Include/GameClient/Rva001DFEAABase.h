// Target facts (code addresses are RVAs): constructor 0x001DFEAA stores the primary vftable VA 0x00BDC940 at 0x001DFEBE; destructor 0x001DFA48 stores the same table at 0x001DFA59 and calls member teardown 0x00360D26 at +0x0C then +0x08. Neither body calls a parent constructor/destructor or installs a secondary vptr. The table has exactly five entries: scalar deleting destructor 0x001DFA84, __purecall 0x0003B810, doFXObj 0x001DFF1F, __purecall 0x0003B810, rva001DFF5D 0x001DFF5D; the next word at table RVA 0x007DC954 begins a string. All rowed methods are declared out of line.
// Target layout: 0x001DFEC4/0x001DFED0 construct four-byte handles through 0x003623E5 at +0x08/+0x0C; 0x001DFED8/0x001DFEE0/0x001DFEEB/0x001DFEF6 call the ledger's Rva0042526Member constructor 0x00042526 at +0x10/+0x5C/+0xA8/+0xF4, whose 0x00042527 pushes the 0x4C-byte memset extent. 0x001DFEFB writes dword +0x04 = 0, 0x001DFF02 writes dword +0x140 = 2, and 0x001DFF0C writes byte +0x144 = 0. The four-byte-aligned extent is 0x148: derived constructor 0x001E1221 calls this constructor at 0x001E1224 and initializes its first member at +0x148 (0x001E122F); SoundFXNugget's 0x001E00B1 does likewise, and its allocation in 0x001E1329 reserves 0x14C bytes. Field names remain neutral; each bulk-zeroed member retains opaque byte storage and its out-of-line constructor declaration.
// Target slots: doFXObj's call through vptr +4 at 0x001DFF55 passes two Coord3D pointers, a Matrix3D pointer and a float as the rowed derived doFXPos at 0x001E00C3 declares. Slot 3's derived row 0x001E1709 declares const void(AssetList &, int) and returns with ret 8 at 0x001E1719; its original base name is unknown, so slot03 is a placeholder. The ledger names slots 2/4 and their constness at 0x001DFF1F/0x001DFF5D. 0x001DFF6F/0x001DFFB1 apply the +0x08/+0x0C handles, 0x001DFF86/0x001DFFCE consume the four storage members, and 0x001DFFD7 reads dword +0x140.
#pragma once

#ifndef __BFME2_RVA001DFEAABASE_H_
#define __BFME2_RVA001DFEAABASE_H_

#include "../GameLogic/Module/Rva003623E5Member.h"
#include "../Common/Rva0042526Member.h"

struct Coord3D;
class Matrix3D;
class Object;
class AssetList;

class Rva001DFEAABase
{
public:
    Rva001DFEAABase();
    virtual ~Rva001DFEAABase();
    virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const = 0;
    virtual void doFXObj(const Object *primary, const Object *secondary) const;
    virtual void slot03(AssetList &assets, int value) const = 0;
    virtual bool rva001DFF5D(Object *primary, Object *secondary);

    int m_nuggetType;
    Rva003623E5Member m_08;
    Rva003623E5Member m_0C;
    Rva0042526Member m_10;
    Rva0042526Member m_5C;
    Rva0042526Member m_A8;
    Rva0042526Member m_F4;
    int m_140;
    bool m_144;
};

#endif
