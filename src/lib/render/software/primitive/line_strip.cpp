// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/line_strip.cpp                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/primitive/line_strip.hpp"

// includes, system

#include <stdexcept> // std::out_of_range

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {

  namespace render {

    namespace software {

      namespace primitive {
        
        // variables, exported
  
        // functions, exported

        /* explicit */
        line_strip::line_strip(vertex_list_type const& a, index_list_type const& b)
          : base(primitive::topology::line_strip, a, b)
        {
          TRACE("hugh::render::software::primitive::line_strip::line_strip");
          
          if (2 > vertices.size()) {
            throw std::out_of_range("<render::software::primitive::line_strip>: "
                                    "requires at least 2 vertices");
          }
        }
        
        /* virtual */
        line_strip::~line_strip()
        {
          TRACE("hugh::render::software::primitive::line_strip::~line_strip");
        }
        
      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
