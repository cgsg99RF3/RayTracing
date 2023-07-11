/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : win.h
  * PURPOSE     : Raytracing project.
  *               Windows declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 23.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __rt_win_h_
#define __rt_win_h_

#include "win.h"
#include "rt/shapes/sphere.h"
#include "rt/shapes/plane.h"
#include "rt/shapes/box.h"
#include "rt/shapes/cylinder.h"
#include "rt/shapes/csg.h"
#include "rt/shapes/triangle.h"

namespace rirt
{
 class rt_win: public win
   {
   public:
    scene Scene;

     /* WM_PAINT window message handle function.
      * ARGUMENTS:
      *   - window device context:
      *       HDC hDC;
      *   - paint message structure pointer:
      *       PAINTSTRUCT *PS;
      * RETURNS: None.
      */
     VOID OnPaint( HDC hDC, PAINTSTRUCT *PS )
     {
       Scene.Frm.Draw(hDC);
     } /* End of 'OnPaint' function */
 
     /* WM_CREATE window message handle function.
      * ARGUMENTS:
      *   - structure with creation data:
      *       CREATESTRUCT *CS;
      * RETURNS:
      *   (BOOL) TRUE to continue creation window, FALSE to terminate.
      */
     BOOL OnCreate( CREATESTRUCT* CS ) override
     {
       Scene.Frm.Resize(W, H);
       return TRUE;
     } /* End of 'OnCreate' function */
 
     /* WM_TIMER window message handle function.
      * ARGUMENTS:
      *   - specified the timer identifier.
      *       INT Id;
      * RETURNS: None.
      */
     VOID OnTimer(INT Id) override
     {
       //Cam.Set(Cam.Loc = mth::vec3<DBL>(Cam.Loc.X, Cam.Loc.Y, Cam.Loc.Z + sin(clock())), Cam.At, Cam.Up);       
     } /* End of 'OnTimer' function */
 
     /* WM_DESTROY window message handle function.
      * ARGUMENTS: None.
      * RETURNS: None.
      */
     VOID OnDestroy(VOID) override
     {  
      // Scene.Flg.wait(FALSE);
     } /* End of 'OnDestroy' function */
 
     /* WM_SIZE window message handle function.
      * ARGUMENTS:
      *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
      *       UINT State;
      *   - new width and height of client area:
      *       INT W, H;
      * RETURNS: None.
      */
     VOID OnSize(UINT State, INT W, INT H) override
     {
       Scene.Frm.Resize(W, H);
     } /* End of 'OnSize' function */
     
     /* WM_KEYDOWN window message handle function.
      * ARGUMENTS:
      *   - message first parameter ('word' param)
      *       WPARAM wParam;
      * RETURNS: None.
      */
     VOID OnKeyDown( WPARAM wParam ) override
     {
       if (wParam == 'Q')
       {
         std::thread Th;
         Th = std::thread(  
           [this]( VOID )
           {
            // Scene.Cam.ProjSet(0.1, 0.1, 1000);
             while(!(GetAsyncKeyState(VK_SPACE)))
             {
               //Scene.Cam.Set(mth::vec3<DBL>(0, 1, 2 + cos(clock())), Scene.Cam.At, Scene.Cam.Up);
                
                Scene.Render();
               //Cam.Loc -= mth::vec3<DBL>(0, 0, cos(clock()));
               InvalidateRect(hWnd, nullptr, FALSE);
               UpdateWindow(hWnd);
             }
           });
         Th.detach();
       }
       else if (wParam == 'F')
         FlipFullScreen();
       else if (wParam == VK_ESCAPE)
         DestroyWindow(hWnd);
       else if (wParam == VK_DOWN)
         Scene.Cam.Set(Scene.Cam.Loc - Scene.Cam.Dir, Scene.Cam.At - Scene.Cam.Dir, Scene.Cam.Up);
       else if (wParam == VK_UP)
         Scene.Cam.Set(Scene.Cam.Loc + Scene.Cam.Dir, Scene.Cam.At + Scene.Cam.Dir, Scene.Cam.Up);
       else if (wParam == VK_RIGHT)                                                       
         Scene.Cam.Set(Scene.Cam.Loc + Scene.Cam.Right, Scene.Cam.At + Scene.Cam.Right , Scene.Cam.Up);
       else if (wParam == VK_LEFT)
         Scene.Cam.Set(Scene.Cam.Loc - Scene.Cam.Right, Scene.Cam.At - Scene.Cam.Right, Scene.Cam.Up);
       else if (wParam == '1')
         Scene.Cam.Set(Scene.Cam.Loc + Scene.Cam.Up, Scene.Cam.At + Scene.Cam.Up , Scene.Cam.Up);
       else if (wParam == '2')
         Scene.Cam.Set(Scene.Cam.Loc - Scene.Cam.Up, Scene.Cam.At - Scene.Cam.Up, Scene.Cam.Up);
       else if (wParam == 'S')
         Scene.Cam.Set(Scene.Cam.Loc - Scene.Cam.Dir, Scene.Cam.At, Scene.Cam.Up);
       else if (wParam == 'W')
         Scene.Cam.Set(Scene.Cam.Loc + Scene.Cam.Dir, Scene.Cam.At, Scene.Cam.Up);
       else if (wParam == 'D')                                                       
         Scene.Cam.Set(Scene.Cam.Loc + Scene.Cam.Right, Scene.Cam.At, Scene.Cam.Up);
       else if (wParam == 'A')
         Scene.Cam.Set(Scene.Cam.Loc - Scene.Cam.Right, Scene.Cam.At, Scene.Cam.Up);

     }   
   };
}

#endif /* __rt_win_h_ */

/* END OF 'rt_win.h' FILE */