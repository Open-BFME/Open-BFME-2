// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V06: 75-byte bodies that, for
// an array delete (flag bit 1), run the eh vector destructor iterator
// (0x00629110) over the count stored before the array with the destructor's
// address and the element size, then free the block from its count word with
// operator delete[] (0x0002FD80); otherwise they call the destructor and free
// through operator delete (0x0002FD60). The element size is the class size.
// Each class's destructor is declared, not defined (pinned); the anchor below
// (no retail counterpart) news an array of each class so this TU emits the
// vector deleting destructor. Owners are opaque unless the destructor already
// carried a ledger name.
//
//   ??_E        dtor        size  vtable#slot
//   0x003AB899  0x003AB86E  0x24  0x00C1C2F4#0
//   0x003AB946  0x003AB86E  0x28  0x00C1C314#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

class Rva003AB86E
{
public:
	virtual ~Rva003AB86E();
private:
	char m_unmodelled_04[0x24 - 0x04];
};

class Rva003AB946Vec
{
public:
	virtual ~Rva003AB946Vec();
private:
	char m_unmodelled_04[0x28 - 0x04];
};

// ?<bfmeVectorDeleteAnchorV06> absent-from-retail
void bfmeVectorDeleteAnchorV06()
{
	new Rva003AB86E[2];
	new Rva003AB946Vec[2];
}
