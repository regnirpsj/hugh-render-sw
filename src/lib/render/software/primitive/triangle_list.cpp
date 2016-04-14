// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/primitive/triangle_list.cpp                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/render/software/primitive/triangle_list.hpp"

// includes, system

//#include <>

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
        triangle_list::triangle_list(vertex_list_type const& a, index_list_type const& b)
          : base(primitive::topology::triangle_list, a, b)
        {
          TRACE("hugh::render::software::primitive::triangle_list::triangle_list");
        }
        
        /* virtual */
        triangle_list::~triangle_list()
        {
          TRACE("hugh::render::software::primitive::triangle_list::~triangle_list");
        }

      } // namespace primitive {
      
    } // namespace software {

  } // namespace render {
  
} // namespace hugh {
