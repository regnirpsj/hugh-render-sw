// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/triangle.hpp                                               */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_TRIANGLE_HPP)

#define HUGH_RENDER_SOFTWARE_TRIANGLE_HPP

// includes, system

//#include <>

// includes, project

#include <hugh/render/software/vertex.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      // types, exported (class, enum, struct, union, typedef)

      class HUGH_RENDER_SOFTWARE_EXPORT triangle : public support::printable {

      public:

        vertex const    p0;
        vertex const    p1;
        vertex const    p2;
        glm::vec3 const n;
        
        explicit triangle(vertex const&, vertex const&, vertex const&);
        virtual ~triangle();

        virtual void print_on(std::ostream&) const;
        
      };
        
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_TRIANGLE_HPP)
