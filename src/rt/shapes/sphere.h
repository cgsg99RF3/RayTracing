/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : sphere.h
  * PURPOSE     : Raytracing project.
  *               Shape shpere declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 23.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __sphere_h_
#define __sphere_h_

#include "rt/rt.h"

namespace rirt
{
  template<typename Type>
  class sphere : public shape
  {
  public:
    mth::vec3<DBL> C;
    DBL R;

    /* Sphere constructor function
     * ARGUMENTS: None.
     */
    sphere( VOID ) : C(mth::vec3<DBL>(0, 0, 0)), R(0)
    {
    } /* End of 'sphere' function */

    /* Sphere constructor function
     * ARGUMENTS:
     *   - centre and radius
     *       mth::vec3<DBL> NewC, NewR;
     *   - surface reference
     *       surface &S;
     */
    sphere( mth::vec3<DBL> NewC,DBL NewR, surface &S ) : C(NewC), R(NewR)
    {
      Surf = S;
    } /* End of 'sphere' function */

    /* Intersection function
     * ARGUMENTS:
     *   - intersection pointer
     *       intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr *I ) override
    {
      I->N = (I->P - C) / R;
    } /* End of 'GetNormal' function */

    /* Intersection function
     * ARGUMENTS:
     *   - ray
     *       const ray<DBL> &R;
     *   - intr vector
     *       intr_list &Il;
     * RETURNS:
     *   (INT) amount of intersections.
     */
    INT AllIntersect( const mth::ray<DBL> &r, intr_list &Il ) override
    {
      mth::vec3<DBL> a;
      DBL OC2, OK, h2;
      intr Intr, Intr1;

      a = C - r.Org;
      OC2 = a & a;
      OK = a & (r.Dir.Normalizing());
      h2 = R * R - (OC2 - OK * OK);

      if (OC2 < R * R)
      {
        Intr.T = OK + sqrt(h2);
        Intr.P = r.Org + r.Dir * Intr.T;
        Intr.N = (Intr.P - C) / R;
        Intr.N.Normalize();
        Intr.Shp = this;
        Il << Intr;
        return 1;
      }
      if (OK < 0.001)//Threshold)
        return 0;
      if (h2 < 0.001)//Threshold)
        return 0;
      Intr.T = OK - sqrt(h2);
      Intr.P = r.Org + r.Dir * Intr.T;
      Intr.N = (Intr.P - C) / R;
      Intr.N.Normalize();
      Intr.Shp = this;
      Il << Intr;
      Intr1.T = OK + sqrt(h2);
      Intr1.P = r.Org + r.Dir * Intr.T;
      Intr1.N = (Intr.P - C) / R;
      Intr1.N.Normalize();
      Intr1.Shp = this;
      Il << Intr1;
      return 2;
     } /* End of 'AllIntersect' function */

    /* Intersection function
     * ARGUMENTS:
     *   - point coordinates
     *       const vec3 &P;
     * RETURNS:
     *   (BOOL) if inside - TRUE, else - FALSE.
     */
    BOOL IsInside( const mth::vec3<DBL> &P ) override
    {
      if (!(P - C) <= R)
        return TRUE;
      return FALSE;
    } /* End of 'IsInside' function */

    /* Intersection function
     * ARGUMENTS:
     *   - ray
     *       const ray<DBL> &R;
     *   - intr
     *       const vec<Type> &D;
     * RETURNS:
     * (BOOL) if intersected - TRUE, else - FALSE.
     */
    BOOL Intersect( const mth::ray<DBL> &r, intr *Intr ) override
    {
      mth::vec3<DBL> a;
      DBL OC2, OK, h2;

      a = C - r.Org;
      OC2 = a & a;
      OK = a & (r.Dir);
      h2 = R * R - (OC2 - OK * OK);

      if (OC2 < R * R)
      {
        Intr->T = OK + sqrt(h2);
        Intr->P = r.Org + r.Dir * Intr->T;
        return TRUE;
      }
      if (OK < 0.001)//Threshold)
        return FALSE;
      if (h2 < 0.001)//Threshold)
        return FALSE;
      Intr->T = OK - sqrt(h2);
      Intr->P = r.Org + r.Dir * Intr->T;
      Intr->Shp = this;
      return TRUE;
    } /* End of 'Intersect' function */
  };
}

#endif /* __sphere_h_ */

/* END OF 'sphere.h' FILE */