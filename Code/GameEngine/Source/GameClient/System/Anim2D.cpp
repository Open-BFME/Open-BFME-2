// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
extern "C" void *g_anim2DGameClient;
#pragma comment(linker, "/alternatename:_g_anim2DGameClient=?TheGameClient@@3PAVClientFrameSubsystem@@A")
// Same target pointer at VA00DFE77C; avoid the incompatible donor GameClient declaration.

#define Matrix4x4 Matrix4  // BFME renamed it
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: Anim2D.cpp ///////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, July 2002
// Desc:   A collection of 2D images to make animation
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////

#define ANIM2D_INLINE_SNAPSHOT_DTOR
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#define DEFINE_ANIM_2D_MODE_NAMES
#include "Common/RandomValue.h"
#include "Common/Xfer.h"
#include "GameClient/Anim2D.h"
#include "GameClient/Display.h"
#include "GameClient/GameClient.h"
#include "GameClient/Image.h"

// BFME retains formatted exceptions in release and adds an integer to ZH's message storage.
class INIException
{
public:
	INIException(Int, const char *message, ...);
	INIException(const INIException &other);
	~INIException();

private:
	char *m_message;
	Int m_unreconstructed04;
};
#include "GameLogic/GameLogic.h"

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// GLOBAL /////////////////////////////////////////////////////////////////////////////////////////
Anim2DCollection *TheAnim2DCollection = NULL;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0Anim2DTemplate@@QAE@VAsciiString@@@Z
// Readable body in Code/GameEngine/Source/GameClient/System/Anim2DTemplate.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1Anim2DTemplate@@UAE@XZ
#pragma inline_depth(0)
Anim2DTemplate::~Anim2DTemplate( void )
{

	// delete the images
	if( m_images )
		delete [] m_images;

}  // end ~Anim2DTemplate
#pragma inline_depth(255)

// ------------------------------------------------------------------------------------------------
/** Field parse table for 2D animation templates */
// ---------i---------------------------------------------------------------------------------------
const FieldParse Anim2DTemplate::s_anim2DFieldParseTable[] = 
{

	{ "NumberImages",					Anim2DTemplate::parseNumImages,			NULL,							0 },
	{ "Image",								Anim2DTemplate::parseImage,					NULL,							0 },
	{ "ImageSequence",				Anim2DTemplate::parseImageSequence, NULL,							0 },
	{ "AnimationMode",				INI::parseIndexList,								Anim2DModeNames,	offsetof( Anim2DTemplate, m_animMode ) },
	{ "AnimationDelay",				INI::parseDurationUnsignedShort,		NULL,							offsetof( Anim2DTemplate, m_framesBetweenUpdates ) },
	{ "RandomizeStartFrame",	INI::parseBool,											NULL,							offsetof( Anim2DTemplate, m_randomizeStartFrame ) },
	{ NULL,										NULL,																NULL,							0 }

};

// ------------------------------------------------------------------------------------------------
/** Parse the number of images we will have in this animation and allocate the array for them */
// ------------------------------------------------------------------------------------------------
// ?parseNumImages@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z
// Readable body in Code/GameEngine/Source/GameClient/System/Anim2DTemplate.cpp.

// ------------------------------------------------------------------------------------------------
/** Allocate the image array for an animation template and store the number of frames we have */
// ------------------------------------------------------------------------------------------------
// ?allocateImages@Anim2DTemplate@@QAEXG@Z
void Anim2DTemplate::allocateImages( UnsignedShort numFrames )
{

	// store the number of frames
	m_numFrames = numFrames;

	// allocate an array to hold the image pointers
	m_images = NEW const Image *[ m_numFrames ];	// pool[]ify

	// set all the images to NULL;
	for( Int i = 0; i < m_numFrames; ++i )
		m_images[ i ] = NULL;

}  // end allocateImages

// ------------------------------------------------------------------------------------------------
/** Parsing a single image definition for an animation */
// ------------------------------------------------------------------------------------------------
void Anim2DTemplate::parseImage( INI *ini, void *instance, void *store, const void *userData )
{

	// parse the image name from the file and store as an image pointer
	const Image *image;
	ini->parseMappedImage( ini, instance, &image, userData );

	// sanity
	if( image == NULL )
	{

		//We don't care if we're in the builder
		//DEBUG_CRASH(( "Anim2DTemplate::parseImage - Image not found\n" ));
		//throw INI_INVALID_DATA;

	}  // end if

	//
	// assign the image to the animation template list of images ... note since we've pre-allocated
	// the array of images and the index an image is loaded into depends on its order specified
	// in INI, we need to get the number of images currently loaded into this animation template
	// so that we can put it at the next free image spot ... and then tell the animation 
	// template we've loaded one more
	//
	Anim2DTemplate *animTemplate = (Anim2DTemplate *)instance;
	animTemplate->storeImage( image );

}  // end parseImage

// ------------------------------------------------------------------------------------------------
/** This will parse the image sequence of an animation.  You can use this as a shortcut to
	* specifying a series of images for an animation instead of having to specify them all
	* individually.  Image names will be assumed to start with an appended "000" to the end
	* end of the first image name and incremented up to the number of images for the 
	* animation.  NOTE: That the number images *must* have already been specified before
	* we can parse this entry so we know how many images to allocate and look for */
// ------------------------------------------------------------------------------------------------
// ?parseImageSequence@Anim2DTemplate@@KAXPAVINI@@PAX1PBX@Z
void Anim2DTemplate::parseImageSequence( INI *ini, void *instance, void *store, const void *userData )
{

	const Image *image;
	Anim2DTemplate *animTemplate = (Anim2DTemplate *)instance;
	if( animTemplate->getNumFrames() == 0 )
		throw INIException( 3, "Anim2DTemplate::parseImageSequence - You must specify the number of animation frames for animation '%s' *BEFORE* specifying the image sequence name\n", animTemplate->m_name.str() );

	AsciiString imageBaseName = ini->getNextAsciiString();
	AsciiString imageName;
	for( Int i = 0; i < animTemplate->getNumFrames(); ++i )
	{
		imageName.format( "%s%03d", imageBaseName.str(), i );
		image = TheMappedImageCollection->findImageByName( imageName );
		if( image == NULL )
			throw INIException( 3, "Anim2DTemplate::parseImageSequence - Image '%s' not found for animation '%s'.  Check the number of images specified in INI and also make sure all the actual images exist.\n", imageName.str(), animTemplate->m_name.str() );

		animTemplate->storeImage( image );
	}

}  // end parseImageSequence

// ------------------------------------------------------------------------------------------------
/** Store the image at the next open image slot for the animation */
// ------------------------------------------------------------------------------------------------
// ?storeImage@Anim2DTemplate@@QAEXPBVImage@@@Z
// Readable body in Code/GameEngine/Source/GameClient/System/Anim2DTemplate.cpp.

// ------------------------------------------------------------------------------------------------
/** Return the Image* for the frame number requested */
// ------------------------------------------------------------------------------------------------
// ?getFrame@Anim2DTemplate@@QBEPBVImage@@G@Z
const Image* Anim2DTemplate::getFrame( UnsignedShort frameNumber ) const
{ 

	// sanity
	DEBUG_ASSERTCRASH( m_images != NULL, 
										 ("Anim2DTemplate::getFrame - Image data is NULL for animation '%s'\n",
										  getName().str()) );
	
	// sanity										
	if( frameNumber < 0 || frameNumber >= m_numFrames )
	{
		
		DEBUG_CRASH(( "Anim2DTemplate::getFrame - Illegal frame number '%d' for animation '%s'\n",
									frameNumber, getName().str() ));
		return NULL;

	}  // end if
	else
	{

		// return the image frame
		return m_images[ frameNumber ];

	}  // end else

}  // end getFrame

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0Anim2D@@QAE@PAVAnim2DTemplate@@PAVAnim2DCollection@@@Z
// Readable body in Code/GameEngine/Source/GameClient/System/Anim2DConstructor.cpp.

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1Anim2D@@MAE@XZ
Anim2D::~Anim2D( void )
{

	// if we were registered with a system, un-register ourselves
	if( m_collectionSystem )
		m_collectionSystem->unRegisterAnimation( this );

}  // end ~Anim2D

// ------------------------------------------------------------------------------------------------
/** Set the current animation frame */
// ------------------------------------------------------------------------------------------------
// Retail frame holder at 0xDFE77C slot 0x7C (slot1F) returns the current
// frame; DrawableFade (landed 0x2707A8/0x270756) and ScriptEngine_setFrame
// prove the global and slot. BFME1 donor uses TheGameClient->getFrame()
// (slot 0x68 in the ZH header), but BFME2 retail calls [eax+0x7C] here.
class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual int slot1F();
};

#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&g_anim2DGameClient)

void Anim2D::setCurrentFrame( UnsignedShort frame )
{

	// sanity
	DEBUG_ASSERTCRASH( m_template != NULL, ("Anim2D::reset - No template for animation\n") );

	// sanity
	DEBUG_ASSERTCRASH( TheGameLogic != NULL,	
										 ("Anim2D::setCurrentFrame - TheGameLogic must exist to use animation instances (%s)\n",
										  m_template->getName().str()) );

	// sanity
	DEBUG_ASSERTCRASH( frame >= 0 && frame < m_template->getNumFrames(),
										 ("Anim2D::setCurrentFrame - Illegal frame number '%d' in animation\n", 
										 frame, m_template->getName().str()) );

	// set the frame
	m_currentFrame = frame;

	// record the frame of this update to our current frame
	m_lastUpdateFrame = TheRva00DFE77C->slot1F();

}  // end setCurrentFrame

// ------------------------------------------------------------------------------------------------
/** Randomize the current frame */
// ------------------------------------------------------------------------------------------------
#line 424 "C:\\\\projects\\\\bfme2patch103\\\\bfme2\\\\Code\\\\GameEngine\\\\Source\\\\GameClient\\\\System\\\\Anim2D.cpp"
void Anim2D::randomizeCurrentFrame( void )
{

	// sanity
	DEBUG_ASSERTCRASH( m_template != NULL, ("Anim2D::reset - No template for animation\n") );

	// set the current frame to a random frame
	setCurrentFrame( GameClientRandomValue( 0, m_template->getNumFrames() - 1 ) );

}  // end randomizeCurrentFrame
#line 273

// ------------------------------------------------------------------------------------------------
/** Reset this animation instance to the "start" of the animation */
// ------------------------------------------------------------------------------------------------
void Anim2D::reset( void )
{

	// sanity
	DEBUG_ASSERTCRASH( m_template != NULL, ("Anim2D::reset - No template for animation\n") );

	switch( m_template->getAnimMode() )
	{

		// --------------------------------------------------------------------------------------------
		case ANIM_2D_ONCE:
		case ANIM_2D_LOOP:
		case ANIM_2D_PING_PONG:
			setCurrentFrame( m_minFrame );
			break;

		// --------------------------------------------------------------------------------------------
		case ANIM_2D_ONCE_BACKWARDS:
		case ANIM_2D_LOOP_BACKWARDS:
		case ANIM_2D_PING_PONG_BACKWARDS:
			setCurrentFrame( m_maxFrame );
			break;

		// --------------------------------------------------------------------------------------------
		default:
			DEBUG_CRASH(( "Anim2D::reset - Unknown animation mode '%d' for '%s'\n",
										m_template->getAnimMode(), m_template->getName().str() ));
			break;

	}  // end switch, animation mode

}  // end reset

// ------------------------------------------------------------------------------------------------
/** This is called after we are drawn ... if sufficient time has passed since our last
	* frame update we will update our current frame */
// ------------------------------------------------------------------------------------------------
void Anim2D::tryNextFrame( void )
{

	// sanity
	DEBUG_ASSERTCRASH( TheGameLogic != NULL,	
										 ("Anim2D::tryNextFrame - TheGameLogic must exist to use animation instances (%s)\n",
										  m_template->getName().str()) );

	// how many frames have passed since our last update
	// BFME2 reads the frame through the 0x00DFE77C holder's slot 0x7C (see
	// setCurrentFrame above); the ZH header's TheGameClient->getFrame() is
	// slot 0x68.
	if( TheRva00DFE77C->slot1F() - m_lastUpdateFrame >= m_framesBetweenUpdates )
	{

		switch( m_template->getAnimMode() )
		{

			// ------------------------------------------------------------------------------------------
			case ANIM_2D_ONCE:
			{

				if( m_currentFrame < m_maxFrame )
					setCurrentFrame( m_currentFrame + 1 );
				else
					setStatus( ANIM_2D_STATUS_COMPLETE );
				break;

			}  // end once

			// -------------------------------------------------------------------------------------------
			case ANIM_2D_ONCE_BACKWARDS:
			{

				if( m_currentFrame > m_minFrame )
					setCurrentFrame( m_currentFrame - 1 );
				else
					setStatus( ANIM_2D_STATUS_COMPLETE );
				break;

			}  // end once backwards

			// -------------------------------------------------------------------------------------------
			case ANIM_2D_LOOP:
			{

				if( m_currentFrame == m_maxFrame )
					setCurrentFrame( m_minFrame );
				else
					setCurrentFrame( m_currentFrame + 1 );
				break;

			}  // end loop

			// -------------------------------------------------------------------------------------------
			case ANIM_2D_LOOP_BACKWARDS:
			{

				if( m_currentFrame > m_minFrame )
					setCurrentFrame( m_currentFrame - 1 );
				else
					setCurrentFrame( m_maxFrame );
				break;
			
			}  // end loop backwards
				
			// -------------------------------------------------------------------------------------------
			case ANIM_2D_PING_PONG:
			case ANIM_2D_PING_PONG_BACKWARDS:
			{

				if( BitTest( m_status, ANIM_2D_STATUS_REVERSED ) )
				{
					//
					// decrement frame, unless we're at frame 0 in which case we
					// increment and reverse directions
					//
					if( m_currentFrame == m_minFrame )
					{

						setCurrentFrame( m_currentFrame + 1 );
						clearStatus( ANIM_2D_STATUS_REVERSED );

					}  // end if
					else
					{

						setCurrentFrame( m_currentFrame - 1 );

					}  // end else

				}  // end if
				else
				{

					//
					// increment frame, unless we're at the end in which case we decrement
					// and reverse directions
					//
					if( m_currentFrame == m_maxFrame )
					{

						setCurrentFrame( m_currentFrame - 1 );
						setStatus( ANIM_2D_STATUS_REVERSED );

					}  // end if
					else
					{

						setCurrentFrame( m_currentFrame + 1 );

					}  // end else

				}  // end else

				break;

			}  // end ping pong / ping pong backwards

			// -------------------------------------------------------------------------------------------
			default:
			{

				DEBUG_CRASH(( "Anim2D::tryNextFrame - Unknown animation mode '%d' for '%s'\n",
											m_template->getAnimMode(), m_template->getName().str() ));
				break;

			}  // end default
							
		}  // end switch

	}  // end if

}  // end tryNextFrame

// ------------------------------------------------------------------------------------------------
/** Set status bit */
// ------------------------------------------------------------------------------------------------
void Anim2D::setStatus( UnsignedByte statusBits )
{

	// set the bits
	BitSet( m_status, statusBits );

}  // end setStatus

// ------------------------------------------------------------------------------------------------
/** Clear status bit */
// ------------------------------------------------------------------------------------------------
void Anim2D::clearStatus( UnsignedByte statusBits )
{

	// clear bits
	BitClear( m_status, statusBits );

}  // end clearStatus

// ------------------------------------------------------------------------------------------------
/** Return the "natural" width of the image for our current frame */
// ------------------------------------------------------------------------------------------------
// Anim2D::getCurrentFrameWidth: defined in Anim2DCurrentFrameWidth.cpp (its row's unit).
  // end getCurrentFrameWidth

// ------------------------------------------------------------------------------------------------
/** Return the "natural" height of the image for our current frame */
// ------------------------------------------------------------------------------------------------
// ?getCurrentFrameHeight@Anim2D@@QBEIXZ
// Readable body in Code/GameEngine/Source/GameClient/System/Anim2DCurrentFrameHeight.cpp.

class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

// ------------------------------------------------------------------------------------------------
/** Drawing an Anim2D using a forced width and height */
// ------------------------------------------------------------------------------------------------
// ?draw@Anim2D@@QAEXHHHH@Z, retail 0x002D709A, 141 bytes. Evidence: Anim2D offsets
// (+4 frame +0xC template +0x10 status +0x1C alpha +0x20 collection), rowed
// getFrame 0x002D6B2D, rowed W3DDisplay::rva0004D6B3 0x0004D6B3 via TheDisplay
// 0x00DFE9D8, rowed tryNextFrame 0x002D6E26.
void Anim2D::draw( Int x, Int y )
{

	// get the current image
	const Image *image = m_template->getFrame( m_currentFrame );

	// sanity
	DEBUG_ASSERTCRASH( image != NULL, ("Anim2D::draw - Image not found for frame '%d' on animation '%s'\n",
										 m_currentFrame, m_template->getName().str()) );

	// get the natural width and height of this image
	const ICoord2D *imageSize = image->getImageSize();

	// draw the image
	Color color = GameMakeColor( 255, 255, 255, 255 * m_alpha );
	((W3DDisplay *)TheDisplay)->rva0004D6B3( (Image *)image, (float)x, (float)y, (float)( x + imageSize->x ), (float)( y + imageSize->y ), color, 2 );

	//
	// see if it's time for us to go to the next frame in the sequence, we do not update
	// frame numbers for animation instances that are registered with a system as the
	// system will update them during its update phase
	//
 	if( m_collectionSystem == NULL && BitTest( m_status, ANIM_2D_STATUS_FROZEN ) == FALSE )
		tryNextFrame();

}  // end draw

// ------------------------------------------------------------------------------------------------
/** Drawing an Anim2D using a forced width and height */
// ------------------------------------------------------------------------------------------------
void Anim2D::draw( Int x, Int y, Int width, Int height )
{

	// get the current image
	const Image *image = m_template->getFrame( m_currentFrame );
	
	// sanity
	DEBUG_ASSERTCRASH( image != NULL, ("Anim2D::draw - Image not found for frame '%d' on animation '%s'\n",
										 m_currentFrame, m_template->getName().str()) );


	// draw image to the display
	Color color = GameMakeColor( 255, 255, 255, 255 * m_alpha );
	((W3DDisplay *)TheDisplay)->rva0004D6B3( (Image *)image, (float)x, (float)y, (float)( x + width ), (float)( y + height ), color, 2 );

	//
	// see if it's time for us to go to the next frame in the sequence, we do not update
	// frame numbers for animation instances that are registered with a system as the
	// system will update them during its update phase
	//
 	if( m_collectionSystem == NULL && BitTest( m_status, ANIM_2D_STATUS_FROZEN ) == FALSE )
		tryNextFrame();

}  // end draw

// ------------------------------------------------------------------------------------------------
/** Xfer Method
	* Version Info:
	* 1: Initial version */
// ------------------------------------------------------------------------------------------------
// byte-exact reconstruction: Code/GameEngine/Source/GameClient/System/Anim2DXfer.cpp

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??0Anim2DCollection@@QAE@XZ present-unmatched
Anim2DCollection::Anim2DCollection( void )
{

	m_templateList = NULL;
	m_instanceList = NULL;
}  // end Anim2DCollection

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ??1Anim2DCollection@@UAE@XZ present-unmatched
Anim2DCollection::~Anim2DCollection( void )
{

	// there should not be any animation instances registered with us since we're being destroyed
	DEBUG_ASSERTCRASH( m_instanceList == NULL, ("Anim2DCollection - instance list is not NULL\n") );

	// delete all the templates
	Anim2DTemplate *nextTemplate;
	while( m_templateList )
	{

		// get next template
		nextTemplate = m_templateList->friend_getNextTemplate();

		// delete this template
		delete m_templateList;  // BFME: no memory pool for Anim2DTemplate

		// set the head of our list to the next template
		m_templateList = nextTemplate;

	}  // end while

}  // end ~Anim2DCollection

// ------------------------------------------------------------------------------------------------
/** Initialize 2D animation collection */
// ------------------------------------------------------------------------------------------------
// ?init@Anim2DCollection@@UAEXXZ present-unmatched
void Anim2DCollection::init( void )
{
	INI ini;

	ini.load( "Data\\INI\\Animation2D.ini", INI_LOAD_OVERWRITE, NULL );

}  // end init

// ------------------------------------------------------------------------------------------------
/** System update phase */
// ------------------------------------------------------------------------------------------------
// BFME 2 keeps the instance list at +0x10 (see registerAnimation); retail
// 0x002D7267, reached only from the collection's vtable.
void Anim2DCollection::update( void )
{
	Anim2D *anim;

	// go through all our animations
	for( anim = *(Anim2D **)((unsigned char *)this + 0x10); anim; anim = anim->m_collectionSystemNext )
	{

		// try to update the frame
		if( BitTest( anim->getStatus(), ANIM_2D_STATUS_FROZEN ) == FALSE )	
			anim->tryNextFrame();

	}  // end for, anim

}  // end update

// ------------------------------------------------------------------------------------------------
/** Search the template list for a template with a matching name */
// ------------------------------------------------------------------------------------------------
// ?findTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
// Readable body in Code/GameEngine/Source/GameClient/System/Anim2DCollectionTemplates.cpp.

//-------------------------------------------------------------------------------------------------
// ?getNextTemplate@Anim2DCollection@@QBEPAVAnim2DTemplate@@PAV2@@Z
Anim2DTemplate* Anim2DCollection::getNextTemplate( Anim2DTemplate *animTemplate ) const
{
	if( animTemplate )
	{
		return animTemplate->friend_getNextTemplate();
	}
	return NULL;
}

// ------------------------------------------------------------------------------------------------
/** Allocate a new template, assign name, and link to our internal list */
// ------------------------------------------------------------------------------------------------
// newTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
// Readable body in Code/GameEngine/Source/GameClient/System/Anim2DCollectionTemplates.cpp.

// ------------------------------------------------------------------------------------------------
/** Register animation instance with us.  When an animation instance is registered it can
	* be updated even when it's not drawn */
// ------------------------------------------------------------------------------------------------
void Anim2DCollection::registerAnimation( Anim2D *anim )
{

	// sanity
	if( anim == NULL )
		return;

	// sanity
	DEBUG_ASSERTCRASH( anim->m_collectionSystemNext == NULL &&
										 anim->m_collectionSystemPrev == NULL,
										 ("Registering animation instance, instance '%s' is already in a system\n",
										 anim->getAnimTemplate()->getName().str()) );

	// tie to our list (retail head at +0x10; cf. unRegisterAnimation below)
	anim->m_collectionSystemPrev = NULL;
	anim->m_collectionSystemNext = *(Anim2D **)((unsigned char *)this + 0x10);
	if( *(Anim2D **)((unsigned char *)this + 0x10) )
		(*(Anim2D **)((unsigned char *)this + 0x10))->m_collectionSystemPrev = anim;
	*(Anim2D **)((unsigned char *)this + 0x10) = anim;

}  // end registerAnimation

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
void Anim2DCollection::unRegisterAnimation( Anim2D *anim )
{

	// sanity
	if( anim == NULL )
		return;

	// if animation is not registered with us do nothing
	if( anim->m_collectionSystem != this )
		return;

	// unlink from our instnace list
	if( anim->m_collectionSystemNext )
		anim->m_collectionSystemNext->m_collectionSystemPrev = anim->m_collectionSystemPrev;
	if( anim->m_collectionSystemPrev )
		anim->m_collectionSystemPrev->m_collectionSystemNext = anim->m_collectionSystemNext;
	else
		*(Anim2D **)((unsigned char *)this + 0x10) = anim->m_collectionSystemNext;

}  // end unRegisterAnimation

class DisplayVirt002D7127
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void beginImageDraw();
	virtual void slotD8(float x0, float y0, float x1, float y1, float w, int color0, int color1);
	virtual void slotDC(float x0, float y0, float x1, float y1, float w, int color);
	virtual void slotE0(float x0, float y0, float x1, float y1, float w, int color);
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void drawImageCore(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
	virtual void unused63();
	virtual void endImageDraw();
};

// ------------------------------------------------------------------------------------------------
/** Drawing an Anim2D using a forced width and height, additive blend (mode 3) via virtual core */
// ------------------------------------------------------------------------------------------------
// ?rva002D7127@Rva002D7127@@QAEXHHHH@Z @0x002D7127 150B via BFME1 Anim2DDrawing donor plus virtual Display 0xF8 core with mode 3. Evidence: Anim2D offsets +4 frame +0xC template +0x10 status +0x1C alpha +0x20 collection same as rowed draw 0x002D709A, rowed getFrame 0x002D6B2D, TheDisplay 0x00DFE9D8 slot 0xF8 drawImageCore, rowed tryNextFrame 0x002D6E26.
class Rva002D7127 : public Anim2D
{
public:
	void rva002D7127(Int x, Int y, Int width, Int height);
	void rva002D6FFF(Int x, Int y);
	void rva002D6F80(Real x, Real y, UnsignedByte opacity);

	// BFME 2 grows Anim2D by a draw size the real-coordinate draw reads.
	Int m_drawWidth;	///< 0x2C
	Int m_drawHeight;	///< 0x30
};

void Rva002D7127::rva002D7127(Int x, Int y, Int width, Int height)
{

	// get the current image
	const Image *image = m_template->getFrame(m_currentFrame);

	// sanity
	DEBUG_ASSERTCRASH(image != NULL, ("Anim2D::draw - Image not found for frame '%d' on animation '%s'\n",
		m_currentFrame, m_template->getName().str()));

	// draw image to the display
	Color color = GameMakeColor(255, 255, 255, 255 * m_alpha);
	((DisplayVirt002D7127 *)TheDisplay)->drawImageCore((Image *)image, (float)x, (float)y, (float)(x + width), (float)(y + height), color, 3);

	//
	// see if it's time for us to go to the next frame in the sequence, we do not update
	// frame numbers for animation instances that are registered with a system as the
	// system will update them during its update phase
	//
	if (m_collectionSystem == NULL && BitTest(m_status, ANIM_2D_STATUS_FROZEN) == FALSE)
		tryNextFrame();

}  // end rva002D7127

// ?rva002D6FFF@Rva002D7127@@QAEXHH@Z @0x002D6FFF 155B: the natural-size
// sibling of rva002D7127. Same body as Anim2D::draw(x, y) (0x002D6EF1, the
// image's own width and height at Image +0x24/+0x28) but straight into the
// virtual Display slot 0xF8 core with mode 2, without the non-virtual
// Display::drawImage wrapper (0x0004D6B3) that brackets the core between
// slots 0xD4 and 0x100. No code or data reference reaches it.
void Rva002D7127::rva002D6FFF(Int x, Int y)
{

	// get the current image
	const Image *image = m_template->getFrame(m_currentFrame);

	// sanity
	DEBUG_ASSERTCRASH(image != NULL, ("Anim2D::draw - Image not found for frame '%d' on animation '%s'\n",
		m_currentFrame, m_template->getName().str()));

	// get the natural width and height of this image
	const ICoord2D *imageSize = image->getImageSize();

	// draw image to the display
	Color color = GameMakeColor(255, 255, 255, 255 * m_alpha);
	((DisplayVirt002D7127 *)TheDisplay)->drawImageCore((Image *)image, (float)x, (float)y, (float)(x + imageSize->x), (float)(y + imageSize->y), color, 2);

	if (m_collectionSystem == NULL && BitTest(m_status, ANIM_2D_STATUS_FROZEN) == FALSE)
		tryNextFrame();

}  // end rva002D6FFF

// ?rva002D6F80@Rva002D7127@@QAEXMME@Z @0x002D6F80 127B: BFME's real-coordinate
// draw with an explicit opacity byte (BFME1 Anim2DRealCoordinateDrawing.cpp's
// Rva005BA910Anim2D::draw is the same shape): the opacity fills all four
// colour channels, the size comes from Anim2D +0x2C/+0x30, and the image goes
// through the non-virtual Display::drawImage wrapper (0x0004D6B3) with mode 3.
// Called from 0x002A4BC2.
void Rva002D7127::rva002D6F80(Real x, Real y, UnsignedByte opacity)
{
	Color color = GameMakeColor( opacity, opacity, opacity, opacity );
	((W3DDisplay *)TheDisplay)->rva0004D6B3( (Image *)m_template->getFrame( m_currentFrame ), x, y, x + m_drawWidth, y + m_drawHeight, color, 3 );

	if (m_collectionSystem == NULL && BitTest(m_status, ANIM_2D_STATUS_FROZEN) == FALSE)
		tryNextFrame();

}  // end rva002D6F80
