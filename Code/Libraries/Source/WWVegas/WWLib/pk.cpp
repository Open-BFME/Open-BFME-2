// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
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

#include "rendobj.h"	// the bfmerendobj shim has to win the include guard
#include	"always.h"
#include	"pk.h"
#include	"rndstraw.h"
#include	<string.h>

// ZH WWLib int.cpp defines these Int<64> template statics for bignum. The
// matched pk.cpp DIR32 sites place them in retail's zero-fill data at
// 0x00E098F0, 0x00E098F1, 0x00E098F4, and 0x00E098F8 respectively.
int bignum::Error = 0;
bool bignum::Carry = false;
bool bignum::Borrow = false;
bignum bignum::Remainder;


#if defined(__BORLANDC__)
extern BigInt Generate_Prime<BigInt>(Straw &, int, BigInt const *);
#endif

#ifdef _MSC_VER
//BigInt Generate_Prime(Straw &, int, BigInt const *);
#endif


PKey::PKey(void const * exponent, void const * modulus)
{
	Modulus.DERDecode((unsigned char *)modulus);
	Exponent.DERDecode((unsigned char *)exponent);
	BitPrecision = Modulus.BitCount()-1;
}


int PKey::Encode_Modulus(void * buffer) const
{
	if (buffer == NULL) {
		return(0);
	}
	return(Modulus.DEREncode((unsigned char *)buffer));
}


int PKey::Encode_Exponent(void * buffer) const
{
	if (buffer == NULL) {
		return(0);
	}
	return(Exponent.DEREncode((unsigned char *)buffer));
}


void PKey::Decode_Modulus(void * buffer)
{
	Modulus.DERDecode((unsigned char *)buffer);
	BitPrecision = Modulus.BitCount()-1;
}


void PKey::Decode_Exponent(void * buffer)
{
	Exponent.DERDecode((unsigned char *)buffer);
}


void PKey::Generate(Straw & random, int bits, PKey & fastkey, PKey & slowkey)
{
	/*
	**	Key generation consists of create a key pair and then testing the key
	**	pair. If the test fails, then repeat the process. The test and repeat
	**	method is required since the prime number generating process can't
	**	guarantee the generation of a prime number -- it can only generate a
	**	highly likely prime number.
	*/
	for (;;) {
		/*
		**	Generate the two random prime numbers. This is the longest
		**	step.
		*/
		BigInt p = Generate_Prime(random, bits, &p);
		BigInt q = Generate_Prime(random, bits, &q);

		/*
		**	The exponent factors are easy to calculate from the prime numbers.
		*/
		BigInt e = Fast_Exponent();
		BigInt n = p * q;
		BigInt pqmin = (p-(unsigned short)1)*(q-(unsigned short)1);
		BigInt d = e.Inverse(pqmin);

		/*
		**	Store the data into the key objects. Notice that the modulus is the
		**	same for both the fast and slow keys. Also notice that the exponent for
		**	the fast key is ALWAYS 65537. Given this, it is possible to economize the
		**	fast key into being just the modulus and the slow key to being just the
		**	exponent (presuming the slow key also has access to the fast key so that
		**	it can get the modulus).
		*/
		fastkey.Exponent = e;
		fastkey.Modulus = n;
		fastkey.BitPrecision = n.BitCount()-1;

		slowkey.Exponent = d;
		slowkey.Modulus = n;
		slowkey.BitPrecision = fastkey.BitPrecision;

		/*
		**	Test the keys by encrypting a block of random bytes. If it decrypts
		**	correctly, then a valid key pair has been generated -- bail.
		*/
		char before[256];
		char after[256];

		for (int index = 0; index < fastkey.Plain_Block_Size(); index++) {
			before[index] = (char)rand();
		}
		fastkey.Encrypt(before, fastkey.Plain_Block_Size(), after);
		slowkey.Decrypt(after, slowkey.Crypt_Block_Size(), after);

		/*
		**	Compare the pre and post processing buffer. A match indicates
		**	a valid key pair.
		*/
		if (memcmp(before, after, fastkey.Plain_Block_Size()) == 0) break;
	}
}


int PKey::Encrypt(void const * source, int slen, void * dest) const
{
	int total = 0;

	/*
	**	Encrypt the source data in full blocks. Partial blocks are not processed and are not
	**	copied to the destination buffer.
	*/
	while (slen >= Plain_Block_Size()) {

		/*
		**	Perform the encryption of the block.
		*/
		BigInt temp = 0;
		memmove(&temp, source, Plain_Block_Size());
		temp = temp.exp_b_mod_c(Exponent, Modulus);

		/*
		**	Move the cypher block to the destination.
		*/
		memmove(dest, &temp, Crypt_Block_Size());
		slen -= Plain_Block_Size();
		source = (char *)source + Plain_Block_Size();
		dest = (char *)dest + Crypt_Block_Size();
		total += Crypt_Block_Size();
	}

	return(total);
}


int PKey::Decrypt(void const * source, int slen, void * dest) const
{
	int total = 0;
	BigInt temp;

	/*
	**	Decrypt the source data in full blocks. Partial blocks are not processed in any way.
	*/
	while (slen >= Crypt_Block_Size()) {

		/*
		**	Perform the encryption.
		*/
		temp = 0;
		memmove(&temp, source, Crypt_Block_Size());
		temp = temp.exp_b_mod_c(Exponent, Modulus);

		/*
		**	Move the cypher block to the destination.
		*/
		memmove(dest, &temp, Plain_Block_Size());
		slen -= Crypt_Block_Size();
		source = (char *)source + Crypt_Block_Size();
		dest = (char *)dest + Plain_Block_Size();
		total += Plain_Block_Size();
	}

	return(total);
}
