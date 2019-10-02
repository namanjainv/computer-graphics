The problem with resizing -
Let matrix 
 x = [[0 1 0],
      [0 1 0]]

Here shape of x is (2, 3).
Let 1 represent black and 0 white
Thus when seen as image, it is a black strip in the center of an image

Say I want to resize x to (3, 2)
Then:
 x = [[0 1],
      [0 0],
      [1 0]]

Here we do not see a black strip
This can be randled with inter cubic interpolation. That is small cubes or patches are reshaped. Here,
- An image is broken down into small cubes
- Then these patches are reshaped
- Thus these patches generates image with desired shape.

The problem in the following code is the use of glLoadIdentity() between both projective and model view.
When a view is converted to projective and assigned identity or default again, then projective reshaping does not take place

Thus glLoadIdentity() needs not be called after matrix is made projective [ glMatrixMode( GL_PROJECTION ) ]

-- Before -- 
  def reshape( self, width, height ) :
    print( f'RESHAPE ({width}, {height})' )

    self.width = width
    self.height = height

    glViewport( 0, 0, self.width, self.height )

    glMatrixMode( GL_PROJECTION )
    glLoadIdentity()

    glMatrixMode( GL_MODELVIEW )
    glLoadIdentity()

-- After -- 
  def reshape( self, width, height ) :
    print( f'RESHAPE ({width}, {height})' )

    self.width = width
    self.height = height

    glViewport( 0, 0, self.width, self.height )

    glMatrixMode( GL_PROJECTION )
    # glLoadIdentity()

    glMatrixMode( GL_MODELVIEW )
    glLoadIdentity()

References: 
- https://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html
- https://stackoverflow.com/questions/628796/what-does-glloadidentity-do-in-opengl
- https://community.khronos.org/t/how-to-load-an-image-in-opengl/71231
- https://community.khronos.org/t/getting-the-depth-image-of-a-3d-object/67006