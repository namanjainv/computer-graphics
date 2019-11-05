// Dalio, Brian A.
// dalioba
// 2019-11-05
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "bezier.h"
#include "line.h"
#include "model.h"
#include "projection.h"
#include "triangle.h"
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

  // Set the portal that we draw triangles against.
  setPortal( v );

  // Allocate space for the generated Bézier surface points.
  allocPatchVertices( m, v->m_resolution );

  // Compute the projecion according to the parameters given
  // in the view.
  Projection *p = computeProjection( v );

  // Dump the model, view, and projection as documentation.
  dumpModel( m, 0 );
  dumpView( v );
  dumpProjection( p );

  //--------------------------------------
  // Rotate the vertices, which includes the Bézier control
  // points, according to the Euler angles specified in the view.
  rotateVertexList( v, m->m_vertex, m->m_numVertices, m->m_center );

  //--------------------------------------
  // Print the canvas side for the SDF file.
  printf( "c %4d %4d\n", v->m_width, v->m_height );

  //--------------------------------------
  // Draw lines corresponding to the viewport region.
  Line line;

  line.p1X = v->m_portalXMin;  line.p1Y = v->m_portalYMin;
  line.p2X = v->m_portalXMin;  line.p2Y = v->m_portalYMax;
  dumpLine( &line );
 
  line.p1X = v->m_portalXMin;  line.p1Y = v->m_portalYMax;
  line.p2X = v->m_portalXMax;  line.p2Y = v->m_portalYMax;
  dumpLine( &line );
 
  line.p1X = v->m_portalXMax;  line.p1Y = v->m_portalYMax;
  line.p2X = v->m_portalXMax;  line.p2Y = v->m_portalYMin;
  dumpLine( &line );
 
  line.p1X = v->m_portalXMax;  line.p1Y = v->m_portalYMin;
  line.p2X = v->m_portalXMin;  line.p2Y = v->m_portalYMin;
  dumpLine( &line );
   
  //--------------------------------------
  // Generate the Bézier surface points
  generateBezierPoints( m, v->m_resolution );

  // Project the Bézier surface points
  projectVertexList( p, m->m_patchVertex, m->m_numPatchVertices );

  // Generate (and draw) the triangles for the Bézier surfaces.
  generateBezierTriangles( m, v->m_resolution );

  //--------------------------------------
  // Project the regular vertices
  projectVertexList( p, m->m_vertex, m->m_numVertices );

  // Draw each triangle (in clipped form if necesssary).
  for ( int i=0; i<m->m_numFaces; i++ ) {
    dumpTriangle(
      &m->m_vertex[m->m_face[i].v1],
      &m->m_vertex[m->m_face[i].v2],
      &m->m_vertex[m->m_face[i].v3] );
  }

  //--------------------------------------
  // All done!  Free up the allocated strucures.
  freeModel( m );
  freeView( v );
  freeProjection( p );
}

//----------------------------------------------------------

