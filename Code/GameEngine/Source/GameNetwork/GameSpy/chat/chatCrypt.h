/* GameSpy Chat reconstruction declarations from nitrocaster/GameSpy
 * d1deb2d1a951cf77933dda040b8d311cc09815a7, src/GameSpy/Chat.
 * Adapted to the retail-compatible2004 platform/collection headers.
 * See ../PROVENANCE.txt and CHAT-SDK-LICENSE.txt. */
#ifndef _CHATCRYPT_H_
#define _CHATCRYPT_H_
#ifdef __cplusplus
extern "C" {
#endif

	
typedef struct _gs_crypt_key
{      
   unsigned char state[256];       
   unsigned char x;        
   unsigned char y;
} gs_crypt_key;


void gs_prepare_key(const unsigned char *key_data_ptr, int key_data_len, gs_crypt_key *key);
void gs_crypt(unsigned char *buffer_ptr, int buffer_len, gs_crypt_key *key);
void gs_xcode_buf(char *buf, int len, char *enckey);

#ifdef __cplusplus
}
#endif

#endif
