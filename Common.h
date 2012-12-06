
#ifndef COMMON_H
#define COMMON_H

#if defined(_DEBUG) && defined(WIN32)
	#define	_CRTDBG_MAP_ALLOC	1
#endif

#define	IN_EXT_VERSION2
#define	COXSDK

// ----------------------------------------------
// VERSION AND BUILD YOUR EXTENSION CAN WORK WITH
// ----------------------------------------------
//#define TGFEXT		// TGF, MMF Standard and MMF Pro
#define	MMFEXT			// MMF Standard and MMF Pro
//#define PROEXT		// MMF Pro only

//#define MMFHWA		// MMF HWA only version
//#define MMFUNICODE	// MMF UNICODE only version

// Build number of the minimum required version of MMF
#define	MINBUILD	244

// General includes
#include	"ccxhdr.h"
#include	"Surface.h"

// Specific to this cox
#include	"resource.h"
#include	"main.h"
#include	"DynExt.h"
//#include	"TigsExt.hpp"

// Globals and Prototypes
extern HINSTANCE hInstLib;
extern short conditionsInfos[];
extern short actionsInfos[];
extern short expressionsInfos[];

long (WINAPI * ConditionJumps[])(LPRDATA rdPtr, long param1, long param2);
short (WINAPI * ActionJumps[])(LPRDATA rdPtr, long param1, long param2);
long (WINAPI * ExpressionJumps[])(LPRDATA rdPtr, long param);

// Used to ensure the MMF version is 2.0, you can safely ignore this
#if defined(MMFEXT)
#define	IS_COMPATIBLE_A(v) (v->mvGetVersion != NULL && (v->mvGetVersion() & MMFBUILD_MASK) >= MINBUILD && (v->mvGetVersion() & MMFVERSION_MASK) >= MMFVERSION_20 && ((v->mvGetVersion() & MMFVERFLAG_MASK) & MMFVERFLAG_HOME) == 0)
#elif defined(PROEXT)
#define IS_COMPATIBLE_A(v) (v->mvGetVersion != NULL && (v->mvGetVersion() & MMFBUILD_MASK) >= MINBUILD && (v->mvGetVersion() & MMFVERSION_MASK) >= MMFVERSION_20 && ((v->mvGetVersion() & MMFVERFLAG_MASK) & MMFVERFLAG_PRO) != 0)
#else
#define	IS_COMPATIBLE_A(v) (v->mvGetVersion != NULL && (v->mvGetVersion() & MMFBUILD_MASK) >= MINBUILD && (v->mvGetVersion() & MMFVERSION_MASK) >= MMFVERSION_20)
#endif

#if defined(MMFUNICODE)
#define	IS_COMPATIBLE(v) (IS_COMPATIBLE_A(v) && v->mvCallFunction(NULL, EF_ISUNICODE, 0, 0, 0))
#elif defined(MMFHWA)
#define	IS_COMPATIBLE(v) (IS_COMPATIBLE_A(v) && v->mvCallFunction(NULL, EF_ISHWA, 0, 0, 0))
#else
#define	IS_COMPATIBLE(v) (IS_COMPATIBLE_A(v))
#endif

#endif
