// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /O1 /arch:SSE /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Import-inline: this unit's bfmealloc _Vector_base<Object*> dtor copy is not retail's
// EH-framed body (0x001F1609); its uses here are all inlined, so none is emitted.
class Object;
namespace _STL { template <> __declspec(dllimport) __forceinline _Vector_base<Object *, allocator<Object *> >::~_Vector_base() { if (this->_M_start != 0) this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start); } }
// Likewise import-inline vector<Object*>'s dtor: retail's out-of-line copy is the
// tail jump to the EH-framed base dtor (0x001F22A3), not this unit's inline form.
namespace _STL { template <> __declspec(dllimport) __forceinline vector<Object *, allocator<Object *> >::~vector() { _Destroy(this->_M_start, this->_M_finish); } }

class Object;
typedef void *(__cdecl *Rva00282B26Callback)(void *key);
// The 40-byte group built by the rowed constructor 0x00281A76; the member
// call 0x002829BD is the rowed sphere merge (Rva002829BDSphereMerge.cpp).
class ModuleData;
class Rva002829BD { public: void rva002829BD(const ModuleData *key, Rva00282B26Callback callback); };
class Rva00281A76
{
public:
 Rva00281A76(float);
 void add(void *key, Rva00282B26Callback callback) { ((Rva002829BD *)this)->rva002829BD((const ModuleData *)key, callback); }
 bool active00; float radius04, centerX08, centerY0C, centerZ10; float padding14; bool selected18;
 _STL::vector<Object *> objects1C;
 ~Rva00281A76() {}
};
class Rva00282B26 { public: int rva00282B26(void *key); };

// Native 00283114..00283246 RET4: clear every group's active flag and run the
// rowed nested scan 0x00282B26. No match: build a new group from virtual slot
// zero's padding and append it. Otherwise merge each later active group into
// the first active one, then destroy it and erase its slot.
class Rva00283114
{
public:
 virtual float padding() = 0;
 void rva00283114(void *key);
private:
 char m_pad04[0xC];
 _STL::vector<Rva00281A76 *> m_groups;
 int m_1C;
 Rva00282B26Callback m_callback;
};

void Rva00283114::rva00283114(void *key)
{
 Rva00281A76 *group;
 _STL::vector<Rva00281A76 *>::iterator it;
 _STL::vector<Rva00281A76 *>::iterator end = m_groups.end();
 for (it = m_groups.begin(); it != end; ++it)
 {
  Rva00281A76 *g = *it;
  g->active00 = false;
 }
 int count = ((Rva00282B26 *)this)->rva00282B26(key);
 if (count == 0)
 {
  group = new Rva00281A76(padding());
  group->add(key, m_callback);
  m_groups.push_back(group);
  return;
 }
 Rva00281A76 *first = 0;
 it = m_groups.begin();
 end = m_groups.end();
 while (first == 0 && it != end)
 {
  if ((*it)->active00)
   first = *it;
  ++it;
 }
 while (it != end)
 {
  if ((*it)->active00)
  {
   group = *it;
   _STL::vector<Object *> &objects = group->objects1C;
   _STL::vector<Object *>::iterator oend = objects.end();
   for (_STL::vector<Object *>::iterator o = objects.begin(); o != oend; ++o)
    first->add(*o, m_callback);
   objects.erase(objects.begin(), objects.end());
   delete group;
   it = m_groups.erase(it);
   end = m_groups.end();
  }
  else
   ++it;
 }
}
