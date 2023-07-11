/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : mth_matr.h
  * PURPOSE     : Ray tracing project.
  *               Matrix declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 24.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mthdef.h"

// Space math namespace 
namespace mth
{
  // Matrix representation type
  template<typename Type>
  class matr
  {
    template<typename Type>
      friend class vec3;
  private:
    Type M[4][4]; // Matrix coordinates array
    mutable Type InvM[4][4];
    mutable BOOL IsInverseIvaluated;
   
  public:
    /* Vector coords referense get function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    operator Type*( VOID )
    {
      return &M[0][0];
    } /* End of 'operator Type*' function */

    /* Matrix constructor function.
      * ARGUMENTS: None.
     * RETURNS: None.
     */
    matr( VOID ) : M{{0}}
    {
    } /* End of 'matr' function */

    /* Matrix constructor function.
     * ARGUMENTS: 
     *   - matrix coordinates:
     *        Type M00, Type M01, Type M02, Type M03,
              Type M10, Type M11, Type M12, Type M13,
              Type M20, Type M21, Type M22, Type M23,
              Type M30, Type M31, Type M32, Type M33
     * RETURNS: None.
     */
    matr( Type M00, Type M01, Type M02, Type M03,
          Type M10, Type M11, Type M12, Type M13,
          Type M20, Type M21, Type M22, Type M23,
          Type M30, Type M31, Type M32, Type M33 ) :
      M{
        {M00, M01, M02, M03}, 
        {M10, M11, M12, M13},
        {M20, M21, M22, M23}, 
        {M30, M31, M32, M33}
       }
    {
    } /* End of 'matr' function */

    /* Coping Matrix constructor function.
     * ARGUMENTS:
     *   - matrix array
     *       Type A[4][4]
     * RETURNS: None.
     */
    matr( Type A[4][4] ) : M(A)
    {
    } /* End of 'matr' function */

  private:
    /* Matrix 3x3 determinatar counting function.
     * ARGUMENTS:
     *   - matrix coordinates
     *       Type A11, A12, A13,
                  A21, A22, A23,
                  A31, A32, A33
     * RETURNS:
     *   (Type) result number.
     */
    Type MatrDeterm3x3( Type A11, Type A12, Type A13,
                        Type A21, Type A22, Type A23,
                        Type A31, Type A32, Type A33 ) const
    {
      return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
             A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
    } /* End of 'MatrDeterm3x3' function */
  public:

    /* Counting of matrix determinatar function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result number.
     */
    Type operator!( VOID ) const
    {
      return
        +M[0][0] * MatrDeterm3x3(M[1][1], M[1][2], M[1][3],
                                 M[2][1], M[2][2], M[2][3],
                                 M[3][1], M[3][2], M[3][3]) +
        -M[0][1] * MatrDeterm3x3(M[1][0], M[1][2], M[1][3],
                                 M[2][0], M[2][2], M[2][3],
                                 M[3][0], M[3][2], M[3][3]) +
        +M[0][2] * MatrDeterm3x3(M[1][0], M[1][1], M[1][3],
                                 M[2][0], M[2][1], M[2][3],
                                 M[3][0], M[3][1], M[3][3]) +
        -M[0][3] * MatrDeterm3x3(M[1][0], M[1][1], M[1][2],
                                 M[2][0], M[2][1], M[2][2],
                                 M[3][0], M[3][1], M[3][2]);
    } /* End of 'operator!' function */

    /* Matrix identification function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (matr) result matrix.
     */
    matr Identity( VOID )
    {
      return matr(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1);
    } /* End of 'Identity' function */

    /* Matrix multiplication function
     * ARGUMENTS:
     *   - matrix reference to multiplicate
     *       const matr &A;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr operator*( const matr &A ) const
    {
      matr r;

      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          for (int k = 0; k < 4; k++)
            r.M[i][j] += M[i][k] * A.M[k][j];
      return r;
    } /* End of 'operator*' function */

    /* Matrix inverse function
     * ARGUMENTS: None.
     * RETURNS:
     *   (matr) result matrix.
     */
    matr Inverse( VOID ) const
    {
      FLT det = !(*this);
      matr r;

      if (det == 0)
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);

      /* build adjoint matrix */
      r.M[0][0] =
        +MatrDeterm3x3(M[1][1], M[1][2], M[1][3],
                       M[2][1], M[2][2], M[2][3],
                       M[3][1], M[3][2], M[3][3]) / det;
      r.M[1][0] =
        -MatrDeterm3x3(M[1][0], M[1][2], M[1][3],
                       M[2][0], M[2][2], M[2][3],
                       M[3][0], M[3][2], M[3][3]) / det;
      r.M[2][0] =
        +MatrDeterm3x3(M[1][0], M[1][1], M[1][3],
                       M[2][0], M[2][1], M[2][3],
                       M[3][0], M[3][1], M[3][3]) / det;
      r.M[3][0] =
        -MatrDeterm3x3(M[1][0], M[1][1], M[1][2],
                       M[2][0], M[2][1], M[2][2],
                       M[3][0], M[3][1], M[3][2]) / det;

      r.M[0][1] =
        -MatrDeterm3x3(M[0][1], M[0][2], M[0][3],
                       M[2][1], M[2][2], M[2][3],
                       M[3][1], M[3][2], M[3][3]) / det;
      r.M[1][1] =
        +MatrDeterm3x3(M[0][0], M[0][2], M[0][3],
                       M[2][0], M[2][2], M[2][3],
                       M[3][0], M[3][2], M[3][3]) / det;
      r.M[2][1] =
        -MatrDeterm3x3(M[0][0], M[0][1], M[0][3],
                       M[2][0], M[2][1], M[2][3],
                       M[3][0], M[3][1], M[3][3]) / det;
      r.M[3][1] =
        +MatrDeterm3x3(M[0][0], M[0][1], M[0][2],
                       M[2][0], M[2][1], M[2][2],
                       M[3][0], M[3][1], M[3][2]) / det;

      r.M[0][2] =
        +MatrDeterm3x3(M[0][1], M[0][2], M[0][3],
                       M[1][1], M[1][2], M[1][3],
                       M[3][1], M[3][2], M[3][3]) / det;
      r.M[1][2] =
        -MatrDeterm3x3(M[0][0], M[0][2], M[0][3],
                       M[1][0], M[1][2], M[1][3],
                       M[3][0], M[3][2], M[3][3]) / det;
      r.M[2][2] =
        +MatrDeterm3x3(M[0][0], M[0][1], M[0][3],
                       M[1][0], M[1][1], M[1][3],
                       M[3][0], M[3][1], M[3][3]) / det;
      r.M[3][2] =
        -MatrDeterm3x3(M[0][0], M[0][1], M[0][2],
                       M[1][0], M[1][1], M[1][2],
                       M[3][0], M[3][1], M[3][2]) / det;

      r.M[0][3] =
        -MatrDeterm3x3(M[0][1], M[0][2], M[0][3],
                       M[1][1], M[1][2], M[1][3],
                       M[2][1], M[2][2], M[2][3]) / det;
      r.M[1][3] =
        +MatrDeterm3x3(M[0][0], M[0][2], M[0][3],
                       M[1][0], M[1][2], M[1][3],
                       M[2][0], M[2][2], M[2][3]) / det;
      r.M[2][3] =
        -MatrDeterm3x3(M[0][0], M[0][1], M[0][3],
                       M[1][0], M[1][1], M[1][3],
                       M[2][0], M[2][1], M[2][3]) / det;
      r.M[3][3] =
        +MatrDeterm3x3(M[0][0], M[0][1], M[0][2],
                       M[1][0], M[1][1], M[1][2],
                       M[2][0], M[2][1], M[2][2]) / det;
      return r;
    } /* End of 'Inverse' function */
  private:
    /* Realisation of swapping function
     * ARGUMENTS:
     *   - Swapping numbers
     *       Type a, b;
     * RETURNS: None.
     */
    VOID Swap1( Type a, Type b ) const
    {
      double tmp = a;

      a = b;
      b = tmp;
    } /* End of 'Swap1' function */
  public:
    /* Matrix transposition function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (matr) result matrix.
     */
    matr Transpose( VOID ) const
    {
      matr A = *this;

      Swap1(A.M[0][1], A.M[1][0]);
      Swap1(A.M[0][2], A.M[2][0]);
      Swap1(A.M[0][3], A.M[3][0]);
      Swap1(A.M[1][2], A.M[2][1]);
      Swap1(A.M[1][3], A.M[3][1]);
      Swap1(A.M[2][3], A.M[3][2]);
      return A;
    } /* End of 'Transpose' function */

    /* Inversed transponsed matrix get function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EvaluateInverseMatrix( VOID ) const
    {
      if (IsInverseIvaluated)
        return;
      IsInverseIvaluated = true;

      matr A = Transpose();
      A = A.Inverse();
      InvM = A.M;
    } /* End of 'EvaluateInverseMatrix' function */


    /* Matrix rotation function.
     * ARGUMENTS:
     *   - angle of rotation
     *       const FLT AngleInDegree;
     *   - reference to vector of rotation
     *       const vec3 <Type>&V
     * RETURNS:
     *   (MATR) result matrix.
     */
    matr Rotate( const FLT AngleInDegree, const vec3<Type> &V ) const 
    {
      FLT a = D2R(AngleInDegree), s = sin(a), c = cos(a);
      vec3<Type> A = V.Normalizing();

      return matr(c + A.X * A.X * (1 - c), 
                  A.X * A.Y * (1 - c) + A.Z * s, 
                  A.X * A.Z * (1 - c) - A.Y * s, 
                  0,
                  A.Y * A.X * (1 - c) - A.Z * s,
                  c + A.Y * A.Y * (1 - c), 
                  A.Y * A.Z * (1 - c) + A.X * s , 
                  0,
                  A.Z * A.X * (1 - c) + A.Y * s, 
                  A.Z * A.Y * (1 - c) - A.X * s,
                  c + A.Z * A.Z * (1 - c), 0,
                  0, 0, 0, 1);
    }
    /* End of 'Rotate' function */

    /* Matrix X rotation function.
     * ARGUMENTS:
     *   - angle of rotation
     *       const FLT AngleInDegree;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr RotateX( const FLT AngleInDegree ) const
    {
      matr m(1, 0, 0, 0,
             0, cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0,
             0, -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0,
             0, 0, 0, 1);
      return m;
    } /* End of 'RotateX' function */

    /* Matrix Y rotation function.
     * ARGUMENTS:
     *   - angle of rotation
     *       const FLT AngleInDegree;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr RotateY( const FLT AngleInDegree ) const
    {
      matr m(cos(D2R(AngleInDegree)), 0, -sin(D2R(AngleInDegree)), 0,
             0, 1, 0, 0,
             sin(D2R(AngleInDegree)), 0, cos(D2R(AngleInDegree)), 0,
             0, 0, 0, 1);
      return m;
    } /* End of 'MatrRotateY' function */

    /* Matrix Z rotation function.
     * ARGUMENTS:
     *   - Angle of rotation
     *       const FLT AngleInDegree;
     * RETURNS:
     *   (MATR) result matrix.
     */
    matr RotateZ( const FLT AngleInDegree ) const
    {
      return matr(cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0, 0, 
                  -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0, 0, 
                  0, 0, 1, 0, 
                  0, 0, 0, 1);
    } /* End of 'RotateZ' function */

    /* Scale function.
     * ARGUMENTS:
     *   - scale vector reference
     *       const vec3<Type> &V;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr Scale( const vec3<Type> &V ) const
    {
      return matr(V.X, 0, 0, 0,
                  0, V.Y, 0, 0, 
                  0, 0, V.Z, 0, 
                  0, 0, 0, 1);
    } /* End of 'Scale' function */

    /* Matrix translation function.
     * ARGUMENTS:
     *   - vector to translate
     *       const vec3<Type> &V;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr Translate( const vec3<Type> &V ) const
    {
      return matr(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  V.X, V.Y, V.Z, 1);
    } /* End of 'Translate' function */

    /* Matrix frustum function.
     * ARGUMENTS:
     *    - coordinates
     *        const FLT l, r, b, t, n, f;
     * RETURNS:
     *   (matr) result matrix.
     */
    matr Frustum( const FLT l, const FLT r, const FLT b, 
                  const FLT t, const FLT n, const FLT f )
    {
      return matr(2 * n / (r - l), 0, 0, 0,
                  0, 2 * n / (t - b), 0, 0,
                  (r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1,
                  0, 0, -2 * n * f / (f - n), 0);
    } /* End of 'Frustum' function */
  };
}

#endif /* __mth_matr_h_ */

/* END OF 'mth_matr.h' FILE */