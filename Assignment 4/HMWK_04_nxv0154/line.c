// Vimal Kumar, Naman Jain
// nxv0154
// 2019-10-29
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
  int p1_region = _regionCode(l->p1X, l->p1Y, v);
  int p2_region = _regionCode(l->p2X, l->p2Y, v);
  if ( (p1_region == p2_region) && (p1_region == INSIDE) )
    return 1;
  if( ( p1_region & p2_region) != INSIDE) {
    printf("Line Clipped");
    dumpLine(l);
    return 0;
  }
  
  int l_region = ( p1_region == INSIDE )? p2_region : p1_region;
  int pt = ( p1_region == INSIDE )? 2 : 1;
  double x = 0;
  double y = 0;
  
  if(l_region & ABOVE) {
    x = l->p1X + ( l->p2X - l->p1X ) * ( v->m_portalYMax - l->p1Y ) * ( l->p2Y - l->p1Y );
    y = v->m_portalYMax;
  }
  else if(l_region & BELOW) {
    x = l->p1X + ( l->p2X - l->p1X ) * ( v->m_portalYMin - l->p1Y ) * ( l->p2Y - l->p1Y );
    y = v->m_portalYMin;
  }
  else if(l_region & RIGHT) {
    x = v->m_portalXMax;
    y = l->p1Y + ( l->p2Y - l->p1Y ) * ( v->m_portalXMax - l->p1X ) * ( l->p2X - l->p1X );
  }
  else if(l_region & LEFT) {
    x = v->m_portalXMin;
    y = l->p1Y + ( l->p2Y - l->p1Y ) * ( v->m_portalXMin - l->p1X ) * ( l->p2X - l->p1X );
  }
  if(pt == 1) {
    l->p1X = x;
    l->p1Y = y;
  }
  else {
    l->p2X = x;
    l->p2Y = y;
  }
  return clipLine(v, l);
}

//----------------------------------------------------------
void dumpLine( Line *l )
{
  printf( "l %8.1f %8.1f %8.1f %8.1f\n",
    l->p1X, l->p1Y, l->p2X, l->p2Y );
}

//----------------------------------------------------------
int _regionCode( double x, double y, View *v )
{
  int CODE = INSIDE;

  if( x < v->m_portalXMin ) 
    CODE = CODE | LEFT;
  else if( x > v->m_portalXMax )
    CODE = CODE | RIGHT;
  if( y < v->m_portalYMin ) 
    CODE = CODE | BELOW;
  else if( y > v->m_portalYMax )
    CODE = CODE | ABOVE;
  return CODE;
}

//----------------------------------------------------------

