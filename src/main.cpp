/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : win.h
  * PURPOSE     : Raytracing project.
  *               Main module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 23.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */
 
#include "win/rt_win.h"

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
  CHAR* CmdLine, INT ShowCmd )
{ 
  rirt::rt_win Win;
  //Win.Scene.Cam.Set(mth::vec3<DBL>(20, 20, 10), mth::vec3<DBL>(2, 3, 5), mth::vec3<DBL>(0, 1, 0));
  //Win.Scene.Cam.Set(mth::vec3<DBL>(0, 0, 4), mth::vec3<DBL>(0, 0, 0), mth::vec3<DBL>(0, 1, 0));
  Win.Scene.Cam.Set(mth::vec3<DBL>(20, 20, 30), mth::vec3<DBL>(2, 3, 5), mth::vec3<DBL>(0, 1, 0));
  
  Win.Scene << new rirt::light(1, 3, 0.7, mth::vec3<DBL>(-2, 3, 0), mth::vec3<DBL>(1, 1, 1), 100);
  Win.Scene << new rirt::light(0.1, 0.3, 0.7, mth::vec3<DBL>(-3, 4, 0), mth::vec3<DBL>(1, 1, 1), 100);
  Win.Scene << new rirt::light(0.1, 0.3, 0.7, mth::vec3<DBL>(0, 5, 5), mth::vec3<DBL>(0.2, 0.1, 0.5), 100);
  
  rirt::surface Surf(mth::vec3<DBL>(0.0, 0.0, 0.0), mth::vec3<DBL>(0.01, 0.01, 0.01), mth::vec3<DBL>(0.5, 0.5, 0.5), 1, 1, 30);
  rirt::surface Surf2(mth::vec3<DBL>(0.25, 0.20725, 0.20725), mth::vec3<DBL>(1.0, 0.829, 0.829), mth::vec3<DBL>(0.296648, 0.296648, 0.296648), 1, 0.01, 0.1);
  rirt::surface Surf3(mth::vec3<DBL>(0, 0, 0), mth::vec3<DBL>(1.0, 0.829, 0.829), mth::vec3<DBL>(0.296648, 0.296648, 0.296648), 3, 0.7, 0.1);
  rirt::surface Surf4(mth::vec3<DBL>(0.10588,0.058824,0.113725), mth::vec3<DBL>(0.427451,0.470588,0.541176), mth::vec3<DBL>(0.3333,0.3333,0.521569), /*9.84615*/1, 0.01, 0.1);
  rirt::surface Surf5(mth::vec3<DBL>(0.329412,0.223529,0.027451), mth::vec3<DBL>(0.780392,0.568627,0.113725), mth::vec3<DBL>(0.992157,0.941176,0.807843), 0.097, 0.01, 0.1);
  
  Win.Scene << new rirt::plane<DBL>(mth::vec3<DBL>(-3), mth::vec3<DBL>(-3, -3, 0), mth::vec3<DBL>(2, -3, 0), Surf3);

  //Win.Scene << new rirt::triangle(mth::vec3<DBL>(0), mth::vec3<DBL>(1, 0, 0), mth::vec3<DBL>(1, 1, 0));  
  //Win.Scene << new rirt::cylinder<DBL>(mth::vec3<DBL>(0, 3, 0), mth::vec3<DBL>(0, 1, 0), 2);
 
  //Win.Scene << new rirt::sphere<DBL>(mth::vec3<DBL>(-3, 1, 0), 1, Surf3);
  //Win.Scene << new rirt::box<DBL>(mth::vec3<DBL>(-2, 0, -2), mth::vec3<DBL>(2, 4, 2), Surf3);

  //Win.Scene << new rirt::csg(new rirt::box<DBL>(mth::vec3<DBL>(-3, 1, -1), mth::vec3<DBL>(1, 3, 1), Surf2), new rirt::sphere<DBL>(mth::vec3<DBL>(0, 2, 0), 2, Surf));

 // Win.Scene << new rirt::sphere<DBL>(mth::vec3<DBL>(0, 2, 0), 2, Surf4); 
  //for (int i = 0; i < 10; i += 3)
    ;//Win.Scene << new rirt::sphere<DBL>(mth::vec3<DBL>(0, 3, 0 + i ), 1, Surf2); 
  for (int j = 0; j < 2; j += 1)
    for (int i = 0; i < 2; i += 1)
      Win.Scene << new rirt::sphere<DBL>(mth::vec3<DBL>(-3 + j + i, 3, 0 + i ), 0.5, Surf3);
  
  //Win.Scene << new rirt::box<DBL>(mth::vec3<DBL>(-1), mth::vec3<DBL>(1), Surf2);
  // Win.Scene << new rirt::box<DBL>(mth::vec3<DBL>(3, 2, 3), mth::vec3<DBL>(2, 4, 2), Surf);
  //rirt::triangle Obj;
 // Obj.Load("Z:\\RF3\\T05RT\\cow.obj", Win.Scene.Shapes, Surf5);
  //Win.Scene << new rirt::sphere<DBL>(mth::vec3<DBL>(3, 11, 0), 1, Surf3); 
  
  //Win.Scene << new rirt::csg(new rirt::box<DBL>(mth::vec3<DBL>(-2, 1, -2), mth::vec3<DBL>(2, 3, 2), Surf2), new rirt::sphere<DBL>(mth::vec3<DBL>(0, 2, 0), 2, Surf));
  //Win.Scene << new rirt::csg(new rirt::sphere<DBL>(mth::vec3<DBL>(-1, 0, 0), 2, Surf), new rirt::sphere<DBL>(mth::vec3<DBL>(1, 0, 0), 2, Surf3));

  Win.Scene.Cam.Resize(1000, 1000);
  Win.Scene.Cam.ProjSet(0.1, 2, 1000);

  //Win.Scene << new rirt::cylinder<DBL>(mth::vec3<DBL>(1, 2, 1), mth::vec3<DBL>(1, 0, 0), 1);

  Win.Run();
}


/* END OF 'main.cpp' FILE */