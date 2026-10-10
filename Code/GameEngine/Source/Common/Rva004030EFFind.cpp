// cl: /O1 /G7 /MD /Oi-
// ?rva004030EF@Rva0022B46BSubsystem@@QAEHPBD@Z @0x004030EF 58B
// Index lookup in the pointer table g_00DC1B68: return the index of the
// first entry that strcmp-matches the argument, else 0. Evidence: the
// ret-4 single-arg shape with no ecx use; caller00404648 independently passes
// the registered TheAttributeModifierStore receiver. This member ignores it. The
// E8 call at 0x00403108 targets the ji_006291c6 thunk whose TU body is
// { strcmp(); }; caller at 0x00404679. Plain extern strcmp (no dllimport)
// so the call routes through the thunk; /Oi- keeps it a call instead of
// inlined repz cmpsb. Original method name remains unknown.
extern "C" int __cdecl strcmp(const char *a, const char *b);

// g_00DC1B68: VA 0x00DC1B68 (.data). Retail's 28 string pointers end at the
// null sentinel at VA 0x00DC1BD8; strcmp observes text, not literal addresses.
const char *g_00DC1B68[] = {
	"ATTRIBUTE_NONE",
	"ARMOR",
	"DAMAGE_ADD",
	"DAMAGE_MULT",
	"RESIST_FEAR",
	"RESIST_TERROR",
	"EXPERIENCE",
	"RANGE",
	"SPEED",
	"CRUSH_DECELERATE",
	"RESIST_KNOCKBACK",
	"SPELL_DAMAGE",
	"RECHARGE_TIME",
	"PRODUCTION",
	"HEALTH",
	"HEALTH_MULT",
	"VISION",
	"BOUNTY_PERCENTAGE",
	"MINIMUM_CRUSH_VELOCITY",
	"AUTO_HEAL",
	"SHROUD_CLEARING",
	"RATE_OF_FIRE",
	"DAMAGE_STRUCTURE_BOUNTY_ADD",
	"CRUSHER_LEVEL",
	"COMMAND_POINT_BONUS",
	"CRUSHABLE_LEVEL",
	"CRUSHED_DECELERATE",
	"INVULNERABLE",
	0
};

class Rva0022B46BSubsystem { public: int rva004030EF(const char*); };
int Rva0022B46BSubsystem::rva004030EF(const char *s)
{
	int i;
	for (i = 0; g_00DC1B68[i] != 0; ++i)
		if (strcmp(g_00DC1B68[i], s) == 0)
			return i;
	return 0;
}
