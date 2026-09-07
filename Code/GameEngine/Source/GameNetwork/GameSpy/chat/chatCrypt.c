// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK: clean C reconstruction from the 2007 SDK through
   Open-BFME-1 commit 9f4139765ead6d02b8a04bbf167b59f1186a964e.
   See ../PROVENANCE.txt for the source and project permission record.
   gs_prepare_key places uniquely in game.dat at RVA 0x006A9ED0;
   its complete 341-byte body has no relocations. */
typedef struct
{
	unsigned char state[256];
	unsigned char x;
	unsigned char y;
} gs_crypt_key;

void gs_prepare_key(const unsigned char *key_data_ptr, int key_data_len, gs_crypt_key *key);
void gs_crypt(unsigned char *buffer_ptr, int buffer_len, gs_crypt_key *key);
void gs_xcode_buf(char *buf, int len, char *enckey);


#define swap_byte(x,y) t = *(x); *(x) = *(y); *(y) = t

void gs_prepare_key(const unsigned char *key_data_ptr, int key_data_len, gs_crypt_key *key)
{
	unsigned char t;
	unsigned char index1;
	unsigned char index2;
	unsigned char* state;
	int counter;
	
	state = &key->state[0];
	for(counter = 0; counter < 256; counter++)
		state[255 - counter] = (unsigned char)counter; //crt - we fill reverse of normal
	key->x = 0;
	key->y = 0;
	index1 = 0;
	index2 = 0;
	for(counter = 0; counter < 256; counter++)
	{
		index2 = (unsigned char)((key_data_ptr[index1] + state[counter] + index2) % 256);
		swap_byte(&state[counter], &state[index2]);
		index1 = (unsigned char)((index1 + 1) % key_data_len);
	}
}
