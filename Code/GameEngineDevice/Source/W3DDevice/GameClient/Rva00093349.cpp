// cl: /MD /EHsc /DNDEBUG
// ?rva00093349@Rva00093349@@QAEXXZ @0x00093349 (100B):
// Weather sync helper: sets m_ac and m_41 then copies weather +0x70/+0x74/+0x78
// to m_58/m_5c/m_60 through override hops. Same null/next diamond around pinned
// getFinalOverride 0x001E35DF as neighbours Rva000932E1Get.cpp and
// Rva00093457Finish.cpp. Evidence: caller jmp 0x0009470A in W3DSnowManager
// target_00094652; LINK 1 file 46B; globals VA 0x00DFE118 TheWeatherSetting.
#define TheWeather00DFE118 (g_Va00DFE118)
class WeatherSetting;
extern WeatherSetting *g_Va00DFE118;
class Overridable
{
public:
	void *m_vftable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};
class WeatherSetting : public Overridable
{
public:
	char m_pad08[0x70 - 0x08];
	int m_70;
	int m_74;
	int m_78;
};
class Rva00093349
{
public:
	void rva00093349();
private:
	char m_pad[0x41];
	bool m_41;
	char m_pad42[0x58 - 0x42];
	int m_58;
	int m_5c;
	int m_60;
	char m_pad64[0xac - 0x64];
	int m_ac;
};
void Rva00093349::rva00093349()
{
	m_ac = 1;
	m_41 = true;
	const WeatherSetting *gv = TheWeather00DFE118;
	const WeatherSetting *o = (gv == 0) ? 0 : ((gv->m_nextOverride != 0) ? (const WeatherSetting *)gv->m_nextOverride->getFinalOverride() : gv);
	m_58 = o->m_70;
	const WeatherSetting *gv2 = TheWeather00DFE118;
	const WeatherSetting *o2 = (gv2 == 0) ? 0 : ((gv2->m_nextOverride != 0) ? (const WeatherSetting *)gv2->m_nextOverride->getFinalOverride() : gv2);
	m_5c = o2->m_74;
	const WeatherSetting *gv3 = TheWeather00DFE118;
	const WeatherSetting *o3 = (gv3 == 0) ? 0 : ((gv3->m_nextOverride != 0) ? (const WeatherSetting *)gv3->m_nextOverride->getFinalOverride() : gv3);
	m_60 = o3->m_78;
}
