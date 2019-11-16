// Dalio, Brian A.
// dalioba
// 2019-10-25
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "line.h"

//----------------------------------------------------------
#define INSIDE (0)
#define LEFT   (1)
#define RIGHT  (2)
#define BELOW  (4)
#define ABOVE  (8)

#define EPSILON (1e-13)

int _regionCode( double x, double y, View *v );

//----------------------------------------------------------
int clipLine( View *v, Line *l )
{
  int doDraw = 0;

  int p1Code = _regionCode( l->p1X, l->p1Y, v );
  int p2Code = _regionCode( l->p2X, l->p2Y, v );

  while ( 1 ) {
    if ( ( p1Code | p2Code ) == 0 ) {
      doDraw = 1;
      break;
    }

    if ( ( p1Code & p2Code ) != 0 ) {
      doDraw = 0;
      break;
    }

    int aRegionCode = p1Code == INSIDE ? p2Code : p1Code;
    double x, y;

    if ( aRegionCode & ABOVE ) {
      // Point was ABOVE.  Move it along the line down to Y max.
      x = l->p1X + ( l->p2X - l->p1X )*( v->m_portalYMax - l->p1Y )/( l->p2Y - l->p1Y );
      y = v->m_portalYMax;
    } else if ( aRegionCode & BELOW ) {
      // Point was BELOW.  Move it along the line up to Y min.
      x = l->p1X + ( l->p2X - l->p1X )*( v->m_portalYMin - l->p1Y )/( l->p2Y - l->p1Y );
      y = v->m_portalYMin;
    } else if ( aRegionCode & RIGHT ) {
      // Point was to the RIGHT.  Move it along the line over to X max.
      x = v->m_portalXMax;
      y = l->p1Y + ( l->p2Y - l->p1Y )*( v->m_portalXMax - l->p1X )/( l->p2X - l->p1X );
    } else if ( aRegionCode & LEFT ) {
      // Point was to the LEFT.  Move it along the line over to X min.
      x = v->m_portalXMin;
      y = l->p1Y + ( l->p2Y - l->p1Y )*( v->m_portalXMin - l->p1X )/( l->p2X - l->p1X );
    } else {
      // Huh?  We didn't match _any_ region?  How did that happen?
      fprintf( stderr, "Code 0x%x did not match any region?\n", aRegionCode );
      exit( 1 );
    }

    // Replace whatever point we chose with the newly computed point.
    // We also have to recompute its region code.
    if ( aRegionCode == p1Code ) {
      // We were looking at p1.  Update its location and its code.
      l->p1X = x;
      l->p1Y = y;
      p1Code = _regionCode( l->p1X, l->p1Y, v );
    } else {
      // We were looking at p2.  Update its location and its code.
      l->p2X = x;
      l->p2Y = y;
      p2Code = _regionCode( l->p2X, l->p2Y, v );
    }
  }

  return doDraw;
}

//----------------------------------------------------------
void dumpLine( Line *l )
{
  printf( "l %8.1f %8.1f %8.1f %8.1f\n",
    l->p1X, l->p1Y, l->p2X, l->p2Y );
}

int _regionCode( double x, double y, View *v )
{
  int code = INSIDE;

  if ( ( v->m_portalXMin - x ) > EPSILON ) {
    code |= LEFT;
  } else if ( ( x - v->m_portalXMax ) > EPSILON ) {
    code |= RIGHT;
  }

  if ( ( v->m_portalYMin - y ) > EPSILON ) {
    code |= BELOW;
  } else if ( ( y - v->m_portalYMax ) > EPSILON ) {
    code |= ABOVE;
  }

  return code;
}

//----------------------------------------------------------

