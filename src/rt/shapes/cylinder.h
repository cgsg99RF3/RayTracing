/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : cylinder.h
  * PURPOSE     : Raytracing project.
  *               Shape box declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 26.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __cylinder_h_
#define __cylinder_h_

#include "rt/rt.h"

namespace rirt
{
  template<typename Type>
  class cylinder : public shape
  {
  public:
    mth::vec3<DBL> C, Axis;
    DBL R;

    /* Cylinder constructor function
     * ARGUMENTS:
     *   - centre
     *       mth::vec3<DBL> NewC;
     *   - axis
     *       mth::vec3<DBL> NewAx;
     *   - radius 
     *       DBL R;
     */
    cylinder( mth::vec3<DBL> NewC, mth::vec3<DBL> NewAx, DBL NewR ) : C(NewC), Axis(NewAx), R(NewR) 
    {      
    } /* End of 'cylinder' function */

    /* Get normal function
     * ARGUMENTS:
     *   - intersection pointer
     *       intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr *I ) override
    {
      I->N = (Axis % I->P) % Axis;
      I->N.Normalize();
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
      DBL a11, a12, a21, a22, b1, b2, t1, t2;
      mth::vec3<DBL> Q1, Q2;

      Axis.Normalize();
      a11 = -(r.Dir) & r.Dir;
      a12 = Axis & r.Dir;
      a21 = -(Axis) & r.Dir;
      a22 = Axis & Axis;
      b1 = (r.Org & r.Dir) - (C & r.Dir);
      b2 = (r.Org & Axis) - (C & Axis);

      DBL k = (a11 * a22 - a12 * a21);
      if (abs(k) < Threshold)
        return FALSE;
      t1 = (b1 * a22 - b2 * a12) / k; 
      t2 = (a11 * b2 - a21 * b1) / k;
     
     // if (t2 < 0.001)
       // return FALSE;

      Q1 = r.Org + (r.Dir * t1);
      Q2 = C + (Axis * t2);
      DBL d = !(Q2 - Q1);
      if ((d) > R)
        return FALSE;
      DBL q2 = R * R - d * d, 
          x2 = q2 / (1 - (r.Dir & Axis) * (r.Dir & Axis));
      Intr->T = t1 + sqrt(x2);   
      if ( t1 > sqrt(x2))
        Intr->T = t1 - sqrt(x2);
      Intr->Shp = this;
      Intr->P = r.Org + r.Dir * Intr->T;
      return TRUE;
    } /* End of 'Intersect' function */
  };
}

#endif /* __cylinder_h_ */

/* END OF 'cylinder.h' FILE */
