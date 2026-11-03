// Target facts (RVAs): 0x005EC832 stores Impl construction's result at wrapper +0 (ctor 0x005EC64E, allocation 0x2C at 0x005EC83E). Show (0x005EC1A4), Hide (0x005EC21D) and FadeOut (0x005EC23E) dereference that pointer; their ledger names declare nonvirtual bool, void and void members. Impl's ctor names its owner StrategicVeterancy* and its input Data*.
// Target facts: allocations at 0x005CFF3D and 0x005D11B5 reserve 0x0C for states whose ctors 0x005CFB35 and 0x005D1064 construct this wrapper at +8 and call Show there. Cleanup 0x005EC422 clears wrapper +0 and directly calls Impl teardown 0x005EC09B; wrapper destructor 0x005EC4AA jumps to that cleanup. Impl's +0 receives its owner at 0x005EC66E; no wrapper or Impl vptr is installed.
// Structural inference: StrategicVeterancy is a plain four-byte class with no base or virtual functions and an Impl pointer at +0. Its field spelling is unknown. Data is a separate nested type: AutoResolve ctor 0x005ECE81 and dtor 0x005ECFE4 install VA 0x00C785B4 in that data object, whose allocation is 0x1C at 0x005ED168; those virtual slots do not belong to the wrapper.
#pragma once

#ifndef BFME2_STRATEGICVETERANCY_H
#define BFME2_STRATEGICVETERANCY_H

class StrategicVeterancy
{
public:
    class Data;

    bool Show();
    void Hide();
    void FadeOut();

private:
    struct Impl;
    Impl *field00;
};

#endif
