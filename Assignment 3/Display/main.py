# Dalio, Brian A.
# dalioba
# 2019-10-14
#----------------------------------------------------------------------
# The initialization of tkinter is deeply recursive.  On Ubuntu, the
# limit is too low for tkinter to succeed.  Trial-and-error has shown
# that 2000 seems to work.  If a more complex program starts failing,
# the limit might have to be even higher.
import sys
_RECURSION_LIMIT = 2000

if ( sys.getrecursionlimit() < _RECURSION_LIMIT ) :
  print( f'System recursion limit was {sys.getrecursionlimit()}, setting to {_RECURSION_LIMIT}.' )
  sys.setrecursionlimit( _RECURSION_LIMIT )

#----------------------------------------------------------------------
import tkinter as tk
import myWidgets
import myGraphics

#----------------------------------------------------------------------
def onClosing() :
  if tk.messagebox.askokcancel( "Really Quit?", "Do you really wish to quit?" ) :
    tk.Tk().quit()

#----------------------------------------------------------------------
def main() :
  ob_root_window = tk.Tk()
  ob_root_window.protocol( "WM_DELETE_WINDOW", onClosing )

  ob_world = myGraphics.cl_world()

  myWidgets.cl_widgets( ob_root_window, ob_world )

  ob_root_window.mainloop()
  print( '... mainloop has exited.' )

if ( __name__ == "__main__" ) :
  main()

#----------------------------------------------------------------------
