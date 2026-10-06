// cl: /DNDEBUG /MD /EHsc
// Retail 0x00418BE3 is a 24-byte bounds-checked index lookup. Its table at
// VA 0x00DC85C4 contains exactly eight target strings: AutoResolveUnit_Soldier,
// Archer, Pikemen, Cavalry, Monster, Hero, Fortress, and INVALID. The name and
// range are target evidence; the Zero Hour BitFlags helper is only a donor
// shape lead and does not establish the target's class or template type.
extern const char **g_Va00DC85C4Names;
const char *getAutoResolveUnitNameFromIndex(int index)
{
	return (index >= 0 && (unsigned int)index < 8)
		? ((const char *const *)&g_Va00DC85C4Names)[index]
		: 0;
}
