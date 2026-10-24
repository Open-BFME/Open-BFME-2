// cl: /O1 /G7 /EHsc /MD
//
// ??_GRva0046AA69Record@@QAEPAXI@Z at 0x0046AA69 (28B): the scalar deleting
// destructor of the record whose destructor is rowed at 0x00469DCE
// (AudioEventRTSDtor.cpp). Retail saves this, calls that destructor, tests
// bit 0 of the flags, conditionally frees through operator delete
// (0x0002FD60), returns this and pops one argument. The STLport stable_sort
// instantiation this unit once used to emit it also pulled in the record's
// copy constructor, assignment and comparison, none of which retail shows;
// a delete expression emits the same wrapper on its own. Record identity and
// layout remain unresolved (address-derived).

struct Rva0046AA69Record
{
	~Rva0046AA69Record();
	char bytes[1];
};

// Emitter only: no retail body.
void Rva0046AA69Record_Delete(Rva0046AA69Record *p)
{
	delete p;
}
