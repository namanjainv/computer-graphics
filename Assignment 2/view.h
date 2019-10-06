// Dalio, Brian A.
// dalioba
// 2019-10-04

#if !defined( __VIEW_H__ )
#define __VIEW_H__

//----------------------------------------------------------
typedef struct _View {
  int m_width;
  int m_height;

  double m_worldXMin;
  double m_worldXMax;
  double m_worldYMin;
  double m_worldYMax;
  
  double m_viewportXMin;
  double m_viewportXMax;
  double m_viewportYMin;
  double m_viewportYMax;
} View;

//----------------------------------------------------------
View *allocView();
void  dumpView( View *view );
void  freeView( View *view );
View *loadView( char *fName );

//----------------------------------------------------------

#endif

