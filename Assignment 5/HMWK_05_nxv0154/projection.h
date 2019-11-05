// Dalio, Brian A.
// dalioba
// 2019-10-17

#if !defined( __PROJECTION_H__ )
#define __PROJECTION_H__

//----------------------------------------------------------
#include "vertex.h"
#include "view.h"

//----------------------------------------------------------
typedef struct _Projection {
  double m_fx, m_fy;
  double m_gx, m_gy;
  double m_sx, m_sy;
  double m_ax, m_ay;
  double m_cameraDistance;
} Projection;

//----------------------------------------------------------
Projection *allocProjection();
Projection *computeProjection( View *view );
void dumpProjection( Projection *projection );
void freeProjection();
void projectVertexList( Projection *projection, Vertex *vertex, int numVertices );
void rotateVertexList( View *view, Vertex *vertex, int numVertices, Vertex center );

//----------------------------------------------------------

#endif

