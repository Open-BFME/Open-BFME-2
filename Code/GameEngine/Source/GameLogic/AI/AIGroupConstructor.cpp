// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /arch:SSE /G7 /I.
// stlport
// AIGroup::AIGroup: native 0036E4C7..0036E55E RET0 (151 bytes).
// BF1 f98983a7d AIGroupConstructor and ZH AIGroup.cpp are semantic leads.
// AI::createGroup (2FEC4B) allocates3C and calls this; retail vtableC17D00
// and its unique AIGroup name getter independently identify the class.
// WB EDCDF0 confirms list4 plus the two12B coordinate members18/24.
// Target getSpeed36E333 proves speed8/dirtyC; ID10 reads AI nextID1C.
// Retail float bytes at7C2428 establish spacing10, agreeing with WB.
// Existing getAllIDs owner36F710 establishes
// the vector<ObjectID> at30 independently of the BF1 formation layout.
// Sequential canonical Coord3D zero helper preserves native pointer-clear
// before XORPS scheduling. Real Object-pointer list constructor41B folds
// at4EC36C; the old1EB98440B pin is a distinct candidate, not this call.
#include <list>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
class Object {public: void leaveGroup();};
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <vector>

typedef unsigned int UnsignedInt;

class AI
{
public:
	UnsignedInt getNextGroupID() { return ++m_nextGroupID; }

private:
	unsigned char m_unmodelled[0x1C];
	UnsignedInt m_nextGroupID;
};

extern AI *TheAI;



enum ObjectID { INVALID_OBJECT_ID = 0 };

#define BFME_SNAPSHOT_NAME_SLOT
#include "reference/shims/moduledata/Common/Snapshot.h"

class AIGroup : public Snapshot
{
public:
	AIGroup();
 void rva0036CE87();
protected:
 virtual ~AIGroup();
public:
 virtual void loadPostProcess();
 virtual const char *GetSnapshotName() const;
 virtual void xfer(Xfer *);

private:
	
	_STL::list<Object *> m_memberList;
	float m_speed;
	bool m_dirty;
	UnsignedInt m_id;
	void *m_groundPath;
	Coord3D m_position;
	Coord3D m_spacing;
	_STL::vector<ObjectID> m_lastRequestedIDList;
};

static __forceinline void zero(Coord3D& p){p.x=0.0f;p.y=0.0f;p.z=0.0f;}
AIGroup::AIGroup()
{
	m_groundPath = 0;
	float tmp24 = 10.0f;
	zero(m_position);
	m_spacing.x = tmp24;
	m_spacing.y = 0.0f;
	m_spacing.z = 0.0f;
	m_speed = 0.0f;
	m_dirty = false;
	m_id = TheAI->getNextGroupID();
	m_memberList.clear();
}

// Native36E564..36E5F1 RET0. Scalar deleting wrapper36E8EA calls
// this protected destructor. BF1 f989 AIGroupDestructors supplies the
// remove-or-erase loop; WBEDD090 and native calls28C01F/36CE87 prove
// the BFME2 reset helper. Iterator/Object* payload and vector<ObjectID>
// layout are shared with the verified constructor and getAllIDs owner.
AIGroup::~AIGroup()
{
    std::list<Object*>::iterator i=m_memberList.begin();
    while(i!=m_memberList.end()) {
        Object*member=*i;
        if(member) {member->leaveGroup(); i=m_memberList.begin();}
        else {i=m_memberList.erase(i);}
    }
    rva0036CE87();
}
