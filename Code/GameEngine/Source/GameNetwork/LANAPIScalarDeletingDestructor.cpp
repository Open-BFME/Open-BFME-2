// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0044BA0E, 28 bytes. This scalar-deleting destructor calls the
// LANAPI complete destructor at 0x0044B992, deletes this when flag bit 0 is
// set, and returns this. The target complete destructor establishes LANAPI
// identity by restoring its vtable and destroying its transport and three
// string members. BFME1's generated LANAPI scalar-deleting destructor is the
// source pattern.

class LANAPI
{
public:
	virtual ~LANAPI(void);
};

void forceLANAPIScalarDeletingDestructor(void)
{
	LANAPI value;
}
