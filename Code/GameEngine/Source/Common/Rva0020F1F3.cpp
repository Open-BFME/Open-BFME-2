// cl: /O1 /arch:SSE /G7 /MD /Ireference/shims/bfme2_ascii
// Native 0020F1F3..0020F27E RET4. Find a record by its leading string,
// select it at +8, rebuild region effects, and reset each child at +2C.
// The pointer-vector boundaries and calls are target facts; the record
// identity remains unresolved. The receiver is
// LivingWorldRegionManager::SelectCampaign per WorldBuilder.
#include "string_base.h"
class Rva003F3F27 { public: void rva003F3F27(); };
template<class T> struct Rva0020F1F3Vector
{
 T *begin;
 T *end;
 T *capacity;
 unsigned size() const { return (unsigned)(end - begin); }
 T &operator[](unsigned i) { return begin[i]; }
};
struct Rva0020F1F3Record
{
 StringBase<char> name;
 char pad[0x2C-4];
 Rva0020F1F3Vector<Rva003F3F27 *> children;
};
class LivingWorldManager { public: void SetUpRegionEffectsManager(); };
extern LivingWorldManager *TheLivingWorldManager;
class LivingWorldRegionManager
{
public:
 void SelectCampaign(const StringBase<char> &name);
private:
 char pad0[8];
 Rva0020F1F3Record *m_current;
 char padC[0x34-0xC];
 Rva0020F1F3Vector<Rva0020F1F3Record *> m_records;
};

void LivingWorldRegionManager::SelectCampaign(const StringBase<char> &name)
{
 for (unsigned i = 0; i < m_records.size(); ++i)
 {
  if (name.compare(m_records[i]->name) == 0)
  {
   if (m_current && m_current != m_records[i])
    m_current = 0;
   m_current = m_records[i];
   TheLivingWorldManager->SetUpRegionEffectsManager();
   Rva0020F1F3Vector<Rva003F3F27 *> *children = &m_current->children;
   for (unsigned j = 0; j < children->size(); ++j)
    (*children)[j]->rva003F3F27();
   break;
  }
 }
}
