// cl: /DNDEBUG /MD /EHsc
//
// ?rva004DEA68@Rva0028AF76Sub@@QAEHXZ, retail 0x004DEA68 (8B), filling the
// gap between the rowed 0x004DEA62 and 0x004DEA70 after the FiringTracker
// destructor 0x004DEA0C: returns the +0x38 ObjectID and clears it. Its only
// caller is the Object+0x240 forwarder 0x0028AF97 (ObjectRvaSmallGetters.cpp,
// whose address-derived class name for the firing tracker this keeps); the
// +0x38 field is the second ObjectID the rowed FiringTracker::xfer 0x004DEBC1
// transfers. Flags follow the FiringTracker siblings.

struct Rva0028AF76Sub
{
	int rva004DEA68();

	char m_pad[0x38];				// +0x000..+0x038 unknown
	int m_id38;						// +0x038 ObjectID
};

int Rva0028AF76Sub::rva004DEA68()
{
	int id = m_id38;
	m_id38 = 0;
	return id;
}
