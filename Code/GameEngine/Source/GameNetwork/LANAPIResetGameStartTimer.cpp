// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0044973C, 9 bytes. The target LANAPI table places this body at
// slot 31, immediately after RequestLobbyLeave at slot 30; BFME1 names the
// corresponding virtual ResetGameStartTimer. Retail clears the two timer
// dwords at LANAPI +0x20 and +0x24.

typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class LANAPI
{
public:
	virtual void slot00( void ) = 0;
	virtual void slot01( void ) = 0;
	virtual void slot02( void ) = 0;
	virtual void slot03( void ) = 0;
	virtual void slot04( void ) = 0;
	virtual void slot05( void ) = 0;
	virtual void slot06( void ) = 0;
	virtual void slot07( void ) = 0;
	virtual void slot08( void ) = 0;
	virtual void slot09( void ) = 0;
	virtual void slot10( void ) = 0;
	virtual void slot11( void ) = 0;
	virtual void slot12( void ) = 0;
	virtual void slot13( void ) = 0;
	virtual void slot14( void ) = 0;
	virtual void slot15( void ) = 0;
	virtual void slot16( void ) = 0;
	virtual void slot17( void ) = 0;
	virtual void slot18( void ) = 0;
	virtual void slot19( void ) = 0;
	virtual void slot20( void ) = 0;
	virtual void slot21( void ) = 0;
	virtual void slot22( void ) = 0;
	virtual void slot23( void ) = 0;
	virtual void slot24( void ) = 0;
	virtual void slot25( void ) = 0;
	virtual void slot26( void ) = 0;
	virtual void slot27( void ) = 0;
	virtual void slot28( void ) = 0;
	virtual void slot29( void ) = 0;
	virtual void slot30( void ) = 0;
	virtual void ResetGameStartTimer( void );

protected:
	UnsignedByte m_beforeTimer[0x20 - 4];
	UnsignedInt m_gameStartTime;
	UnsignedInt m_gameStartSeconds;
};

void LANAPI::ResetGameStartTimer( void )
{
	m_gameStartTime = 0;
	m_gameStartSeconds = 0;
}
