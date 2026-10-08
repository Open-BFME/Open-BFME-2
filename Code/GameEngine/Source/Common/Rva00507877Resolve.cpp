// cl: /Oy- /DNDEBUG /MD /GX- /Oi-
// stlport
//
// ?rva00507877@Rva00507823@@UAEXXZ retail 0x00507877 163B
// Virtual slot 8 offset 0x20 of vtable 0x00864010 class of
// ??1Rva00507823@@UAE@XZ plus slot 8 of 0x00864C38 Made002CCA37 and
// 0x008650B8 Made002CCCF3. Resolves upgrade-name vectors at +0x108 and
// +0x114 via UpgradeCenter findUpgrade 0x0026F26D into bitsets at +0x04
// and +0x84 then erases both vectors via 0x002CCFC. Same UpgradeMuxData
// getUpgradeActivationMasks shape with masks at +0x04 and vectors at
// +0x108 per ctor 0x0050775B clear80 and Vector_base layout. Callers at
// 0x005092B5 and 0x005095FE and 0x005097D1 plus jmp at 0x0050B928.
#include <vector>
#include <string.h>

template <typename Char>
class StringBase
{
protected:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		Char text[1];
	};
	Header *m_data;
public:
	bool isEmpty() const;
	bool isNone() const;
};

class AsciiString : public StringBase<char>
{
public:
	const char *str() const
	{
		const char *data = *reinterpret_cast<const char *const *>(this);
		return data ? data + 8 : BfmeEmptyString;
	}
private:
	static const char BfmeEmptyString[];
};

struct UpgradeMaskType
{
	void clear()
	{
		memset(&m_words[0], 0, sizeof(m_words));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= (unsigned long)1 << (bit & 31);
	}
	unsigned long m_words[32];
};

class UpgradeTemplate
{
public:
	unsigned int getUpgradeMask() const { return m_upgradeMaskIndex; }
private:
	unsigned char m_pad[0x38];
	unsigned int m_upgradeMaskIndex;
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;	// Upgrade.cpp's global (0x009FEB60)

class Rva00507823
{
public:
	virtual ~Rva00507823();
	virtual void s1();
	virtual void s2();
	virtual void s3();
	virtual void s4();
	virtual void s5();
	virtual void s6();
	virtual void s7();
	virtual void rva00507877();
private:
	UpgradeMaskType m_bits04;
	UpgradeMaskType m_bits84;
	unsigned char m_pad104[0x108 - 0x104];
	_STL::vector<AsciiString> m_vec108;
	_STL::vector<AsciiString> m_vec114;
	unsigned m_filter120;
};

void Rva00507823::rva00507877()
{
	_STL::vector<AsciiString>::const_iterator it;
	for (it = m_vec108.begin(); it != m_vec108.end(); ++it)
	{
		const UpgradeTemplate *theTemplate = TheUpgradeCenter->findUpgrade(*it);
		if (theTemplate)
			m_bits04.set(theTemplate->getUpgradeMask());
	}
	for (it = m_vec114.begin(); it != m_vec114.end(); ++it)
	{
		const UpgradeTemplate *theTemplate = TheUpgradeCenter->findUpgrade(*it);
		if (theTemplate)
			m_bits84.set(theTemplate->getUpgradeMask());
	}
	m_vec108.clear();
	m_vec114.clear();
}
