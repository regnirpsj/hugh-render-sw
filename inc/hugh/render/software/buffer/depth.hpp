// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/buffer/depth.hpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_RENDER_SOFTWARE_BUFFER_DEPTH_HPP)

#define HUGH_RENDER_SOFTWARE_BUFFER_DEPTH_HPP

// includes, system

#include <glm/gtc/vec1.hpp> // glm::vec1
#include <vector>           // std::vector<>

// includes, project

#include <hugh/render/software/buffer/base.hpp>

namespace hugh {

  namespace render {

    namespace software {
      
      namespace buffer {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_RENDER_SOFTWARE_EXPORT depth : public base {

        public:
          
          explicit depth(viewport_type const& = viewport_type());
          virtual ~depth();

          virtual void clear ();
          virtual bool update(fragment const&);

        private:

          using buffer_type = std::vector<glm::vec1>;
          
          buffer_type::value_type const clear_value_;
          buffer_type                   buffer_;
          
        };
        
        // variables, exported (extern)

        // functions, inlined (inline)
  
        // functions, exported (extern)

      } // namespace buffer {

    } // namespace software {

  } // namespace render {
  
} // namespace hugh {

#endif // #if !defined(HUGH_RENDER_SOFTWARE_BUFFER_DEPTH_HPP)