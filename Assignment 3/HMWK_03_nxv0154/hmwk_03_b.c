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
  // Load the model and view.
  Model *m = loadModel( argv[1] );
  View *v = loadView( argv[2] );

  // Print the canvas side for the SDF file.
  printf( "c %4d %4d\n", v->m_width, v->m_height );

  // Rotate the vertices according to the Euler angles
  // specified in the view.
  rotateVertexList( v, m->m_vertex, m->m_numVertices, m->m_center );

  // Compute the projecion according to the parameters given
  // in the view.
  Projection *p = computeProjection( v );

  // Project the rotated vertices according to the just-computed
  // projection.
  projectVertexList( p, m->m_vertex, m->m_numVertices );

  // Display the three rotated, projected vertices that make up
  // each triangle of the model in SDF form.
  for ( int i=0; i<m->m_numFaces; i++ ) {
    // TODO: Retrieve the rotated/projected values of the three
    //       vertices making up face i.
    double v1pX = 0.0, v1pY = 0.0;
    double v2pX = 0.0, v2pY = 0.0;
    double v3pX = 0.0, v3pY = 0.0;

    v1pX = m->m_vertex[m->m_face[i].v1].x;
    v1pY = m->m_vertex[m->m_face[i].v1].y;

    v2pX = m->m_vertex[m->m_face[i].v2].x;
    v2pY = m->m_vertex[m->m_face[i].v2].y;

    v3pX = m->m_vertex[m->m_face[i].v3].x;
    v3pY = m->m_vertex[m->m_face[i].v3].y;

    printf( "p %8.1f %8.1f %8.1f %8.1f %8.1f %8.1f\n",
      v1pX, v1pY, v2pX, v2pY, v3pX, v3pY );
  }

  //--------------------------------------
  // All done!  Free up the allocated strucures.
  freeModel( m );
  freeView( v );
  freeProjection( p );
}

//----------------------------------------------------------

