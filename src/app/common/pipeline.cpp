// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  common/pipeline.cpp                                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "pipeline.hpp"

// includes, system

#include <glm/gtx/io.hpp> // glm::operator<<
#include <ostream>        // std:;ostream
#include <stdexcept>      // std::logic_error

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

namespace pipeline {
  
  // variables, exported
  
  // functions, exported
  
  /* explicit */
  result::result(glm::vec3 const& a, glm::vec4 const& b, glm::vec4 const& c, glm::vec4 const& d,
                 glm::vec4 const& e, glm::vec3 const& f, glm::vec3 const& g)
    : object(a), homogeneous(b), world(c), eye(d), clip(e), ndc(f), window(g)
  {
    TRACE("pipeline::result::result");
  }
  
  /* virtual */
  base::~base()
  {
    TRACE("pipeline::base::~base");
  }

  result
  base::transform(glm::vec3 const& a, bool b) const
  {
    TRACE("pipeline::base::transform");

    glm::vec4 const homogeneous(glm::vec4(a, (b ? 1 : 0)));
    glm::vec4 const world      (object_to_world  (homogeneous));
    glm::vec4 const eye        (world_to_eye     (world));
    glm::vec4 const clip       (eye_to_clip      (eye));
    glm::vec3 const ndc        (b ? clip_to_ndc  (clip) : clip.xyz());
    glm::vec3 const window     (b ? ndc_to_window(ndc)  : clip.xyz());
    
    return result(a, homogeneous, world, eye, clip, ndc, window);
  }
  
  /* virtual */ void
  base::print_on(std::ostream& os) const
  {
    TRACE_NEVER("pipeline::base::print_on");

    os << '[' << '\n'
       << "m:"  << xform_model_ << '\n'
       << "v:"  << xform_view_  << '\n'
       << "p:"  << xform_proj_  << '\n'
       << "vp:" << viewport_
       << ']';
  }

  /* explicit */
  base::base(glm::mat4 const& a, glm::mat4 const& b, glm::mat4 const& c, viewport const& d)
    : hugh::support::printable(),
      xform_model_            (a),
      xform_view_             (b),
      xform_proj_             (c),
      viewport_               (d)
  {
    TRACE("pipeline::base::base");
  }

  glm::vec4
  base::object_to_world(glm::vec4 const& a) const
  {
    TRACE("pipeline::base::object_to_world");
    
    return (xform_model_ * a);
  }

  glm::vec4
  base::world_to_eye(glm::vec4 const& a) const
  {
    TRACE("pipeline::base::world_to_eye");
    
    return (xform_view_ * a);
  }

  glm::vec4
  base::eye_to_clip(glm::vec4 const& a) const
  {
    TRACE("pipeline::base::eye_to_clip");

    return (xform_proj_ * a);
  }

  glm::vec3
  base::clip_to_ndc(glm::vec4 const& a) const
  {
    TRACE("pipeline::base::clip_to_ndc");

    return glm::vec3(a.x / a.w, a.y / a.w, a.z / a.w);
  }

  /* virtual */
  glm::vec3
  base::ndc_to_window(glm::vec3 const&) const
  {
    TRACE("pipeline::base::ndc_to_window");

    throw std::logic_error("pure virtual function 'pipeline::base::ndc_to_window' called");
    
    return glm::vec3();
  }

  /* explicit */
  d3d::d3d(glm::mat4 const& a, glm::mat4 const& b, glm::mat4 const& c, viewport const& d)
    : base(a, b, c, d)
  {
    TRACE("pipeline::d3d::d3d");
  }

  /* virtual */ glm::vec3
  d3d::ndc_to_window(glm::vec3 const& a) const
  {
    TRACE("pipeline::d3d::ndc_to_window");

    glm::vec3 result;

    // http://msdn.microsoft.com/en-us/library/windows/desktop/bb205126%28v=vs.85%29.aspx
    result.x = ((a.x + 1) * (viewport_.width  / 2.0f))        + viewport_.x;
    result.y = ((1 - a.y) * (viewport_.height / 2.0f))        + viewport_.y;
    result.z = ( a.z      * (viewport_.far - viewport_.near)) + viewport_.near;

    return result;
  }

  /* explicit */
  opengl::opengl(glm::mat4 const& a, glm::mat4 const& b, glm::mat4 const& c, viewport const& d)
    : base(a, b, c, d)
  {
    TRACE("pipeline::opengl::opengl");
  }

  /* virtual */ glm::vec3
  opengl::ndc_to_window(glm::vec3 const& a) const
  {
    TRACE("pipeline::opengl::ndc_to_window");

    glm::vec3 result;

#if 1
    // glspec43.core20120806:13.6.1
    result.x  = ((a.x + 1) * (viewport_.width  / 2.0f)) + viewport_.x;
    result.y  = ((a.y + 1) * (viewport_.height / 2.0f)) + viewport_.y;
    result.z  = ((a.z      * ((viewport_.far - viewport_.near) / 2.0f)) +
                 ((viewport_.near + viewport_.far) / 2.0f));
#else
    // assuming viewport_.df:1 and viewport_.dn:0
    result    = a * 0.5f + 0.5f;
    result.x *= viewport_.width  + viewport_.x;
    result.y *= viewport_.height + viewport_.y;
#endif

    return result;
  }

  std::ostream&
  operator<<(std::ostream& os, result const& a)
  {
    TRACE_NEVER("pipeline::operator<<(result const&)");

    std::ostream::sentry const cerberus(os);

    if (cerberus) {
      os << '[' << '\n'
         << " o:" << a.object      << ',' << '\n'
         << " h:" << a.homogeneous << ',' << '\n'
         << " m:" << a.world       << ',' << '\n'
         << " v:" << a.eye         << ',' << '\n'
         << " c:" << a.clip        << ',' << '\n'
         << " n:" << a.ndc         << ',' << '\n'
         << " w:" << a.window             << '\n'
         << ']';
    }

    return os;
  }

} // namespace hugh {