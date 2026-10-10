// ?rva0059614B@AIUnitStats@@QAE_NPAX@Z
// partial score=0.979429789501732 date=2026-10-10
// ?rva0059614B@AIUnitStats@@QAE_NPAX@Z
// partial score=0.9280575539 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD
// ?Register@AIUnitStats@@QAE_NPAX@Z @0x005962F7 111B.
// Predicate over holder driven by 0x005960FF bit-test plus base push and
// element clear with Science vector at plus 0x98 on the Check-false path.
// Evidence: thiscall ret 4 returning al 1 or 0; Get 0x005960FF rowed;
// Check 0x004884B7 rowed; base 0x0025C061 rowed; element 0x003ECB52 rowed;
// vector push_back 0x002E01C6 rowed; callers at 0x004E024A unclaimed;
// prev 0x005962E7 step next 0x00596366 ctor prove Common owner.
typedef int Int;
Int __stdcall Rva005960FFGet(void *arg);

class Object;
bool __cdecl rva004884B7(Object *obj);

enum ObjectID { OBJECT_FIRST=0 };

enum ScienceType
{
	SCIENCE_FIRST = 0
};

namespace _STL
{

template<class I,class V> I find(I,I,const V&);

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	void push_back(const _Tp &v);
 _Tp *erase(_Tp *);
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_end;
};

}

class Rva0025C061
{
public:
	void rva0025C061(void *holder);
private:
	int m_unk0;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_sciences;
};

struct Rva003ECB52Arg;

class Rva003ECA69Element
{
public:
	Rva003ECA69Element *rva003ECB52(Rva003ECB52Arg *arg);
 Rva003ECA69Element *rva003ECB94(Rva003ECB52Arg *arg);
};

class Rva0025BF8C {public:bool rva0025BF8C(void*);};

class AIUnitStats : public Rva0025C061
{
public:
	bool Register(void *holder);
 bool rva0059614B(void *holder);
};

bool AIUnitStats::Register(void *holder)
{
	if (((unsigned char)Rva005960FFGet(holder)) != 0) {
		void *inner = *(void **)((char *)holder + 4);
		unsigned int flags = *(unsigned int *)((char *)inner + 0x108);
		if ((flags & 8) == 0 && (((unsigned char *)inner)[0x113] & 4) == 0) {
			if ((flags & 0x4000) != 0) {
				if (!rva004884B7((Object *)holder))
					((_STL::vector<ScienceType, _STL::allocator<ScienceType> > *)((char *)this + 0x98))->push_back((ScienceType)*(int *)((char *)holder + 0x74));
			}
		} else {
			((Rva0025C061 *)this)->rva0025C061(holder);
			((Rva003ECA69Element *)((char *)this + 0x10))->rva003ECB52((Rva003ECB52Arg *)holder);
		}
		return true;
	}
	return false;
}

bool AIUnitStats::rva0059614B(void *holder) {
 if((unsigned char)Rva005960FFGet(holder)) {
  void *inner=*(void**)((char*)holder+4);
  unsigned int flags=*(unsigned int*)((char*)inner+0x108);
  if((flags&8)==0 && (((unsigned char*)inner)[0x113]&4)==0) {
   if(flags&0x4000) {
    if(!rva004884B7((Object*)holder)) {
     typedef _STL::vector<ObjectID,_STL::allocator<ObjectID> > IdVector;
     IdVector *v=(IdVector*)((char*)this+0x98);
     ObjectID value=*(ObjectID*)((char*)holder+0x74);
     ObjectID *end=v->m_finish;
     ObjectID *found=_STL::find(v->m_start,end,value);
     if(found!=end)v->erase(found);
    }
   }
  } else {
   if(((Rva0025BF8C*)this)->rva0025BF8C(holder))
    ((Rva003ECA69Element*)((char*)this+0x10))->rva003ECB94((Rva003ECB52Arg*)holder);
  }
  return true;
 }
 return false;
}
