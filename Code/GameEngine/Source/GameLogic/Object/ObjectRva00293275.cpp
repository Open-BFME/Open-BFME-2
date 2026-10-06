// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva00293275@Object@@QAEXVAsciiString@@@Z @0x00293275 187B
// Honest Object method tokenizing AsciiString upgrades via rowed nextToken
// 0x00036D90 and UpgradeCenter findUpgrade 0x0026F26D, granting via rowed
// Object 0x0028C197/0x00293077 and slots 0xB4/0xB8. Evidence: EH prolog,
// loop over tokens, [ebx+4]+0x115 bit 0x20 selects path, callers unblock.
typedef bool Bool;

#include "ascii_string.h"


class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class Provider
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s43b();
	virtual Bool s44(const UpgradeTemplate *t);
	virtual void s46(const UpgradeTemplate *t, int x);
};

struct Holder04
{
	char m_pad[0x115];
	unsigned char m_flags;
};

class Object
{
public:
	void rva00293275(AsciiString upgrades);
	void *rva0028C197() const;
	void rva00293077(const void *x);
private:
	char m_pad[4];
	Holder04 *m_holder;
};

void Object::rva00293275(AsciiString upgrades)
{
	AsciiString token;
	while (upgrades.nextToken(&token, 0)) {
		const UpgradeTemplate *t = TheUpgradeCenter->findUpgrade(token);
		if (t == 0)
			continue;
		if ((m_holder->m_flags & 0x20) != 0) {
			Provider *p = (Provider *)rva0028C197();
			if (p == 0)
				continue;
			if (!p->s44(t))
				p->s46(t, 1);
		} else {
			rva00293077(t);
		}
	}
}
