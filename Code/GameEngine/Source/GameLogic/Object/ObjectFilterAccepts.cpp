// cl: /MD
// Native [0x00362437,0x00362461), RET8. This is the existing address-based
// Rva2225E0Filter::accepts pin used by RespawnBody and HordeContain.
// BFME1 6583b3c1 Rva2225E0FilteredCountThunk.cpp supplies the Object/Player
// interface lead. Target calls independently pass the object and context
// player. The body rejects null, reads Object's template at +4 and calls
// 0x3618B9 with template, controlling player and context player in that order.
class Player;
class ThingTemplate;
class Object {
public:
    void *vtable;
    const ThingTemplate *objectTemplate;
    Player *getControllingPlayer() const;
};
class ObjectFilter { public: bool testTemplate(const ThingTemplate *, const Player *, const Player *); };
struct Rva2225E0Filter {
    bool accepts(Object *, Player *);
};

bool Rva2225E0Filter::accepts(Object *obj, Player *context)
{
    if (!obj)
        return false;
    const ThingTemplate *objectTemplate = obj->objectTemplate;
    return reinterpret_cast<ObjectFilter*>(this)->testTemplate(objectTemplate, obj->getControllingPlayer(), context);
}
