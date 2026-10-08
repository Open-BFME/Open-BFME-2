// cl: /O1 /arch:SSE /G7 /MD
// Native282B26..282B9F RET4. Vector10/14 contains groups. Each group's
// 1C/20 vector supplies candidate words; first matching candidate sets its
// flag and increments the result. Only the first matching group calls29BD.
// Layout and control flow are target facts; group/key semantics are open.
class Rva002829BD;
typedef void *(__cdecl *Rva00282B26Callback)(void *key);
class Rva002829BD
{
public:
 void rva002829BD(void *key, Rva00282B26Callback callback);
 unsigned char active;
 char pad[0x1C-1];
 void **begin;
 void **end;
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
