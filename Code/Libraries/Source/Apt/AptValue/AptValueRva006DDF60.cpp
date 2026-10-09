// cl: /O2 /DNDEBUG /MD /EHsc
// ?rva006DDF60@AptValue@@QAE?AVEAStringC@@XZ retail 0x006DDF60 (490 bytes).
// Original name unknown; the only caller is 0x006E1787. For a value whose
// flag bit 4 (+0x04) is set it walks the native hash its virtual slot 3
// returns (rowed AptNativeHash first/next 0x0070AA40 / 0x0070AAA0) and
// serialises every "_"-prefixed member other than "__proto__" and "_type"
// whose value is not a native function as "name=value&" (rowed
// AptValue::toString 0x006DD6C0 and EAStringC appends 0x006D4F00 /
// 0x006D50A0), then trims the trailing "&" (rowed 0x006D5DA0). The result is
// returned by value. WorldBuilder twin 0x0176E860 (strings lead, unnamed).
extern "C" int __cdecl strcmp(const char *a, const char *b);
#pragma intrinsic(strcmp)

class EAStringC
{
	void *mpData;
public:
	EAStringC();
	EAStringC(const EAStringC &other);
	~EAStringC();
	int GetAt(int index) const;
	const char *rva00620090() const;
	EAStringC &Rva006D4F00Append(const EAStringC &other);
	EAStringC &Rva006D50A0Append(const char *text);
	bool rva006D5DA0(const char *suffix);
};

class AptValue;

class AptNativeHash
{
public:
	struct Entry
	{
		EAStringC key;
		AptValue *value;
	};
	class AsciiString *rva0070AA40();
	Entry *rva0070AAA0(Entry *pItem);
};

class AptValue
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual AptNativeHash *rva006DDF60Slot3();

	bool isNativeFunction() const;
	void toString(EAStringC &out) const;
	EAStringC rva006DDF60();

private:
	unsigned int m_flags; // +0x04
};

EAStringC AptValue::rva006DDF60()
{
	EAStringC result;
	if (!(bool)((m_flags >> 4) & 1))
		return result;

	AptNativeHash *hash = rva006DDF60Slot3();
	if (!hash)
		return result;

	EAStringC valueText;
	for (AptNativeHash::Entry *entry = (AptNativeHash::Entry *)hash->rva0070AA40(); entry; entry = hash->rva0070AAA0(entry))
	{
		EAStringC name(entry->key);
		if (name.GetAt(0) == '_')
		{
			const char *rest = name.rva00620090() + 1;
			if (strcmp(rest, "_proto__") != 0 && strcmp(rest, "type") != 0)
			{
				AptValue *value = entry->value;
				if (!value->isNativeFunction())
				{
					value->toString(valueText);
					result.Rva006D4F00Append(name);
					result.Rva006D50A0Append("=");
					result.Rva006D4F00Append(valueText);
					result.Rva006D50A0Append("&");
				}
			}
		}
	}
	result.rva006D5DA0("&");
	return result;
}
