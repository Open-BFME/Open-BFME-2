// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
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

#include <vector>

namespace _STL
{
// Bind the three vector/find calls to their rowed bodies (push_back
// 0x002E01C6, find 0x0020E873 and the element erase) instead of emitting
// second copies of the STLport headers' inline definitions.
template <> ObjectID *find(ObjectID *, ObjectID *, const ObjectID &);
template <> void vector<ScienceType, allocator<ScienceType> >::push_back(const ScienceType &);
template <> ObjectID *vector<ObjectID, allocator<ObjectID> >::erase(ObjectID *);
}

// The canonical vector keeps its three pointers protected; read them through a
// layout view of the same 12 bytes.
struct BfmeIdVectorView
{
	ObjectID *m_start;
	ObjectID *m_finish;
	ObjectID *m_end;
};

class Rva0025C061
{
public:
	void addObject(void *holder);
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

class AIStatBase {public:bool removeObject(void*);};

class AIUnitStats : public Rva0025C061
{
public:
	bool Register(void *holder);
 bool UnRegister(void *holder);
 private:
  typedef _STL::vector<ObjectID,_STL::allocator<ObjectID> > IdVector;
  IdVector &ids() { return *(IdVector *)((char *)this + 0x98); }   // +0x98
 public:
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
			((Rva0025C061 *)this)->addObject(holder);
			((Rva003ECA69Element *)((char *)this + 0x10))->rva003ECB52((Rva003ECB52Arg *)holder);
		}
		return true;
	}
	return false;
}

// Native 0x0059614B..0x005961D6 (139B, RET 4): Register's removal twin.
// On the Check-false path it erases the holder's ID (+0x74) from the
// +0x98 ID vector (find 0x0020E873, erase); otherwise it forwards to the
// +0x10 element like Register. The vector is reached through an accessor
// at each use: native adjusts ESI to it only after pushing the value
// address, which a cached vector pointer moves ahead of the push.
// WorldBuilder AIUnitStats::UnRegister, WB VA 0x0148E380 (callgraph lead, score 2).
bool AIUnitStats::UnRegister(void *holder) {
 if((unsigned char)Rva005960FFGet(holder)) {
  void *inner=*(void**)((char*)holder+4);
  unsigned int flags=*(unsigned int*)((char*)inner+0x108);
  if((flags&8)==0 && (((unsigned char*)inner)[0x113]&4)==0) {
   if(flags&0x4000) {
    if(!rva004884B7((Object*)holder)) {
     ObjectID value=*(ObjectID*)((char*)holder+0x74);
     ObjectID *end=((BfmeIdVectorView*)&ids())->m_finish;
     ObjectID *found=_STL::find(((BfmeIdVectorView*)&ids())->m_start,end,value);
     if(found!=end)ids().erase(found);
    }
   }
  } else {
   if(((AIStatBase*)this)->removeObject(holder))
    ((Rva003ECA69Element*)((char*)this+0x10))->rva003ECB94((Rva003ECB52Arg*)holder);
  }
  return true;
 }
 return false;
}
