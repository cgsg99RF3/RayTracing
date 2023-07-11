/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : ray.h
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

#ifndef __ray_h_
#define __ray_h_

#include "mthdef.h"

namespace mth
{
  template<typename Type>
  class ray
  {
  public:
    vec3<Type>
      Org,            // Ray origin 
      Dir;           // Ray direction
  
    /* Ray constructor function
     * ARGUMENTS: None.
     */
    ray( VOID )
    {
    } /* End of 'ray' function */
  
    /* Ray constructor function
     * ARGUMENTS:
     *   - origin
     *       const vec<Type> &O;
     *   - diraction
     *       const vec<Type> &D;
     */
    ray( const vec3<Type> &O, const vec3<Type> &D ) : Org(O), Dir(D.Normalizing())
    {
      Dir.Normalize();
    } /* End of 'ray' function */

  };
}

#endif /* __ray_h_ */
