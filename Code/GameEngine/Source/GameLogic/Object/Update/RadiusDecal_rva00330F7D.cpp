// cl: /DNDEBUG /MD
//
// ?rva00330F7D@RadiusDecal@@QAEXPAVXfer@@@Z @0x00330F7D 27B
// Unlock lane: if Xfer::IsLoading (slot 1) then RadiusDecal::clear.
// This is RadiusDecal (proven by rowed clear 0x00330DBA with same this).
// Caller 0x003915D2 (RadiusDecalUpdate::xfer slot 3 for member +0x20).
class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading() const;
};

class RadiusDecal
{
public:
	void clear();
	void rva00330F7D(Xfer *xfer);
};

void RadiusDecal::rva00330F7D(Xfer *xfer)
{
	if (xfer->IsLoading())
		clear();
}
