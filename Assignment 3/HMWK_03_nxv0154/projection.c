// Vimal Kumar, Naman Jain
// nxv0154
// 2019-10-21
//----------------------------------------------------------
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "projection.h"

//----------------------------------------------------------
Projection *allocProjection()
{
  Projection *p;

  p = (Projection *) calloc( 1, sizeof( Projection ) );
  if ( p == NULL ) {
    fprintf( stderr, "allocProjection: Unable to allocate Projection.\n" );
    exit( 1 );
  }

  return p;
}

//----------------------------------------------------------
Projection *computeProjection( View *v )
{
  Projection *p = allocProjection();

  // TODO: Compute the proper values of fx, fy, gx, gy, sx, sy,
  //       ax, and ay and store them in p->...
  //       Save the camera distance from the view in the
  //       projection.

  return p;
}

//----------------------------------------------------------
void dumpProjection( Projection *p )
{
  printf( "#- Projection parameters ---------------\n" );
  printf( "(fx, fy) : ( %13.6f, %13.6f )\n", p->m_fx, p->m_fy );
  printf( "(gx, gy) : ( %13.6f, %13.6f )\n", p->m_gx, p->m_gy );
  printf( "(sx, sy) : ( %13.6f, %13.6f )\n", p->m_sx, p->m_sy );
  printf( "(ax, ay) : ( %13.6f, %13.6f )\n", p->m_ax, p->m_ay );
  printf( "Camera distance : %13.6f\n", p->m_cameraDistance );
  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void freeProjection( Projection *p )
{
  free( p );
}

//----------------------------------------------------------
void projectVertexList( Projection *p, Vertex *v, int numVertices )
{
  // TODO: Using the projection parameters in p, traverse the
  //       given list of vertices (there are numVertices of them)
  //       and project each vertex:
  //         1. If camera distance is not 0.0, first do a
  //            perspective adjustment.
  //         2. Once the vertex is adjusted for perspective,
  //            calculate its corresponding screen coordinates.
}

//----------------------------------------------------------
#define DEGREES_TO_RADIANS(d) (M_PI*(d)/180.0)

void rotateVertexList( View *view, Vertex *vertex, int numVertices, Vertex center )
{
  // TODO: Using the Euler angles given in the view, traverse the
  //       given list of vertices (there are numVertices of them)
  //       and rotate each vertex.
  //
  //       Compute the r00 through r22 values and the ex, ey, ez
  //       values _before_ looping through the vertex list!
}

//----------------------------------------------------------

