// ?rva0059B5A3@Rva0059B5A3@@QAE?AV?$StringBase@D@@XZ
// partial score=0.99 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0059B5A3@Rva0059B5A3@@QAE?AV?$StringBase@D@@XZ
// Retail 0x0059B5A3..0x0059B7CB (552 bytes). BANKED NEAR MISS (score ~0.99):
// one instruction short: retail copies the materialised label into the
// result with the source address re-derived (`lea eax,[ebp-0x18]` between
// `xor edi,edi` and `inc edi`), this build pushes the materialiser's returned
// eax. Tried: AsciiString-typed local (copy elided), direct init, reference
// and pointer casts of the temporary, a conversion-operator view, declared /
// inline AsciiString copy ctor and dtor.
//
// Debug description of a living-world AI army unit, the sibling of
// Rva0059B4FFDescribe.cpp (same reads; no retail caller):
// "<template name> (Plyr:<player>, Lvl:<level>, HP:<hp>/<max hp>, Weapon:
// <weapon>, Armor:<armor>, Upgrades:<names...>)" or "... Upgrades:<None>)".
// Built through the narrow concat chain (rowed operator+ 0x000B49C5 /
// 0x002226E5, node builders 0x0059AFC2 / 0x0059B036, materialiser 0x0059B2EC,
// string += node 0x0059B0DD), _itoa / _gcvt into one 128-byte buffer, the
// current auto-resolve weapon / armor of the template (+0x2C) for the unit's
// upgrades (+0x08 -> +0x10, a 1024-bit mask walked with UpgradeCenter's
// by-id lookup 0x0026EEA0).
// class-gate: allow AsciiString the narrow concat chain needs the StringBase-derived view the sibling Rva0059B4FFDescribe.cpp uses

extern "C" __declspec(dllimport) char *__cdecl _itoa(int value, char *buffer, int radix);
extern "C" __declspec(dllimport) char *__cdecl _gcvt(double value, int digits, char *buffer);

template <class T> class StringBase;
template <> class StringBase<char>
{
public:
	StringBase(const StringBase<char> &other);
	~StringBase();
	void concat(const char *text);
	void concat(const StringBase<char> &other);
protected:
	void *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString &operator+=(char c);
};

struct Rva0059AFC2In { int m_a, m_b, m_c; };
struct AsciiStringPlusText : Rva0059AFC2In {};
struct Rva002226E5TextPlusString : Rva0059AFC2In {};
struct Rva0059AFC2Out { int m_a, m_b, m_c, m_d, m_e; };
struct Rva0059B036Out { int m_a, m_b, m_c, m_d, m_e, m_f; };

AsciiStringPlusText __cdecl operator+(const AsciiString &left, const char *right);			// 0x000B49C5
Rva002226E5TextPlusString __cdecl operator+(const char *left, const AsciiString &right);		// 0x002226E5
Rva0059AFC2Out *__cdecl Rva0059AFC2Copy(Rva0059AFC2Out *dst, Rva0059AFC2In *src, const char *text);	// node + text
void *__cdecl Rva0059B036Copy(void *dst, void *src, int tail);					// node + string
StringBase<char> *__cdecl Rva0059B0DDConcat(StringBase<char> *dst, const char *src);		// string += node

class Rva0059B2EC
{
public:
	AsciiString rva0059B2EC();	// materialises the node
};

class Rva00427157;
class Rva0033A9A5
{
public:
	const Rva00427157 *rva0033A9A5(const void *upgrades);	// current auto-resolve armor
};
class ThingTemplate
{
public:
	void *getCurrentLivingWorldAutoResolveWeapon(const void *upgrades) const;
	unsigned char m_pad00[0x64];
	AsciiString m_name;	// +0x64
};

class UpgradeTemplate
{
public:
	unsigned char m_pad00[8];
	AsciiString m_name;	// +0x08
};
class UpgradeCenter
{
public:
	const UpgradeTemplate *rva0026EEA0(int upgradeID) const;	// by id
};
extern UpgradeCenter *TheUpgradeCenter;

namespace _STL
{
template <int N> struct _Base_bitset
{
	bool _M_is_any() const;	// 0x000454A6
	unsigned int _M_w[N];
};
}
struct UpgradeMaskType : _STL::_Base_bitset<32>
{
	bool any() const { return _M_is_any(); }
	__forceinline bool test(unsigned int pos) const { return (_M_w[pos / 32] & (1 << (pos % 32))) != 0; }
};

struct Rva0059B5A3Unit
{
	unsigned char m_pad00[0x0C];
	int m_level;			// +0x0C
	UpgradeMaskType m_upgrades;	// +0x10
};

class Rva0059AEBC
{
public:
	float rva0059AEBC();	// maximum health
};

class Rva0059B5A3
{
public:
	StringBase<char> rva0059B5A3();
private:
	unsigned char m_pad00[0x08];
	Rva0059B5A3Unit *m_unit;	// +0x08
	float m_health;			// +0x0C
	unsigned char m_pad10[0x2C - 0x10];
	ThingTemplate *m_template;	// +0x2C
	int m_player;			// +0x30
};

StringBase<char> Rva0059B5A3::rva0059B5A3()
{
	char buffer[128];
	const AsciiString &name = m_template->m_name;
	Rva0059AFC2Out part;
	StringBase<char> str = ((Rva0059B2EC *)Rva0059AFC2Copy(&part, &operator+(name, " (Plyr:"),
		_itoa(m_player, buffer, 10)))->rva0059B2EC();
	str.concat(", Lvl:");
	int level = m_unit->m_level;
	str.concat(_itoa(level, buffer, 10));
	str.concat(", HP:");
	str.concat(_gcvt(m_health, 4, buffer));
	str.concat("/");
	str.concat(_gcvt(((Rva0059AEBC *)this)->rva0059AEBC(), 4, buffer));

	const Rva00427157 *armor = ((Rva0033A9A5 *)m_template)->rva0033A9A5(&m_unit->m_upgrades);
	const AsciiString *weapon = (const AsciiString *)m_template->getCurrentLivingWorldAutoResolveWeapon(&m_unit->m_upgrades);
	Rva0059AFC2Out weaponPart;
	Rva0059B036Out armorPart;
	Rva0059B0DDConcat(&str, (const char *)Rva0059B036Copy(&armorPart,
		Rva0059AFC2Copy(&weaponPart, &(", Weapon:" + *weapon), ", Armor:"), (int)armor));

	str.concat(", Upgrades:");
	const UpgradeMaskType &upgrades = m_unit->m_upgrades;
	if (upgrades.any())
	{
		bool first = true;
		for (int i = 0; i < 1024; ++i)
		{
			if (upgrades.test(i))
			{
				const UpgradeTemplate *upgrade = TheUpgradeCenter->rva0026EEA0(i);
				if (upgrade)
				{
					if (first)
						first = false;
					else
						((AsciiString &)str) += ' ';
					str.concat(upgrade->m_name);
				}
			}
		}
		((AsciiString &)str) += ')';
	}
	else
	{
		str.concat("<None>)");
	}
	return str;
}
