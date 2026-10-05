// cl: /O1 /MD
// RespawnUpdate entry RVA 0x004AF182, native [4AF182,4AF1CE), RET.
// RespawnBody::apply's proved lookup of "RespawnUpdate" calls this entry
// at 4C14A8 and 4C14CA. The constructor at 4AF096 independently establishes
// the module/object pointers (+4/+8) and state/timer fields (+2C/+30).
// Module data supplies two 0x4C-byte condition sets at +C and +58.
// The original method name is unknown; retain its target address.

enum DisabledType;
enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3FFFFFFF };
class Object { public: bool clearDisabled(DisabledType); };
class Rva001E42F2 { public: void rva001E42F2(const int *); };
struct RespawnUpdateData004AF182 {
    unsigned char before0C[0xC];
    int conditions0C[19];
    int conditions58[19];
};
class UpdateModule {
protected:
    void *vtable;
    RespawnUpdateData004AF182 *data;
    Object *object;
    unsigned char before20[0x14];
    void setWakeFrame(Object *, UpdateSleepTime);
};
class RespawnUpdate : public UpdateModule {
    unsigned char before2C[0xC];
    unsigned int state;
    unsigned int timer;
public:
    void rva004AF182();
};

void RespawnUpdate::rva004AF182()
{
    Object *obj = object;
    const RespawnUpdateData004AF182 *md = data;
    if (state != 0) {
        ((Rva001E42F2 *)obj)->rva001E42F2(md->conditions0C);
        ((Rva001E42F2 *)obj)->rva001E42F2(md->conditions58);
        obj->clearDisabled((DisabledType)4);
        setWakeFrame(obj, UPDATE_SLEEP_FOREVER);
        timer = 0;
        state = 2;
    }
}
