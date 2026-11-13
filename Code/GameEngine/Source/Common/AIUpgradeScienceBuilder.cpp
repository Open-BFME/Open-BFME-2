// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// The science builder shuts down its +0x0C base and destroys its three
// vectors before restoring the secondary and primary bases.
#include <vector>

enum ObjectID { INVALID_ID = 0 };

class Object;
#include "../../Include/Common/BaseA.h"

class Rva00506B1B
{
public:
    virtual ~Rva00506B1B();
    virtual void rva00597fc5() = 0;
    virtual void shutdown() = 0;
    bool m_04;
};

class AIUpgradeScienceBuilder : public BaseA, public Rva00506B1B
{
public:
    virtual void Register(Object *, void *);
    virtual void UnRegister(Object *);
    virtual ~AIUpgradeScienceBuilder();
    virtual void rva00597fc5();
    virtual void shutdown();
private:
	char m_pad14[0x18 - 0x14];
	_STL::vector<ObjectID> m_vec18;
	_STL::vector<ObjectID> m_vec24;
	_STL::vector<ObjectID> m_vec30;
};

AIUpgradeScienceBuilder::~AIUpgradeScienceBuilder()
{
	AIUpgradeScienceBuilder::shutdown();
}
