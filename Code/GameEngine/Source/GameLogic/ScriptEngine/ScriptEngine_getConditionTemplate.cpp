// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ScriptEngine::getConditionTemplate, retail 0x00203941 (30 bytes).
// Condition template table at +0x12BA0, 128 bytes per entry, 202 entries;
// out-of-range ids fall back to entry 0.

class ConditionTemplate
{
public:
	unsigned char bytes[128];
};

class ScriptEngine
{
public:
	const ConditionTemplate *getConditionTemplate(int id);

private:
	unsigned char pad_0000[0x12BA0];
	ConditionTemplate templates[202];
};

const ConditionTemplate *ScriptEngine::getConditionTemplate(int id)
{
	if (id < 0 || id >= 202)
		id = 0;
	return &templates[id];
}
