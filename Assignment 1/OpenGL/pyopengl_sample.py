#-----------------------------------------------------------
import imageio

import matplotlib.pyplot as plt  # Uncomment if showing depth buffers.
import numpy as np
import sys

try :
  from OpenGL.GLUT import *
  from OpenGL.GL   import *
  from OpenGL.GLU  import *

except :
  print( 'PyOpenGL not installed (properly ?).' )
  sys.exit()

#-----------------------------------------------------------
START_WIDTH  = 512
START_HEIGHT = 512

#-----------------------------------------------------------
class GLRenderShape :
  def Triangle( self ) :
    glBegin( GL_TRIANGLES )

    glColor3f( 1, 0, 0 )
    glVertex3f( -1, -1, 0 )

    glColor3f( 0, 1, 0 )
    glVertex3f( 1, -1, 0 )

    glColor3f( 0, 0, 1 )
    glVertex3f( 0, 1, 0 )

    glEnd()

#-----------------------------------------------------------
class Scene :
  BTN_STATE_STR = { 0 : 'DOWN', 1 : 'UP' }
  BTN_NAME_STR  = { 0 : 'LEFT', 1 : 'MIDDLE', 2 : 'RIGHT' }

  def __init__( self ) :
    self.quadric = gluNewQuadric()
    self.render_shapes = GLRenderShape()
    self.init()
    self.eye = [ 0.25, 0.25, -100 ]
    self.center = [ 0.2, -0.3, 0 ]
    self.up = [ 0, 1, 0 ]
    self.m_saveIndex = 0

  def display( self ) :
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT )

    glPushMatrix()
    glRotatef( 45, 0, 0 , 1 )
    glScalef( 0.5, 0.5, 0.5 )
    self.render_shapes.Triangle()
    glPopMatrix()

    glPushAttrib( GL_COLOR_BUFFER_BIT )
    glColor3f( 0.4, 0.2, 0.2 )
    glPushMatrix()
    glTranslatef( 0, .25, 0 )
    glutSolidTeapot( 0.25 )
    glPopMatrix()
    glPopAttrib()

    glPushMatrix()
    glColor3f( 1, 0, 0 )
    glTranslatef( -0.5, -0.5, -1 )
    gluSphere( self.quadric, 0.5, 32, 32 )
    glPopMatrix()

    glutSwapBuffers()

  def reshape( self, width, height ) :
    print( f'RESHAPE ({width}, {height})' )

    self.width = width
    self.height = height

    glViewport( 0, 0, self.width, self.height )

    glMatrixMode( GL_PROJECTION )
    # glLoadIdentity()

    glMatrixMode( GL_MODELVIEW )
    glLoadIdentity()

  def keyboard( self, key, x, y ) :
    # Key comes in as a byte, so convert it to a string for
    # easier manipulation.
    key = key.decode( 'utf-8' )

    print( f'KEY {key!r} ({x}, {y})' )

    if key == '\033' :    # ESCAPE key means exit the program.
      sys.exit()

    elif key == 's' :     # s means save a screenshot.
      # Save successive screenshots using incrementing filenames.
      self.m_saveIndex += 1
      imageFName = f'image-{self.m_saveIndex:03d}.png'
      depthFName = f'depth-{self.m_saveIndex:03d}.png'

      glReadBuffer( GL_FRONT )

      # The image comes back flipped top-to-bottom, so we have to
      # flip it before the save.  Also, the pixels are 32 bits per
      # channel, so we have to convert them to uint8 before
      # saving as PNG file.
      im = glReadPixels( 0, 0, self.width, self.height, GL_RGBA, GL_UNSIGNED_INT )
      im = np.right_shift( np.flipud( im ), 24 ).astype( np.uint8 )
      print( f'saving screen shot {im.shape} to {imageFName}' )
      imageio.imwrite( imageFName, im )

      # Depth buffer info comes back as float32, so it has to be
      # converted to uint8 before saving as PNG file.
      im_depth = glReadPixels( 0, 0, self.width, self.height, GL_DEPTH_COMPONENT, GL_FLOAT )
      im_depth = ( np.flipud( im_depth ).astype( np.float64 )
        * 255 + 0.499999999 ).astype( np.uint8 )

      print( f'im_depth dtype {im_depth.dtype}' )
      print( f'saving depth buffer {im_depth.shape} to {depthFName}' )
      imageio.imwrite( depthFName, im_depth )

      # Uncommment this if one wants to see the depth buffer
      # displayed as an image.
      # plt.imshow( im_depth ) 
      # plt.show()

      print( 'done' )

    elif key == 'r' :     # r means resize to original shape.
      glutReshapeWindow( START_WIDTH, START_HEIGHT )

    elif key == 'g' :     # g means grow by 15%.
      glutReshapeWindow( int( 1.15 * self.width ), int( 1.15 * self.height ) )

  def mouse( self, button, state, x, y ) :
    btnStr   = Scene.BTN_NAME_STR.get( button, str( button ) )
    stateStr = Scene.BTN_STATE_STR.get( state, str( state ) )

    print( f'BUTTON {btnStr}, {stateStr}, ({x}, {y})' )

  def motion( self, x, y ) :
    #print( f'MOVE ({x}, {y})' )
    pass

  def init( self ) :
    glClearColor( 0.0, 0.0, 0.0, 1.0 )
    glEnable( GL_DEPTH_TEST )

#-----------------------------------------------------------
def _main() :
  glutInit()
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH )

  w1 = glutCreateWindow( 'PyOpenGL Sample' )
  glutReshapeWindow( START_WIDTH, START_HEIGHT )

  scene = Scene()

  glutReshapeFunc( scene.reshape )
  glutDisplayFunc( scene.display )
  glutKeyboardFunc( scene.keyboard )
  glutMouseFunc( scene.mouse )
  glutMotionFunc( scene.motion )

  scene.init()

  glutMainLoop()

if __name__ == '__main__':
  _main()

#-----------------------------------------------------------

