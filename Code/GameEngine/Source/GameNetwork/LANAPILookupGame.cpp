// ?LookupGame@LANAPI@@UAEPAVLANGameInfo@@VUnicodeString@@@Z
// cl: /O1 /DNDEBUG /MD /EHsc
//
// Retail 0x0044B915, 125 bytes. The target LANAPI table places LookupGame
// after OnNameChange at slot 49. It searches the game list at +0x10, obtains
// each name through LANGameInfo slot 23, compares UnicodeStrings, and follows
// the target next link at +0xF5C. BFME1 supplies the same search operation.

typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;

class UnicodeString;

template <typename T> class StringBase
{
friend class UnicodeString;

public:
	int compare( const StringBase<T> &other ) const throw();

protected:
	~StringBase();

private:
	StringBase( const StringBase<T> &other );
	void releaseBuffer( void );
	void *m_data;
};

class UnicodeString : public StringBase<WideChar>
{
public:
	__forceinline UnicodeString( const UnicodeString &other )
		: StringBase<WideChar>( other ) {}
	~UnicodeString();
	int compare( const UnicodeString &other ) const;
};

class LANGameInfo
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
	virtual UnicodeString getName( void ) = 0;
	UnsignedByte m_beforeNext[0xF5C - 4];
	LANGameInfo *m_next;
};

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
	virtual void slot31( void ) = 0;
	virtual void slot32( void ) = 0;
	virtual void slot33( void ) = 0;
	virtual void slot34( void ) = 0;
	virtual void slot35( void ) = 0;
	virtual void slot36( void ) = 0;
	virtual void slot37( void ) = 0;
	virtual void slot38( void ) = 0;
	virtual void slot39( void ) = 0;
	virtual void slot40( void ) = 0;
	virtual void slot41( void ) = 0;
	virtual void slot42( void ) = 0;
	virtual void slot43( void ) = 0;
	virtual void slot44( void ) = 0;
	virtual void slot45( void ) = 0;
	virtual void slot46( void ) = 0;
	virtual void slot47( void ) = 0;
	virtual void slot48( void ) = 0;
	virtual LANGameInfo *LookupGame( UnicodeString name );

protected:
	UnsignedByte m_beforeGames[0x10 - 4];
	LANGameInfo *m_games;
};

LANGameInfo *LANAPI::LookupGame( UnicodeString name )
{
	LANGameInfo *game = m_games;
	while( game && ((const StringBase<WideChar> &)game->getName()).compare( (const StringBase<WideChar> &)name ) != 0 )
		game = game->m_next;
	return game;
}
