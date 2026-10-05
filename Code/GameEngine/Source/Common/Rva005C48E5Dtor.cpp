// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/moduledata
//
// ??1Rva005C48E5@@UAE@XZ @0x005C48E5 (85B)

#include "Common/Snapshot.h"

class PrimaryBase : public Snapshot
{
public:
	inline virtual ~PrimaryBase() {}
	int m_pad04;
	int m_pad08;
};

class SecondaryBase
{
public:
	virtual ~SecondaryBase();
};

class Rva005C48B2Listener
{
public:
	virtual void notify(void *);
};

class Rva005C48B2List
{
public:
	void forEach(void (Rva005C48B2Listener::*notify)(void *), void *arg);
};

class Rva005C48E5 : public PrimaryBase, public SecondaryBase
{
public:
	virtual ~Rva005C48E5();

private:
	Rva005C48B2List m_listeners;
};

Rva005C48E5::~Rva005C48E5()
{
	m_listeners.forEach(&Rva005C48B2Listener::notify, static_cast<SecondaryBase *>(this));
}
