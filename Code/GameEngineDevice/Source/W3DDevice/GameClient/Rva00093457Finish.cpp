// cl: /MD /EHsc /DNDEBUG
// ?rva00093457@Rva00093457@@QAEXXZ @0x00093457 176B
// Weather sync method: zeroes two members, pulls an int through the second data
// global, then copies weather fields through override hops. A shared global
// local feeds the nested-ternary diamond around the +0x46 flag; when +0x46 is
// clear only m_3c/m_41/m_14 are written and the block joins the epilogue, so
// the o3/o4 override hops sit INSIDE the else arm. The banked attempt had them
// after the if/else, which produced a shorter true-branch jump (eb 1e vs eb 5a).
// Evidence: callers 0x00093B49 0x00093CBE; globals VA 0x00E01CE4 0x00DFE118;
// neighbour Rva000932E1Get.cpp (same WeatherSetting layout, pinned resolve
// 0x001E35DF).
#define TheOther00E01CE4 ((*(Rva00E01CE4Holder **)&TheGlobalWeatherSystem))
#define TheWeather00DFE118 (g_Va00DFE118)
struct Rva00E01CE4Holder
{
	char m_pad[0x10];
	int m_10;
};
class WeatherSetting;
extern class GlobalWeatherSystem *TheGlobalWeatherSystem;
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
	char m_pad08[0x3c - 0x08];
	int m_3c;
	int m_40;
	char m_pad44[2];
	bool m_46;
	char m_pad47[5];
	int m_4c;
	int m_50;
};
class Rva00093457
{
public:
	void rva00093457();
private:
	char m_pad[0x14];
	int m_14;
	char m_pad18[0x3c - 0x18];
	int m_3c;
	char m_pad40;
	bool m_41;
	char m_pad42[6];
	int m_48;
	int m_4c;
	char m_pad50[0x58 - 0x50];
	int m_58;
	char m_pad5c[0x64 - 0x5c];
	int m_64;
	int m_68;
	char m_pad6c[0xa8 - 0x6c];
	int m_a8;
	int m_ac;
};
void Rva00093457::rva00093457()
{
	m_58 = 0;
	m_ac = 0;
	m_a8 = TheOther00E01CE4->m_10;
	const WeatherSetting *gv = TheWeather00DFE118;
	const WeatherSetting *o = (gv == 0) ? 0 : ((gv->m_nextOverride != 0) ? (const WeatherSetting *)gv->m_nextOverride->getFinalOverride() : gv);
	if (o->m_46 == 0) {
		m_3c = m_64;
		m_41 = false;
		m_14 = m_68;
	} else {
		const WeatherSetting *o2 = (gv == 0) ? 0 : ((gv->m_nextOverride != 0) ? (const WeatherSetting *)gv->m_nextOverride->getFinalOverride() : gv);
		m_3c = o2->m_3c;
		const WeatherSetting *o3 = TheWeather00DFE118;
		if (o3 != 0 && o3->m_nextOverride != 0)
			o3 = (const WeatherSetting *)o3->m_nextOverride->getFinalOverride();
		m_14 = o3->m_40;
		const WeatherSetting *o4 = TheWeather00DFE118;
		if (o4 != 0 && o4->m_nextOverride != 0)
			o4 = (const WeatherSetting *)o4->m_nextOverride->getFinalOverride();
		m_48 = o4->m_4c;
		m_4c = o4->m_50;
	}
}
