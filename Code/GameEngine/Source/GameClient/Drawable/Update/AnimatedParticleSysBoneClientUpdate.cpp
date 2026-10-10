// cl: /O1 /G7 /MD /EHsc
// Semantic reference: GeneralsMD AnimatedParticleSysBoneClientUpdate.cpp,
// carried at Open-BFME-1 575ba2b04743f190f069805fbdc59936123c45da.
// Target: WB 126D0C0 names clientUpdate; native 4C9053..4C908B.
// Only the accessed fields and virtual slots are modeled. No vtable is emitted.
template<int N> class ParticleBoneDrawSlots : public ParticleBoneDrawSlots<N-1> {
public:
    virtual void unknownSlot(char (*)[N]);
};
template<> class ParticleBoneDrawSlots<1> {
public:
    virtual void unknownSlot(char (*)[1]);
};
class ObjectDrawInterface : public ParticleBoneDrawSlots<27> {
public:
    // Retail passes zero at slot +6C; the added argument's role is unasserted.
    virtual bool updateBonesForClientParticleSystems(int);
};
class DrawModule : public ParticleBoneDrawSlots<42> {
public:
    // Retail slot +A8; WB uses +AC.
    virtual ObjectDrawInterface *getObjectDrawInterface();
};
class Drawable {
public:
    DrawModule **getDrawModules();
};
class AnimatedParticleSysBoneClientUpdate {
public:
    virtual void clientUpdate();
private:
    void *moduleData;
    Drawable *drawable;
    unsigned life;
};
void AnimatedParticleSysBoneClientUpdate::clientUpdate()
{
    ++life;
    Drawable *draw = drawable;
    if (draw) {
        for (DrawModule **dm = draw->getDrawModules(); *dm; ++dm) {
            ObjectDrawInterface *di = (*dm)->getObjectDrawInterface();
            if (di && di->updateBonesForClientParticleSystems(0))
                break;
        }
    }
}
