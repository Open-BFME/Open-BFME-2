// cl: /O1 /DNDEBUG /MD /EHsc
// ??_ERva00112291@@UAEPAXI@Z @0x000E1072 78B.
// Same shape as ??_ERva001FBF4D: flag bit 1 walks 0xD4 elements via
// ??_M@YGXPAXIHP6EX0@Z@Z using the count before the array, then operator
// delete[]; otherwise it calls the element destructor and operator delete.
// Element destructor 0x00112291 is pinned, not defined.

void operator delete[](void *block);

class Rva00112291
{
public:
	virtual ~Rva00112291();

private:
	char m_unmodelled_04[0xD4 - 0x04];
};

// ?bfmeVectorDeleteAnchorE1072 absent-from-retail
void bfmeVectorDeleteAnchorE1072()
{
	new Rva00112291[2];
}
