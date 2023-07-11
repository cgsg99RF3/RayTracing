/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : cylinder.h
  * PURPOSE     : Raytracing project.
  *               Shape triangle declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 26.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __triangle_h_
#define __triangle_h_

#include "rt/rt.h"
#include <fstream>
#include <string>

namespace rirt
{
  class triangle : public shape
  {
  protected:
    mth::vec3<DBL> P0, P1, P2;
    mth::vec3<DBL> u_coeff, v_coeff, s1, s2;
    DBL Down;
    
  public:
    /* Triangle constructor function.
     * ARGUMENTS: None.
     */
    triangle( VOID ) : P0(0, 0, 0), P1(1, 0, 0), P2(1, 0, 1)
    {
      s1 = P1 - P0, 
      s2 = P2 - P0;

      Down = ((!s1 * !s1) * (!s2 * !s2)) - ((s1 & s2) * (s1 & s2));
      u_coeff = (s1 * (s2 & s2) - s2 * (s1 & s2)) / Down;
      v_coeff = (s2 * (s1 & s1)- s1 * (s2 & s1)) / Down;
    } /* End of 'triangle' function */
 
    /* Triangle constructor function.
     * ARGUMENTS:
     *   - vertex positions:
     *       mth::vec3<DBL> NewP1, NewP2, NewP3;
     */
    triangle( mth::vec3<DBL> NewP1, mth::vec3<DBL> NewP2, mth::vec3<DBL> NewP3, surface &S ) : P0(NewP1), P1(NewP2), P2(NewP3)
    {
      Surf = S;
      s1 = P1 - P0, 
      s2 = P2 - P0;
    
      Down = ((!s1 * !s1) * (!s2 * !s2)) - ((s1 & s2) * (s1 & s2));
      u_coeff = (s1 * (s2 & s2) - s2 * (s1 & s2)) / Down;
      v_coeff = (s2 * (s1 & s1)- s1 * (s2 & s1)) / Down;
    } /* End of 'triangle' function */
 
    /* triangle destructor function.
     * ARGUMENTS: None.
     */
    ~triangle( VOID )
    {
    } /* End of 'triangle' function */
 
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
      Intr->N = ((P2 - P0) % (P1 - P0)).Normalize();
      Intr->T= Intr->N & (P0 - r.Org) / (r.Dir & Intr->N);
      if (Intr->T < Threshold)
        return FALSE;

      mth::vec3<DBL> 
        Rp = r.Org + r.Dir * Intr->T; 
      
      DBL u = (Rp & u_coeff) - (P0 & u_coeff);

      DBL v = (Rp & v_coeff) - (P0 & v_coeff);

      // if (Threshold <= u && u <= 1 && Threshold <= v && v <= 1 && u + v <= 1)
      if (0 <= u && u <= 1 && 0 <= v && v <= 1 && u + v <= 1)
      {
        Intr->Shp = this;
        return TRUE;
      }
      return FALSE;
    } /* End of 'Intersection' function. */
  
    /* Load primitive from '*.OBJ' file function.
     * ARGUMENTS:
     *   - pointer to primitive to load:
     *       rf3PRIM *Pr;
     *   - '*.OBJ' file name:
     *       CHAR *FileName;
     * RETURNS:
     *   (BOOL) TRUE if success, FALSE otherwise.
     */
    BOOL Load( std::string FileName, stock<shape *> &Shapes, surface &S )
    { 
      FILE *F;
      INT nv = 0, ni = 0;
      static CHAR Buf[10000];
      mth::vec3<DBL> *V;
      INT *I;
      if ((F = fopen( FileName.c_str(), "r")) == NULL)
        return FALSE;
     
      /* Count quantities */
      while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
      {
        if (Buf[0] == 'v' && Buf[1] == ' ')
          nv++;
        else if (Buf[0] == 'f' && Buf[1] == ' ')
        {
          CHAR *S = Buf + 2, oldc = ' ';
          INT cnt = 0;
     
          while (*S != 0)
            cnt += isspace((UCHAR)oldc) && !isspace((UCHAR)*S), oldc = *S++;
          ni += cnt - 2;
        }
      }
      V = new mth::vec3<DBL>[nv];
      I = new INT[ni * 3];

      /* Read model data */
      rewind(F);
      nv = 0;
      ni = 0;
      while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
      {
        if (Buf[0] == 'v' && Buf[1] == ' ')
        {
          DBL x, y, z;
     
          sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
          V[nv++] = mth::vec3<DBL>(x, y, z);
        }
        else if (Buf[0] == 'f' && Buf[1] == ' ')
        {
          CHAR *S = Buf + 2, oldc = ' ';
          INT n = 0, n0 = 0, n1 = 0, nc;
     
          while (*S != 0)
          {
            if (isspace((UCHAR)oldc) && !isspace((UCHAR)*S))
            {
              sscanf(S, "%d", &nc);
     
              if (nc > 0)
                nc--;
              else
                nc += nv;
     
              if (n == 0)
                n0 = nc;
              else if (n == 1)
                n1 = nc;
              else
              {
               I[ni++] = n0;
               I[ni++] = n1;
               I[ni++] = nc;
               n1 = nc;
              }
              n++;
            }
            oldc = *S++;
          }
        }
      }
      for( int i = 0; i < ni; i += 3)
        Shapes << new rirt::triangle(V[I[i]], V[I[i + 1]], V[I[i + 2]], S); 
      fclose(F);
      delete[] I;
      delete[] V;
      return TRUE;
    }

    /* Get normal function
     * ARGUMENTS:
     *   - intersection pointer
     *       intr *I;
     * RETURNS: None.            
     */
    VOID GetNormal( intr *Intr )
    {
      Intr->N = ((P2 - P0) % (P1 - P0)).Normalize();
    } /* End of 'GetNormal' function. */
  };
}

#endif /* __triangle_h_ */

/* END OF 'tringle.h' FILE */