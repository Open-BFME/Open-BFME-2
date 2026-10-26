// cl: /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /O1 /DNDEBUG /MD /EHsc /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// Use the native 17-byte specialization at RVA 0x00013740 rather than
// emitting a separately optimized copy from this unit.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include <map>
#include <hash_map>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

#include <cstddef>
// Keep const bucket access visible so _M_find caches the key across the
// bucket lookup, as the47-byte retail body at2888D4 does.
namespace _STL {
template <> __declspec(dllimport) __forceinline vector<void *>::const_iterator _STL::vector<void *>::begin() const { return this->_M_start; }
}

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}
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
// display.h (shim bfme_windowvideo) declares TheDisplay as its private DisplayInterface
// view; spell that declaration aside and bind the one global, ?TheDisplay@@3PAVDisplay@@A.
#define TheDisplay TheDisplay_displayInterfaceView
#include "display.h"
// Keep allocator and bucket construction visible: opaque declarations here
// make VC7 reload the temporary bucket storage and change native resize53F1EC.
// Its stateless swap and cleanup follow the established FXListStoreParse view.
// bfme link decl-only begin
namespace _STL { template <> __declspec(dllimport) __forceinline void swap<void **>(void **&a, void **&b) { void **tmp=a; a=b; b=tmp; }
template <> inline void swap(_STLP_alloc_proxy<void **, void *, allocator<void *> > &a, _STLP_alloc_proxy<void **, void *, allocator<void *> > &b) { swap(a._M_data,b._M_data); } }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base() { if (_M_start) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); } }
namespace _STL { template <> __forceinline vector<void *, allocator<void *> >::~vector() { _Destroy(this->_M_start, this->_M_finish); } }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Hashtable_node@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class GameWindow; class WindowVideo;
namespace _STL { template <> void allocator<_Hashtable_node<pair<GameWindow const * const,WindowVideo *> > >::deallocate(_Hashtable_node<pair<GameWindow const * const,WindowVideo *> > *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
// Inline-only const bucket access; the native lookup has no accessor call.
namespace _STL { template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t n) const { return *(this->_M_start+n); } }
#undef TheDisplay
class Display;
extern Display *TheDisplay;

//-----------------------------------------------------------------------------
// DEFINES ////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// WindowVideo PUBLIC FUNCTIONS ///////////////////////////////////////////////
//-----------------------------------------------------------------------------
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
	if ( !videoStream->attach( ((DisplayInterface *)TheDisplay)->createVideoBuffer( false ) ) )
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
