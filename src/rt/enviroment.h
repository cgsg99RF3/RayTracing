/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : enviroment.h
  * PURPOSE     : Raytracing project.
  *               Enviroment declaration  module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 23.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __enviroment_h_
#define __enviroment_h_

#include "def.h"

namespace rirt
{
  class shape;
  class surface
  {
  public:
    mth::vec3<DBL> Ka, Kd, Ks; // ambient, diffuse, specular
    DBL Ph;                    // Bui Tong Phong coefficient
    DBL Kr, Kt;                // reflected, transmitted

    /* Surface cinstructor function.
     * ARGUMENTS: None.
     */
    surface( VOID )
    {
    } /* End of 'surface' constructor */

    /* Surface cinstructor function.
     * ARGUMENTS:
     *   - default cofficients
     *       mth::vec3<DBL> NewKa, NewKd, NewKs;
     *   - other cofficients
     *       DBL Ph, Kr, Kt;
     */
    surface( mth::vec3<DBL> NewKa, mth::vec3<DBL> NewKd, mth::vec3<DBL> NewKs,
             DBL NewPh, DBL NewKr, DBL NewKt ) : Ka(NewKa), Kd(NewKd), Ks(NewKs), 
                                                 Ph(NewPh), Kr(NewKr), Kt(NewKt)
    {
    } /* End of 'surface' function */
  };
  
  class envi
  {
  public:
    DBL
      RefractionCoef,  // Refraction coefficient
      Decay;           // Environment media decay coefficient
  };
  
  class light_info
  {
  public:
    mth::vec3<DBL> L;       // light source direction
    mth::vec3<DBL> Color;   // light source color
    DBL Dist;               // distance to light source
  };
 
  class light
  {
  public:
    DBL Cc, Cl, Cq;   // Attenuation coefficients
    light_info LtI;   // Light information
    
    /* Light constructor function.
     * ARGUMENTS: None.
     */
    light( VOID )
    {
    } /* End of 'light' function */

    /* Light constructor function.
     * ARGUMENTS: 
     *   - attenuation cofficients
     *       DBL NewCc, NewCl, NewCq;
     *   - light information
     *       light_info NewLtI;
     */
    light( DBL NewCc, DBL NewCl, DBL NewCq, light_info NewLtI ) : Cc(NewCc), Cl(NewCl), Cq(NewCq), LtI(NewLtI)
    {
    } /* End of 'light' function */
                                           
    /* Light constructor function.
     * ARGUMENTS: 
     *   - attenuation cofficients
     *       DBL NewCc, NewCl, NewCq;
     *   - light information
     *         mth::vec3<DBL> NewL, NewColor, DBL NewDist;
     */
    light( DBL NewCc, DBL NewCl, DBL NewCq, mth::vec3<DBL> NewL, mth::vec3<DBL> NewColor, DBL NewDist ) : Cc(NewCc), Cl(NewCl), Cq(NewCq)
    {
      LtI.L = NewL;
      LtI.Color = NewColor;
      LtI.Dist = NewDist;
    } /* End of 'light' function */
    //virtual DBL Shadow( const mth::vec3<DBL> &P, light_info *L );
  };
  /* Shading store info type */
  struct shade_info
  {
    mth::vec3
    <DBL> P;       // Point of shading evaluation
    mth::vec3<DBL> N;       // Point normal
    shape *Shp;             // Shape pointer
    surface Surf;           // Surface material
    envi Media;             // Oobject media environment
    mth::vec3<DBL> Du, Dv;  // Tangent vectors
  };

  class modifier
  {
  public:

    /* Modifier destructor */
    virtual ~modifier( VOID )
    {
    } /* End of '~modifier' function */

    /* Modifier application function
    * ARGUMENTS:
    *   - shade information
    *       shade_info *Sh;
    * RETURNS: None.
    */
    virtual VOID Apply( shade_info *Sh )
    {
    } /* End of 'Apply' function */
  };
 
  class checker : public modifier
  {
  public:
   /* Modifier application function
    * ARGUMENTS:
    *   - shade information
    *       shade_info *Sh;
    * RETURNS: None.
    */
    VOID Apply( shade_info *Sh ) override
    {
      //Sh->Surf.Kd = Sh->Surf.Ka + (Sh->Surf.Ka - Sh->Surf.Kd) * ((1 + sin(sqrt(Sh->P.X * Sh->P.X + Sh->P.Y * Sh->P.Y))) / 2);
      Sh->Surf.Kd = (((INT(Sh->P.Z) ^ INT(Sh->P.Y) ^ INT(Sh->P.Z)) & 1) ? mth::vec3<DBL>(1) : mth::vec3<DBL>(0));
    } /* End of 'Apply' function */
  };
}
#endif /* __enviroment_h_ */

/* END OF 'enviroment.h' FILE */