// cl: /O1 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// Native 0041F042..0041F095 destroys its two 20-byte tables at +20 and
// +0C after draining the global registry, then destroys its 12-byte base.
// Keep the established address-derived owner; the original manager name
// and the tables' mapped types are unresolved.
typedef bool Bool;
#include "subsystem_interface.h"

struct OwnedBucketStorage
{
	void **begin;
	void **end;
	void **capacity;
};

class Rva0041E77F
{
public:
	~Rva0041E77F();
private:
	int m_functors;
	OwnedBucketStorage m_buckets;
	unsigned int m_count;
};

class Rva0041EA88
{
public:
	~Rva0041EA88();
private:
	int m_functors;
	OwnedBucketStorage m_buckets;
	unsigned int m_count;
};

// C3AF78's 14 slots override lifetime, init, postProcessLoad, reset and
// update; the remaining nine entries are the canonical subsystem defaults.
class Rva0041F042 : public SubsystemInterface
{
public:
	virtual ~Rva0041F042();
	virtual void init();
	virtual void postProcessLoad();
	virtual void reset();
	virtual void update();
	void rva0041EC10();
private:
	Rva0041E77F m_table0C;
	Rva0041EA88 m_table20;
};

Rva0041F042::~Rva0041F042()
{
	rva0041EC10();
}
