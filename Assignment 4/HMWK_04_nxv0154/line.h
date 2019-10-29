// Dalio, Brian A.
// dalioba
// 2019-10-25

#if !defined( __LINE_H__ )
#define __LINE_H__

//----------------------------------------------------------
#include "view.h"

//----------------------------------------------------------
typedef struct _Line {
  double p1X, p1Y;
  double p2X, p2Y;
} Line;

//----------------------------------------------------------
int  clipLine( View *view, Line *line );
void dumpLine( Line *line );

//----------------------------------------------------------
#endif

