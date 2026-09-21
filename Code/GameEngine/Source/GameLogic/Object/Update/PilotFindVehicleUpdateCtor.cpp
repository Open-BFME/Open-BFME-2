// cl: /O1 /MD /DNDEBUG
// Identity: ModuleFactory registers this data class under "EvaAnnounceClientCreate" (addModule
// pairs the name with this factory); formerly misnamed PilotFindVehicleUpdate/PilotFindVehicleUpdateModuleData.
// Trial: ??0EvaAnnounceClientCreate@@QAE@XZ.
// Root-class default ctor: three INVALID_ID ors, vtable hand-placed late
// (novtable), then zeroed tail. Factory stub order names it.
extern "C" char PilotFindVehicleUpdate_vftable;

class __declspec(novtable) EvaAnnounceClientCreate
{
public:
	EvaAnnounceClientCreate();
	virtual ~EvaAnnounceClientCreate();

private:
	int m_pad04;
	int m_b08;
	int m_c0C;
	int m_d10;
	int m_e14;
	unsigned char m_f18[4];
};

EvaAnnounceClientCreate::EvaAnnounceClientCreate()
{
	int zero = 0;
	m_b08 = -1;
	m_c0C = -1;
	m_d10 = -1;
	*reinterpret_cast<char **>(this) = &PilotFindVehicleUpdate_vftable;
	m_e14 = zero;
	m_f18[0] = (unsigned char)zero;
	m_f18[1] = (unsigned char)zero;
	m_f18[2] = (unsigned char)zero;
	m_f18[3] = (unsigned char)zero;
}

// ??1EvaAnnounceClientCreate@@ present-unmatched
EvaAnnounceClientCreate::~EvaAnnounceClientCreate()
{
}
