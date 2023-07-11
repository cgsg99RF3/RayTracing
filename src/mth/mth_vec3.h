/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : mth_vec3.h
  * PURPOSE     : Ray tracing project.
  *               Vec3 declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 24.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mthdef.h"
#include "mth_matr.h"

 // Space math namespace 
namespace mth
{
  // 3D vector representation type
  template<typename Type>
  class vec3
  {
    template<typename Type>
      friend class matr;
  public:
    Type X, Y, Z;  // Vector coordinates 
   
    /* Vector3 constructor function.
     * ARGUMENTS: None.
     */
    vec3( VOID ) : X(0), Y(0), Z(0)
    {
    } /* End of 'vec3' function */

    /* Vector3 constructor function.
     * ARGUMENTS:
     *   - vector coordinates
     *       Type NewX, NewY NewZ;
     */
    vec3( Type NewX, Type NewY, Type NewZ ) : X(NewX), Y(NewY), Z(NewZ)
    {
    } /* End of 'vec3' function */

    /* Vector3 constructor function.
     * ARGUMENTS:
     *   - vector coordinates
     *       Type NewN;
     */
    vec3( Type NewN ) : X(NewN), Y(NewN), Z(NewN)
    {
    } /* End of 'vec3' function */

    /* Vector coords referense get function.
     * ARGUMENTS: None.
     */
    operator Type *( VOID )
    {
      return &X;
    } /* End of 'operator Type *' function */

    /* Vector coords referense get function.
     * ARGUMENTS: None.
     */
    operator const Type *( VOID ) const
    {
      return &X;
    } /* End of 'operator Type *' function */

    /* Clamp vec color function.
     * ARGUMENTS:
     *   - color coordinate
     *       Type x;
     *   - minimum and maximum coordinate value
     *       Type min, max;
     * RETURNS:
     *   (Type) result coord.
     */
    Type Clamp( Type x, Type min = 0, Type max = 1 )
    {
      return x < min ? min : x > max ? max : x; 
    } /* End of 'Clamp' function */

    /* DWORD coloor creation function.
     * ARGUMENTS: None.
     */
    DWORD Dword( VOID )
    {
      Type X2 = X, Y2 = Y, Z2 = Z;
      BYTE
        r = Clamp(X2) * 255,
        g = Clamp(Y2) * 255,
        b = Clamp(Z2) * 255,
        a = 255;
      return (a << 24) | (r << 16) | (g << 8) | b;    
    } /* End of 'DWORD' function */

    /* Vector minimal coord function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result coord.
     */
    Type Min( VOID ) const
    {
     // return vec3(X + V.X, Y + V.Y, Z + V.Z);
    } /* End of 'operator+' function */

    /* Vector addition function.
     * ARGUMENTS:
     *   - reference to adding vector
     *       const vec3 &V;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3 operator+( const vec3 &V ) const
    {
      return vec3(X + V.X, Y + V.Y, Z + V.Z);
    } /* End of 'operator+' function */

    /* Vector substructon function.
     * ARGUMENTS:
     *   - reference to substructing vector
     *       const vec3 &V;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3 operator-( const vec3 &V ) const
    {
      return vec3(X - V.X, Y - V.Y, Z - V.Z);
    } /* End of 'operator-' function */

    /* Vector number multiplication function.
     * ARGUMENTS:
     *   - multiplying number
     *       const Type N;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3 operator*( const Type N ) const
    {
      return vec3(X * N, Y * N, Z * N);
    } /* End of 'operator*' function */

    /* Vector number division function.
     * ARGUMENTS:
     *   - dividing number
     *       const Type N;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3 operator/( const Type N ) const
    {
      return vec3(X / N, Y / N, Z / N);
    } /* End of 'operator/' function */

    /* Negative vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3 operator-( VOID ) const
    {
      return vec3(X * (-1), Y * (-1), Z * (-1));
    } /* End of 'operator-' function */

    /* Dot vector function.
     * ARGUMENTS:
     *   - reference to vector to dot
     *       const vec3 &V;
     * RETURNS:
     *   (FLT) result number.
     */
    FLT operator&( const vec3 &V ) const
    {
      return (X * V.X + Y * V.Y + Z * V.Z);
    } /* End of 'operator&' function */

    /* Vector length function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result length.
     */
    Type operator!( VOID ) const
    {
     // if (std::is_same_v<Type, FLT>)
       // return sqrtf(X * X + Y * Y + Z * Z);
      return sqrt(X * X + Y * Y + Z * Z);
    } /* End of 'operator!' function */

    /* Vector component multiplication function.
     * ARGUMENTS:
     *   - reference to vector
     *       const vec3 &V;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3 operator*( const vec3 &V ) const
    {
      return vec3(X * V.X, Y * V.Y, Z * V.Z);
    } /* End of 'operator*' function */

    /* Vector addition function.
     * ARGUMENTS:
     *   - reference to vector
     *       const vec3 &V;
     * RETURNS:
     *   (vec3 &) reference to result vector.
     */
    vec3 & operator+=( const vec3 &V )
    {
      *this = *this + V;
      return *this;
    } /* End of 'operator+=' function */

    /* Vector substruction function.
     * ARGUMENTS:
     *   - reference to vector
     *       const vec3 &V;
     * RETURNS:
     *   (vec3 &) reference to result vector.
     */
    vec3 & operator-=( const vec3 &V )
    {
      *this = *this - V;
      return *this;
    } /* End of 'operator-=' function */

    /* Vector multiplication function.
     * ARGUMENTS:
     *   - reference to vector
     *       const vec3 &V;
     * RETURNS:
     *   (vec3 &) reference to result vector.
     */
    vec3 & operator*=( const vec3 &V )
    {
      *this = *this * V;
      return *this;
    } /* End of 'operator*=' function */

    /* Vector to number multiplication function.
     * ARGUMENTS:
     *   - number
     *       const Type &N;
     * RETURNS:
     *   (vec3 &) reference to result vector.
     */
    vec3 & operator*=( const Type N )
    {
      *this = *this * N;
      return *this;
    } /* End of 'operator*=' function */

    /* Vector cross function.
     * ARGUMENTS:
     *   - reference to vecor
     *       const Type &V;
     * RETURNS:
     *   (vec3) reference to result vector.
     */
    vec3 operator%( const vec3 &V ) const
    {
      return vec3(Y * V.Z - V.Y * Z, (-1)* (X * V.Z - V.X * Z), X * V.Y - V.X * Y);
    } /* End of 'operator%' function */

    /* Square vector length function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) length.
     */
    Type Length2( VOID ) const
    {
      return *this & *this;
    } /* End of 'Vec3Length2' function */

    /* Vector number division function.
     * ARGUMENTS:
     *   - dividing number
     *       const Type N;
     * RETURNS:
     *   (vec3) result vector.
     */
    vec3 & operator/=( const Type N ) 
    {
      X /= N, Y /= N, Z /= N;
      return *this;
    } /* End of 'operator/' function */
    /* Vector normalize function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3 &) reference to result vector.
     */
    vec3 & Normalize( VOID ) 
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
    vec3 Normalizing( VOID ) const
    {
      FLT len = *this & *this;
      vec3 V = *this;

      if (len == 1 || len == 0)
        return V;
      return V / sqrt(len);
    } /* End of 'Normalize' function */
 
    /* Vector distance function.
     * ARGUMENTS: 
     *   - reference to vector
     *       const vec3 &P;
     * RETURNS:
     *   (FLT) distance.
     */
    FLT Distance( const vec3 &P ) const
    {
      vec3 V = *this - P;
      return !V;
    } /* End 'Distance' function */

    /* Random vector in range <1, 2> function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) random vector.
     */
    vec3 Rnd1( VOID ) const
    {
      return vec3(2.0 * rand() / RAND_MAX - 1, 2.0 * rand() / RAND_MAX - 1, 2.0 * rand() / RAND_MAX - 1);
    } /* End 'Rnd1' function */

    /* Random vector in range <0, 1> function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) random vector.
     */
    vec3 Rnd0( VOID ) const
    {
      return vec3(rand() / (FLT)RAND_MAX, rand() / (FLT)RAND_MAX, rand() / (FLT)RAND_MAX);
    } /* End 'Rnd0' function */

    /* Vector set (0, 0, 0) function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3 &) reference to result vector.
     */
    vec3 & Zero( VOID )
    {
      return *this = vec3(0, 0, 0);
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
      else if (N == 1)
        return Y;
      return Z;
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
      else if (N == 1)
        return Y;
      return Z;
    } /* End 'operator[]' function */

    /* Point transformation vector function
     * ARGUMENTS:
     *   - matrix of transformation
     *       const matr<Type> &M;
     * RETURNS:
     *   (vec3) result matrix.
     */
    vec3 TransformPoint( const matr<Type> &M ) const
    {
      return vec3((X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[2][0] + M.M[3][0]),
                  (X * M.M[0][1] + Y * M.M[1][1] + Z * M.M[2][1] + M.M[3][1]),
                  (X * M.M[0][2] + Y * M.M[1][2] + Z * M.M[2][2] + M.M[3][2]));
    } /* End of 'TransformPoint' function */

    /* Vector transformation vector function
     * ARGUMENTS:
     *   - matrix of transformation
     *       const matr<Type> &M;
     * RETURNS:
     *   (vec3) result matrix.
     */
    vec3 TransformVector( const matr<Type> &M ) const
    {
      return vec3((X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[0][2]),
                  (X * M.M[1][0] + Y * M.M[1][1] + Z * M.M[1][2]),
                  (X * M.M[2][0] + Y * M.M[1][2] + Z * M.M[2][2]));
    } /* End of 'TransformVector' function */

    /* matrix 4x4 multiplication function.
     * ARGUMENTS:
     *   - matrix of transformation:
     *       const matr<Type> &M;
     * RETURNS:
     *   (VEC) result vector.
     */
    vec3 Transform4x4( const matr<Type> &M ) const
    {
      Type w = X * M.M[0][3] + Y * M.M[1][3] + Z * M.M[2][3] + M.M[3][3];

      return vec3((X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[2][0] + M.M[3][0]) / w,
                  (X * M.M[0][1] + Y * M.M[1][1] + Z * M.M[2][1] + M.M[3][1]) / w,
                  (X * M.M[0][2] + Y * M.M[1][2] + Z * M.M[2][2] + M.M[3][2]) / w);
    } /* End of 'Transform4x4' function */
  };
}

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */