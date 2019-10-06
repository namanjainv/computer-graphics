// Vimal Kumar, Naman Jain.
// nxv0154
// 2019-10-05
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "view.h"

//----------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s <modelFileName> <viewFileName>\n", argv[0] );
    exit( 1 );
  }

  //--------------------------------------
  Model *m;
  m = loadModel( argv[1] );
  dumpModel( m );

  putc( '\n', stdout );
  View *v;
  v = loadView( argv[2] );
  dumpView( v );

  //--------------------------------------
  double fx = 0.0, fy = 0.0;
  double gx = 0.0, gy = 0.0;
  double sx = 0.0, sy = 0.0;
  double ax = 0.0, ay = 0.0;

  fx = -v->m_worldXMin; 
  fy = -v->m_worldYMin;

  gx = v->m_width*v->m_viewportXMin;
  gy = v->m_height*v->m_viewportYMin;

  sx = v->m_width*(v->m_viewportXMax - v->m_viewportXMin)/(v->m_worldXMax - v->m_worldXMin);
  sy = v->m_height*(v->m_viewportYMax - v->m_viewportYMin)/(v->m_worldYMax - v->m_worldYMin);

  ax = fx*sx + gx;
  ay = fy*sy + gy;

  printf( "\n#- Projection parameters ---------------\n" );
  printf( "(fx, fy) : ( %13.6f, %13.6f )\n", fx, fy );
  printf( "(gx, gy) : ( %13.6f, %13.6f )\n", gx, gy );
  printf( "(sx, sy) : ( %13.6f, %13.6f )\n", sx, sy );
  printf( "(ax, ay) : ( %13.6f, %13.6f )\n", ax, ay );
  printf( "#---------------------------------------\n" );

  //--------------------------------------
  printf( "\n#- Transformed vertices ----------------\n" );
  for ( int i=0; i<m->m_numVertices; i++ ) {
    double x = 0.0, y = 0.0;
    double pX = 0.0, pY = 0.0;

    x = m->m_vertex[i].x;
    y = m->m_vertex[i].y;
    pX = sx*x + ax;
    pY = sy*y + ay;

    printf( "  [%5d] ( %13.6f, %13.6f ) => ( %8.1f, %8.1f )\n",
      i, x, y, pX, pY );
  }
  printf( "#---------------------------------------\n" );

  //--------------------------------------
  printf( "\n#- Triangles to draw -------------------\n" );
  for ( int i=0; i<m->m_numFaces; i++ ) {
    double x = 0.0, y = 0.0;
    double v1pX = 0.0, v1pY = 0.0;
    double v2pX = 0.0, v2pY = 0.0;
    double v3pX = 0.0, v3pY = 0.0;
    
    x = m->m_vertex[m->m_face[i].v1].x;
    y = m->m_vertex[m->m_face[i].v1].y;
    v1pX = sx*x + ax;
    v1pY = sy*y + ay;

    x = m->m_vertex[m->m_face[i].v2].x;
    y = m->m_vertex[m->m_face[i].v2].y;
    v2pX = sx*x + ax;
    v2pY = sy*y + ay;

    x = m->m_vertex[m->m_face[i].v3].x;
    y = m->m_vertex[m->m_face[i].v3].y;
    v3pX = sx*x + ax;
    v3pY = sy*y + ay;

    printf( "  [%5d] ( %8.1f, %8.1f ), ( %8.1f, %8.1f ), ( %8.1f, %8.1f )\n",
      i, v1pX, v1pY, v2pX, v2pY, v3pX, v3pY );
  }
  printf( "#---------------------------------------\n" );

  //--------------------------------------
  freeModel( m );
  freeView( v );
}

//----------------------------------------------------------

