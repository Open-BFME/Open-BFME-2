// cl: /O1 /MD
// Semantic donor: Open-BFME-1 6583b3c1ff21db4a561285717028fdafc780b7db,
// game/GameEngine/Source/GameLogic/Object/Body/FreeLifeBody_attemptDamage.cpp.
// Target ctor 0x4C18CA stores secondary table VA 0xC5BD88; slot zero is
// this entry. Native [4C193C,4C1974) has a RET4 or a tail jump to the
// independently pinned ActiveBody::attemptDamage at 0x4BFE07.
// The donor's condition test uses the same secondary receiver. Target
// evidence moves its enable flag to +F0, data index to +78 and the object's
// condition words to +10C. Original class layout remains an opaque view.
class DamageInfo;
class ActiveBody {
public:
    virtual void attemptDamage(DamageInfo *);
};
struct FreeLifeConditionData {
    unsigned char before78[0x78];
    unsigned int condition;
};
struct FreeLifeConditionObject {
    unsigned char before10C[0x10C];
    unsigned int conditions[19];
};
struct Rva004C193COwner {
    unsigned char beforeF0[0xF0];
    bool enabled;
    void attemptDamage(DamageInfo *);
};

void Rva004C193COwner::attemptDamage(DamageInfo *info)
{
    if (enabled) {
        const FreeLifeConditionData *data = *(FreeLifeConditionData **)((char *)this - 12);
        const unsigned int index = data->condition;
        const FreeLifeConditionObject *obj = *(FreeLifeConditionObject **)((char *)this - 8);
        if (obj->conditions[index >> 5] & (1u << (index & 31)))
            return;
    }
    ((ActiveBody *)this)->ActiveBody::attemptDamage(info);
}
