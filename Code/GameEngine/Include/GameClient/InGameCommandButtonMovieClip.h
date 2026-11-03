// Target facts (code addresses are RVAs; tables are VAs): constructor 0x005C802B stores 0x00C74ACC at +0 (0x005C803B), constructs Impl at 0x005C805C and stores its pointer at +4 (0x005C8064). Destructor 0x005C7CBB restores the same table and clears +4 through 0x005C7CA1. The base occupies 8 bytes: derived constructor 0x005C35A6 calls it at +0 and starts its own fields at +8; constructor 0x00567CCD places it at +8 and the next subobject at +0x10. Neither lifetime body constructs or destroys a parent.
// Table 0x00C74ACC has seven slots: deleting destructor 0x005C8075, 0x005C793A, then five copies of 0x000B3FD0 (RET). The next word at 0x00C74AE8 starts "_Timer". Slot 1 takes one pointer argument, writes float 1 and integer 0x80000000 at its +0/+4, and returns with RET 4; its output record is rowed as Rva005C793APair. Impl constructor 0x005C7EF1 binds the slot-1 thunk 0x005CB260 to "_Timer", proving the slot used by its existing NotifyTimer member reference. Callbacks 0x005C790D and 0x005C78D0 call owner slots 2 and 3..6 without arguments; their names remain neutral.
// Impl is a separate nonvirtual 0x60-byte allocation (0x005C8039/0x005C8041), with constructor 0x005C7D4A and destructor 0x005C7954; its first word is this outer object's pointer, not a vfptr. Its definition remains in its owning units. The outer lifetime rows currently use the opaque ledger class Rva005C802B; no registered header defines either identity. All methods below are declarations only.

#pragma once

#ifndef BFME2_INGAMECOMMANDBUTTONMOVIECLIP_H
#define BFME2_INGAMECOMMANDBUTTONMOVIECLIP_H

class AptMovieClipFrame;
class AsciiString;
struct Rva005C793APair;

class InGameCommandButtonMovieClip
{
public:
    class Impl;

    InGameCommandButtonMovieClip(AptMovieClipFrame *frame, const AsciiString &name);
    virtual ~InGameCommandButtonMovieClip();
    virtual void NotifyTimer(Rva005C793APair *out);
    virtual void vslot02();
    virtual void vslot03();
    virtual void vslot04();
    virtual void vslot05();
    virtual void vslot06();

private:
    Impl *m_field04;
};

#endif
