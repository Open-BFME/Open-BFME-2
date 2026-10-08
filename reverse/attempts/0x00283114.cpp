// ?rva00283114@Rva00283114@@QAEXPAX@Z
// partial score=0.6166666666666667 date=2026-10-08
// cl: /O1 /Ob2 /arch:SSE /G7 /MD /EHs
// Native282B26..282B9F RET4. Vector10/14 contains groups. Each group's
// 1C/20 vector supplies candidate words; first matching candidate sets its
// flag and increments the result. Only the first matching group calls29BD.
// Layout and control flow are target facts; group/key semantics are open.
extern "C" void __cdecl free(void *);
class ModuleData;
namespace _STL {
template<class T> class allocator {};
template<class T, class A = allocator<T> > class vector {
public:
 T *m_start, *m_finish, *m_end_of_storage;
 T *erase(T *first, T *last);
 T *erase(T *position);
 void push_back(const T &value);
};
}
class Rva002829BD;
typedef void *(__cdecl *Rva00282B26Callback)(void *key);
class Rva002829BD
{
public:
 Rva002829BD(float padding);
 ~Rva002829BD() { if (begin) free(begin); }
 void rva002829BD(void *key, Rva00282B26Callback callback);
 unsigned char active;
 char pad[0x1C-1];
 void **begin;
 void **end;
 void **capacity;
};
class Rva004DFAB3 { public: bool rva004DFAB3(void *key, void *candidate); };
class Rva00282B26
{
public:
 int rva00282B26(void *key);
private:
 char pad0[0x10]; Rva002829BD **m_begin; Rva002829BD **m_end;
 char pad18[8]; Rva00282B26Callback m_callback;
};
int Rva00282B26::rva00282B26(void *key)
{
 int count = 0;
 Rva002829BD **it = m_begin;
 Rva002829BD **finish = m_end;
 for (; it != finish; ++it)
 {
  Rva002829BD *group = *it;
  void **lastCandidate = group->end;
  for (void **candidate = group->begin; candidate != lastCandidate; ++candidate)
  {
   if (((Rva004DFAB3 *)this)->rva004DFAB3(key, *candidate))
   {
    group->active = 1;
    if (count == 0)
     group->rva002829BD(key, m_callback);
    ++count;
    break;
   }
  }
 }
 return count;
}

// Native 283114..283246: reset every group flag, then use the rowed nested
// scan above. With no match, create a 40-byte group using virtual slot zero's
// float result. Otherwise merge all later marked groups into the first one,
// clear and delete the consumed groups, and erase their pointer slots.
// Group extent/fields and constructor ABI are target facts. The ModuleData
// pointer vector below retains the existing 49-byte provider's slot ABI;
// it does not identify the application elements as ModuleData objects.
class Rva00283114
{
public:
 virtual float padding() = 0;
 void rva00283114(void *key);
private:
 char m_pad04[0xC];
 _STL::vector<void *> m_groups;
 char m_pad1C[4];
 Rva00282B26Callback m_callback;
};

void Rva00283114::rva00283114(void *key)
{
 void **finish = m_groups.m_finish;
 _STL::vector<void *> *groups = &m_groups;
 for (void **it = groups->m_start; it != finish; ++it)
  ((Rva002829BD *)*it)->active = 0;
 if (!((Rva00282B26 *)this)->rva00282B26(key))
 {
  Rva002829BD *group = new Rva002829BD(padding());
  group->rva002829BD(key, m_callback);
  ((_STL::vector<const ModuleData *> *)groups)->push_back(
   *(const ModuleData *const *)&group);
  return;
 }
 Rva002829BD *first = 0;
 void **it = groups->m_start;
 finish = m_groups.m_finish;
 while (it != finish)
 {
  Rva002829BD *group = (Rva002829BD *)*it;
  if (group->active)
   first = group;
  ++it;
  if (first)
   break;
 }
 while (it != finish)
 {
  Rva002829BD *group = (Rva002829BD *)*it;
  if (group->active)
  {
   _STL::vector<void *> *values = (_STL::vector<void *> *)&group->begin;
   void **last = group->end;
   for (void **value = values->m_start; value != last; ++value)
    first->rva002829BD(*value, m_callback);
   values->erase(values->m_start, values->m_finish);
   delete group;
   it = groups->erase(it);
   finish = m_groups.m_finish;
  }
  else
   ++it;
 }
}

// Native 4DFE4F..4DFEC8 repeats the matched282B26 nested scan.
// Target fields and predicate are identical; only the first-match group
// callback moves to4DFCE6. Its indirect cdecl callback and ret8 establish
// the explicit argument ABI. Concrete container/group identity stays open.
class Rva004DFCE6;
typedef void *(__cdecl *Rva004DFE4FCallback)(void *key);
class Rva004DFCE6
{
public:
 void rva004DFCE6(void *key, Rva004DFE4FCallback callback);
 unsigned char active;
 char pad[0x1C-1];
 void **begin;
 void **end;
};
class Rva004DFE4F
{
public:
 int rva004DFE4F(void *key);
private:
 char pad0[0x10]; Rva004DFCE6 **m_begin; Rva004DFCE6 **m_end;
 char pad18[8]; Rva004DFE4FCallback m_callback;
};
int Rva004DFE4F::rva004DFE4F(void *key)
{
 int count = 0;
 Rva004DFCE6 **it = m_begin;
 Rva004DFCE6 **finish = m_end;
 for (; it != finish; ++it)
 {
  Rva004DFCE6 *group = *it;
  void **lastCandidate = group->end;
  for (void **candidate = group->begin; candidate != lastCandidate; ++candidate)
  {
   if (((Rva004DFAB3 *)this)->rva004DFAB3(key, *candidate))
   {
    group->active = 1;
    if (count == 0)
     group->rva004DFCE6(key, m_callback);
    ++count;
    break;
   }
  }
 }
 return count;
}
