// Target facts (code RVAs, table VAs): owner constructor 0x005EE014 stores 0x00C786A8 at 0x005EE024 and the Impl pointer at +4 at 0x005EE04D; destructor 0x005EE05E restores the same table and jumps to owning-pointer cleanup 0x005EDFF5. Derived constructor 0x005D1335 calls 0x005EE014 at 0x005D1340, writes its first member at +8, then installs 0x00C755C0: the owner occupies 8 bytes, with no established parent or vbptr. Identifying this owner as StrategicHUD::RegionAwardMovieClip follows its ownership of the ledger-named Impl, rather than a constructor name in the ledger.
// Table 0x00C786A8 has five slots: scalar deleting destructor 0x005EE0D8, 0x000B3FD0 (ret), 0x0047A69C (ret 4), 0x000B3FD0 and 0x000B3FD0; string data begins at 0x00C786BC. The derived table 0x00C755C0 has 0x005D13A1, 0x005D1358, 0x005D1362, 0x005D14C0 and 0x005D1516. No ledger row proves callback names for the owner, so its slots retain neutral names.
// The allocation size pushed at 0x005EE022 and constructor call at 0x005EE045 establish a separate 0x54-byte Impl (constructor 0x005EDB74, destructor 0x005EDE64), with no virtual functions or table stores. Constructor calls 0x005EDDEA and 0x005EDDF5 reach its ledger-named setters 0x005ED445 and 0x005ED4AC; forwarders 0x005ED5EB, 0x005ED976 and 0x005EE250 load the owner's +4 before reaching Impl methods. Impl remains a separate declaration; its storage is not part of the owner's size. Callback calls at 0x005ED1EE, 0x005ED282, 0x005ED22A and 0x005ED20C prove the owner's slots 1, 2 (one integer argument), 3 and 4.
#pragma once

#ifndef BFME2_REGION_AWARD_MOVIE_CLIP_H
#define BFME2_REGION_AWARD_MOVIE_CLIP_H

class AsciiString;

namespace StrategicHUD
{
class RegionAwardMovieClip
{
public:
    class Impl;

    RegionAwardMovieClip(int level, const AsciiString &name);
    virtual ~RegionAwardMovieClip();

    virtual void vslot01();
    virtual void vslot02(int);
    virtual void vslot03();
    virtual void vslot04();

private:
    Impl *m_impl;
};
}

using StrategicHUD::RegionAwardMovieClip;

typedef char RegionAwardMovieClipSizeCheck[sizeof(RegionAwardMovieClip) == 8 ? 1 : -1];

#endif
