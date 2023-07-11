/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : mth_vec2.h
  * PURPOSE     : Ray tracing project.
  *               Vec2 declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 24.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include "mthdef.h"
#include "mth_matr.h"

 // Space math namespace 
namespace mth
{
  // 2D vector representation type
  template<typename Type>
  class vec2
  {
  private:
    Type X, Y;  // Vector coordinates 
  public:
    /* Vector2 constructor function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    vec2( VOID ) : X(0), Y(0)
    {
    } /* End of 'vec2' function */

    /* Vector2 constructor function.
     * ARGUMENTS:
     *   - vector coordinates
     *       Type NewX, NewY;
     */
    vec2( Type NewX, Type NewY ) : X(NewX), Y(NewY)
    {
    } /* End of 'vec2' function */

    /* Vector2 constructor function.
     * ARGUMENTS:
     *   - vector coordinates
     *       Type NewN;
     */
    vec2( Type NewN ) : X(NewN), Y(NewN)
    {
    } /* End of 'vec2' function */

    /* Vector coords referense get function.
     * ARGUMENTS: None.
     */
    operator const Type*( VOID ) const
    {
      return &X;
    } /* End of 'operator Type*' function */

    /* Vector addition function.
     * ARGUMENTS:
     *   - reference to adding vector
     *       const vec2 &V;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec2 operator+( const vec2 &V ) const
    {
      return vec2(X + V.X, Y + V.Y);
    } /* End of 'operator+' function */

    /* Vector substructon function.
     * ARGUMENTS:
     *   - reference to substructing vector
     *       const vec2 &V;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec2 operator-( const vec2 &V ) const
    {
      return vec2(X - V.X, Y - V.Y);
    } /* End of 'operator-' function */

    /* Vector number multiplication function.
     * ARGUMENTS:
     *   - multiplying number
     *       const Type N;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator*( const Type N ) const
    {
      return vec2(X * N, Y * N);
    } /* End of 'operator*' function */

    /* Vector number division function.
     * ARGUMENTS:
     *   - dividing number
     *       const Type N;
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator/( const Type N ) const
    {
      return vec2(X / N, Y / N);
    } /* End of 'operator/' function */

    /* Negative vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) result vector.
     */
    vec2 operator-( VOID ) const
    {
      return vec2(X * (-1), Y * (-1));
    } /* End of 'operator-' function */

    /* Dot vector function.
     * ARGUMENTS:
     *   - reference to vector to dot
     *       const vec2 &V;
     * RETURNS:
     *   (FLT) result number.
     */
    FLT operator&( const vec2 &V ) const
    {
      return (X * V.X + Y * V.Y);
    } /* End of 'operator&' function */

    /* Vector length function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (FLT) result length.
     */
    FLT operator!( VOID ) const
    {
      return sqrt(X * X + Y * Y);
    } /* End of 'operator!' function */

    /* Vector component multiplication function.
     * ARGUMENTS:
     *   - reference to vector
     *       const vec2 &V;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec2 operator*( const vec2 &V ) const
    {
      return vec2(X * V.X, Y * V.Y);
    } /* End of 'operator*' function */

    /* Vector addition function.
     * ARGUMENTS:
     *   - reference to vector
     *       const vec2 &V;
     * RETURNS:
     *   (vec2 &) reference to result vector.
     */
    vec2 & operator+=( const vec2 &V )
    {
      *this = *this + V;
      return *this;
    } /* End of 'operator+=' function */

    /* Vector substruction function.
     * ARGUMENTS:
     *   - reference to vector
     *       const vec2 &V;
     * RETURNS:
     *   (vec2 &) reference to result vector.
     */
    vec2 & operator-=( const vec2 &V )
    {
      *this = *this - V;
      return *this;
    } /* End of 'operator-=' function */

    /* Vector multiplication function.
     * ARGUMENTS:
     *   - reference to vector
     *       const vec2 &V;
     * RETURNS:
     *   (vec2 &) reference to result vector.
     */
    vec2 & operator*=( const vec2 &V )
    {
      *this = *this * V;
      return *this;
    } /* End of 'operator*=' function */

    /* Vector to number multiplication function.
     * ARGUMENTS:
     *   - number
     *       const Type N;
     * RETURNS:
     *   (vec2 &) reference to result vector.
     */
    vec2 & operator*=( const Type N )
    {
      *this = *this * N;
      return *this;
    } /* End of 'operator*=' function */

    /* Square vector length function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (FLT) length.
     */
    FLT Length2( VOID ) const
    {
      return *this & *this;
    } /* End of 'Length2' function */

    /* Vector normalize function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2 &) reference to result vector.
     */
    vec2 & Normalize( VOID )
    {
      FLT len = *this & *this;

      if (len == 1 || len == 0)
        return *this;
      return *this /= sqrt(len);
    } /* End of 'Normalize' function */

    /* Vector normalizing function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) reference to result vector.
     */
    vec2 Normalizing( VOID ) const
    {
      FLT len = *this & *this;
      vec2 V = *this;

      if (len == 1 || len == 0)
        return V;
      return V / sqrt(len);
    } /* End of 'Normalize' function */

    /* Vector distance function.
     * ARGUMENTS:
     *   - reference to vector
     *       const vec2 &P;
     * RETURNS:
     *   (FLT) distance.
     */
    FLT Distance(const vec2 &P) const
    {
      vec3 V = *this - P;
      return !V;
    } /* End 'Distance' function */

    /* Random vector in range <1, 2> function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) random vector.
     */
    vec2 Rnd1( VOID ) const
    {
      return vec2(2.0 * rand() / RAND_MAX - 1, 2.0 * rand() / RAND_MAX - 1);
    } /* End 'Rnd1' function */

    /* Random vector in range <0, 1> function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) random vector.
     */
    vec2 Rnd0( VOID ) const
    {
      return vec2(rand() / (FLT)RAND_MAX, rand() / (FLT)RAND_MAX);
    } /* End 'Rnd0' function */

    /* Vector set (0, 0, 0) function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2 &) reference to result vector.
     */
    vec2 & Zero( VOID )
    {
      return *this = vec2(0, 0);
    } /* End 'Zero' function */

    /* Vector coordinate get function.
     * ARGUMENTS:
     *   - coordinate number
     *       const INT N;
     * RETURNS:
     *   (Type &) reference to result coordinate.
     */
    Type & operator[]( const INT N )
    {
      if (N == 0)
        return X;
      return Y;
    } /* End 'operator[]' function */

    /* Vector coordinate get function.
     * ARGUMENTS:
     *   - coordinate number
     *       const INT N;
     * RETURNS:
     *   (Type &) reference to result coordinate.
     */
    Type operator[]( const INT N ) const
    {
      if (N == 0)
        return X;
      return Y;
    } /* End 'operator[]' function */
  }; 
}
   

#endif /* __mth_vec2_h_ */