// cl: /DNDEBUG /MD
//
// ?rva00495DD4@AutoPickUpUpdate@@QAE_NXZ, retail 0x00495DD4, 36 bytes.
// Identity: AutoPickUpUpdate scan-ready predicate. ModuleData at +4 carries
// ScanDelayTime at +8 and RunFromButton at +0x21 (see
// AutoPickUpUpdateModuleDataCtor layout: +8 ScanDelayTime, +0x21
// RunFromButton, +0x24 RunFromButtonNumber, +0x28
// CanScanWhileAttackingOrMoving). Behavior holds countdown at +0x24 and
// cached flag at +0x28 (see AutoPickUpUpdateCtor/Xfer: +0x24 uint, +0x28
// bool). If RunFromButton is set return m_28; if countdown is zero reload
// it from ScanDelayTime and return true; else decrement and return false.
// Evidence: offsets match ctor/xfer/dtor triple; caller at 0x00495E5C in
// AutoPickUpUpdate area.

struct AutoPickUpUpdateModuleData
{
	char m_pad00[8];
	int m_scanDelayTime; // +8
	char m_pad0C[0x21 - 0x0C];
	unsigned char m_runFromButton; // +0x21
};

class AutoPickUpUpdate
{
public:
	bool rva00495DD4();

private:
	char m_pad00[4];
	AutoPickUpUpdateModuleData *m_data04; // +4
	char m_pad08[0x24 - 0x08];
	unsigned int m_count24; // +0x24
	bool m_flag28; // +0x28
};

bool AutoPickUpUpdate::rva00495DD4()
{
	AutoPickUpUpdateModuleData *data = m_data04;
	if (data->m_runFromButton)
		return m_flag28;
	if (m_count24 == 0) {
		m_count24 = data->m_scanDelayTime;
		return true;
	}
	m_count24--;
	return false;
}
