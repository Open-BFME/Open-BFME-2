// cl: /O1 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0047CF38@HordeSiegeEngineContain@@QAEXXZ, retail 0x0047CF38 47B.
// Chain from SlaughterHordeContain slot105 0x004631C9: walk list at +0x108
// calling Object::rva0029A12B then tail-jmp to base slot105. Same pin plus
// pair-walk precedent; +0x108 list layout from retail loads.
class Object { public: void rva0029A12B(); };
struct Rva0047CF38Mid { char mPad00[8]; Object *mObj08; };
struct Rva0047CF38Node { void *mHead00; Rva0047CF38Mid *mMid04; };
class SlaughterHordeContain { public: virtual void rva004631C9(); };
class HordeSiegeEngineContain : public SlaughterHordeContain {
public:
    void rva0047CF38();
private:
    char mPad04[0x108 - 4];
    Rva0047CF38Node *mList108;
};
void HordeSiegeEngineContain::rva0047CF38()
{
    Rva0047CF38Node *cur = mList108;
    if (cur == *(Rva0047CF38Node * *)cur)
        goto done;
    do {
        cur->mMid04->mObj08->rva0029A12B();
        cur = (Rva0047CF38Node *)cur->mMid04;
    } while (cur != *(Rva0047CF38Node * *)mList108);
done:
    SlaughterHordeContain::rva004631C9();
}
