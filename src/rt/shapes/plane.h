/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : plane.h
  * PURPOSE     : Raytracing project.
  *               Shape plane declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 23.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __plane_h_
#define __plane_h_

#include "rt/rt.h"

namespace rirt
{
  template<typename Type>
  class plane : public shape
  {
  public:
    mth::vec3<DBL> 
      M,
      N;
    surface Surf;

    /* Plane constructor function
     * ARGUMENTS: None.
     */
    plane( VOID ) : M(nullptr), N(nullptr)
    {
    } /* End of 'plane' function */

    /* Plane constructor function
     * ARGUMENTS:
     *   - plane points
     *       mth::vec3<DBL> NewP1, NewP2, NewP3;
     */
    plane( mth::vec3<DBL> NewP1, mth::vec3<DBL> NewP2, mth::vec3<DBL> NewP3, surface &S ) : M(NewP1), Surf(S) 
    {
      mth::vec3<DBL> a, b;
      a = (NewP2 - NewP1);
      b = (NewP3 - NewP1);
      N = a % b;
      N.Normalize();
    } /* End of 'plane' function */

    /* Intersection function
     * ARGUMENTS:
     *   - intersection pointer
     *       intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr *I ) override
    {
      I->N = N;
    } /* End of 'GetNormal' function */

    /* Intersection function
     * ARGUMENTS:
     *   - ray
     *       const ray<DBL> &R;
     *   - intr
     *      ] const vec<Type> &D;
     * RETURNS:
     * (BOOL) if intersected - TRUE, else - FALSE.
     */
    BOOL Intersect( const mth::ray<DBL> &r, intr *Intr ) override
    {
      Intr->T = -(N & r.Org) / (N & r.Dir);
      if (Intr->T > Threshold)
      {
        Intr->P = r.Org + r.Dir * Intr->T;
        Intr->Shp = this;
        return TRUE;
      }
      return FALSE;
    } /* End of 'Intersect' function */
  };

}

#endif /* __plane_h_ */

/* END OF 'plane.h' FILE */