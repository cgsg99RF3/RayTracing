/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : box.h
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

#ifndef __box_h_
#define __box_h_

#include "rt/rt.h"

namespace rirt
{
  template<typename Type>
  class box : public shape
  {
  public:
    mth::vec3<DBL> 
      B1,
      B2;

    /* Box constructor function
     * ARGUMENTS:
     *   - box points
     *       mth::vec3<DBL> P1, P2;
     *   - surface reference
     *       surface &S;
     */
    box( mth::vec3<DBL> P1, mth::vec3<DBL> P2, surface &S ) : B1(P1), B2(P2) 
    {      
      //for (int i = 0; i < 3; i++)
      //  if (B1[i] > B2[i])
        //  Swap(B1[i], B2[i]);

      Surf = S;
    } /* End of 'box' function */

    /* Swap function
     * ARGUMENTS:
     *   - values to swap:
     *       DBL &a, &b;
     * RETURNS: None.
     */
     VOID Swap( DBL &a, DBL &b )
     {
       DBL tmp = a;
       a = b;
       b = tmp;
     } /* End of 'Swap' function */

    /* Intersection function
     * ARGUMENTS:
     *   - intersection pointer
     *       intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr *I ) override
    {
      mth::vec3<DBL> Ns[] = 
      {
        {-1, 0, 0}, {1, 0, 0}, 
        {0, -1, 0}, {0, 1, 0}, 
        {0, 0, -1}, {0, 0, 1}
      };
      I->N = Ns[I->I[0]];
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
      DBL t0, t1;
      DBL tnear = -1, tfar = -1; 
      INT tnear_no = 0, tfar_no = 0;
      intr Intr, Intr1;

      mth::vec3<DBL> Ns[] = 
      {
        {-1, 0, 0}, {1, 0, 0}, 
        {0, -1, 0}, {0, 1, 0}, 
        {0, 0, -1}, {0, 0, 1}
      };

      for (int i = 0; i < 3; i++)
      {
        if (r.Dir[i] == Threshold)
          if (r.Org[i] < B1[i] && r.Org[i] > B2[i])
            continue;

        t0 = (B1[i] - r.Org[i]) / r.Dir[i];
        t1 = (B2[i] - r.Org[i]) / r.Dir[i];
        if (t0 > t1)
          Swap(t0, t1);
        if (tnear == -1 || t0 > tnear)
        {
          tnear = t0;
          if (r.Dir[i] > Threshold)
            tnear_no = i * 2;
          else
            tnear_no = i * 2 + 1;
        }
        if (tfar == -1 || t1 < tfar)
          tfar = t1;
        if (tnear > tfar)
          return 0;
        if (tfar < Threshold)
          return 0;
      }
      Intr.T = tnear;
      Intr.Shp = this;
      Intr.I[0] = tnear_no;
      Intr.N = Ns[Intr.I[0]];
      Il << Intr;
      Intr1.T = tfar;
      Intr1.Shp = this;
      Intr1.I[0] = tnear_no;
      Intr1.N = Ns[Intr.I[0]];
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
      if (P.X - B1.X >= 0 && P.X - B2.X <= 0 &&
          P.Y - B1.Y >= 0 && P.Y - B2.Y <= 0 && 
          P.Z - B1.Z >= 0 && P.Z - B2.Z <= 0)
            return TRUE;
      return FALSE;
    }

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
      DBL t0, t1;
      DBL tnear = -1, tfar = -1; 
      INT tnear_no = 0, tfar_no = 0;

      for (int i = 0; i < 3; i++)
      {
        if (r.Dir[i] == Threshold)
          if (r.Org[i] < B1[i] && r.Org[i] > B2[i])
            continue;

        t0 = (B1[i] - r.Org[i]) / r.Dir[i];
        t1 = (B2[i] - r.Org[i]) / r.Dir[i];
        if (t0 > t1)
          Swap(t0, t1);
        if (tnear == -1 || t0 > tnear)
        {
          tnear = t0;
          if (r.Dir[i] > Threshold)
            tnear_no = i * 2;
          else
            tnear_no = i * 2 + 1;
        }
        if (tfar == -1 || t1 < tfar)
          tfar = t1;
        if (tnear > tfar)
          return FALSE;
        if (tfar < Threshold)
          return FALSE;
      }
      Intr->T = tnear;
      Intr->Shp = this;
      Intr->I[0] = tnear_no;
      return TRUE;
    } /* End of 'Intersect' function */
  };

}

#endif /* __box_h_ */

/* END OF 'box.h' FILE */