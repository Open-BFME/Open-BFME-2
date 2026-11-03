// Target facts (code addresses are RVAs; table addresses are VAs):
// Rva00355D66 has a 16-byte prefix: its ctor stores VA 0x00C14E5C at 0x00355D59, clears +8 at 0x00355D55 and sets byte +0x0C at 0x00355D5F. Its ProgressIndicator ctor 0x00355C60 stores the list link +4 at 0x00355C6E. VA 0x00C14E5C has the same six-slot shape: deleting dtor 0x00355FDD, update 0x00355FF9, three purecalls 0x0003B810, bool true 0x0050B5C6. The base declaration exposes this prefix and slot shape without asserting another canonical identity.
#ifndef BFME2_GAMECLIENT_RVA00355D66_H
#define BFME2_GAMECLIENT_RVA00355D66_H

class GameInfo;

class Rva00355D66
{
public:
    Rva00355D66();
    virtual ~Rva00355D66();
    virtual void vslot01(int);
    virtual void init(GameInfo *) = 0;
    virtual void vslot03() = 0;
    virtual void processProgress(int, int) = 0;
    virtual bool vslot05();

protected:
    void *field04;
    void *field08;
    bool field0C;
};

#endif
