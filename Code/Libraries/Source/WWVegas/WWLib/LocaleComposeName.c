// cl: /O2 /MD
// STLport 4.5.3 Win32 _Locale_compose_name.

__declspec(dllimport) int __cdecl strcmp(const char *left, const char *right);
__declspec(dllimport) char *__cdecl strcpy(char *destination, const char *source);
__declspec(dllimport) char *__cdecl strcat(char *destination, const char *source);

char *_Locale_compose_name(
    char *buf,
    const char *ctype,
    const char *numeric,
    const char *time,
    const char *collate,
    const char *monetary,
    const char *messages)
{
    if (!strcmp(ctype, numeric) &&
        !strcmp(ctype, time) &&
        !strcmp(ctype, collate) &&
        !strcmp(ctype, monetary) &&
        !strcmp(ctype, messages))
        return strcpy(buf, ctype);

    strcpy(buf, "LC_CTYPE=");
    strcat(buf, ctype);
    strcat(buf, ";");
    strcat(buf, "LC_TIME=");
    strcat(buf, time);
    strcat(buf, ";");
    strcat(buf, "LC_NUMERIC=");
    strcat(buf, numeric);
    strcat(buf, ";");
    strcat(buf, "LC_COLLATE=");
    strcat(buf, collate);
    strcat(buf, ";");
    strcat(buf, "LC_MONETARY=");
    strcat(buf, monetary);
    strcat(buf, ";");
    strcat(buf, "LC_MESSAGES=");
    strcat(buf, messages);
    strcat(buf, ";");
    return buf;
}




char *Rva0084D360(char *name, char *out)
{
	char *esi = out;
	if (name[0] == 0x4c && name[1] == 0x43 && name[2] == 0x5f)
	{
		*(unsigned short *)esi = 0x43;
		return esi;
	}
	{
		int delta = (int)esi - (int)name;
		char c;
		do
		{
			c = *name;
			name[delta] = c;
			++name;
		} while (c);
		return esi;
	}
}


/* STLport 4.5.3 c_locale_win32.c: __Extract_locale_name.
   Whole clean BFME1 game/Libraries/Source/STLport/LocaleExtractName.c at
   6583b3c1ff21db4a561285717028fdafc780b7db supplies the unchanged helper and
   its five source call contexts. Native BF2 216A0/153 is INT3 delimited;
   its signed category guard, LC_ prefix, six category strings, four named CRT
   imports and 256-byte bound independently support the donor helper role.
   The original compiler-private symbol spelling remains donor provenance.
   Native ABI: EAX input text, ECX category, EBX output buffer, EAX result.
   Its shared six-slot table at VA DA7190 is defined once by LocaleFacets.
   The five unpinned source callers preserve that compiler contract; their
   presence is not a BF2 identity or retail-body claim. Whole-byte search
   supplies no supported BF2 placement for those callers. */
typedef unsigned int size_t;
__declspec(dllimport) char *__cdecl strstr(const char *, const char *);
__declspec(dllimport) char *__cdecl strchr(const char *, int);
__declspec(dllimport) size_t __cdecl strcspn(const char *, const char *);
__declspec(dllimport) char *__cdecl strncpy(char *, const char *, size_t);

#define LC_ALL 0
#define LC_MAX 5
#define _Locale_MAX_SIMPLE_NAME 256

extern const char *__category_name[];

static const char *__Extract_locale_name(const char *loc, int category, char *buf)
{
  char *expr;
  size_t len_name;
  buf[0] = 0;

  if (category < LC_ALL || category > LC_MAX) return 0;

  if (loc[0] == 'L' && loc[1] == 'C' && loc[2] == '_') {
    expr = strstr((char*)loc, __category_name[category]);
    if (expr == 0) return 0; /* Category not found. */
    expr = strchr(expr, '=');
    if (expr == 0) return 0;
    ++expr;
    len_name = strcspn(expr, ";");
    len_name = len_name > _Locale_MAX_SIMPLE_NAME ? _Locale_MAX_SIMPLE_NAME : len_name;
    strncpy(buf, expr, len_name); buf[len_name] = 0;
    return buf;
  }
  else {
    return strncpy(buf, loc, _Locale_MAX_SIMPLE_NAME);
  }
}

// ?_Locale_extract_ctype_name present-unmatched
const char *_Locale_extract_ctype_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 2, buf); }
// ?_Locale_extract_numeric_name present-unmatched
const char *_Locale_extract_numeric_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 4, buf); }
// ?_Locale_extract_time_name present-unmatched
const char *_Locale_extract_time_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 5, buf); }
// ?_Locale_extract_collate_name present-unmatched
const char *_Locale_extract_collate_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 1, buf); }
// ?_Locale_extract_monetary_name present-unmatched
const char *_Locale_extract_monetary_name(const char *cname, char *buf) { return __Extract_locale_name(cname, 3, buf); }
