// cl: /O1 /EHs /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva001B505F@SubsystemInterfaceList@@QAEEXZ @0x001B505F 225B (WB 0xA755A0, unnamed).
// Sibling of the SubsystemInterfaceList members around it (0x001B4FE9, 0x001B5018,
// 0x001B51C0): every non-null subsystem of the 8-byte records at +0x00 and of the
// pointer vector at +0x0C is offered to the member 0x001B4E21 (retail passes ECX=this,
// so it is spelled as a member here and reached through an address-named pin beside
// its stdcall row; its body never reads this), a success flags the result, and the
// subsystem is collected in a local vector; each collected entry then gets virtual
// slot 7 with the flag byte 0x001B4E21 filled, and the rowed Rva0002BBC9Update runs
// when anything succeeded. The local vector's element type is the rowed owner of
// push_back 0x004DFCB0, not a recovered type.
// Codegen: /EHs (not /EHsc) makes the _free in the vector destructor potentially
// throwing, which emits retail's state -1 store and the guarded, bottom-tested loops;
// obj and flag declared at function scope before the vector give retail's frame slots.
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &, unsigned int const &); }
// bfme link decl-only end

class ModuleData;
// push_back's overflow is retail's 0x002DFCF6 body (ModuleFactory.cpp), which inlines
// max(size(), n); the declaration-only max<unsigned> above would make this TU's copy
// call it, so spell the inline form out here.
static inline const unsigned int &moduleOverflowMax(const unsigned int &left, const unsigned int &right)
{
	return left < right ? right : left;
}
namespace _STL {
template <> inline void vector<const ModuleData *>::_M_insert_overflow(pointer __position, const value_type &__x,
	const __true_type &, size_type __fill_len, bool __atend)
{
	const size_type __old_size = size();
	const size_type __len = __old_size + moduleOverflowMax(__old_size, __fill_len);
	pointer __new_start = this->_M_end_of_storage.allocate(__len);
	pointer __new_finish = (pointer)__copy_trivial(this->_M_start, __position, __new_start);
	__new_finish = fill_n(__new_finish, __fill_len, __x);
	if (!__atend)
		__new_finish = (pointer)__copy_trivial(__position, this->_M_finish, __new_finish);
	_M_clear();
	_M_set(__new_start, __new_finish, __new_start + __len);
}
}
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

// Dispatch-only view of the existing slot-7 call with its byte argument.
// The canonical data header intentionally omits slots 1-13. This view emits
// no vtable or named method definition and makes no additional identity claim.
class Rva001B505FTarget
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2();
	virtual void vf3();
	virtual void vf4();
	virtual void vf5();
	virtual void vf6();
	virtual void vf7(unsigned char flag);
};

struct SubsystemEntry8
{
	SubsystemInterface *object;
	unsigned extra;
};

void Rva0002BBC9Update();

class SubsystemInterfaceList
{
public:
	unsigned char rva001B505F();
	unsigned char rva001B4E21(SubsystemInterface *obj, unsigned char *flag);

private:
	_STL::vector<SubsystemEntry8> m_primary;
	_STL::vector<SubsystemInterface *> m_pending;
};

unsigned char SubsystemInterfaceList::rva001B505F()
{
	unsigned char flag;
	const ModuleData *obj;
	unsigned char any = 0;
	flag = any;
	_STL::vector<const ModuleData *> collected;
	for (SubsystemEntry8 *subsystemEntry8 = m_primary.begin(); subsystemEntry8 != m_primary.end(); ++subsystemEntry8)
	{
		obj = (const ModuleData *)subsystemEntry8->object;
		if (obj != 0)
		{
			if (rva001B4E21((SubsystemInterface *)obj, &flag))
				any = 1;
			collected.push_back(obj);
		}
	}
	for (SubsystemInterface **subsystem = m_pending.begin(); subsystem != m_pending.end(); ++subsystem)
	{
		obj = (const ModuleData *)*subsystem;
		if (obj != 0)
		{
			if (rva001B4E21((SubsystemInterface *)obj, &flag))
				any = 1;
			collected.push_back(obj);
		}
	}
	for (const ModuleData **it = collected.begin(); it != collected.end(); ++it)
	{
		if (*it)
			((Rva001B505FTarget *)*it)->vf7(flag);
	}
	if (any)
		Rva0002BBC9Update();
	return any;
}
