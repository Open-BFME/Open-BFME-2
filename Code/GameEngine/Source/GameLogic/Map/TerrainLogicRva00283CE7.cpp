// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Native00283CE7..00283D70, 137B, RET4. TerrainLogic receiver from rowed
// sibling query00283D70 and its callers. Pointer range578/57C, child584,
// stamp1910 and record key+C are measured; original member names unknown.
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva00283CE7FrameView { char unknown00[0x40]; unsigned int frame; };
class Rva0027D098
{
public:
    void rva0027D098();
};
struct Rva00283CE7RecordView { char unknown00[12]; unsigned int key; };
class Rva002872BA
{
public:
    void rva0028641F(unsigned int key, Rva0027D098 *record);
};
extern Rva002872BA *TheTriggerManager;
class G00DFF080Obj;
extern G00DFF080Obj *g_00DFF080;
template<int N> class Rva00283CE7Slots : public Rva00283CE7Slots<N-1>
{
public:
    virtual void unused(char (*)[N]) = 0;
};
template<> class Rva00283CE7Slots<0> {};
class Rva00283CE7GlobalView : public Rva00283CE7Slots<22>
{
public:
    virtual void slot58(unsigned int key) = 0;
};
class Rva00283CB3
{
public:
    void rva00283CB3(Rva0027D098 *record);
};
class TerrainLogic
{
public:
    void rva00283CE7(unsigned int key);
private:
    char unknown00[0x578];
    Rva0027D098 **first, **last, **limit;
    Rva00283CB3 *child;
    char unknown588[0x1910 - 0x588];
    unsigned int stamp;
};
void TerrainLogic::rva00283CE7(unsigned int key)
{
    stamp = reinterpret_cast<Rva00283CE7FrameView *>(TheGameLogic)->frame;
    for (Rva0027D098 **i=first; i!=last; ++i)
    {
        if (reinterpret_cast<Rva00283CE7RecordView *>(*i)->key == key)
        {
            if (TheTriggerManager)
                TheTriggerManager->rva0028641F(key, *i);
            (*i)->rva0027D098();
            break;
        }
    }
    reinterpret_cast<Rva00283CE7GlobalView *>(g_00DFF080)->slot58(key);
    Rva0027D098 **end=last;
    for (Rva0027D098 **i=first; i!=end; ++i)
    {
        if (reinterpret_cast<Rva00283CE7RecordView *>(*i)->key == key)
        {
            child->rva00283CB3(*i);
            break;
        }
    }
}
