// Rva007E8810Message: canonical declarations for the FESL message record the GameNetwork units share.
// Fields +0x04..+0x30 follow the stores of the rowed constructor at 0x006558C0; +0x00 stays opaque.
#ifndef CANONICAL_RVA007E8810MESSAGE_H
#define CANONICAL_RVA007E8810MESSAGE_H

class Rva007E8810Message
{
public:
	Rva007E8810Message();
	~Rva007E8810Message();
	void addBool(const char *key, bool value);
	void addInt(const char *key, int value);
	void addInt64(const char *key, __int64 value);
	void addString(const char *key, const char *value);
	bool getBool(const char *key, bool defaultValue);
	int getError();
	int getInt(const char *key, int defaultValue);
	__int64 getInt64(const char *name, __int64 missing);
	bool getString(const char *key, char *dest, int destSize);
	bool hasError();
	void reset();
	void rva007E8EF0(const char *key, const char *value);
	void setError(int code);

	char m_pad00[4];
	int m_04;
	int m_08;
	int m_0C;
	char *m_10;
	int m_14;
	int m_18;
	unsigned int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;
};

#endif // CANONICAL_RVA007E8810MESSAGE_H
