// WB 0x015FDF40 names SelectedMemberDestPicker::IsPickable (line 350).
// Native 0x005E575E / 68 B and vtable 0x00C77D90 slot 7 corroborate
// the virtual member ABI. The owner +8 -> army +0x18 -> player id +0x54
// chain agrees in WB and retail. The unnamed slot 6 consumes the selected
// army; region and slot argument types are pointer ABI views, not full layouts.
// Use the established singleton type and query's corrected thiscall ABI;
// the previous bank's stdcall declaration omitted a required ECX load.
// cl: /O1 /arch:SSE /G7 /MD /EHs /EHc- /D_STLP_USE_MALLOC /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /DNDEBUG
// stlport
#include <vector>
#include <map>
#include <set>
struct Rva005E59FCKeyIterator {
 typedef _STL::bidirectional_iterator_tag iterator_category;
 typedef int value_type;
 typedef int difference_type;
 typedef int *pointer;
 typedef int &reference;
 _STL::_Rb_tree_node_base *node;
 Rva005E59FCKeyIterator(_STL::set<int>::iterator it):node(it._M_node) {}
 int &operator*() const {return *(int*)((char*)node+16);}
 Rva005E59FCKeyIterator &operator++(){node=_STL::_Rb_global<bool>::_M_increment(node);return *this;}
 Rva005E59FCKeyIterator &operator--(){node=_STL::_Rb_global<bool>::_M_decrement(node);return *this;}
 bool operator==(const Rva005E59FCKeyIterator&b)const{return node==b.node;}
 bool operator!=(const Rva005E59FCKeyIterator&b)const{return node!=b.node;}
};
// The 12-byte vector ABI is established by the rowed range constructor
// at 0x005E60D1 and its base at 0x00211E58. Declare that constructor here
// so this caller cannot emit competing range/copy helpers. The destructor
// follows the observed start-pointer test and free at both return sites.
namespace _STL {
template <> class vector<int, allocator<int> > {
public:
    template <class Iter> vector(Iter, Iter, const allocator<int>&);
    ~vector() { if (start) ::free(start); }
private:
    int *start;
    int *finish;
    int *end_of_storage;
};
}


struct Rva002B488EResult;
class Rva002B6C9F {public: bool rva002B6CE5(int,int,int);};
struct Rva005E6110OwnerView
{
    unsigned char m_pad00[0x18];
    void *m_army;
    unsigned char m_pad1C[0x2c-0x1c];
    _STL::set<int> m_keyView; // layout view only: original payload is unresolved
};
class Rva002E2903Player;
class Rva002BA8F1Logic
{
public:
    Rva002E2903Player *find(int id, unsigned int *index);
    Rva002B488EResult *rva002B488E(int armyID);
};
class LivingWorldLogic
{
public:
    void *rva002B4948(void *owner, void *region, void *excludedArmy);
};
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva005E575EArmyView
{
    unsigned char m_pad00[0x54];
    int m_playerID;
};
struct Rva005E575EOwnerView
{
    unsigned char m_pad00[0x18];
    Rva005E575EArmyView *m_army;
};
class StrategicInGameUI
{
public:
    class PlanningPhaseArmySelection
    {
    public:
        class Impl
        {
        public:
            class SelectedMemberArmyDest
            {
            public:
                virtual void slot00();
                virtual void slot01();
                virtual void slot02();
                virtual int GetMouseCursor();
            private:
                Rva005E6110OwnerView *m_owner;
                int m_armyID;
            };
            class SelectedMemberDestPicker
            {
            public:
                virtual void slot00() throw();
                virtual void slot01() throw();
                virtual void slot02() throw();
                virtual void slot03() throw();
                virtual void slot04() throw();
                virtual void slot05() throw();
                virtual bool rva005E575EQuery(void *army) throw();
                virtual bool IsPickable(void *region);
            private:
                int m_field04;
                Rva005E575EOwnerView *m_owner;
            };
        };
    };
};
bool StrategicInGameUI::PlanningPhaseArmySelection::Impl::SelectedMemberDestPicker::IsPickable(void *region)
{
    int id = m_owner->m_army->m_playerID;
    Rva002E2903Player *player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(id, 0);
    if (player != 0)
    {
        void *found = TheLivingWorldLogic->rva002B4948(player, region, 0);
        if (found != 0)
            return rva005E575EQuery(found);
    }
    return false;
}

// Named WB 0x015FD520 (line 200); native Ghidra 0x005E6110 / 152 B and vtable
// 0x00C77D44 slot 3 establish the virtual cursor query. The range constructor
// and key-only iterator ABI are the already verified 0x005E60D1 provider;
// original tree payload remains unresolved. Cursor 14 is returned when the
// singleton's existing movement check succeeds, else -1. Both temporary-vector
// cleanup paths and their EH states must reproduce retail.
int StrategicInGameUI::PlanningPhaseArmySelection::Impl::SelectedMemberArmyDest::GetMouseCursor()
{
    Rva002B488EResult *army = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->rva002B488E(m_armyID);
    _STL::vector<int> values(Rva005E59FCKeyIterator(m_owner->m_keyView.begin()),
        Rva005E59FCKeyIterator(m_owner->m_keyView.end()), _STL::allocator<int>());
    if (army && reinterpret_cast<Rva002B6C9F *>(TheLivingWorldLogic)->rva002B6CE5(
            (int)m_owner->m_army, (int)&values, (int)army))
        return 14;
    return -1;
}
