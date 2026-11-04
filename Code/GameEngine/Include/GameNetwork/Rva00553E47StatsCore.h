// Target facts (addresses are retail RVAs):
// Constructors 0x00554463 and 0x00554F70 store table 0x0086B0DC at +0 before constructing their maps; neither constructs a parent. The four slots are reset (0x00553E47), rva005550A0 (0x005550A0), rva00555109 (0x00555109), and rva00554AF2 (0x00554AF2). The next table, 0x0086B0EC, belongs to Rva0038454E, whose constructor 0x0055459E installs it after calling 0x00554463.
// Destructor 0x00383D71 destroys the same map members and stores no vptr. It is nonvirtual; none of the four slots is a destructor. Both constructors and the destructor have rowed out-of-line bodies.
// Constructors, reset 0x00553E47, transfers 0x005550A0/0x00555109, and merge 0x00554AF2 establish 12-byte byte-key maps: six short maps at +0x04..+0x40, six-element short-map arrays at +0x4C and +0x94, and eight float maps at +0xDC..+0x130. Constructor/destructor iterators pass count 6 and stride 12 for each array; merge reads short values at node+0x12 and float values at node+0x14.
// Reset and merge access unsigned dwords at +0x13C/+0x140 and words at +0x144..+0x14C. No meaning is established for +0x14E..+0x14F. The id constructor stores its argument at +0x150; PSPlayerAllStats::setID (0x00552CDE) stores the same id in all three blocks.
// The +0x150 dword ends at +0x154. Derived constructors 0x0055459E and 0x005546C2 begin their own maps at +0x154, establishing the base extent 0x154. Their tables have five slots; tournament constructor 0x005561CD extends the latter with a six-slot table at 0x0086B114. None adds a destructor slot.
// ParseToolTipStats (0x00556982) reads the open-play block's +0x144 word before calling 0x00552E9E, establishing the inline getField144 access.

#pragma once

#ifndef BFME2_RVA00553E47STATSCORE_H
#define BFME2_RVA00553E47STATSCORE_H

#include <map>

class XferStub;

class Rva00553E47StatsCore
{
public:
    Rva00553E47StatsCore(const Rva00553E47StatsCore &);
    Rva00553E47StatsCore(int id);
    // No user-declared destructor: retail's 0x00383D71 is the implicit one,
    // which stores no vptr; an explicit empty body adds that store.

    virtual void reset();
    virtual void rva005550A0(XferStub *);
    virtual void rva00555109(XferStub *);
    virtual void rva00554AF2(const Rva00553E47StatsCore *);

    unsigned short getField144() const { return m_144; }

    _STL::map<unsigned char, short> m_maps04_0;
    _STL::map<unsigned char, short> m_maps04_1;
    _STL::map<unsigned char, short> m_maps04_2;
    _STL::map<unsigned char, short> m_maps04_3;
    _STL::map<unsigned char, short> m_maps04_4;
    _STL::map<unsigned char, short> m_maps04_5;
    _STL::map<unsigned char, short> m_maps4c[6];
    _STL::map<unsigned char, short> m_maps94[6];
    _STL::map<unsigned char, float> m_mapsdc_0;
    _STL::map<unsigned char, float> m_mapsdc_1;
    _STL::map<unsigned char, float> m_mapsdc_2;
    _STL::map<unsigned char, float> m_mapsdc_3;
    _STL::map<unsigned char, float> m_mapsdc_4;
    _STL::map<unsigned char, float> m_mapsdc_5;
    _STL::map<unsigned char, float> m_mapsdc_6;
    _STL::map<unsigned char, float> m_mapsdc_7;
    unsigned m_13c, m_140;
    unsigned short m_144, m_146, m_148, m_14a, m_14c;
    unsigned short m_unmodelled14e;
    int m_id;
};

#endif
