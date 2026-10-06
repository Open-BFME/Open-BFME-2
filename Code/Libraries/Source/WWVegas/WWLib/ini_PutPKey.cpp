// cl: /Ireference/shims/bfmerendobj /DNDEBUG /D_WINDOWS /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// WWLib INIClass::Put_PKey, from the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WWLib/ini.cpp). Retail 0x00618FB0 (90B).
// Split from ini.cpp (which omits the PKey methods to avoid the pk.h/BigInt
// dependency); PKey crypto itself lives in pk.cpp.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
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

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include	"always.h"
#include	"ini.h"
#include	"pk.h"


/***********************************************************************************************
 * INIClass::Put_PKey -- Stores the key to the INI database.                                   *
 *                                                                                             *
 *    The key stored to the database will have both the exponent and modulus portions saved.   *
 *                                                                                             *
 * INPUT:   key   -- The key to store the INI database.                                        *
 *                                                                                             *
 * OUTPUT:  bool; Was the key stored to the database?                                          *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/08/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
bool INIClass::Put_PKey(PKey const & key)
{
	char buffer[512];

	int len = key.Encode_Modulus(buffer);
	Put_UUBlock("PublicKey", buffer, len);

	len = key.Encode_Exponent(buffer);
	Put_UUBlock("PrivateKey", buffer, len);
	return(true);
}


/***********************************************************************************************
 * INIClass::Get_PKey -- Fetch a key from the ini database.                                    *
 *                                                                                             *
 *    This routine will fetch the key from the INI database. The key fetched is controlled by  *
 *    the parameter. There are two choices of key -- the fast or slow key.                     *
 *                                                                                             *
 * INPUT:   fast  -- Should the fast key be retrieved? The fast key has the advantage of       *
 *                   requiring only the modulus value.                                         *
 *                                                                                             *
 * OUTPUT:  Returns with the key retrieved.                                                    *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   07/08/1996 JLB : Created.                                                                 *
 *=============================================================================================*/
PKey INIClass::Get_PKey(bool fast) const
{
	PKey key;
	char buffer[512];

	/*
	**	When retrieving the fast key, the exponent is a known constant. Don't parse the
	**	exponent from the database.
	*/
	if (fast) {
		BigInt exp = PKey::Fast_Exponent();
		exp.DEREncode((unsigned char *)buffer);
		key.Decode_Exponent(buffer);
	} else {
		Get_UUBlock("PrivateKey", buffer, sizeof(buffer));
		key.Decode_Exponent(buffer);
	}

	Get_UUBlock("PublicKey", buffer, sizeof(buffer));
	key.Decode_Modulus(buffer);

	return(key);
}
