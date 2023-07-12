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
    Win.Scene.Cam.Set(mth::vec3<DBL>(10, 30, 10), mth::vec3<DBL>(2, 10, 5), mth::vec3<DBL>(0, 1, 0));

    // Win.Scene << new rirt::light(0.5, 0.2, 0.7, mth::vec3<DBL>(5, 3, 20), mth::vec3<DBL>(1, 1, 1), 100);
    Win.Scene << new rirt::light(0.1, 0.3, 0.1, mth::vec3<DBL>(-3, 10, 0), mth::vec3<DBL>(0.1, 0.8, 0.1), 10);
    Win.Scene << new rirt::light(0.1, 0.2, 0.1, mth::vec3<DBL>(0, 5, 5), mth::vec3<DBL>(0.2, 0.1, 0.9), 10);
    //Win.Scene << new rirt::light(1, 0.6, 0.5, mth::vec3<DBL>(-2, 2, -3), mth::vec3<DBL>(1, 0.1, 0.1), 100);
    //Win.Scene << new rirt::light(3, 10, 2, mth::vec3<DBL>(0, 0, 0), mth::vec3<DBL>(1, 0.1, 0.1), 100);

    rirt::surface Surf(mth::vec3<DBL>(0.0, 0.0, 0.0), mth::vec3<DBL>(0.01, 0.01, 0.01), mth::vec3<DBL>(0.5, 0.5, 0.5), 1, 1, 30);
    rirt::surface Surf2(mth::vec3<DBL>(0.25, 0.20725, 0.20725), mth::vec3<DBL>(1.0, 0.829, 0.829), mth::vec3<DBL>(0.296648, 0.296648, 0.296648), 1, 0.01, 0.1);
    //shinig
    rirt::surface Surf3(mth::vec3<DBL>(0, 0, 0), mth::vec3<DBL>(1.0, 0.829, 0.829), mth::vec3<DBL>(0.296648, 0.296648, 0.296648), 1, 0.7, 0.1);
    // mate material
    rirt::surface Surf4(mth::vec3<DBL>(0.10588, 0.058824, 0.113725), mth::vec3<DBL>(0.427451, 0.470588, 0.541176), mth::vec3<DBL>(0.3333, 0.3333, 0.521569), /*9.84615*/1, 0.01, 0.1);
    //bad
    rirt::surface Surf5(mth::vec3<DBL>(0.329412, 0.223529, 0.027451), mth::vec3<DBL>(0.780392, 0.568627, 0.113725), mth::vec3<DBL>(0.992157, 0.941176, 0.807843), 0.097, 0.01, 0.1);
    //red
    rirt::surface Surf6(mth::vec3<DBL>(1, 0, 0), mth::vec3<DBL>(1, 0, 0), mth::vec3<DBL>(1, 0, 0), 0.1, 0.03, 0.1);

    Win.Scene << new rirt::plane<DBL>(mth::vec3<DBL>(-3), mth::vec3<DBL>(-3, -3, 0), mth::vec3<DBL>(2, -3, 0), Surf2);
   
    for (int j = 0; j < 4; j += 1)
        for (int i = 0; i < 4; i += 1)
        {
            if (i %2 == 0)
                Win.Scene << new rirt::sphere<DBL>(mth::vec3<DBL>(-4 + j + i, 4, 0 + i), 0.5, Surf3);
            else
                Win.Scene << new rirt::sphere<DBL>(mth::vec3<DBL>(-4 + j + i, 4, 0 + i), 0.5, Surf4);
        }
      
      // Win.Scene << new rirt::box<DBL>(mth::vec3<DBL>(-3, 3, 0), mth::vec3<DBL>(1, 7, 4), Surf6);
       //
   // Win.Scene << new rirt::sphere<DBL>(mth::vec3<DBL>(-1, 5, 2), 2, Surf6);
    //Win.Scene << new rirt::csg(new rirt::sphere<DBL>(mth::vec3<DBL>(-1, 5, 2), 2, Surf6), new rirt::sphere<DBL>(mth::vec3<DBL>(2, 5, 2), 2, Surf6));

    Win.Scene.Cam.Resize(1000, 1000);
    Win.Scene.Cam.ProjSet(0.1, 2, 1000);

    Win.Run();

}


/* END OF 'main.cpp' FILE */