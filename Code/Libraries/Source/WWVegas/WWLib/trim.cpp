// cl: /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep


#include	"always.h"
#include	"trim.h"
#include	<string.h>

#ifdef _UNIX
#include	<wctype.h>
#endif // _UNIX


char* strtrim(char* buffer)
{
	if (buffer) {
		/* Strip leading white space from the string. */
		char* source = buffer;

		while ((*source != 0) && ((unsigned char)*source <= 32)) {
			++source;
		}

		if (source != buffer) {
			strcpy(buffer, source);
		}

		/* Clip trailing white space from the string. */
		for (int index = strlen(buffer) - 1; index >= 0; --index) {
			if ((*source != 0) && ((unsigned char)buffer[index] <= 32)) {
				buffer[index] = '\0';
			} else {
				break;
			}
		}
	}

	return buffer;
}


wchar_t* wcstrim(wchar_t* buffer)
{
	if (buffer) {
		/* Strip leading white space from the string. */
		wchar_t* source = buffer;

		while ((*source != 0) && ((unsigned int)*source <= 32)) {
			++source;
		}

		if (source != buffer) {
			wcscpy(buffer, source);
		}

		/* Clip trailing white space from the string. */
		for (int index = wcslen(buffer) - 1; index >= 0; --index) {
			if ((*source != 0) && ((unsigned int)buffer[index] <= 32)) {
				buffer[index] = L'\0';
			} else {
				break;
			}
		}
	}

	return buffer;
}
