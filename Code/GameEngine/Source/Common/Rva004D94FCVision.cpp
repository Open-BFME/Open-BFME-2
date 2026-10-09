// cl: /O1 /MD
// ?rva004D94FC@@YA_NPAVObject@@@Z
// Native61B complete boundary; WB12932E0 establishes the status-bit test
// followed by canonical Object vision range and AI enemy range query.
// The WB debug function label describes its inlined bit test and does not
// establish the enclosing helper name. A compiler barrier preserves retail
// read/shift/byte-test shape; it emits no instruction or extra memory access.
class Object
{
	public: float getVisionRange() const;
};
class AttackPriorityInfo; class PartitionFilter;
class AI
{
public:
	Object *findClosestEnemy(const Object *, float, unsigned, const AttackPriorityInfo*, PartitionFilter*, int);
};
extern AI *TheAI;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
bool rva004D94FC(Object *object)
{
	const unsigned int *flags = (const unsigned int *)((char *)object + 0x11c);
	unsigned int bits=*flags;
    _ReadWriteBarrier();
    unsigned char bit=(unsigned char)(bits >> 29);
    if ((bit & 1) == 0)
		return false;
	return TheAI->findClosestEnemy(
		object, object->getVisionRange(), 0x6e, 0, 0, 1) != 0;
}
