// Vimal Kumar, Naman Jain
// nxv0154
// 2019-11-22

#if !defined( __TRIANGLE_H__ )
#define __TRIANGLE_H__

//----------------------------------------------------------
#include "vertex.h"
#include "view.h"

//----------------------------------------------------------
void cullProjectDumpTriangle( View *view, Projection *projection, Vertex *v1, Vertex *v2, Vertex *v3 );
void dumpTriangle( Vertex *v1, Vertex *v2, Vertex *v3 );
void setPortal( View *v );

//----------------------------------------------------------
#endif

