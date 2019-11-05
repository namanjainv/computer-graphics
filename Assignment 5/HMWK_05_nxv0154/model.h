// Dalio, Brian A.
// dalioba
// 2019-11-03

#if !defined( __MODEL_H__ )
#define __MODEL_H__

//----------------------------------------------------------
#include "vertex.h"

//----------------------------------------------------------
typedef struct _Face {
  int v1;
  int v2;
  int v3;
} Face;

typedef int Patch[16];

//----------------------------------------------------------
typedef struct _Model {
  int     m_numVertices;
  int     m_numFaces;
  int     m_numPatches;
  int     m_numPatchVertices;

  Vertex  m_minimum;
  Vertex  m_maximum;
  Vertex  m_center;
  Vertex  m_size;

  Vertex *m_vertex;
  Face   *m_face;

  Patch  *m_patch;
  Vertex *m_patchVertex;
} Model;

//----------------------------------------------------------
Model *allocModel( int numVertices, int numFaces, int numPatches );
void   allocPatchVertices( Model *m, int resolution );
void   dumpFace( Face *face );
void   dumpModel( Model *model, int doLists );
void   dumpPatch( Patch *patch );
void   freeModel( Model *m );
Model *loadModel( char *fName );

//----------------------------------------------------------

#endif

