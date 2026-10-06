// cl: /MD /EHsc /DNDEBUG
// ?rva000932E1@Rva000932E1@@QAEMXZ @0x000932E1 (104B):
// Float getter: default shared 1.0f unless the weather global resolves and
// both its +0x54 flag and this +0x50 flag are set, then a second resolve and
// the +0x58 random variable getValue. Nested ternaries force the explicit
// null/next diamond around pinned getFinalOverride 0x001E35DF.
// Evidence: callers 0x0009355B 0x00093FFA; unblocks 0x00093507; Snow weather global VA 0x00DFE118.
extern float g_Va00BBB8D8;
class WeatherSetting;
// g_Va00DFE118: VA 0x00dfe118 (.data/bss); retail zero-filled.
WeatherSetting *g_Va00DFE118;
#define TheWeather00DFE118 g_Va00DFE118
class Overridable
{
public:
	void *m_vftable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};
class GameClientRandomVariable
{
public:
	float getValue() const;
};
class WeatherSetting : public Overridable
{
public:
	char m_pad08[0x54 - 0x08];
	bool m_54;
	char m_pad55[3];
	GameClientRandomVariable m_58;
};
class Rva000932E1
{
public:
	float rva000932E1();
private:
	char m_pad[0x50];
	bool m_50;
};
float Rva000932E1::rva000932E1()
{
	float def = g_Va00BBB8D8;
	const WeatherSetting *gv = TheWeather00DFE118;
	const WeatherSetting *o = (gv == 0) ? 0 : ((gv->m_nextOverride != 0) ? (const WeatherSetting *)gv->m_nextOverride->getFinalOverride() : gv);
	if (o->m_54 != 0) {
		if (m_50 != 0) {
			const WeatherSetting *o2 = (gv == 0) ? 0 : ((gv->m_nextOverride != 0) ? (const WeatherSetting *)gv->m_nextOverride->getFinalOverride() : gv);
			return o2->m_58.getValue();
		}
	}
	return def;
}
