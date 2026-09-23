// cl: /MD
//
// profile_result.cpp Delete virtuals, retail 0x006C74C0 (8 bytes). All three
// result writers - FileDOT, FileCSV and FileGTT - share this one body: each
// vftable's Delete slot (0x00CE84D0, 0x00CE85E4 and 0x00CE85D8) points at it,
// so the linker folded the three identical methods. Every one of them is
//
//   this->~X();
//   ProfileFreeMemory(this);
//
// with a trivial inline destructor, which is just ProfileFreeMemory(this):
// push the thiscall this pointer and call the deleter at 0x006C5300. The GTT class (GetName "file_gtt_dot", default file
// "profile_gtt.dot") has no Zero Hour donor: the name below composes the
// retail strings and claims no donor provenance for the GTT token itself.

void ProfileFreeMemory(void *ptr);

class ProfileResultFileDOT
{
public:
	virtual void WriteResults();
	virtual void Delete();
	virtual const char *GetName() const;
};

// ?Delete@ProfileResultFileDOT@@UAEXXZ
void ProfileResultFileDOT::Delete()
{
	this->~ProfileResultFileDOT();
	ProfileFreeMemory(this);
}

class ProfileResultFileCSV
{
public:
	virtual void WriteResults();
	virtual void Delete();
	virtual const char *GetName() const;
};

// ?Delete@ProfileResultFileCSV@@UAEXXZ
void ProfileResultFileCSV::Delete()
{
	this->~ProfileResultFileCSV();
	ProfileFreeMemory(this);
}

class ProfileResultFileGTT
{
public:
	virtual void WriteResults();
	virtual void Delete();
	virtual const char *GetName() const;
};

// ?Delete@ProfileResultFileGTT@@UAEXXZ
void ProfileResultFileGTT::Delete()
{
	this->~ProfileResultFileGTT();
	ProfileFreeMemory(this);
}
