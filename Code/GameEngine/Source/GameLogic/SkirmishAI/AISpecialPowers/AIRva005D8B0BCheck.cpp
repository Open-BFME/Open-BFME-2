// cl: /O1 /G7 /arch:SSE /EHs /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva005D8B0B@Rva005D8AE4@@UAE_NPAVObject@@@Z @0x005D8B0B 184B
// Method of the AoE picker derivative Rva005D8AE4 (dtor 0x005D8AE4, base chain Rva005EE30C ->
// the picker Rva005EE816 of AISPecialPowerTargetAoE.cpp): true when the object's AI has a
// current victim and the corner scan Rva005EE816::rva005EE5D7 (allies, collecting the objects it
// counted) found at least ten and the collected-total-over-count ratio does not exceed 0.75.
// Evidence: target bytes (the scan's documented caller 0x005D8B0B) and WB debug body 01599340
// (unnamed): its per-object virtual summation loop has no retail code, leaving the zero total
// that retail divides by the collected count. The meaning of the ratio is inferred.
#include <vector>

class Object;
// The vector's block is freed through the game allocator's free wrapper (rowed 0x00030830) under
// the CRT name every bfmealloc unit's copy calls. /EHs, not /EHsc: retail leaves EH state -1
// before that call, so cl must treat the extern "C" free as able to throw. Import-inline: this
// unit's out-of-line _Vector_base<Object*> dtor copy is not retail's EH-framed body, and every
// use here is inlined, so none is emitted.
namespace _STL {template<> __declspec(dllimport) __forceinline _Vector_base<Object *, allocator<Object *> >::~_Vector_base() {if(_M_start)free(_M_start);}}
#include "../../../../Include/GameLogic/Module/AIUpdate.h"

struct Rva005D8B0BObject
{
	char m_pad[0x258];
	AIUpdateInterface *m_ai;
};

class Rva005EE816
{
public:
	unsigned rva005EE5D7(Object *source, bool allies, _STL::vector<Object *> *found);
};

class Rva005D8AE4
{
public:
	virtual bool rva005D8B0B(Object *source);
};

bool Rva005D8AE4::rva005D8B0B(Object *source)
{
	bool hasVictim = ((Rva005D8B0BObject *)source)->m_ai->getCurrentVictim() != 0;
	_STL::vector<Object *> found;
	if (hasVictim)
	{
		if (((Rva005EE816 *)this)->rva005EE5D7(source, true, &found) >= 10)
		{
			float total = 0.0f;
			float ratio = total / (float)found.size();
			if (ratio <= 0.75f)
				return true;
		}
	}
	return false;
}
