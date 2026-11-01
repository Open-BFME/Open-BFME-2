// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Retail 0x004C861E (123 bytes): SplitHordeSpecialPower::doSpecialPower, slot 10
// of the vtable 0x00C5E598 that the matched SplitHordeSpecialPower ctor
// installs at +0x10, compiled with that subobject this ([ecx-8] is the Object).
// Name by address (one unsigned argument, unused here). Body: nothing when the
// Object is disabled (inline isDisabled over the matched BitFlags<11>::any on
// its +0x1C8 mask); otherwise, when the contain interface returned by the
// matched Object::rva0028C197 answers slot 125, have its slot 126 fill a local
// STLport vector<Object *> (its unwind funclet 0x007903F6 destroys it through
// the rowed ~vector<Object *> 0x001F22A3; matched _Vector_base ctor 0x00211E58, released
// through the bfmealloc free), the EH frame covering that local.
#include <vector>
template <int N> class BitFlags
{
public:
	bool any() const;
private:
	unsigned int m_words[(N + 31) / 32];
};
template <int N> class Rva004C861ESlots : public Rva004C861ESlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C861ESlots<0>
{
};
class Object;
// The contain interface returned by the matched Object::rva0028C197: slot 125
// is a bool query, slot 126 fills a vector<Object *>.
class Rva004C861EContain : public Rva004C861ESlots<125>
{
public:
	virtual bool rva004C861ESlot125() = 0;
	virtual void rva004C861ESlot126(_STL::vector<Object *> *out) = 0;
};
class Object
{
public:
	void *rva0028C197() const;
	bool isDisabled() const { return m_disabledMask.any(); }
	unsigned char m_pad000[0x1C8];
	BitFlags<11> m_disabledMask; // +0x1C8
};
class ModuleData;
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
template <int N> class Rva004C861ESPSlots : public Rva004C861ESPSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C861ESPSlots<0>
{
};
// The +0x10 interface: slots 0..9 placeholders, slot 10 below.
class Rva004C861EIface10 : public Rva004C861ESPSlots<10>
{
public:
	virtual void doSpecialPower(unsigned int options) = 0;
};
class SpecialPowerModule : public BehaviorModule, public Rva004C861EIface10
{
};
class SplitHordeSpecialPower : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
};
void SplitHordeSpecialPower::doSpecialPower(unsigned int)
{
	Object *object = m_object;
	if (object->isDisabled())
		return;
	Rva004C861EContain *contain = (Rva004C861EContain *)object->rva0028C197();
	if (!contain)
		return;
	if (!contain->rva004C861ESlot125())
		return;
	_STL::vector<Object *> items;
	contain->rva004C861ESlot126(&items);
}
