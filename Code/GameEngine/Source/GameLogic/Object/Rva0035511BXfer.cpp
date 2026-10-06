// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?Rva0035511BXfer@@YAPAVXfer@@PAV1@PAURva0035511BPair@@@Z retail 0x0035511B 29B.
// Chain lane: calls rowed 0x00355096 which you just landed plus rowed XferObjectID 0x003060B2.
// Evidence: callers at 0x003556FC 0x0035574D pass Xfer plus 8-byte pair proving ObjectID plus pointer; same eax-reuse as Rva00469124Xfer.

enum ObjectID
{
	INVALID_ID = 0
};

class Xfer;
void XferObjectID(Xfer *xfer, ObjectID *objectID);

class Rva0054840A
{
	char m_pad[0x14];
};

Xfer *Rva00355096Xfer(Xfer *xfer, Rva0054840A **out);

struct Rva0035511BPair
{
	ObjectID m_id;
	Rva0054840A *m_ptr;
};

Xfer *Rva0035511BXfer(Xfer *xfer, Rva0035511BPair *pair)
{
	// Rowed XferObjectID is declared void but its body tail-calls XferEnum
	// which returns Xfer& in eax; retail reuses that eax as the xfer for the
	// second call, same as Rva00469124Xfer precedent.
	return Rva00355096Xfer(
		((Xfer *(__cdecl *)(Xfer *, ObjectID *))XferObjectID)(xfer, &pair->m_id),
		&pair->m_ptr);
}
