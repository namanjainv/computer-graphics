// Vimal Kumar, Naman Jain
// nxv0154
// 2019-10-29
//----------------------------------------------------------
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "view.h"

//----------------------------------------------------------
View *allocView()
{
  View *view;

  view = (View *) calloc( 1, sizeof( View ) );
  if ( view == NULL ) {
    fprintf( stderr, "allocView: Unable to allocate View.\n" );
    exit( 1 );
  }

  return view;
}

//----------------------------------------------------------
void dumpView( View *view )
{
  printf( "#- View parameters ---------------------\n" );
  printf( "# Euler angles    : %13.6f, %13.6f, %13.6f\n",
    view->m_phi, view->m_theta, view->m_psi );

  printf( "# World limits    : %13.6f, %13.6f, %13.6f, %13.6f\n",
    view->m_worldXMin, view->m_worldYMin,
    view->m_worldXMax, view->m_worldYMax );

  printf( "# Camera distance : %13.6f\n", view->m_cameraDistance );

  printf( "# Canvas width    : %5d\n", view->m_width );
  printf( "# Canvas height   : %5d\n", view->m_height );

  printf( "# Screen limits   : %13.6f, %13.6f, %13.6f, %13.6f\n",
    view->m_viewportXMin, view->m_viewportYMin,
    view->m_viewportXMax, view->m_viewportYMax );

  printf( "# Portal pixels   : %4d, %4d, %4d, %4d\n",
    view->m_portalXMin, view->m_portalXMax,
    view->m_portalYMin, view->m_portalYMax );

  printf( "#---------------------------------------\n" );
}

//----------------------------------------------------------
void freeView( View *view )
{
  free( view );
}

//----------------------------------------------------------
View *loadView( char *fName )
{
  FILE *fp = fopen( fName, "r" );
  if ( fp == NULL ) {
    fprintf( stderr, "loadView: Unable to open '%s' for read.\n", fName );
    exit( 1 );
  }

  //--------------------------------------
  View   *view  = allocView();
  char   *line  = NULL;
  size_t  len   = 0;
  size_t  read;

  int     lineNum = 0;

  while ( ( read = getline( &line, &len, fp ) ) != -1 ) {
    lineNum++;

    char *ptr = line;

    while ( *ptr && isspace( *ptr ) ) ptr++;

    if ( *ptr == 'c' ) {
      int conv = sscanf( ptr+1, "%d %d",
        &view->m_width, &view->m_height );

      if ( conv != 2 ) {
        fprintf( stderr, "loadView: Unable to load canvas size at line %d.", lineNum );
      }

      continue;
    }

    if ( *ptr == 'd' ) {
      int conv = sscanf( ptr+1, "%lf", &view->m_cameraDistance );

      if ( conv != 1 ) {
        fprintf( stderr, "loadView: Unable to load camera distance at line %d.", lineNum );
      }

      continue;
    }

    if ( *ptr == 'e' ) {
      int conv = sscanf( ptr+1, "%lf %lf %lf",
        &view->m_phi, &view->m_theta, &view->m_psi );

      if ( conv != 3 ) {
        fprintf( stderr, "loadView: Unable to load Euler angles at line %d.", lineNum );
      }

      continue;
    }

    if ( *ptr == 's' ) {
      int conv = sscanf( ptr+1, "%lf %lf %lf %lf",
        &view->m_viewportXMin, &view->m_viewportYMin,
        &view->m_viewportXMax, &view->m_viewportYMax );

      if ( conv != 4 ) {
        fprintf( stderr, "loadView: Unable to load viewport limits at line %d.", lineNum );
      }

      continue;
    }

    if ( *ptr == 'w' ) {
      int conv = sscanf( ptr+1, "%lf %lf %lf %lf",
        &view->m_worldXMin, &view->m_worldYMin,
        &view->m_worldXMax, &view->m_worldYMax );

      if ( conv != 4 ) {
        fprintf( stderr, "loadView: Unable to load world limits at line %d.", lineNum );
      }

      continue;
    }
  }

  //--------------------------------------
  if ( line != NULL ) {
    free( line );
  }

  fclose( fp );

  //--------------------------------------

  // TODO: Compute the portal min and max values and
  //       save their values in the m_portal... fields
  //       in the view structure.

  //--------------------------------------
  return view;
}

//----------------------------------------------------------

