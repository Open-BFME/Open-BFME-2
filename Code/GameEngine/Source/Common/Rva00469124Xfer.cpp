// cl: /MD
// ?Rva00469124Xfer@@YAAAVXfer@@PAV1@PAURva00469124Pair@@@Z 0x00469124 30B evidence: ObjectID+int pair via rowed XferObjectID 0x3060B2 then slot 0x78 callers 0x47028A 0x4702D8
typedef unsigned int UnsignedInt;
typedef bool Bool;
#include "System/XferVectorTypes.h"
#include "../../Include/Common/BfmeXfer.h"
enum ObjectID
{
	INVALID_ID = 0
};
void XferObjectID(Xfer *xfer, ObjectID *objectID);
struct Rva00469124Pair
{
	ObjectID m_id;
	int m_value;
};
Xfer &Rva00469124Xfer(Xfer *xfer, Rva00469124Pair *pair)
{
	// Rowed XferObjectID is declared void but its body tail-calls XferEnum
	// which returns Xfer& in eax; retail reuses that eax as the xfer for the
	// slot-0x78 call, so call it through an Xfer&-returning type.
	Xfer &r = ((Xfer &(__cdecl *)(Xfer *, ObjectID *))XferObjectID)(xfer, (ObjectID *)pair);
	return r == reinterpret_cast<unsigned int &>(pair->m_value);
}

// ?Rva00469103Xfer@@YAAAVXfer@@PAV1@PAURva00469103Pair@@@Z 0x00469103 33B evidence: ObjectID+int pair via rowed XferObjectID 0x3060B2 then slot 0x90 callers 0x47403C 0x47408A
struct Rva00469103Pair
{
	ObjectID m_id;
	int m_value;
};
Xfer &Rva00469103Xfer(Xfer *xfer, Rva00469103Pair *pair)
{
	// Same tail-call eax reuse as Rva00469124Xfer above; second field goes
	// through slot 0x90 instead of slot 0x78.
	Xfer &r = ((Xfer &(__cdecl *)(Xfer *, ObjectID *))XferObjectID)(xfer, (ObjectID *)pair);
	return r == reinterpret_cast<bool &>(pair->m_value);
}
