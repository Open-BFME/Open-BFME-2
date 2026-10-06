// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?DeleteThis@BfmeDynamicVBRefCount@@UAEXXZ, retail 0x0006ce57, 20 bytes. Banked partial (score 0.85) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
void __cdecl operator delete(void *) throw();

class BfmeDynamicVBRefCount
{
public:
	virtual void DeleteThis();
	virtual ~BfmeDynamicVBRefCount() {}
	int references;
};

// Retail slot 1 is the scalar deleting destructor (flag 0 returns `this`).
class BfmeDynamicVBDeleteView
{
public:
	virtual void slot0();
	virtual void *scalarDeletingDestructor(unsigned flags);
};

void BfmeDynamicVBRefCount::DeleteThis()
{
	register unsigned int flags = 0;
	void *object = reinterpret_cast<void *>(flags);
	if (reinterpret_cast<unsigned int>(this) != flags)
		object = reinterpret_cast<BfmeDynamicVBDeleteView *>(this)->scalarDeletingDestructor(flags);
	::operator delete(object);
}
