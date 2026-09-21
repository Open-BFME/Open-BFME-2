// cl: /O1 /MD /DNDEBUG
// Identity: ModuleFactory registers this data class under "BeaconClientUpdate" (addModule
// pairs the name with this factory); formerly misnamed CleanupHazardUpdate/CleanupHazardUpdateModuleData.
// ??0BeaconClientUpdate@@QAE@XZ at retail 0x004C964C.
// Root-class default ctor: vtable plus two int members. No base, no calls.
// Factory stub order names it; stub size 0x10 confirms the layout.
class BeaconClientUpdate
{
public:
	BeaconClientUpdate();
	virtual ~BeaconClientUpdate();

private:
	int m_pad04;
	int m_i08;
	int m_i0C;
};

BeaconClientUpdate::BeaconClientUpdate()
	: m_i08(0x1E), m_i0C(0x0F)
{
}

// ??1BeaconClientUpdate@@ present-unmatched
BeaconClientUpdate::~BeaconClientUpdate()
{
}
