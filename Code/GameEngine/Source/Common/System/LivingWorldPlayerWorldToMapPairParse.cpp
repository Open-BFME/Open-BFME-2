// cl: /O1 /G7 /Oy- /GX /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// Native003F005F..003F012E and WB0103AC60 parser twin establish the
// World/RTS tags and validation messages. INI separator pointer420 and pair
// string0/4 are retail facts. Original class name remains unknown.
#include "ascii_string.h"
#include <string.h>


class ModuleData;
class INI;

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};


struct Rva003F25DFPair
{
	AsciiString first;
	AsciiString second;
};

class INIReaderP4
{
public:
 char pad[0x420];
 const char *seps;
};
class INI
{
public:
 const char *getNextToken(const char *);
 const char *getNextTokenOrNull(const char *);
};
void Rva003F005F(void *a, void *, void *pair, void *)
{
 INI *ini = (INI *)a;
 const char *key = ini->getNextToken(((INIReaderP4 *)ini)->seps);
 while (key)
 {
  const char *value = ini->getNextToken(((INIReaderP4 *)ini)->seps);
  if (strcmp("World", key) == 0)
   ((StringBase<char> *)&((Rva003F25DFPair *)pair)->first)->set(value);
  else if (strcmp("RTS", key) == 0)
   ((StringBase<char> *)&((Rva003F25DFPair *)pair)->second)->set(value);
  else
   throw INIException(5, "PlayerWorldToMapMatchingData: Unknown sub-key '%s'", key);
  key = ini->getNextTokenOrNull(((INIReaderP4 *)ini)->seps);
 }
 if (((const StringBase<char> *)&((Rva003F25DFPair *)pair)->first)->isEmpty())
  throw INIException(3, "PlayerWorldToMapMatchingData: You must specify a world player name");
 if (((const StringBase<char> *)&((Rva003F25DFPair *)pair)->second)->isEmpty())
  throw INIException(3, "PlayerWorldToMapMatchingData: You must specify an RTS player name");
}
