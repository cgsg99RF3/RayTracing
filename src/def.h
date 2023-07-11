/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : def.h
  * PURPOSE     : Raytracing project.
  *               Declaration module.
  * PROGRAMMER  : CGSG-SummerCamp'2022.
  *               Rimma Filatova.
  * LAST UPDATE : 23.07.2022.
  * NOTE        : Module namespace 'rirt'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */


#ifndef __def_h_
#define __def_h_

#include <windows.h>
#include <vector>
#include "mth/mth.h"

/* Debug memory allocation support */
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy
{
public:
  /* Class constructor */
  __Dummy( VOID )
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __ooppss;

#endif /* NDEBUG */ 


#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

 /* Storage array class */
template<typename Type>
  class stock : public std::vector<Type>
  {
  public:
    
    /* Adding new element to array function.
     * ARGUMENTS: 
     *   - new element reference
     *       const Type &x;
     * RETURNS: 
     *   (stock &) reference to stock.
     */
    stock & operator<<( const Type &x )
    {
      this->push_back(x);
      return *this;
    } /* End of 'operator<<' function */
  
    /* Applying func to all elements function.
     * ARGUMENTS:
     *   - applying func
     *       WalkType Walk
     * RETURNS: None.
     */
    template<typename WalkType>
      VOID Walk( WalkType Walk )
      {
        for (auto &x: *this)
          Walk(x);
      } /* End of 'Walk' function */
  };

#endif /* __def_h_ */

/* END OF 'def.h' FILE */