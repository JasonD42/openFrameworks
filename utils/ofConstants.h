#ifndef OF_CONSTANTS
#define OF_CONSTANTS



//-------------------------------
#define OF_VERSION	6
//-------------------------------


//-------------------------------
//  find the system type --------
//-------------------------------

// 		helpful:
// 		http://www.ogre3d.org/docs/api/html/OgrePlatform_8h-source.html

#if defined( __WIN32__ ) || defined( _WIN32 )
	#define TARGET_WIN32
#elif defined( __APPLE_CC__)
	#define TARGET_OSX
#else
	#define TARGET_LINUX
#endif
//-------------------------------


// then the the platform specific includes:
#ifdef TARGET_WIN32
	//this is for TryEnterCriticalSection
	//http://www.zeroc.com/forums/help-center/351-ice-1-2-tryentercriticalsection-problem.html
	#ifndef _WIN32_WINNT
		#   define _WIN32_WINNT 0x400
	#endif
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include "GLee.h"
	#define GLUT_BUILDING_LIB
	#include "glut.h"
	#define __WINDOWS_DS__
	#define __WINDOWS_MM__
	#if (_MSC_VER)       // microsoft visual studio
		#pragma warning(disable : 4996)     // disable all deprecation warnings
		#pragma warning(disable : 4068)     // unknown pragmas
		#pragma warning(disable : 4101)     // unreferenced local variable
		#pragma	warning(disable : 4312)		// type cast conversion (in qt vp)
		#pragma warning(disable : 4311)		// type cast pointer truncation (qt vp)
		#pragma warning(disable : 4018)		// signed/unsigned mismatch (since vector.size() is a size_t)
		#pragma warning(disable : 4267)		// conversion from size_t to Size warning... possible loss of data
	#endif

	#define TARGET_LITTLE_ENDIAN			// intel cpu

	// some gl.h files, like dev-c++, are old - this is pretty universal
	#ifndef GL_BGR_EXT
	#define GL_BGR_EXT 0x80E0
	#endif

	// #define WIN32_HIGH_RES_TIMING

	// note: this is experimental!
	// uncomment to turn this on (only for windows machines)
	// if you want to try setting the timer to be high resolution
	// this could make camera grabbing and other low level
	// operations quicker, but you must quit the app normally,
	// ie, using "esc", rather than killing the process or closing
	// the console window in order to set the timer resolution back
	// to normal (since the high res timer might give the OS
	// problems)
	// info: http://www.geisswerks.com/ryan/FAQS/timing.html

#endif

#ifdef TARGET_OSX
	#ifndef __MACOSX_CORE__
		#define __MACOSX_CORE__
	#endif
	#include <unistd.h>
	#include "GLee.h"
	#include <GLUT/glut.h>
	#include <ApplicationServices/ApplicationServices.h>

	#if defined(__LITTLE_ENDIAN__)
		#define TARGET_LITTLE_ENDIAN		// intel cpu
	#endif
#endif

#ifdef TARGET_LINUX
        #include <unistd.h>
        #include "GLee.h"
        #include <GL/glut.h>

    // for some reason, this isn't defined at compile time,
    // so this hack let's us work
    // for 99% of the linux folks that are on intel
    // everyone one else will have RGB / BGR issues.
	//#if defined(__LITTLE_ENDIAN__)
		#define TARGET_LITTLE_ENDIAN		// intel cpu
	//#endif

        // some things for serial compilation:
        #define B14400	14400
        #define B28800	28800


#endif

#ifndef __MWERKS__
#define OF_EXIT_APP(val)		exit(val);
#else
#define OF_EXIT_APP(val)		std::exit(val);
#endif




//------------------------------------------------ capture
// if are linux

#ifdef TARGET_LINUX


	// some cameras don't seem to work in unicap, so we keep
	// V4l code here.  comment out this next line, to switch to the older
	// V4l code...

	// (if you change this, you might need to clean and rebuild, in CB build->rebuild)

	#define OF_SWITCH_TO_UNICAP_FOR_LINUX_VIDCAP



	#ifdef OF_SWITCH_TO_UNICAP_FOR_LINUX_VIDCAP
		#define OF_VIDEO_CAPTURE_UNICAP
    #else
		#define OF_VIDEO_CAPTURE_V4L
	#endif



#else

    // non - linux, pc or osx

    // comment out this following line, if you'd like to use the
    // quicktime capture interface on windows
    // if not, we default to videoInput library for
    // direct show capture...

    #define OF_SWITCH_TO_DSHOW_FOR_WIN_VIDCAP

    #ifdef OF_SWITCH_TO_DSHOW_FOR_WIN_VIDCAP
        #ifdef TARGET_OSX
            #define OF_VIDEO_CAPTURE_QUICKTIME
        #else
            #define OF_VIDEO_CAPTURE_DIRECTSHOW
        #endif
    #else
        // all quicktime, all the time
        #define OF_VIDEO_CAPTURE_QUICKTIME
    #endif
#endif


#ifdef TARGET_LINUX
	#define OF_VIDEO_PLAYER_FOBS
#else
	#define OF_VIDEO_PLAYER_QUICKTIME
#endif

// comment out this line to disable all poco related code
#define OF_USING_POCO

//we don't want to break old code that uses ofSimpleApp
//so we forward declare ofBaseApp and make ofSimpleApp mean the same thing
class ofBaseApp;
typedef ofBaseApp ofSimpleApp;

enum ofLogLevel{
	OF_VERBOSE,
	OF_NOTICE,
	OF_WARNING,
	OF_ERROR,
	OF_FATAL_ERROR,
	OF_SILENT	//this one is special and should always be last - set ofSetLogLevel to OF_SILENT to not recieve any messages
};

#define OF_DEFAULT_LOG_LEVEL  OF_WARNING;

// serial error codes
#define OF_SERIAL_NO_DATA 	 0
#define OF_SERIAL_ERROR		-1

// core: ---------------------------
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>  //for ostringsream
#include <iomanip>  //for setprecision
using namespace std;

#ifndef PI
	#define PI       3.14159265358979323846
#endif

#ifndef TWO_PI
	#define TWO_PI   6.28318530717958647693
#endif

#ifndef M_TWO_PI
	#define M_TWO_PI   6.28318530717958647693
#endif

#ifndef FOUR_PI
	#define FOUR_PI 12.56637061435917295385
#endif

#ifndef HALF_PI
	#define HALF_PI  1.57079632679489661923
#endif

#ifndef DEG_TO_RAD
	#define DEG_TO_RAD (PI/180.0)
#endif

#ifndef RAD_TO_DEG
	#define RAD_TO_DEG (180.0/PI)
#endif

#ifndef MIN
	#define MIN(x,y) (((x) < (y)) ? (x) : (y))
#endif

#ifndef MAX
	#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

#ifndef CLAMP
	#define CLAMP(val,min,max) (MAX(MIN(val,max),min))
#endif

#ifndef ABS
	#define ABS(x) (((x) < 0) ? -(x) : (x))
#endif

#define 	OF_FILLED				0x01
#define 	OF_OUTLINE				0x02
#define 	OF_WINDOW 				0
#define 	OF_FULLSCREEN 			1
#define 	OF_GAME_MODE			2

#define 	OF_RECTMODE_CORNER				0
#define 	OF_RECTMODE_CENTER				1

#define 	OF_IMAGE_GRAYSCALE		0x00
#define 	OF_IMAGE_COLOR			0x01
#define 	OF_IMAGE_COLOR_ALPHA	0x02
#define 	OF_IMAGE_UNDEFINED		0x03

#define		OF_MAX_STYLE_HISTORY	32
#define		OF_MAX_CIRCLE_PTS 1024

// these are straight out of glu, but renamed and included here
// for convenience
//
// we don't mean to wrap the whole glu library (or any other library for that matter)
// but these defines are useful to give people flexability over the polygonizer
//
// some info:
// http://glprogramming.com/red/images/Image128.gif
//
// also: http://glprogramming.com/red/chapter11.html
// (CSG ideas)

#define 	OF_POLY_WINDING_ODD 	          100130
#define 	OF_POLY_WINDING_NONZERO           100131
#define 	OF_POLY_WINDING_POSITIVE          100132
#define 	OF_POLY_WINDING_NEGATIVE          100133
#define		OF_POLY_WINDING_ABS_GEQ_TWO       100134

#define 	OF_CLOSE						  (true)


//--------------------------------------------
//
// 	Keyboard definitions
//
// 	ok -- why this?
// 	glut key commands have some annoying features,
// 	in that some normal keys have the same value as special keys,
// 	but we want ONE key routine, so we need to redefine several,
// 	so that we get some normalacy across keys routines
//
// 	(everything that comes through "glutSpecialKeyFunc" will get 256 added to it,
// 	to avoid conflicts, before, values like "left, right up down" (ie, 104, 105, 106) were conflicting with
// 	letters.. now they will be 256 + 104, 256 + 105....)


#define OF_KEY_MODIFIER 	0x0100

#define OF_KEY_RETURN		13

// http://www.openframeworks.cc/forum/viewtopic.php?t=494
// some issues with keys across platforms:

#ifdef TARGET_OSX
	#define OF_KEY_BACKSPACE	127
	#define OF_KEY_DEL			8
#else
	#define OF_KEY_BACKSPACE	8
	#define OF_KEY_DEL			127
#endif

// zach - there are more of these keys, we can add them here...
// these are keys that are not coming through "special keys"
// via glut, but just other keys on your keyboard like

#define OF_KEY_F1			(GLUT_KEY_F1 | OF_KEY_MODIFIER)
#define OF_KEY_F2			(GLUT_KEY_F2 | OF_KEY_MODIFIER)
#define OF_KEY_F3			(GLUT_KEY_F3 | OF_KEY_MODIFIER)
#define OF_KEY_F4			(GLUT_KEY_F4 | OF_KEY_MODIFIER)
#define OF_KEY_F5			(GLUT_KEY_F5 | OF_KEY_MODIFIER)
#define OF_KEY_F6			(GLUT_KEY_F6 | OF_KEY_MODIFIER)
#define OF_KEY_F7			(GLUT_KEY_F7 | OF_KEY_MODIFIER)
#define OF_KEY_F8			(GLUT_KEY_F8 | OF_KEY_MODIFIER)
#define OF_KEY_F9			(GLUT_KEY_F9 | OF_KEY_MODIFIER)
#define OF_KEY_F10			(GLUT_KEY_F10 | OF_KEY_MODIFIER)
#define OF_KEY_F11			(GLUT_KEY_F11 | OF_KEY_MODIFIER)
#define OF_KEY_F12			(GLUT_KEY_F12 | OF_KEY_MODIFIER)

#define OF_KEY_LEFT			(GLUT_KEY_LEFT | OF_KEY_MODIFIER)
#define OF_KEY_UP			(GLUT_KEY_UP | OF_KEY_MODIFIER)
#define OF_KEY_RIGHT		(GLUT_KEY_RIGHT | OF_KEY_MODIFIER)
#define OF_KEY_DOWN			(GLUT_KEY_DOWN | OF_KEY_MODIFIER)
#define OF_KEY_PAGE_UP		(GLUT_KEY_PAGE_UP | OF_KEY_MODIFIER)
#define OF_KEY_PAGE_DOWN	(GLUT_KEY_PAGE_DOWN | OF_KEY_MODIFIER)
#define OF_KEY_HOME			(GLUT_KEY_HOME | OF_KEY_MODIFIER)
#define OF_KEY_END			(GLUT_KEY_END | OF_KEY_MODIFIER)
#define OF_KEY_INSERT		(GLUT_KEY_INSERT | OF_KEY_MODIFIER)


//--------------------------------------------
//colors for our logger.

#ifdef TARGET_WIN32
//		fg_black = 0,
//		fg_red = FOREGROUND_RED,
//		fg_green = FOREGROUND_GREEN,
//		fg_blue = FOREGROUND_BLUE,
//		fg_yellow = fg_red | fg_green,
//		fg_cyan = fg_green | fg_blue,
//		fg_pink = fg_red | fg_blue,
//		fg_white = fg_red | fg_green | fg_blue,
//		fg_bright = FOREGROUND_INTENSITY,
//		fg_bright_red = fg_bright | fg_red,
//		fg_bright_green = fg_bright | fg_green,
//		fg_bright_blue = fg_bright | fg_blue,
//		fg_bright_yellow = fg_bright | fg_yellow,
//		fg_bright_cyan = fg_bright | fg_cyan,
//		fg_bright_pink = fg_bright | fg_pink,
//		fg_bright_white = fg_bright | fg_white,
//		bg_black = 0,
//		bg_red = BACKGROUND_RED,
//		bg_green = BACKGROUND_GREEN,
//		bg_blue = BACKGROUND_BLUE,
//		bg_yellow = bg_red | bg_green,
//		bg_cyan = bg_green | bg_blue,
//		bg_pink = bg_red | bg_blue,
//		bg_white = bg_red | bg_green | bg_blue,
//		bg_bright = BACKGROUND_INTENSITY,
//		bg_bright_red = bg_bright | bg_red,
//		bg_bright_green = bg_bright | bg_green,
//		bg_bright_blue = bg_bright | bg_blue,
//		bg_bright_yellow = bg_bright | bg_yellow,
//		bg_bright_cyan = bg_bright | bg_cyan,
//		bg_bright_pink = bg_bright | bg_pink,
//		bg_bright_white = bg_bright | bg_white,
//
	#define OF_CONSOLE_COLOR_RESTORE (0 | (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE) )
	#define OF_CONSOLE_COLOR_BLACK (0)
	#define OF_CONSOLE_COLOR_RED (FOREGROUND_RED)
	#define OF_CONSOLE_COLOR_GREEN (FOREGROUND_GREEN)
	#define OF_CONSOLE_COLOR_YELLOW (FOREGROUND_RED|FOREGROUND_GREEN)
	#define OF_CONSOLE_COLOR_BLUE (FOREGROUND_BLUE)
	#define OF_CONSOLE_COLOR_PURPLE (FOREGROUND_RED | FOREGROUND_BLUE )
	#define OF_CONSOLE_COLOR_CYAN (FOREGROUND_GREEN | FOREGROUND_BLUE)
	#define OF_CONSOLE_COLOR_WHITE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
		
#else
	
	#define OF_CONSOLE_COLOR_RESTORE (0)
	#define OF_CONSOLE_COLOR_BLACK (30)
	#define OF_CONSOLE_COLOR_RED (31)
	#define OF_CONSOLE_COLOR_GREEN (32)
	#define OF_CONSOLE_COLOR_YELLOW (33)
	#define OF_CONSOLE_COLOR_BLUE (34)
	#define OF_CONSOLE_COLOR_PURPLE (35)
	#define OF_CONSOLE_COLOR_CYAN (36)
	#define OF_CONSOLE_COLOR_WHITE (37)
 
#endif


//--------------------------------------------



#endif
