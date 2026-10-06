// cl: /DNDEBUG /MD /EHsc
// ??0Rva004C9E94@@QAE@ABVRva0036CA00Str@@PBHMABVWeaponTemplateSetHead@@2@Z @0x004C9E94 95B
// ctor with 5 args: Rva0036CA00Str ref +0x8, int ptr +0xC, float +0x10,
// WeaponTemplateSetHead refs +0x14/+0x18. Members +0 int, +4 str, +8 float,
// +0xC/+0x58 Weapon sets (0x4C each), +0xA4 bool = OR of ModelConditionFlags
// predicate on both Weapon args. Evidence: copy-ctor calls for str/weapons,
// short-circuit OR skipping second call, mov eax,esi return-this epilogue,
// ret 0x14. Caller 0x004CAA5E. Not AnimationSoundClientBehavior (its dtor
// has no member dtors).
class Rva0036CA00Str
{
public:
    Rva0036CA00Str(const Rva0036CA00Str &other);
};

class ModelConditionFlags
{
public:
    bool rva000B3EB3() const;
private:
    unsigned int m_words[19];
};

class WeaponTemplateSetHead
{
public:
    WeaponTemplateSetHead(const WeaponTemplateSetHead &that);
    ModelConditionFlags m_flags;
};

class Rva004C9E94
{
public:
    Rva004C9E94(
        const Rva0036CA00Str &s,
        const int *p,
        float f,
        const WeaponTemplateSetHead &a,
        const WeaponTemplateSetHead &b);
    Rva004C9E94(const Rva004C9E94 &that);
private:
    int m_0;
    Rva0036CA00Str m_1;
    float m_2;
    WeaponTemplateSetHead m_3;
    WeaponTemplateSetHead m_4;
    unsigned char m_5;
};

Rva004C9E94::Rva004C9E94(
    const Rva0036CA00Str &s,
    const int *p,
    float f,
    const WeaponTemplateSetHead &a,
    const WeaponTemplateSetHead &b)
    : m_0(*p), m_1(s), m_2(f), m_3(a), m_4(b)
{
    m_5 = a.m_flags.rva000B3EB3() || b.m_flags.rva000B3EB3();
}
Rva004C9E94::Rva004C9E94(const Rva004C9E94 &that)
	: m_0(that.m_0), m_1(that.m_1), m_2(that.m_2), m_3(that.m_3), m_4(that.m_4), m_5(that.m_5)
{
}
