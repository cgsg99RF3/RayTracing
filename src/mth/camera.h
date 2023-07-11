/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : camera.h
  * PURPOSE     : Ray tracing project.
  *               Camera declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 24.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __camera_h_
#define __camera_h_

#include "mthdef.h"

namespace mth
{
  template<typename Type>
    class camera 
    {
    public:
      mth::vec3<Type> Loc, At, Dir, Right, Up;
      Type Wp, Hp, ProjDist, Size, FarClip;
      INT W, H;
      mth::matr<Type> Proj;

      /* Creating camera matrix by position function
       * ARGUMENTS:
       *   - new camera params
       *       mth::vec3<Type> NewLoc, NewAt, NewUp;
       * RETURNS:
       *   (matr) result matrix.
       */
      mth::matr<Type> MatrView( mth::vec3<Type> NewLoc, mth::vec3<Type> NewAt, mth::vec3<Type> NewUp )
      {
        Dir = NewAt - NewLoc;
        Dir.Normalize();
        Right = Dir % NewUp;
        Right.Normalize();
        Up = Right % Dir;
        Up.Normalize();
        return mth::matr<DBL>(Right.X, Up.X, -Dir.X, 0, 
                         Right.Y, Up.Y, -Dir.Y, 0, 
                         Right.Z, Up.Z, -Dir.Z, 0,
                         -(NewLoc & Right), -(NewLoc & Up), (NewLoc & Dir), 1);
      } /* End of 'MatrView' function */

      /* Setting Proj of render function
       * ARGUMENTS: 
       *   - projection params
       *       Type Size, ProjDist, FarClip;
       * RETURNS: None.
       */
      VOID ProjSet( Type Size, Type NewProjDist, Type FarClip ) 
      {
        DBL rx, ry;

        rx = ry = Size;
        ProjDist = NewProjDist;
        if (W > H)
        {
          rx *= (DBL)W / H;
          Wp = (DBL)W / H;
          Hp = 1;
        }
        else
        {
          ry *= (DBL)H / W;
          Hp = (DBL)H / W;
          Wp = 1;
        }
        
        Proj = 
          Proj.Frustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
            ProjDist, FarClip);
        //VP = MatrMulMatr(RF3_RndMatrView, RF3_RndMatrProj);
      }  /* End of 'ProjSet' function */

      /* Camera setting function
       * ARGUMENTS: 
       *   - new camera params
       *       mth::vec3<Type> NewLoc, NewAt, NewUp;
       * RETURNS: None.
       */
      VOID Set( mth::vec3<Type> NewLoc, mth::vec3<Type> NewAt, mth::vec3<Type> NewUp )
      {
        MatrView(NewLoc, NewAt, NewUp);
        Loc = NewLoc;
        At = NewAt;
        //VP = View * Proj;
      } /* End of 'Set' End */

      /* Resize function
       * ARGUMENTS:
       *   - new camera size params
       *       INT NewW, NewH;
       * RETURNS: None.
       */
      VOID Resize( INT NewW, INT NewH )
      {
        W = NewW;
        H = NewH;
      } /* End of 'Resize' End */

      /* Ray create function
       * ARGUMENTS:
       *   - ray trace screen coords
       *       Type xs, ys;
       * RETURNS:
       *   (ray<Type>) created ray.
       */
      ray<DBL> FrametoRay( Type xs, Type Ys )
      {
        mth::vec3<Type>
          X = Dir * ProjDist +
          Right * ((xs - W / 2) * Wp / W) + 
          Up * ((-Ys + H / 2) * Hp / H);   
        return ray<DBL>(Loc + X, X);
      } /* End of 'FrameToRay' function */
    };
}
#endif /* __camera_h_ */

  /* END OF 'camera.h' FILE */
