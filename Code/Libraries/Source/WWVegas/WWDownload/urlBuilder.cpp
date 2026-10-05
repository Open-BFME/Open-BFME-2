// cl: /O2 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Ported from Zero Hour's Libraries/Source/WWVegas/WWDownload/urlBuilder.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference),
// built like registry.cpp beside it. BFME 2 drops the SKU: the base URL is
// the registry's online server plus "/", the default language is "ENGLISH"
// and it is lower-cased before the URLs are formatted.

// _snprintf and tolower stay the msvcr71 imports retail calls through.
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
namespace _STL { void __cdecl free(void *block); }
#define free _STL::free
#include <string>
#undef free
#include <algorithm>

bool GetStringFromRegistry(std::string path, std::string key, std::string& val);
bool GetUnsignedIntFromRegistry(std::string path, std::string key, unsigned int& val);
const char *GetRegistryOnlineServer();

void FormatURLFromRegistry( std::string& gamePatchURL, std::string& mapPatchURL,
													 std::string& configURL, std::string& motdURL )
{
	std::string language = "ENGLISH";
	unsigned int version = 0; // invalid version - can't get on with a corrupt reg.
	unsigned int mapVersion = 0; // invalid version - can't get on with a corrupt reg.
	std::string baseURL = GetRegistryOnlineServer();
	baseURL.append("/");

	GetStringFromRegistry("", "BaseURL", baseURL);
	GetStringFromRegistry("", "Language", language);
	GetUnsignedIntFromRegistry("", "Version", version);
	GetUnsignedIntFromRegistry("", "MapPackVersion", mapVersion);

	std::transform(language.begin(), language.end(), language.begin(), tolower);

	char buf[256];
	_snprintf(buf, 256, "%s%s-%d.txt", baseURL.c_str(), language.c_str(), version);
	gamePatchURL = buf;
	_snprintf(buf, 256, "%smaps-%d.txt", baseURL.c_str(), mapVersion);
	mapPatchURL = buf;
	_snprintf(buf, 256, "%sconfig.txt", baseURL.c_str());
	configURL = buf;
	_snprintf(buf, 256, "%sMOTD-%s.txt", baseURL.c_str(), language.c_str());
	motdURL = buf;
}
