// Rva007E8810Message: canonical declarations for the members 22 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_RVA007E8810MESSAGE_H
#define CANONICAL_RVA007E8810MESSAGE_H

class Rva007E8810Message
{
public:
	void addBool(const char *key, bool value);
	void addInt(const char *key, int value);
	void addInt64(const char *key, __int64 value);
	void addString(const char *key, const char *value);
	int getError();
	int getInt(const char *key, int defaultValue);
	__int64 getInt64(const char *name, __int64 missing);
	bool getString(const char *key, char *dest, int destSize);
	bool hasError();
	void reset();
	void rva007E8EF0(const char *key, const char *value);
	void setError(int code);
};

#endif // CANONICAL_RVA007E8810MESSAGE_H
