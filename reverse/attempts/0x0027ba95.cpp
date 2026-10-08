// ?calcPhysicsXform@Drawable@@QAE_NAAUPhysicsXformInfo@1@@Z
// partial score=0.9 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Reference control flow: BFME1 90fffa62857c Drawable::calcPhysicsXform,
// originally GeneralsMD Drawable.cpp. Target identity: WB ca7380, file
// Drawable.cpp line 3238; native 27BA95..27BB65. Frame guard, appearances,
// dispatch targets and offsets below are read from the native body.
struct Rva0028AC4EEntry
{
    char unknown[0xAC];
    unsigned int lastPhysicsFrame;
};
class Object
{
public:
    const Rva0028AC4EEntry *rva0028AC4E() const;
};
struct DrawablePhysicsHolder
{
    char unknown[0x1F0];
    Rva0028AC4EEntry *locomotor;
    Rva0028AC4EEntry *getCurrentLocomotor() const { return locomotor; }
};
struct DrawablePhysicsObject
{
    char unknown[0x258];
    DrawablePhysicsHolder *holder;
    DrawablePhysicsHolder *getAIUpdateInterface() const { return holder; }
};
struct DrawablePhysicsAppearance
{
    char unknown[0x74];
    int appearance;
};
struct DrawablePhysicsLocomotor
{
    char unknown00[4];
    DrawablePhysicsAppearance *overrideData;
    char unknown08[0xAC - 8];
    unsigned int lastPhysicsFrame;
    int getAppearance() const { return overrideData->appearance; }
    unsigned int getLastPhysicsFrame() const { return lastPhysicsFrame; }
};
class Rva00DFE77CHolder
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
    virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
    virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
    virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
    virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual int slot1F();
};
class GameClient;
extern GameClient *TheGameClient;

class Drawable
{
public:
    struct PhysicsXformInfo;
    bool calcPhysicsXform(PhysicsXformInfo &info);
    void rva00276CFB(const DrawablePhysicsLocomotor *, PhysicsXformInfo &);
    void rva00270817(const DrawablePhysicsLocomotor *, PhysicsXformInfo &);
    void rva00270B0F(const DrawablePhysicsLocomotor *, PhysicsXformInfo &);
    void rva0027B47F(const DrawablePhysicsLocomotor *, PhysicsXformInfo &);
    void rva00272FB6(const DrawablePhysicsLocomotor *, PhysicsXformInfo &);
    DrawablePhysicsObject *getObject() const { return object; }
private:
    char unknown[0xFC];
    DrawablePhysicsObject *object;
};

bool Drawable::calcPhysicsXform(PhysicsXformInfo &info)
{
    DrawablePhysicsObject *obj = getObject();
    DrawablePhysicsHolder *holder = obj ? obj->getAIUpdateInterface() : 0;
    bool hasPhysicsXform = false;
    if (holder)
    {
        DrawablePhysicsLocomotor *locomotor =
            reinterpret_cast<DrawablePhysicsLocomotor *>(holder->getCurrentLocomotor());
        if (locomotor)
        {
            unsigned int frame = reinterpret_cast<Rva00DFE77CHolder *>(TheGameClient)->slot1F();
            if (locomotor->getLastPhysicsFrame() != frame)
            {
                const Rva0028AC4EEntry *entry = reinterpret_cast<const Object *>(getObject())->rva0028AC4E();
                const_cast<Rva0028AC4EEntry *>(entry)->lastPhysicsFrame = frame;
                switch (locomotor->getAppearance())
                {
                case 1:
                case 8:
                    rva00276CFB(locomotor, info);
                    hasPhysicsXform = true;
                    break;
                case 2:
                case 3:
                    rva00270817(locomotor, info);
                    hasPhysicsXform = true;
                    break;
                case 4:
                    rva0027B47F(locomotor, info);
                    hasPhysicsXform = true;
                    break;
                case 5:
                    rva00270B0F(locomotor, info);
                    hasPhysicsXform = true;
                    break;
                case 9:
                    rva00272FB6(locomotor, info);
                    hasPhysicsXform = true;
                    break;
                }
            }
        }
    }
    return hasPhysicsXform;
}
