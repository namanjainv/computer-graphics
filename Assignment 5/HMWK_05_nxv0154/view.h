// Dalio, Brian A.
// dalioba
// 2019-11-03

#if !defined( __VIEW_H__ )
#define __VIEW_H__

//----------------------------------------------------------
typedef struct _View {
  int m_width;
  int m_height;

  double m_cameraDistance;

  double m_worldXMin;
  double m_worldXMax;
  double m_worldYMin;
  double m_worldYMax;

  double m_viewportXMin;
  double m_viewportXMax;
  double m_viewportYMin;
  double m_viewportYMax;

  int m_portalXMin;
  int m_portalXMax;
  int m_portalYMin;
  int m_portalYMax;

  double m_phi;
  double m_theta;
  double m_psi;

  int m_resolution;
} View;

//----------------------------------------------------------
View *allocView();
void  dumpView( View *view );
void  freeView( View *view );
View *loadView( char *fName );

//----------------------------------------------------------

#endif

