// cl: /MD
// ?Rva00407099Update@@YAXPAVXfer@@PAW4ObjectID@@PAXPAVRva00406FBF@@@Z @0x00407099 29B: free cdecl 4-arg helper calling XferObjectID(a1 a2) then Rva00406FBF::rva00406FBF(a2) with this=a4 arg3 unused. Evidence: chain via 0x00406FBF now ready; retail push push call pop pop push mov ecx call; callee row XferEnumHelpers.
class Xfer;
enum ObjectID
{
	INVALID_ID = 0
};
void __cdecl XferObjectID(Xfer *xfer, ObjectID *objectID);
class Rva00406FBF
{
public:
	void rva00406FBF(unsigned char *data);
};
void __cdecl Rva00407099Update(Xfer *a1, ObjectID *a2, void *a3_unused, Rva00406FBF *a4)
{
	XferObjectID(a1, a2);
	(void)a3_unused;
	a4->rva00406FBF((unsigned char *)a2);
}
