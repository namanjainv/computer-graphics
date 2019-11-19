// Vimal Kumar, Naman Jain
// nxv0154
// 2019-11-22
//----------------------------------------------------------
#include <stdio.h>

#include "cull.h"
#include "line.h"
#include "projection.h"
#include "triangle.h"
#include "vertex.h"

View *_view = NULL;

//----------------------------------------------------------
void cullProjectDumpTriangle( View *view, Projection *projection, Vertex *v1, Vertex *v2, Vertex *v3 )
{
  // TODO: If culling is active and the triangle should be culled,
  //       do nothing.  Otherwise project the vertices and dump
  //       the triangl.

  Vertex cameraPosition;
  cameraPosition.x = 0;
  cameraPosition.y = 0;
  cameraPosition.z = projection->m_cameraDistance;

  
  if( cull( v1, v2, v3, &cameraPosition ) == 0 ) {

    Vertex pv1, pv2, pv3;
    projectVertex(projection, v1, &pv1);
    projectVertex(projection, v2, &pv2);
    projectVertex(projection, v3, &pv3);

    dumpTriangle(&pv1, &pv2, &pv3);

  }
}

//----------------------------------------------------------
void dumpTriangle( Vertex *v1, Vertex *v2, Vertex *v3 )
{
  Line l;

  l.p1X = v1->x;
  l.p1Y = v1->y;
  l.p2X = v2->x;
  l.p2Y = v2->y;

  if ( clipLine( _view, &l ) ) {
    dumpLine( &l );
  }

  l.p1X = v2->x;
  l.p1Y = v2->y;
  l.p2X = v3->x;
  l.p2Y = v3->y;

  if ( clipLine( _view, &l ) ) {
    dumpLine( &l );
  }

  l.p1X = v3->x;
  l.p1Y = v3->y;
  l.p2X = v1->x;
  l.p2Y = v1->y;

  if ( clipLine( _view, &l ) ) {
    dumpLine( &l );
  }
}

//----------------------------------------------------------
void setPortal( View *v )
{
  _view = v;
}

//----------------------------------------------------------

