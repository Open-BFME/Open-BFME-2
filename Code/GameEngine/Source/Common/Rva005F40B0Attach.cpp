// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?rva005F40B0@Rva005F40B0@@QAEXXZ @0x005F40B0 123B.
// Slot target of the tail jump at 0x005F41AF. When the reference member at +0x0C
// is still empty, asks the source object at +4 for a key (its second virtual),
// fetches a counted reference for it (its third virtual, returned by value) into
// the member through the shared intrusive-reference assignment (0x002174A4),
// drops the temporary through the rowed release (0x0007DEEF), pushes the byte at
// +0x14 into the target (0x005FC6F7) and registers this object on the target's
// listener list at +8 (0x005A0B4C). A set reference is then touched through the
// pointer-chase getter 0x005FC745. Layout views are neutral.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class AptCommandMap;
template <class T>
class AptRef
{
public:
	AptRef() : m_ptr(0) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	AptRef &operator=(const AptRef &other);
	TargetRef00217D4C *m_ptr;
};

struct Rva002BA8F1Listener;
#include "../../Include/Common/Rva005A0B4CList.h"

#include "../../Include/Common/Rva005FC6F7.h"

class Rva005FC745PtrChaseField
{
public:
	void *get() const;
};

class Rva005F40B0Source
{
public:
	virtual void slot0();
	virtual void *findKey();
	virtual AptRef<AptCommandMap> getReference(void *key);
};

// Neutral view of the referenced target: only the offsets this body uses.
class Rva005F40B0Target
{
public:
	void rva005FC6F7(unsigned char flag) { reinterpret_cast<Rva005FC6F7 *>(this)->rva005FC6F7(flag); }
	Rva005A0B4CList *listeners() { return reinterpret_cast<Rva005A0B4CList *>(reinterpret_cast<char *>(this) + 8); }
	void *get() const { return reinterpret_cast<const Rva005FC745PtrChaseField *>(this)->get(); }
};

class Rva005F40B0
{
public:
	void rva005F40B0();
private:
	void *m_00;
	Rva005F40B0Source *m_source;
	int m_08;
	AptRef<AptCommandMap> m_reference;
	unsigned char m_10;
	unsigned char m_pad11[3];
	unsigned char m_flag;
};

void Rva005F40B0::rva005F40B0()
{
	if (!m_reference.m_ptr)
	{
		void *key = m_source->findKey();
		if (key)
		{
			m_reference = m_source->getReference(key);
			reinterpret_cast<Rva005F40B0Target *>(m_reference.m_ptr)->rva005FC6F7(m_flag);
			reinterpret_cast<Rva005F40B0Target *>(m_reference.m_ptr)->listeners()->append(reinterpret_cast<Rva002BA8F1Listener *>(this));
		}
	}
	if (m_reference.m_ptr)
		reinterpret_cast<Rva005F40B0Target *>(m_reference.m_ptr)->get();
}
