/* FILE NAME: mthdef.h
 * PURPOSE: 3D animation project.
 *          Math declaration module.
 * PROGRAMMER: RF3
 * LAST UPDATE: 22.07.2022
 */

#ifndef __mthdef_h_
#define __mthdef_h_

#include <cmath>
#include "commondf.h"

#define PI 3.14159265359
#define D2R(A) ((A) * PI / 180.0)
#define Degree2Radian(A) D2R(A)
#define R2D(A) ((A) * 180.0 / PI)
#define Radian2Degree(A) R2D(A)

typedef DOUBLE DBL;
typedef FLOAT FLT;

template<typename Type> class vec3;
template<typename Type> class vec2;
template<typename Type> class matr;
template<typename Type> class ray;
template<typename Type> class camera;

#endif /* __mthdef_h_ */

/* END OF 'mthdef.h' FILE */