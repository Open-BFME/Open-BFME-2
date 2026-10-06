// ?rva004F5473@Rva004F54BF@@QAE_NPAVObject@@_N@Z
// cl: /DNDEBUG /MD /EHsc
// stlport
// ?rva004F5473@Rva004F54BF@@QAE_NPAVObject@@_N@Z, retail 0x004F5473, 76 bytes.
// Finish lane from stash 0x004f5473 (score 0.93): count-limit check with testStatus 0x26 and flag109 0x10 guards.
// Layout: Rva004F54BF list at +0x10 count at +0x18 per neighbours Rva004F5436Count plus Rva004F54BFRemove; Object+4 inner flag109; GlobalData limit at +0xA98. Evidence: finish packet slot plus callers 0x004664FC 0x0047DDD0.
#include <list>

enum ObjectID
{
	OBJECTID_NONE = 0
};

namespace _STL
{
template <class _InputIter, class _Tp>
_InputIter find(_InputIter __first, _InputIter __last, const _Tp &__val);
}

class Rva004F54BF
{
public:
	bool rva004F5473(class Object *obj, bool flag);
private:
	char m_pad[0x10];
	_STL::list<ObjectID> m_list;
	int m_14;
	int m_count;
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

struct Rva004F5473Inner
{
	char m_pad[0x109];
	unsigned char m_flag109;
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes status) const;
	char m_pad0[4];
	Rva004F5473Inner *m_04;
};

class GlobalData
{
public:
	char m_pad[0xa98];
	int m_limitA98;
};

extern GlobalData *TheWritableGlobalData;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

bool Rva004F54BF::rva004F5473(Object *obj, bool flag)
{
	if (obj != 0) {
		if ((obj->m_04->m_flag109 & 0x10) == 0) {
			if (!flag || obj->testStatus(OBJECT_STATUS_26))
				return true;
			int limit = TheWritableGlobalData->m_limitA98;
			int count = m_count;
			_ReadWriteBarrier();
			return count < limit;
		}
	}
	return false;
}
