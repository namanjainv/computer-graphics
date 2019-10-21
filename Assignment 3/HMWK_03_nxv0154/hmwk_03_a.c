// Vimal Kumar, Naman Jain
// nxv0154
// 2019-10-21
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "model.h"
#include "projection.h"
#include "view.h"

//----------------------------------------------------------
int main( int argc, char *argv[] )
{
  if ( argc != 3 ) {
    fprintf( stderr, "Usage: %s <modelFileName> <viewFileName>\n", argv[0] );
    exit( 1 );
  }

  //--------------------------------------
  // Load the model and dump its contents.
  Model *m;
  m = loadModel( argv[1] );
  dumpModel( m );

  // Load the view and dump its contents.
  putc( '\n', stdout );
  View *v;
  v = loadView( argv[2] );
  dumpView( v );

  // Rotate the vertices according to the Euler angles
  // specified in the view.  Then dump them.
  putc( '\n', stdout );
  rotateVertexList( v, m->m_vertex, m->m_numVertices, m->m_center );
  printf( "#- Rotated vertices --------------------\n" );
  dumpVertexList( m->m_vertex, m->m_numVertices );
  printf( "#---------------------------------------\n" );

  // Compute the projecion according to the parameters given
  // in the view.  Then dump the projection.
  putc( '\n', stdout );
  Projection *p = computeProjection( v );
  dumpProjection( p );

  // Project the rotated vertices according to the just-computed
  // projection.  Then dump the projected vertices.
  putc( '\n', stdout );
  projectVertexList( p, m->m_vertex, m->m_numVertices );
  printf( "#- Projected vertices ------------------\n" );
  dumpVertexList( m->m_vertex, m->m_numVertices );
  printf( "#---------------------------------------\n" );

  // Display the three rotated, projected vertices that make up
  // each triangle of the model.
  putc( '\n', stdout );
  printf( "#- Triangles to draw -------------------\n" );
  for ( int i=0; i<m->m_numFaces; i++ ) {
    // TODO: Retrieve the rotated/projected values of the three
    //       vertices making up face i.
    double v1pX = 0.0, v1pY = 0.0;
    double v2pX = 0.0, v2pY = 0.0;
    double v3pX = 0.0, v3pY = 0.0;

    printf( "  [%5d] ( %8.1f, %8.1f ), ( %8.1f, %8.1f ), ( %8.1f, %8.1f )\n",
      i, v1pX, v1pY, v2pX, v2pY, v3pX, v3pY );
  }
  printf( "#---------------------------------------\n" );

  //--------------------------------------
  // All done!  Free up the allocated strucures.
  freeModel( m );
  freeView( v );
  freeProjection( p );
}

//----------------------------------------------------------

