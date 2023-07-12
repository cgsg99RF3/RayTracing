/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : csg.h
  * PURPOSE     : Raytracing project.
  *               Csg shape declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 23.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __csg_h_
#define __csg_h_

#include "rt/rt.h"

namespace rirt
{
  class csg : public shape
  {
  public:
    shape *ShpA, *ShpB;
  
    /* Csg constructor.
     * ARGUMENTS:
     *   - shapes to intersecate
     *       shape *A, *B;
     */
    csg( shape *A, shape * B ) : ShpA(A), ShpB(B)
    {
    } /* End of 'csg' function */

    /* Csg destructor.
     * ARGUMENTS: None.
     */
    ~csg( VOID )
    {
      delete ShpA;
      delete ShpB;
    } /* End of '~csg' function */
    
   /* Intersection function
    * ARGUMENTS:
    *   - ray
    *       const ray<DBL> &R;
    *   - intr
    *      ] const vec<Type> &D;
    * RETURNS:
    * (BOOL) if intersected - TRUE, else - FALSE.
    */
    BOOL Intersect( const mth::ray<DBL> &r, intr *I ) override 
    {
      return Intr(r, I);
    } /* End of 'Intersect' finction */

    /* Intersection function
    * ARGUMENTS:
    *   - ray
    *       const ray<DBL> &R;
    *   - intr
    *      ] const vec<Type> &D;
    * RETURNS:
    * (BOOL) if intersected - TRUE, else - FALSE.
    */
    BOOL Intr( const mth::ray<DBL> &r, intr *I )
    {
      intr_list il1, il2;

       if (ShpA->AllIntersect(r, il1) > 0 &&
          ShpB->AllIntersect(r, il2) > 0)
      {
        intr best_in(0, nullptr);
        for (auto &i : il1)
        {
          i.P = r.Org + r.Dir * i.T;
          if (ShpB->IsInside(i.P))
            if (best_in.Shp == nullptr || best_in.T > i.T)
              best_in = i;
        }
        for (auto &i : il2)
        {
          i.P = r.Org + r.Dir * i.T;
          if (ShpA->IsInside(i.P))
            if (best_in.Shp == nullptr || best_in.T > i.T)
              best_in = i;
        }
        *I = best_in;
        return best_in.Shp != nullptr;
      }
      return FALSE;    
    } /* End of 'Intr' function */
      
   /* Intersection function
    * ARGUMENTS:
    *   - ray
    *       const ray<DBL> &R;
    *   - intr
    *      ] const vec<Type> &D;
    * RETURNS:
    * (BOOL) if intersected - TRUE, else - FALSE.
    */
    BOOL Cut( const mth::ray<DBL> &r, intr *I )
    {
      intr_list il1, il2;

       if (ShpA->AllIntersect(r, il1) > 0 &&
           ShpB->AllIntersect(r, il2) > 0)
      {
        intr best_in(0, nullptr);
        for (auto &i : il2)
        {
          i.P = r.Org + r.Dir * i.T;
          if (ShpA->IsInside(i.P))
            if (best_in.Shp == nullptr || best_in.T > i.T)
              //best_in = i;
              ;
        }
        for (auto &i : il1)
        {
          i.P = r.Org + r.Dir * i.T;
          if (!ShpB->IsInside(i.P))
            if (best_in.Shp == nullptr || best_in.T > i.T)
              best_in = i;
        }
        *I = best_in;
        return best_in.Shp != nullptr;
      }
       else if (ShpA->AllIntersect(r, il1) > 0 &&
              !(ShpB->AllIntersect(r, il2) > 0))
       {
         intr best_in(0, nullptr);
        
         for (auto &i : il1)
         {
           i.P = r.Org + r.Dir * i.T;
           if (!ShpB->IsInside(i.P))
             if (best_in.Shp == nullptr || best_in.T > i.T)
               best_in = i;
         }
         *I = best_in;
        return best_in.Shp != nullptr;
       }
      return FALSE;    
    } /* End of 'Intr' function */

  };
}

#endif /* __csg_h_ */
