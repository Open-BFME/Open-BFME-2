// Target facts (addresses are retail RVAs):
// Constructors 0x0055459E and 0x00555616 call Rva00553E47StatsCore's 0x00554463 at +0, then store their own table 0x0086B0EC at +0. The parent's table 0x0086B0DC is installed by the base constructor; the derived maps begin at +0x154. The copy constructor constructs Core(0), constructs the maps, calls reset 0x00553F2F, then merges the source through 0x0055524B.
// Table 0x0086B0EC has five slots before the next constructor-owned table at 0x0086B100: reset (0x00553F2F), inherited rva005550A0 (0x005550A0), rva00555109 (0x0055573B), inherited rva00554AF2 (0x00554AF2), and rva0055524B (0x0055524B). Destructor 0x0038454E stores no vptr and calls the base destructor 0x00383D71; no slot is a destructor, so it is nonvirtual.
// Constructors, reset 0x00553F2F, transfer 0x0055573B, merge 0x0055524B, assignment 0x00387945 and destructor 0x0038454E establish fifteen separate 12-byte byte-key maps: eight float maps at +0x154..+0x1A8, two short maps at +0x1B4/+0x1C0, and five float maps at +0x1CC..+0x1FC. Merge reads float values at node+0x14 and short values at node+0x12; transfer calls the byte-key float/short helpers 0x0055499A/0x005548E9.
// The last map ends at +0x208; setStrategicStats 0x00555B30 and trackPlayerStrategicStats 0x0055961C both destroy their by-value argument through 0x0038454E and return with RET 0x208, proving sizeof 0x208. PSPlayerAllStats constructs this member at +0x340 in 0x0055621F. The id constructor writes the inherited id at +0x150. Constructors, destructor and assignment have rowed out-of-line bodies.

#pragma once

#ifndef BFME2_RVA0038454E_H
#define BFME2_RVA0038454E_H

#include "Rva00553E47StatsCore.h"

class Rva0038454E : public Rva00553E47StatsCore
{
public:
    Rva0038454E(int);
    Rva0038454E(const Rva0038454E &);
    ~Rva0038454E();
    Rva0038454E &operator=(const Rva0038454E &);

    virtual void reset();
    virtual void rva00555109(XferStub *);
    virtual void rva0055524B(const Rva0038454E *);

    _STL::map<unsigned char, float> m_map154;
    _STL::map<unsigned char, float> m_map160;
    _STL::map<unsigned char, float> m_map16c;
    _STL::map<unsigned char, float> m_map178;
    _STL::map<unsigned char, float> m_map184;
    _STL::map<unsigned char, float> m_map190;
    _STL::map<unsigned char, float> m_map19c;
    _STL::map<unsigned char, float> m_map1a8;
    _STL::map<unsigned char, short> m_map1b4;
    _STL::map<unsigned char, short> m_map1c0;
    _STL::map<unsigned char, float> m_map1cc;
    _STL::map<unsigned char, float> m_map1d8;
    _STL::map<unsigned char, float> m_map1e4;
    _STL::map<unsigned char, float> m_map1f0;
    _STL::map<unsigned char, float> m_map1fc;
};

#endif
