// Dalio, Brian A.
// dalioba
// 2019-11-03
//----------------------------------------------------------
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"

#define min(a,b) ({ __typeof__(a) _a = (a);  __typeof__(b) _b = (b); _a < _b ? _a : _b; })
#define max(a,b) ({ __typeof__(a) _a = (a);  __typeof__(b) _b = (b); _a > _b ? _a : _b; })

//----------------------------------------------------------
Model *allocModel( int numVertices, int numFaces, int numPatches )
{
  Model *model;

  model = (Model *) calloc( 1, sizeof( Model ) );
  if ( model == NULL ) {
    fprintf( stderr, "allocModel: Unable to allocate Model.\n" );
    exit( 1 );
  }

  if ( numFaces > 0 ) {
    model->m_numFaces = numFaces;
    model->m_face = (Face *) calloc( numFaces, sizeof( Face ) );
    if ( model->m_face == NULL ) {
      fprintf( stderr, "allocModel: Unable to allocate %d Face%s.\n",
        numFaces, (numFaces == 1) ? "" : "s" );
    }
  }

  if ( numPatches > 0 ) {
    model->m_numPatches = numPatches;
    model->m_patch = (Patch *) calloc( numPatches, sizeof( Patch ) );
    if ( model->m_patch == NULL ) {
      fprintf( stderr, "allocModel: Unable to allocate %d Patch%s.\n",
        numPatches, (numPatches == 1) ? "" : "es" );
    }
  }

  if ( numVertices > 0 ) {
    model->m_numVertices = numVertices;
    model->m_vertex = (Vertex *) calloc( numVertices, sizeof( Vertex ) );
    if ( model->m_vertex == NULL ) {
      fprintf( stderr, "allocModel: Unable to allocate %d Vert%s.\n",
        numVertices, (numVertices == 1) ? "ex" : "ices" );
    }
  }

  return model;
}

void allocPatchVertices( Model *m, int resolution )
{
  if ( m->m_numPatches > 0 ) {
    m->m_numPatchVertices = m->m_numPatches*resolution*resolution;
    m->m_patchVertex = (Vertex *) calloc( m->m_numPatchVertices, sizeof( Vertex ) );
    if ( m->m_patchVertex == NULL ) {
      fprintf( stderr, "allocModel: Unable to allocate %d Patch vert%s.\n",
        m->m_numPatchVertices, (m->m_numPatchVertices == 1) ? "ex" : "ices" );
    }
  }
}

//----------------------------------------------------------
void dumpModel( Model *model, int doLists )
{
  printf( "#- Model parameters --------------------\n" );
  printf( "# Vertex count       : %5d\n", model->m_numVertices );
  printf( "# Face count         : %5d\n", model->m_numFaces );
  printf( "# Patch count        : %5d\n", model->m_numPatches );
  printf( "# Patch vertex count : %5d\n", model->m_numPatchVertices );
  printf( "# Minimum            : ( %13.6f, %13.6f, %13.6f )\n",
    model->m_minimum.x, model->m_minimum.y, model->m_minimum.z );
  printf( "# Maximum            : ( %13.6f, %13.6f, %13.6f )\n",
    model->m_maximum.x, model->m_maximum.y, model->m_maximum.z );
  printf( "# Center             : ( %13.6f, %13.6f, %13.6f )\n",
    model->m_center.x, model->m_center.y, model->m_center.z );
  printf( "# Size               : ( %13.6f, %13.6f, %13.6f )\n",
    model->m_size.x, model->m_size.y, model->m_size.z );

  if ( doLists ) {
    printf( "\n#- Vertex list -------------------------\n" );
    for ( int i=0; i<model->m_numVertices; i++ ) {
      printf( "  [%5d]  ", i );
      dumpVertex( &model->m_vertex[i] );
      putc( '\n', stdout );
    }
  }

  if ( doLists ) {
    printf( "\n#- Face list ---------------------------\n" );
    for ( int i=0; i<model->m_numFaces; i++ ) {
      printf( "  [%5d]  ", i );
      dumpFace( &model->m_face[i] );
      putc( '\n', stdout );
    }
  }

  if ( doLists ) {
    printf( "\n#- Patch list --------------------------\n" );
    for ( int i=0; i<model->m_numPatches; i++ ) {
      printf( "  [%5d]  ", i );
      dumpPatch( &model->m_patch[i] );
      putc( '\n', stdout );
    }
  }

  if ( doLists ) {
    printf( "\n#- Patch vertex list -------------------\n" );
    for ( int i=0; i<model->m_numPatchVertices; i++ ) {
      printf( "  [%5d]  ", i );
      dumpVertex( &model->m_patchVertex[i] );
      putc( '\n', stdout );
    }
  }

  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void dumpFace( Face *face )
{
  printf( "%5d, %5d, %5d", face->v1, face->v2, face->v3 );
}

//----------------------------------------------------------
void dumpPatch( Patch *patch )
{
  printf( "%5d", (*patch)[0] );

  for ( int i=1; i<16; i++ ) {
    printf( ", %5d", (*patch)[i] );
  }
}

//----------------------------------------------------------
void freeModel( Model *model )
{
  if ( model->m_face != NULL ) {
    free( model->m_face );
  }

  if ( model->m_patchVertex != NULL ) {
    free( model->m_patchVertex );
  }

  if ( model->m_vertex != NULL ) {
    free( model->m_vertex );
  }

  free( model );
}

//----------------------------------------------------------
Model *loadModel( char *fName )
{
  FILE *fp = fopen( fName, "r" );
  if ( fp == NULL ) {
    fprintf( stderr, "loadModel: Unable to open '%s' for read.\n", fName );
    exit( 1 );
  }

  //--------------------------------------
  int     numVertices = 0;
  int     numFaces    = 0;
  int     numPatches  = 0;
  char   *line        = NULL;
  size_t  len         = 0;
  size_t  read;

  double  xMin = +HUGE_VAL;
  double  xMax = -HUGE_VAL;
  double  yMin = +HUGE_VAL;
  double  yMax = -HUGE_VAL;
  double  zMin = +HUGE_VAL;
  double  zMax = -HUGE_VAL;

  while ( ( read = getline( &line, &len, fp ) ) != -1 ) {
    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;
    if ( *ptr == 'f' ) ++numFaces;
    if ( *ptr == 'p' ) ++numPatches;
    if ( *ptr == 'v' ) ++numVertices;
  }

  rewind( fp );

  //--------------------------------------
  Model *model = allocModel( numVertices, numFaces, numPatches );

  Vertex *vertex  = model->m_vertex;
  Face   *face    = model->m_face;
  Patch  *patch   = model->m_patch;
  int     lineNum = 0;

  while ( ( read = getline( &line, &len, fp ) ) != -1 ) {
    lineNum++;

    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;

    if ( *ptr == 'f' ) {
      int conv = sscanf( ptr+1, "%d %d %d",
        &face->v1, &face->v2, &face->v3 );

      if ( conv != 3 ) {
        fprintf( stderr, "loadModel: Unable to load face at line %d.", lineNum );
      }

      face->v1--;
      face->v2--;
      face->v3--;

      face++;
      continue;

    } else if ( *ptr == 'p' ) {
      int conv = sscanf( ptr+1, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
        &((*patch)[ 0]), &((*patch)[ 1]), &((*patch)[ 2]), &((*patch)[ 3]),
        &((*patch)[ 4]), &((*patch)[ 5]), &((*patch)[ 6]), &((*patch)[ 7]),
        &((*patch)[ 8]), &((*patch)[ 9]), &((*patch)[10]), &((*patch)[11]),
        &((*patch)[12]), &((*patch)[13]), &((*patch)[14]), &((*patch)[15]) );

      if ( conv != 16 ) {
        fprintf( stderr, "loadModel: Unable to load patch at line %d.", lineNum );
      }

      for ( int i=0; i<16; i++ ) {
        (*patch)[i]--;
      }

      patch++;
      continue;

    } else if ( *ptr == 'v' ) {
      int conv = sscanf( ptr+1, "%lf %lf %lf",
        &vertex->x, &vertex->y, &vertex->z );

      if ( conv != 3 ) {
        fprintf( stderr, "loadModel: Unable to load vertex at line %d.", lineNum );
      }

      xMin = min( vertex->x, xMin );
      xMax = max( vertex->x, xMax );
      yMin = min( vertex->y, yMin );
      yMax = max( vertex->y, yMax );
      zMin = min( vertex->z, zMin );
      zMax = max( vertex->z, zMax );

      vertex++;
      continue;
    }
  }

  model->m_minimum.x = xMin;
  model->m_minimum.y = yMin;
  model->m_minimum.z = zMin;

  model->m_maximum.x = xMax;
  model->m_maximum.y = yMax;
  model->m_maximum.z = zMax;

  model->m_center.x = ( xMin + xMax ) / 2.0;
  model->m_center.y = ( yMin + yMax ) / 2.0;
  model->m_center.z = ( zMin + zMax ) / 2.0;

  model->m_size.x = xMax - xMin;
  model->m_size.y = yMax - yMin;
  model->m_size.z = zMax - zMin;

  //--------------------------------------
  if ( line != NULL ) {
    free( line );
  }

  fclose( fp );

  //--------------------------------------
  return model;
}

//----------------------------------------------------------

