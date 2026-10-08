// cl: /O1 /G7 /arch:SSE /MD
// AiOrdersManager::cloneOrderForPatrol: WB callsite/source/assert504.
// Native 0x0035560B..0x00355664 proves the order ID fields +0x10/+0x14,
// clone-producing vcall +0x34, and manager lookup at +0x10. Other fields
// and virtual purposes are intentionally unnamed. ArmorTemplate is only
// the existing lookup provider's spelling, not the order's identity.
class Object;
class ObjectLookupMap {
public:
    Object **findSlot(int *key);
    char opaque[0x14];
};
enum NameKeyType { NK_NONE = 0 };
class ArmorTemplate;
class Rva00355B61 {
public:
    const ArmorTemplate *rva00355155(NameKeyType) const;
};
class OrderCloneView {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual OrderCloneView *slot13();
    char opaque04[0x0c];
    int id10;
    int clone14;
};
class AiOrdersManager {
public:
    int cloneOrderForPatrol(int key);
private:
    char opaque00[0x10];
    ObjectLookupMap lookup10;
};
int AiOrdersManager::cloneOrderForPatrol(int key)
{
    int result = 0;
    if (key) {
        OrderCloneView *order = (OrderCloneView *)((Rva00355B61 *)this)->rva00355155((NameKeyType)key);
        if (order) {
            result = order->clone14;
            if (!result) {
                OrderCloneView *clone = order->slot13();
                if (clone) {
                    result = clone->id10;
                    order->clone14 = result;
                    int id = clone->id10;
                    *lookup10.findSlot(&id) = (Object *)clone;
                }
            }
        }
    }
    return result;
}
