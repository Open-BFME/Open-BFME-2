// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?doSelectBuilderButtonFlash@ScriptActions@@IAEXH@Z, retail 0x003BD28D 25B chain via rowed 0x002D36C3.
// Scaled forwarder: scaled = g_00DBA4E8 * value; theRadarWindowOverrideSource guarded setter.
// Evidence: callee ?rva002D36C3@Rva002D36C3@@QAEXPAX@Z rowed; caller 0x003CED45; prev 0x003BCFC9 next 0x003BD405 same /O1.
class Rva002D36C3
{
public:
	void rva002D36C3(void *p);
};

class RadarWindowOverrideSource
{
};

extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
extern int g_009BA4E8;

class ScriptActions
{
protected:
	void doSelectBuilderButtonFlash(int value);
};

void ScriptActions::doSelectBuilderButtonFlash(int value)
{
	int scaled = g_009BA4E8 * value;
	((Rva002D36C3 *)theRadarWindowOverrideSource)->rva002D36C3((void *)scaled);
}
