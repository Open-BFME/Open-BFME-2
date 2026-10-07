// cl: /Od /GZ /GS /MD /DNDEBUG
/* BFME-era DirtySock ProtoSSL certificate parser and verifier. */

typedef unsigned char uint8_t;

enum
{
	ASN_TYPE_INTEGER = 0x02,
	ASN_TYPE_BITSTRING = 0x03,
	ASN_TYPE_OBJECT = 0x06,
	ASN_TYPE_SEQN = 0x10,
	ASN_TYPE_SET = 0x11,
	ASN_TYPE_PRINTSTR = 0x13,
	ASN_TYPE_T61 = 0x14,
	ASN_TYPE_UTCTIME = 0x17,
	ASN_CONSTRUCT = 0x20,
	ASN_OBJ_NONE = 0,
	ASN_OBJ_COUNTRY = 1,
	ASN_OBJ_STATE = 2,
	ASN_OBJ_CITY = 3,
	ASN_OBJ_ORGANIZATION = 4,
	ASN_OBJ_UNIT = 5,
	ASN_OBJ_COMMON = 6,
	ASN_OBJ_RSA_PKCS_KEY = 7,
	ASN_OBJ_RSA_PKCS_MD5 = 8,
	ASN_OBJ_RSA_PKCS_SHA1 = 9
};

struct ProtoSSLCertIdent
{
	char country[32];
	char state[32];
	char city[32];
	char organization[32];
	char unit[32];
	char common[32];
};

struct X509Certificate
{
	int unused00;
	struct ProtoSSLCertIdent issuer;
	struct ProtoSSLCertIdent subject;
	char goodFrom[32];
	char goodTill[32];
	int serialSize;
	uint8_t serialData[32];
	int sigType;
	int sigSize;
	uint8_t sigData[128];
	int keyType;
	uint8_t unused274[64];
	int keyDataSize;
	uint8_t keyData[256];
	int keyModSize;
	uint8_t keyModData[128];
	int unused43c;
	int keyExpSize;
	uint8_t keyExpData[129];
};

struct ProtoSSLCACert
{
	const char *country;
	const char *state;
	const char *city;
	const char *organization;
	const char *unit;
	const char *common;
	const uint8_t *keyModData;
	int keyModSize;
	uint8_t keyExpData[4];
};

/* Target certificate data: three 36-byte records followed by the zero sentinel.
 * The record-1 empty names use three adjacent target zero-fill cells. */
static const uint8_t g_Rva0112CB48Modulus0[128] = {
	0x92, 0x75, 0xA1, 0x5B, 0x08, 0x02, 0x40, 0xB8, 0x9B, 0x40, 0x2F, 0xD5, 0x9C, 0x71, 0xC4, 0x51,
	0x58, 0x71, 0xD8, 0xF0, 0x2D, 0x93, 0x7F, 0xD3, 0x0C, 0x8B, 0x1C, 0x7D, 0xF9, 0x2A, 0x04, 0x86,
	0xF1, 0x90, 0xD1, 0x31, 0x0A, 0xCB, 0xD8, 0xD4, 0x14, 0x12, 0x90, 0x3B, 0x35, 0x6A, 0x06, 0x51,
	0x49, 0x4C, 0xC5, 0x75, 0xEE, 0x0A, 0x46, 0x29, 0x80, 0xF0, 0xD5, 0x3A, 0x51, 0xBA, 0x5D, 0x6A,
	0x19, 0x37, 0x33, 0x43, 0x68, 0x25, 0x2D, 0xFE, 0xDF, 0x95, 0x26, 0x36, 0x7C, 0x43, 0x64, 0xF1,
	0x56, 0x17, 0x0E, 0xF1, 0x67, 0xD5, 0x69, 0x54, 0x20, 0xFB, 0x3A, 0x55, 0x93, 0x5D, 0xD4, 0x97,
	0xBC, 0x3A, 0xD5, 0x8F, 0xD2, 0x44, 0xC5, 0x9A, 0xFF, 0xCD, 0x0C, 0x31, 0xDB, 0x9D, 0x94, 0x7C,
	0xA6, 0x66, 0x66, 0xFB, 0x4B, 0xA7, 0x5E, 0xF8, 0x64, 0x4E, 0x28, 0xB1, 0xA6, 0xB8, 0x73, 0x95,
};

static const uint8_t g_Rva0112CB48Modulus1[125] = {
	0x92, 0xCE, 0x7A, 0xC1, 0xAE, 0x83, 0x3E, 0x5A, 0xAA, 0x89, 0x83, 0x57, 0xAC, 0x25, 0x01, 0x76,
	0x0C, 0xAD, 0xAE, 0x8E, 0x2C, 0x37, 0xCE, 0xEB, 0x35, 0x78, 0x64, 0x54, 0x03, 0xE5, 0x84, 0x40,
	0x51, 0xC9, 0xBF, 0x8F, 0x08, 0xE2, 0x8A, 0x82, 0x08, 0xD2, 0x16, 0x86, 0x37, 0x55, 0xE9, 0xB1,
	0x21, 0x02, 0xAD, 0x76, 0x68, 0x81, 0x9A, 0x05, 0xA2, 0x4B, 0xC9, 0x4B, 0x25, 0x66, 0x22, 0x56,
	0x6C, 0x88, 0x07, 0x8F, 0xF7, 0x81, 0x59, 0x6D, 0x84, 0x07, 0x65, 0x70, 0x13, 0x71, 0x76, 0x3E,
	0x9B, 0x77, 0x4C, 0xE3, 0x50, 0x89, 0x56, 0x98, 0x48, 0xB9, 0x1D, 0xA7, 0x29, 0x1A, 0x13, 0x2E,
	0x4A, 0x11, 0x59, 0x9C, 0x1E, 0x15, 0xD5, 0x49, 0x54, 0x2C, 0x73, 0x3A, 0x69, 0x82, 0xB1, 0x97,
	0x39, 0x9C, 0x6D, 0x70, 0x67, 0x48, 0xE5, 0xDD, 0x2D, 0xD6, 0xC8, 0x1E, 0x7B,
};

static const uint8_t g_Rva0112CB48Modulus2[128] = {
	0x9F, 0x50, 0x24, 0x61, 0xED, 0xBB, 0xC5, 0x6A, 0x2D, 0x17, 0x67, 0x34, 0x6C, 0x9B, 0x59, 0xA1,
	0x2A, 0x24, 0xB4, 0x71, 0x58, 0x54, 0xC0, 0x30, 0x57, 0x9D, 0x05, 0x78, 0x14, 0x83, 0x3B, 0xA8,
	0x9C, 0x6C, 0x7A, 0x06, 0x31, 0x79, 0x3E, 0xD4, 0x9F, 0xAC, 0x77, 0x0E, 0x6A, 0x43, 0x98, 0x66,
	0x75, 0xDB, 0x75, 0xE4, 0x49, 0x86, 0x3E, 0xB1, 0x62, 0x53, 0x52, 0xE7, 0xD4, 0xAA, 0x8C, 0x8D,
	0x66, 0x76, 0xB9, 0x0B, 0x1B, 0x20, 0x11, 0x33, 0x04, 0x4B, 0xD0, 0xFF, 0xF0, 0x62, 0x4B, 0x50,
	0x4D, 0x3E, 0xB6, 0x17, 0x49, 0x7C, 0xD8, 0xF3, 0x9F, 0x3D, 0x95, 0x30, 0xDD, 0x6D, 0x77, 0xB0,
	0x2D, 0x37, 0xF4, 0xE4, 0xFD, 0xCD, 0x5B, 0x76, 0x94, 0xF5, 0x04, 0xF7, 0x86, 0x2F, 0xBB, 0x03,
	0x7C, 0xCC, 0x2A, 0x09, 0xCE, 0x23, 0xA7, 0x3F, 0x97, 0x00, 0x55, 0xD5, 0xA0, 0x1E, 0xC5, 0xC5,
};

static const char g_Rva0112CB48EmptyStrings[3] = { 0, 0, 0 };

struct ProtoSSLCACert g_Rva0112CB48[4] =
{
	{ "US", "California", "Redwood City", "Electronic Arts, Inc.", "Online Technology Group", "OTG3 Certificate Authority", g_Rva0112CB48Modulus0, 128, { 0x00, 0x00, 0x00, 0x03 } },
	{ "US", g_Rva0112CB48EmptyStrings + 0, g_Rva0112CB48EmptyStrings + 1, "RSA Data Security, Inc.", "Secure Server Certification Authority", g_Rva0112CB48EmptyStrings + 2, g_Rva0112CB48Modulus1, 125, { 0x00, 0x01, 0x00, 0x01 } },
	{ "US", "California", "Redwood City", "Electronic Arts, Inc.", "Online Technology Group", "OTG Certificate Authority", g_Rva0112CB48Modulus2, 128, { 0x00, 0x01, 0x00, 0x01 } },
	{ 0, 0, 0, 0, 0, 0, 0, 0, { 0, 0, 0, 0 } }
};

const uint8_t *Rva0080D7A0(const uint8_t *, const uint8_t *, int *, int *);
int Rva0080D890(const void *, int);
void Rva0080D930(const char *, int, char *, int);
void Rva0080D590(const uint8_t *, int, char *);
void Rva0080D620(const uint8_t *, int, uint8_t *);
void Rva0080D6C0(struct ProtoSSLCACert *, const void *, int, void *, int);
void Rva007FE780(const char *, ...);
void *memset(void *, int, unsigned int);
void *memcpy(void *, const void *, unsigned int);
int memcmp(const void *, const void *, unsigned int);
int strcmp(const char *, const char *);

int Rva0080C960(void *state, struct X509Certificate *cert,
	const uint8_t *data, int size)
{
	int iType;
	int objectType;
	const uint8_t *infoSkip;
	const uint8_t *sigSkip;
	const uint8_t *issuerSkip;
	const uint8_t *subjectSkip;
	const uint8_t *keySkip;
	const uint8_t *infoData;
	const uint8_t *last = data + size;
	int infoSize;
	int hashSize;
	uint8_t strHash[20];
	uint8_t strSigHash[20];
	struct ProtoSSLCACert *ca;

	memset(cert, 0, sizeof(*cert));
	data = Rva0080D7A0(data, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -1;

	infoData = data;
	data = Rva0080D7A0(data, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -2;
	infoSize = size + 4;
	infoSkip = data + size;

	if (*data != ASN_TYPE_INTEGER)
	{
		data = Rva0080D7A0(data, last, 0, &size);
		if (data == 0)
			return -3;
		data += size;
	}

	data = Rva0080D7A0(data, infoSkip, &iType, &size);
	if (data == 0 || size < 0 || (unsigned int)size > sizeof(cert->serialData))
		return -4;
	cert->serialSize = size;
	memcpy(cert->serialData, data, size);
	data += size;

	data = Rva0080D7A0(data, infoSkip, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -5;
	sigSkip = data + size;
	data = Rva0080D7A0(data, infoSkip, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_OBJECT)
		return -6;
	cert->sigType = Rva0080D890(data, size);
	if (cert->sigType == ASN_OBJ_NONE)
	{
		Rva007FE780("ProtoSSL: unsupported signature algorithm\n");
		return -7;
	}
	data += size;

	data = Rva0080D7A0(sigSkip, infoSkip, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -8;
	issuerSkip = data + size;
	objectType = 0;
	while ((data = Rva0080D7A0(data, issuerSkip, &iType, &size)) != 0)
	{
		if (iType != ASN_TYPE_SEQN + ASN_CONSTRUCT && iType != ASN_TYPE_SET + ASN_CONSTRUCT)
		{
			if (iType == ASN_TYPE_OBJECT)
				objectType = Rva0080D890(data, size);
			if (iType == ASN_TYPE_PRINTSTR || iType == ASN_TYPE_T61)
			{
				if (objectType == ASN_OBJ_COUNTRY) Rva0080D930((const char *)data, size, cert->issuer.country, 32);
				if (objectType == ASN_OBJ_STATE) Rva0080D930((const char *)data, size, cert->issuer.state, 32);
				if (objectType == ASN_OBJ_CITY) Rva0080D930((const char *)data, size, cert->issuer.city, 32);
				if (objectType == ASN_OBJ_ORGANIZATION) Rva0080D930((const char *)data, size, cert->issuer.organization, 32);
				if (objectType == ASN_OBJ_UNIT) Rva0080D930((const char *)data, size, cert->issuer.unit, 32);
				if (objectType == ASN_OBJ_COMMON) Rva0080D930((const char *)data, size, cert->issuer.common, 32);
				objectType = 0;
			}
			data += size;
		}
	}

	data = Rva0080D7A0(issuerSkip, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -9;
	data = Rva0080D7A0(data, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_UTCTIME)
		return -10;
	Rva0080D930((const char *)data, size, cert->goodFrom, 32);
	data += size;
	data = Rva0080D7A0(data, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_UTCTIME)
		return -11;
	Rva0080D930((const char *)data, size, cert->goodTill, 32);
	data += size;

	data = Rva0080D7A0(data, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -12;
	subjectSkip = data + size;
	objectType = 0;
	while ((data = Rva0080D7A0(data, subjectSkip, &iType, &size)) != 0)
	{
		if (iType != ASN_TYPE_SEQN + ASN_CONSTRUCT && iType != ASN_TYPE_SET + ASN_CONSTRUCT)
		{
			if (iType == ASN_TYPE_OBJECT)
				objectType = Rva0080D890(data, size);
			if (iType == ASN_TYPE_PRINTSTR || iType == ASN_TYPE_T61)
			{
				if (objectType == ASN_OBJ_COUNTRY) Rva0080D930((const char *)data, size, cert->subject.country, 32);
				if (objectType == ASN_OBJ_STATE) Rva0080D930((const char *)data, size, cert->subject.state, 32);
				if (objectType == ASN_OBJ_CITY) Rva0080D930((const char *)data, size, cert->subject.city, 32);
				if (objectType == ASN_OBJ_ORGANIZATION) Rva0080D930((const char *)data, size, cert->subject.organization, 32);
				if (objectType == ASN_OBJ_UNIT) Rva0080D930((const char *)data, size, cert->subject.unit, 32);
				if (objectType == ASN_OBJ_COMMON) Rva0080D930((const char *)data, size, cert->subject.common, 32);
				objectType = 0;
			}
			data += size;
		}
	}

	data = Rva0080D7A0(subjectSkip, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -13;
	data = Rva0080D7A0(data, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -14;
	keySkip = data + size;
	data = Rva0080D7A0(data, keySkip, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_OBJECT)
		return -15;
	cert->keyType = Rva0080D890(data, size);
	data = Rva0080D7A0(keySkip, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_BITSTRING || size < 1 || (unsigned int)size > 256)
		return -16;
	cert->keyDataSize = size - 1;
	memcpy(cert->keyData, data + 1, size - 1);
	data += size;

	data = Rva0080D7A0(infoSkip, sigSkip, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
		return -18;
	sigSkip = data + size;
	data = Rva0080D7A0(data, sigSkip, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_OBJECT)
		return -19;
	cert->sigType = Rva0080D890(data, size);
	data = Rva0080D7A0(sigSkip, last, &iType, &size);
	if (data == 0 || iType != ASN_TYPE_BITSTRING || size - 1 < 0 || (unsigned int)(size - 1) > 128)
		return -20;
	cert->sigSize = size - 1;
	memcpy(cert->sigData, data + 1, size - 1);
	data += size;

	if (cert->keyType == ASN_OBJ_RSA_PKCS_KEY)
	{
		data = Rva0080D7A0(cert->keyData, cert->keyData + cert->keyDataSize, &iType, &size);
		if (data == 0 || iType != ASN_TYPE_SEQN + ASN_CONSTRUCT)
			return -21;
		data = Rva0080D7A0(data, cert->keyData + cert->keyDataSize, &iType, &size);
		if (data == 0 || iType != ASN_TYPE_INTEGER || size < 4 || (unsigned int)size > 129)
			return -22;
		if (*data == 0)
		{
			cert->keyModSize = size - 1;
			memcpy(cert->keyModData, data + 1, size - 1);
		}
		else
		{
			cert->keyModSize = size;
			memcpy(cert->keyModData, data, size);
		}
		data += size;
		data = Rva0080D7A0(data, cert->keyData + cert->keyDataSize, &iType, &size);
		if (data == 0 || iType != ASN_TYPE_INTEGER || size < 1 || (unsigned int)size > 129)
			return -23;
		if (*data == 0)
		{
			cert->keyExpSize = size - 1;
			memcpy(cert->keyExpData, data + 1, size - 1);
		}
		else
		{
			cert->keyExpSize = size;
			memcpy(cert->keyExpData, data, size);
		}
		data += size;
	}

	if (strcmp((const char *)state + 8, cert->subject.common) != 0)
	{
		Rva007FE780("ProtoSSL: subject mismatch %s != %s\n",
			(const char *)state + 8, cert->subject.common);
		return -24;
	}

	for (ca = g_Rva0112CB48; ca->country != 0; ca++)
	{
		if (strcmp(ca->country, cert->issuer.country) == 0 &&
			strcmp(ca->state, cert->issuer.state) == 0 &&
			strcmp(ca->city, cert->issuer.city) == 0 &&
			strcmp(ca->organization, cert->issuer.organization) == 0 &&
			strcmp(ca->common, cert->issuer.common) == 0)
			break;
	}
	if (ca->country == 0)
		return -25;
	if (ca->keyModSize != cert->sigSize)
	{
		Rva007FE780("ProtoSSL: modulus size mismatch\n");
		return -26;
	}

	switch (cert->sigType)
	{
	case ASN_OBJ_RSA_PKCS_MD5:
		Rva0080D590(infoData, infoSize, (char *)strHash);
		hashSize = 16;
		break;
	case ASN_OBJ_RSA_PKCS_SHA1:
		Rva0080D620(infoData, infoSize, strHash);
		hashSize = 20;
		break;
	default:
		Rva007FE780("ProtoSSL: unknown signature algorithm, should never get here\n");
		hashSize = 0;
	}

	Rva0080D6C0(ca, cert->sigData, cert->sigSize, strSigHash, hashSize);
	if (memcmp(strHash, strSigHash, hashSize) != 0)
	{
		Rva007FE780("ProtoSSL: signature strHash mismatch\n");
		return -27;
	}
	return 0;
}
