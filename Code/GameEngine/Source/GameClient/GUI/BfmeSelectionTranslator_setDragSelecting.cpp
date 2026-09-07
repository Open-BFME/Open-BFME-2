// cl: /DNDEBUG /MD /EHsc

// BfmeSelectionTranslator::setDragSelecting, transferred from the exact
// BFME1 reconstruction
// (Code/GameEngine/Source/GameClient/GUI/BfmeSelectionTranslator_setDragSelecting.cpp).
// Retail BFME2 clears the same three state bytes at +0x05, +0x06 and +0x04.

class BfmeSelectionTranslator
{
private:
	unsigned char m_unmodelled_00[ 0x04 ];
	unsigned char m_unmodelled_04;
	unsigned char m_unmodelled_05;
	unsigned char m_unmodelled_06;

public:
	void setDragSelecting( void );
};

// ?setDragSelecting@BfmeSelectionTranslator@@QAEXXZ
void BfmeSelectionTranslator::setDragSelecting( void )
{
	m_unmodelled_05 = 0;
	m_unmodelled_06 = 0;
	m_unmodelled_04 = 0;
}
