// cl: /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Use the native 17-byte specialization at RVA 0x00013740 rather than
// emitting a separately optimized copy from this unit.
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include <map>
#include <hash_map>
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

// FILE: WindowVideoManager.cpp /////////////////////////////////////////////////
//-----------------------------------------------------------------------------
//                                                                          
//                       Electronic Arts Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2002 - All Rights Reserved                  
//                                                                          
//-----------------------------------------------------------------------------
//
//	created:	Apr 2002
//
//	Filename: 	WindowVideoManager.cpp
//
//	author:		Chris Huybregts
//	
//	purpose:	Every window is setup to be able to draw a movie.  The 
//						WindowVideoManager will take care of setting up the window,
//						creating/destroying the buffers, and the ability to pause/stop
//						movies.
//
//	To Use:		Create a manager and initialize it. Make sure the manager's Update
//						is called every frame or how ever often it needs to be updated.
//						Call reset if the manager needs to be cleared.
//						Play a movie in a window by passing a window pointer, a movie name,
//						and the playtype.
//						If a user trys to play a two different movies on the same window,
//						only the last one added will play.
//						It's important when destroying a window, that window is removed
//						from the manager (Or call Reset if you know no other windows are
//						playing a movie).
//
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// SYSTEM INCLUDES ////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// USER INCLUDES //////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
#include "prerts.h"
#include "ascii_string.h"
#include "subsystem_interface.h"	// This must go first in EVERY cpp file int the GameEngine

#include "window_video_manager.h"
#include "game_window.h"
#include "video_player.h"
#include "display.h"

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// WindowVideo PUBLIC FUNCTIONS ///////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ?WindowVideo::WindowVideo present-unmatched
WindowVideo::WindowVideo( void )
{
	
	m_playType = WINDOW_PLAY_MOVIE_ONCE;
	m_win = NULL;
	m_videoStream = NULL;
	// BFME2 retail (0x53F0F3) calls releaseBuffer 0x36410 directly (clear() inlined), which is the
	// address the AsciiString teardown folds to; the StringBase::clear thunk (0x48BA39) is not used here.
	m_movieName.~AsciiString();
	m_state = WINDOW_VIDEO_STATE_STOP;

}

// ?WindowVideo::~WindowVideo present-unmatched
WindowVideo::~WindowVideo( void )
{
	// Don't Delete the window, only set it's video buffer to NULL
	if(m_win)
		m_win->winGetInstanceData()->setVideoBuffer( NULL );
	m_win = NULL;

	if ( m_videoStream )
		m_videoStream->close();
	m_videoStream = NULL;

}
	
// ?WindowVideo::init present-unmatched
void WindowVideo::init( GameWindow *win, AsciiString movieName, 
												WindowVideoPlayType playType,
												VideoStreamInterface *videoStream)
{
	m_win = win;
	m_movieName = movieName;
	m_playType = playType;
	m_videoStream = videoStream;
	m_state = WINDOW_VIDEO_STATE_PLAY;
	if(m_win)
		m_win->winGetInstanceData()->setVideoBuffer( m_videoStream->getVideoBuffer() );
}

// BFME2: the stream owns its buffer (vtable +0x3C); out-of-line at 0x53F0BF
VideoBuffer *WindowVideo::getVideoBuffer( void )
{
	if ( m_videoStream )
		return m_videoStream->getVideoBuffer();
	return NULL;
}
	
// ?WindowVideo::setWindowState present-unmatched
void WindowVideo::setWindowState( WindowVideoStates state )
{ 
	m_state = state; 

	if(m_state == WINDOW_VIDEO_STATE_STOP && m_win)
		m_win->winGetInstanceData()->setVideoBuffer( NULL );

	if((m_state == WINDOW_VIDEO_STATE_PLAY || m_state == WINDOW_VIDEO_STATE_PAUSE )&& m_win)
		m_win->winGetInstanceData()->setVideoBuffer( m_videoStream->getVideoBuffer() );
}	

//-----------------------------------------------------------------------------
// WindowVideoManager PUBLIC FUNCTIONS ////////////////////////////////////////
//-----------------------------------------------------------------------------
// ?WindowVideoManager::WindowVideoManager present-unmatched
WindowVideoManager::WindowVideoManager( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			delete winVid;
		it++;
	}
	m_playingVideos.clear();
	
	m_stopAllMovies = FALSE;
	m_pauseAllMovies = FALSE;

}

// ?WindowVideoManager::~WindowVideoManager present-unmatched
WindowVideoManager::~WindowVideoManager( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			delete winVid;
		it++;
	}
	m_playingVideos.clear();
	
}

	
void WindowVideoManager::init( void )
{
	m_playingVideos.clear();
	
	m_stopAllMovies = FALSE;
	m_pauseAllMovies = FALSE;
}

void WindowVideoManager::reset( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			delete winVid;
		it++;
	}
	m_playingVideos.clear();
	
	m_stopAllMovies = FALSE;
	m_pauseAllMovies = FALSE;
}

// ?WindowVideoManager::update present-unmatched
void WindowVideoManager::update( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();

	if(m_pauseAllMovies || m_stopAllMovies)
		return;

	//Iterate through the maps
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		
		if(!winVid)
		{
			DEBUG_CRASH(("There's No WindowVideo in the m_playignVideos list"));
			return;
		}
		GameWindow *win = winVid->getWin();

		if(winVid->getState() == WINDOW_VIDEO_STATE_HIDDEN && (win->winIsHidden() == FALSE))
		{
			resumeMovie(win);
		}

		if(winVid->getState() == WINDOW_VIDEO_STATE_PLAY && win->winIsHidden())
		{
			hideMovie(win);
		}

		// Only advance the frame if we're playing
		if(winVid->getState() != WINDOW_VIDEO_STATE_PLAY)
		{
			it++;
			continue;
		}

		// Get the Stream and the buffer to update for each animation
		VideoStreamInterface *videoStream = winVid->getVideoStream();
		VideoBuffer *videoBuffer = winVid->getVideoBuffer();
		
		if ( videoStream && videoBuffer )
		{
			// BFME2: the stream advances itself (vtable +0x18); looping streams pass the loop flag,
			// the others report a finished frame in bit 0 and are paused or stopped at frame 0.
			switch(winVid->getPlayType())
			{
				case WINDOW_PLAY_MOVIE_LOOP:
					videoStream->frameUpdate( 4 );
					break;
				case WINDOW_PLAY_MOVIE_SHOW_LAST_FRAME:
					if ( (videoStream->frameUpdate( 0 ) & 1) && videoStream->frameIndex() == 0 )
						pauseMovie(win);
					break;
				default:
					if ( (videoStream->frameUpdate( 0 ) & 1) && videoStream->frameIndex() == 0 )
						stopMovie(win);
					break;
			}
		}
		
		it++;
	}
}

// ?WindowVideoManager::playMovie present-unmatched
void WindowVideoManager::playMovie( GameWindow *win, AsciiString movieName, WindowVideoPlayType playType )
{
	// if we already have a movie playing for that window, kill it.
	stopAndRemoveMovie( win );
	
	// create the new stream
	VideoStreamInterface *videoStream = TheVideoPlayer->open( movieName, 0 );
	if ( videoStream == NULL )
	{
		return;
	}

	// BFME2: the stream takes ownership of a display-created buffer (vtable +0x38)
	if ( !videoStream->attach( TheDisplay->createVideoBuffer( false ) ) )
	{
		videoStream->close();
		return;
	}

	// now that we have everything, create the new WindowVideo Structure
	WindowVideo *winVid = NEW WindowVideo;
	
	// init it.
	winVid->init( win, movieName,playType,videoStream);

	// add it to our map.
	m_playingVideos[win] = winVid;

	m_pauseAllMovies = FALSE;
	m_stopAllMovies = FALSE;
}


// ?WindowVideoManager::pauseMovie present-unmatched
void WindowVideoManager::pauseMovie( GameWindow *win )
{
	WindowVideoMap::iterator it = m_playingVideos.find(win);
	if(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
		winVid->setWindowState(WINDOW_VIDEO_STATE_PAUSE);
	}
	
}
// ?hideMovie@WindowVideoManager@@QAEXPAVGameWindow@@@Z
// Open-BFME5: map lookup + direct state store at +0x10 (BFME WindowVideo layout).
void WindowVideoManager::hideMovie( GameWindow *win )
{
	WindowVideoMap::iterator it = m_playingVideos.find(win);
	if(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			winVid->setWindowState(WINDOW_VIDEO_STATE_HIDDEN);
	}
}

// ?WindowVideoManager::resumeMovie present-unmatched
void WindowVideoManager::resumeMovie( GameWindow *win )
{
	WindowVideoMap::iterator it = m_playingVideos.find(win);
	if(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			winVid->setWindowState(WINDOW_VIDEO_STATE_PLAY);
	}
	m_pauseAllMovies = FALSE;
	m_stopAllMovies = FALSE;
}

// ?WindowVideoManager::stopMovie present-unmatched
void WindowVideoManager::stopMovie( GameWindow *win )
{
	WindowVideoMap::iterator it = m_playingVideos.find(win);
	if(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			winVid->setWindowState(WINDOW_VIDEO_STATE_STOP);
	}
}

void WindowVideoManager::stopAndRemoveMovie( GameWindow *win )
{
	WindowVideoMap::iterator it = m_playingVideos.find(win);
	if(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			delete winVid;
		winVid = NULL;
		m_playingVideos.erase(it);
	}
}

// ?WindowVideoManager::stopAllMovies present-unmatched
void WindowVideoManager::stopAllMovies( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	//Iterate through the maps
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			winVid->setWindowState(WINDOW_VIDEO_STATE_STOP);
		it++;
	}
	
	m_stopAllMovies = TRUE;
	m_pauseAllMovies = FALSE;
}

// ?WindowVideoManager::pauseAllMovies present-unmatched
void WindowVideoManager::pauseAllMovies( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	//Iterate through the maps
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			winVid->setWindowState(WINDOW_VIDEO_STATE_PAUSE);
		it++;
	}
	
	m_pauseAllMovies = TRUE;
	m_stopAllMovies = FALSE;
}

// ?WindowVideoManager::resumeAllMovies present-unmatched
void WindowVideoManager::resumeAllMovies( void )
{
	WindowVideoMap::iterator it = m_playingVideos.begin();
	//Iterate through the maps
	while(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			winVid->setWindowState(WINDOW_VIDEO_STATE_PLAY);
		it++;
	}
	m_stopAllMovies = FALSE;
	m_pauseAllMovies = FALSE;
}

// ?WindowVideoManager::getWinState present-unmatched
Int WindowVideoManager::getWinState( GameWindow *win )
{
	WindowVideoMap::iterator it = m_playingVideos.find(win);
	if(it != m_playingVideos.end())
	{
		WindowVideo *winVid = it->second;
		if(winVid)
			return winVid->getState();
	}
	return WINDOW_VIDEO_STATE_STOP;
}

//-----------------------------------------------------------------------------
// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------
// ?TheDisplay@@3PAVDisplayInterface@@A: the global at VA 0xdfe9d8 is ?TheDisplay@@3PAVDisplay@@A.
#pragma comment(linker, "/alternatename:?TheDisplay@@3PAVDisplayInterface@@A=?TheDisplay@@3PAVDisplay@@A")

// Callers elsewhere reach this body through a spelling pinned to the same retail
// address with the same calling convention; bind it here.
#pragma comment(linker, "/alternatename:?first@Rva000427195@@QAEPAXPAVRva000411084@@@Z=?begin@?$hashtable@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAE?AU?$_Ht_iterator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@U?$_Nonconst_traits@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@2@XZ")
