// cl: /O1 /DNDEBUG /MD /EHsc
//
// Scalar deleting destructor (??_G) at retail 0x0042D4B3 (27B). Calls the
// class's virtual dtor (pinned retail 0x00977E3E), frees the block through
// scalar operator delete (rowed 0x0002FD60) when the flag bit is set, and
// returns this. The anchor below (no retail counterpart) plain-deletes one
// heap object so this TU emits the scalar deleting destructor; the dtor
// itself stays pinned, never defined here.
class Rva0042D4B3
{
public:
	virtual ~Rva0042D4B3();
};

// ?<rva0042D4B3DeleteAnchor> absent-from-retail
void rva0042D4B3DeleteAnchor()
{
	Rva0042D4B3 *p = new Rva0042D4B3;
	delete p;
}
