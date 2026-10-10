// cl: /O1 /MD
// INI field-parse forwarders: Zero Hour's BitFlags<N>::parseFromINI shape,
//   static void parseFromINI(INI *ini, void *, void *store, const void *)
//   { ((BitFlags *)store)->parse(ini, NULL); }
// for seven parse targets the ledger already rows under address-derived
// classes. Each forwarder is a FieldParse entry's parser (token, parser,
// userData, offset) in retail .data; the token names are in each comment.
// The forwarders stay static members of their target's class.
class INI;
class Rva0033B84ETok;

class Rva0021B7B6
{
public:
	void rva0021B7B6(INI *ini, void *str);
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

class Rva0033AFBB
{
public:
	void rva0033B84E(INI *ini, Rva0033B84ETok *str);
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

class Rva003B1017
{
public:
	void rva003B1017(INI *ini, void *str);
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

class Rva003FB508
{
public:
	void rva003FB508(INI *ini, void *str);
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

class Rva00417DFB
{
public:
	void rva00417DFB(INI *ini, void *str);
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

class Rva0049B8A0
{
public:
	void rva0049B8A0(INI *ini, void *str);
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

class Rva0049DD83
{
public:
	void rva0049DD83(INI *ini, void *str);
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

// @0x0021C3E7 16B
void Rva0021B7B6::parseFromINI(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	((Rva0021B7B6 *)store)->rva0021B7B6(ini, 0);
}

// @0x0033BEE5 16B
void Rva0033AFBB::parseFromINI(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	((Rva0033AFBB *)store)->rva0033B84E(ini, 0);
}

// @0x003B1327 16B
void Rva003B1017::parseFromINI(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	((Rva003B1017 *)store)->rva003B1017(ini, 0);
}

// @0x003FB5F2 16B
void Rva003FB508::parseFromINI(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	((Rva003FB508 *)store)->rva003FB508(ini, 0);
}

// @0x00417EF9 16B
void Rva00417DFB::parseFromINI(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	((Rva00417DFB *)store)->rva00417DFB(ini, 0);
}

// @0x0049BBA3 16B
void Rva0049B8A0::parseFromINI(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	((Rva0049B8A0 *)store)->rva0049B8A0(ini, 0);
}

// @0x0049DF62 16B
void Rva0049DD83::parseFromINI(INI *ini, void * /*instance*/, void *store, const void * /*userData*/)
{
	((Rva0049DD83 *)store)->rva0049DD83(ini, 0);
}
