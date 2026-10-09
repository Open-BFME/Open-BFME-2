// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// Native200280..20030F. BFME1 f989 RankInfoDestructors.cpp and ZH
// RankInfoStore::~RankInfoStore supply the signed deletion loop and clear.
// Target evidence: BE2704 table and rowed constructor/deleting destructor
// retain the existing Rva0022CA74 owner, vector at0C and SubsystemInterface
// base at0; GameEngine registration supports the rank-store role separately.
// Native slot0 flag0 followed by global delete requires ::delete, guarded
// by the donor's explicit null test. Pointer storage uses the already rowed
// void-pointer erase fold. Game allocator30830 retains native EH state0;
// ordinary CRT free is nonthrowing and incorrectly removes that transition.
#include <vector>
void Rva00030830FreeAllocation(void *);
namespace _STL {
template<> inline void allocator<void *>::deallocate(void **p,unsigned int) const
{
 if(p) Rva00030830FreeAllocation(p);
}
}
class SubsystemInterface
{
public:
 virtual ~SubsystemInterface();
private:
 char pad[8];
};
class RankInfo { public: virtual ~RankInfo(); };
class Rva0022CA74 : public SubsystemInterface
{
protected:
 virtual ~Rva0022CA74();
private:
 std::vector<void *> ranks;
};
Rva0022CA74::~Rva0022CA74()
{
 for(int i=0; i<(int)ranks.size(); ++i)
 {
  RankInfo *r=(RankInfo *)ranks[i];
  if(r) ::delete r;
 }
 ranks.clear();
}
