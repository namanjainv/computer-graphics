// Dalio, Brian A.
// dalioba
// 2019-10-04
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

  // TODO: Write something here to compute fx, fy, gx, gy, sx,
  //    sy, ax, and ay using the information in the View v.
  //    (All the math you need is recapped in the
  //    "4303 Projection Parallel.pdf" handout.)

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

    // TODO: Write something here to get the x, y coordinates of
    //    vertex i of Model m and then compute the projected
    //    values pX and pY using x and y and the projecion
    //    parameters computed above.  (Again, all the math you
    //    need is in the handout.)

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

    // TODO: Write something here to get the x, y coordinates of
    //    each of the vertices of face i and compute the
    //    projected values v1pX, v1pY, v2pX, v2pY, v3pX, and v3pY
    //    using the projection parameters computed above.  (All
    //    the math you need is still in the handout.  It hasn't
    //    disappeared.)

    printf( "  [%5d] ( %8.1f, %8.1f ), ( %8.1f, %8.1f ), ( %8.1f, %8.1f )\n",
      i, v1pX, v1pY, v2pX, v2pY, v3pX, v3pY );
  }
  printf( "#---------------------------------------\n" );

  //--------------------------------------
  freeModel( m );
  freeView( v );
}

//----------------------------------------------------------

