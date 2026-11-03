// Target facts (code RVAs, table VAs): SidesList constructors 0x0032EE24 and 0x0032EF3E call 0x00330757 on +0x10 at 0x0032EE4B/0x0032EF68, then construct the next member at +0x20. The copy path default-constructs this storage without reading the source. Constructor 0x00330757 initializes pointer words +0/+4/+8 through 0x00211E58 and 0x0014F3C4, then sets +0x0C to -1. Destructor 0x0032EC63 frees the pointer at +0x10 at 0x0032ED21..0x0032ED31; the registered base destructor 0x0007FAB3 performs the same nullable release. The notifier footprint is 0x10 bytes and has no retail virtual functions, vptr, vbptr or table.
// SidesList installs 0x00C0DA98 at +0 and 0x00C0DA88 at +0x0C (0x0032EE5B/0x0032EE61, 0x0032EF78/0x0032EF7E, 0x0032EC76/0x0032EC7C); Snapshot's 0x00BBB554 at +0x0C is base construction/teardown (0x0032EE41/0x0032EF5E/0x0032ED38). None occupies the notifier at +0x10. Dispatch 0x0032AE25/0x0032AE92 reads begin/end words +0/+4 and latches the index at +0x0C; table 0x00BFB1CC is stored on the stack at 0x0032AE3D/0x0032AEAA for LatchRestore, whose sole slot is 0x0027EA91. These are separate owners, not competing notifier tables.
// Ledger post overloads at 0x0032B522 and 0x0032B540 build two/three-word Post/PostIndexed records and call dispatch 0x0032AE25/dispatchIndexed 0x0032AE92 with this unchanged. Their callback/owner/index words occupy +0/+4/+8; dispatch loads a listener into ECX before calling the callback. The member-pointer post spelling at 0x0032B522 has its own ledger row; 0x0032B871 calls it on this+0x10 with the slot-0x24 thunk. The listener's original identity is unproved. All rowed methods remain out of line; the callback records retain the function-pointer spellings of the two post provider rows.
#pragma once

#ifndef BFME2_COMMON_SIDESLISTNOTIFIER_H
#define BFME2_COMMON_SIDESLISTNOTIFIER_H

#include "Rva00330757Member.h"

class Rva00281A15Listener;

class SidesListNotifier : public Rva00330757Member
{
public:
    struct Post
    {
        void (*callback)();
        void *owner;
    };

    struct PostIndexed
    {
        void (*callback)();
        void *owner;
        int index;
    };

    __forceinline SidesListNotifier() : Rva00330757Member() {}
    __forceinline SidesListNotifier(const SidesListNotifier &) : Rva00330757Member() {}

    void post(void (*callback)(), void *owner);
    void post(void (*callback)(), void *owner, int index);
    void post(void (Rva00281A15Listener::*callback)(void *), void *owner);
    void dispatch(const Post *post);
    void dispatchIndexed(const PostIndexed *post);
};

typedef char SidesListNotifierSizeCheck[sizeof(SidesListNotifier) == 0x10 ? 1 : -1];
typedef char SidesListNotifierPostSizeCheck[sizeof(SidesListNotifier::Post) == 8 ? 1 : -1];
typedef char SidesListNotifierPostIndexedSizeCheck[sizeof(SidesListNotifier::PostIndexed) == 12 ? 1 : -1];

#endif
