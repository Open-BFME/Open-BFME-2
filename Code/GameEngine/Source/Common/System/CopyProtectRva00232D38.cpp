// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00232D38@CopyProtect@@SA_NXZ, retail 0x00232D38, 43 bytes. Full-string
// gate beside CopyProtect::validate: when the launcher view is present it
// compares the whole view against the rowed ?GetRegistryG4@@YAPBDXZ string,
// returns true on equality and otherwise tail-calls validate (which checks
// the 'M' guard and the +1 comparison). Prev/next rows give the TU and /O1.

extern "C" int __cdecl strcmp(const char *a, const char *b);

const char *GetRegistryG4(void);

class CopyProtect
{
public:
	static bool validate(void);
	static bool rva00232D38(void);

private:
	static void *s_protectedData;
};

bool CopyProtect::rva00232D38(void)
{
	if (s_protectedData != 0)
	{
		char *data = (char *)s_protectedData;
		bool matched = strcmp(data, GetRegistryG4()) ? false : true;
		if (matched)
		{
			return matched;
		}
		return validate();
	}
	return false;
}
