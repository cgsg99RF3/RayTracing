/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : rt.h
  * PURPOSE     : Raytracing project.
  *               Ray tracing declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 23.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __rt_h_
#define __rt_h_

#include "enviroment.h"
#include <thread>
#include <atomic>

#define Threshold 0.001

namespace rirt
{
  class shape;

  class intr
  {
  public:
    DBL T;
    mth::vec3<DBL> N;      // Intersection point
    mth::vec3<DBL> P;      //  Normal at intersecion point
    BOOL IsN;
    BOOL IsP;
    shape *Shp;            // Pointer to object
    
    // cache addon:
    INT I[8];
    DBL D[8];
    mth::vec3<DBL> V[8];

    /* Intr constructor function
     * ARGUMENTS: None.
     */
    intr( VOID ): T(0), Shp(nullptr), N(0, 0, 0), P(0, 0, 0)
    {
    } /* End of 'intr' function */

    /* Intr constructor function
     * ARGUMENTS: 
     *   - ray length
     *       DBL NewT;
     *   - pointer to figure shape
     *       shape *NewShp;
     */
    intr( DBL NewT, shape *NewShp ) : T(NewT), Shp(NewShp)
    {
    } /* End of 'intr' function */
  };

  class shape : public modifier
  {
  public:
    typedef stock<intr> intr_list; // intersection stock (sorted by T)
    surface Surf;
    stock<modifier *> Mode;

     /* Light addition function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID operator<<( modifier *M )
    {
      Mode << M;
    }
    shape( VOID )
    {
      Surf.Ka = mth::vec3<DBL>(0.1, 0.18, 0.19);
      Surf.Kd = mth::vec3<DBL>(0.5, 0.5, 0.5);
      Surf.Ks = mth::vec3<DBL>(0.5, 0.5, 0.5);
      Surf.Ph = 1;
      Surf.Kr = 0.05;
      Surf.Kt  = 0.05;
      Mode << new checker();
    }
    /* Intersection function
     * ARGUMENTS:
     *   - ray
     *       const ray<DBL> &R;
     *   - intr
     *       const vec<Type> &D;
     * RETURNS:
     *   (BOOL) if intersected - TRUE, else - FALSE.
     */
    virtual BOOL Intersect( const mth::ray<DBL> &r, intr *Intr )
    {
      return FALSE;
    } /* End of 'Intersect' function */

    /* Intersection function
     * ARGUMENTS:
     *   - ray
     *       const ray<DBL> &R;
     *   - intr vector
     *       ;
     * RETURNS:
     *   (INT) amount of intersections.
     */
    virtual INT AllIntersect( const mth::ray<DBL> &r, intr_list &Il )
    {
      return 0;
    } /* End of 'AllIntersect' function */

    /* Intersection function
     * ARGUMENTS:
     *   - point coordinates
     *       const vec3 &P;
     * RETURNS:
     *   (BOOL) if inside - TRUE, else - FALSE.
     */
    virtual BOOL IsInside( const mth::vec3<DBL> &P )
    {
      return FALSE;
    } /* End of 'IsInside' function */

    /* Intersection function
     * ARGUMENTS:
     *   - intersection pointer
     *       intr *I;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intr *I )
    {
    } /* End of 'GetNormal' function */
  };

  class scene
  {
  public:
    mth::vec3<DBL> AmbientColor, BackgroundColor, FogColor;
    DBL FogStart, FogEnd, Weight;
    stock<light *> Lights;
    stock<shape *> Shapes;   // Shape stock
    frame Frm; 
    mth::camera<DBL> Cam;
    INT RecLevel, MaxRecLevel;
    envi Air;
    BOOL Flg;

    /* Scene constructor function.
    * ARGUMENRS: None.
    */
    scene( VOID ) : 
      Frm(frame(0, 0)), AmbientColor(mth::vec3<DBL>(0, 0, 0.5)), FogColor(mth::vec3<DBL>(1, 0, 0)), 
      BackgroundColor(mth::vec3<DBL>(0.7, 0.9, 0.7)), FogStart(0), FogEnd(10), Weight(0.1),
      RecLevel(0), MaxRecLevel(100)
    {
      Air.RefractionCoef = 1;
      Air.Decay = 0.1;
    } /* End of 'scene' function */
    
    /* Light addition function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID operator<<( light *Lgh )
    {
      Lights << Lgh;
    }

    /* Tracing function.
     * ARGUMENTS:
     *   ray reference
     *     
     * RETURNS: None.
     */
    mth::vec3<DBL> Trace( const mth::ray<DBL> &R, const envi &Media, DBL Weight )
    {
      mth::vec3<DBL> color = BackgroundColor;
      RecLevel = 0;
      intr in;
       
      if (RecLevel < MaxRecLevel)
      {
        RecLevel++;
        if (Intersect(R, &in))
        {
          in.Shp->GetNormal(&in);
          in.N.Normalize();
          color = Shade(R.Dir, Media, &in, Weight);
          color *= exp(-in.T * Media.Decay);
          RecLevel--;
        }
     }
      return color;
    } /* End of 'Trace' function */


    mth::vec3<DBL> Shade( const mth::vec3<DBL> &V, const envi &Media, intr *I, DBL Weight )
    {     
      checker A;
      shade_info si {I->P, I->N, I->Shp, I->Shp->Surf, Media, {1, 0, 0}, {0, 1, 0}};
     // for (auto m: si.Shp->Mode)
        //A.Apply(&si);
      mth::vec3<DBL> color = si.Surf.Ka * AmbientColor * mth::vec3<DBL>(0);
      mth::vec3<DBL> R = V - si.N * (2 * (V & si.N));
      for (auto Lgh : Lights)
      {
        light_info li = Lgh->LtI;
         mth::ray<DBL> shd(si.P + li.L * Threshold, li.L);
          if (IsIntersect(shd, I))
            continue;
            //DBL sh = Lgh->Shadow(si.P, &li);
        // cast shadow
      /*  intr_list il;
        if (AllIntersect(ray(si.P + li.L * Threshold, li.L), il) > 0 &&
            il[0].T < li.Dist)
          continue; // point in shadow
        */    
          DBL nl = si.N & li.L;
        // diffuse
        if (nl > Threshold)
        {
          color += si.Surf.Kd * li.Color * nl;
    
          // specular
          DBL rl = R & li.L;
          if (rl > Threshold)
          {
            color += si.Surf.Ks * li.Color * pow(rl, si.Surf.Ph);
          }
          /*
          DBL fog;
          if (si.P.Z < FogStart)
            fog = 0;
          else if (si.P.Z > FogEnd)
            fog = 1;
          else 
            fog = (si.P.Z - FogStart) / (FogEnd - FogStart);
          color = color * fog + FogColor * (1 - fog);
          */
        }
      //Reflection other scene shapes
      DBL w = si.Surf.Kr * Weight;
      if (w > Threshold)          
        color += Trace(mth::ray<DBL>(si.P + R * Threshold, R), Media, w);
      /*mth::vec3<DBL> T;
      T = (V - (I->N & (V & I->N))) * si.Media.RefractionCoef 
           -  I->N * (sqrt(1 - (1 - (V.Normalizing() & I->N) * (V.Normalizing() & I->N)) 
             * si.Media.RefractionCoef * si.Media.RefractionCoef));
      color += Trace(mth::ray<DBL>(si.P, T), Media, w);
      */
      }
       return color;
    }

  // Refraction – the same
             
    /* Render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
   
    mth::vec3<DBL> Trace1( const mth::ray<DBL> &R )
    {
      mth::vec3<DBL> L(0, 0, 0);
      mth::vec3<DBL> color(1, 0, 0);
      L.Normalize();
      intr in;
      if (Intersect(R, &in))
      {
        in.Shp->GetNormal(&in);
        in.N.Normalize();
        DBL n1 = L & in.N;
        if (n1 < 0.1)
          n1 = 0.1;
        color *= n1;
        mth::ray<DBL> shd(in.P + Threshold, L);

        if (IsIntersect(shd, &in))
          color = mth::vec3<DBL>(0, 0, 0);
        return color;
      }
      return mth::vec3<DBL>(0.2, 0.2, 0.2);
    } 
    
    /* Render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      INT n = std::thread::hardware_concurrency() - 2;
     
      std::vector<std::thread> Thr;
      Thr.resize(n);
      for (int i = 0; i < n; i++)
      {
        Thr[i] = std::thread([&, i]( VOID )
          {
            for (int y = i; y < Frm.H; y += n)
              for (int x = 0; x < Frm.W; x++)
              {
                mth::ray<DBL> r; 
                r = Cam.FrametoRay(x + 0.5, y - 0.5);
                mth::vec3<DBL> color = Trace(r, Air, Weight);
                Frm.PutPixel(x, y, color.Dword());
              } 
          });
      }
      for (int i = 0; i < n; i++)
        Thr[i].join();
     //  Flg = TRUE;
    } /* End of 'Render' function */
 
    /* Adding new element to array function.
     * ARGUMENTS: 
     *   - new element reference
     *       const Type &x;
     * RETURNS: 
     *   (stock &) reference to stock.
     */
    VOID operator<<( shape *x )
    {
      Shapes << x;
    } /* End of 'operator<<' function */

    /* Intersection function
     * ARGUMENTS:
     *   - ray
     *       const ray<DBL> &R;
     *   - intr
     *       const vec<Type> &D;
     * RETURNS:
     *   (BOOL) if intersected - TRUE, else - FALSE.
     */
    BOOL Intersect( const mth::ray<DBL> &R, intr *Intr )
    {
      intr best_in(0, nullptr);
      Shapes.Walk([&](shape *Shp)
        {
          intr in;

            if (Shp->Intersect(R, &in))
              if (best_in.Shp == nullptr || best_in.T > in.T)
                best_in = in;
        });
      *Intr = best_in;
      return best_in.Shp != nullptr;
    } /* End of 'Intersect' function */

    /* Intersection function
     * ARGUMENTS:
     *   - ray
     *       const ray<DBL> &R;
     *   - intr
     *       const vec<Type> &D;
     * RETURNS:
     *   (BOOL) if intersected - TRUE, else - FALSE.
     */
    BOOL IsIntersect( const mth::ray<DBL> &R, intr *Intr )
    {
      BOOL IsIntr = FALSE;
      Shapes.Walk([&](shape *Shp)
        {
          intr in;          
          if (Shp->Intersect(R, &in))
            IsIntr = TRUE;
        });
      return IsIntr;
    } /* End of 'Intersect' function */

    /* Scene destructor function */
    ~scene( VOID )
    {
     Shapes.Walk([](shape *Shp)
       {
          delete Shp;
       });
    }
  };
}
#endif /* __rt_h_ */

  /* END OF 'rt.h' FILE */