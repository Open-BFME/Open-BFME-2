// Target facts (retail RVAs): constructors 0x005546C2 and 0x005559FC call Rva00553E47StatsCore(0) at 0x00554463, then install table 0x0086B100 at +0. Constructor 0x0055459E instead installs sibling table 0x0086B0EC; tournament constructor 0x005561CD calls 0x005546C2 and installs its own six-slot table 0x0086B114.
// Table 0x0086B100 has five slots: reset 0x00553FDD, inherited rva005550A0 0x005550A0, rva00555109 0x00555988, inherited rva00554AF2 0x00554AF2, and rva00555845 0x00555845. Destructor 0x003844D7 destroys five maps and calls base destructor 0x00383D71 without storing a table; no slot is a destructor. Assignment 0x003874F9 and both constructors are out of line.
// Constructors, reset 0x00553FDD, transfer 0x00555988, merge 0x00555845 and destructor 0x003844D7 establish five 12-byte byte-key maps at +0x154/+0x160/+0x16C/+0x178/+0x184 with int/short/short/float/float values. Merge reads node+0x14 as integer or float and node+0x12 as short. The by-value receiver 0x0055954E returns with ret 0x190; aggregate constructor 0x0055621F places this block at +0x1B0 and the next at +0x340, confirming sizeof 0x190 and base extent 0x154.

#pragma once

#ifndef BFME2_RVA003844D7_H
#define BFME2_RVA003844D7_H

#include "Rva00553E47StatsCore.h"

class Rva003844D7 : public Rva00553E47StatsCore
{
public:
    Rva003844D7(int);
    Rva003844D7(const Rva003844D7 &);
    ~Rva003844D7();
    Rva003844D7 &operator=(const Rva003844D7 &);

    virtual void reset();
    virtual void rva00555109(XferStub *);
    virtual void rva00555845(const Rva003844D7 *);

    _STL::map<unsigned char, int> m_map154;
    _STL::map<unsigned char, short> m_map160;
    _STL::map<unsigned char, short> m_map16c;
    _STL::map<unsigned char, float> m_map178;
    _STL::map<unsigned char, float> m_map184;
};

#endif
