// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016-2017 University of Hull                                                     */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/render/software/test/rasterizer/simple.cpp                                 */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <array>          // std::array<>
#include <memory>         // std::unique_ptr<>
#include <glm/gtx/io.hpp> // glm::operator<<

// includes, project

#include <hugh/render/software/rasterizer/simple.hpp>
#include <hugh/support/io.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_render_software_rasterizer_simple_ctor)
{
  using namespace hugh::render::software;
  
  std::unique_ptr<rasterizer::base> const rs(new rasterizer::simple);

  BOOST_CHECK(nullptr != rs);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_rasterizer_simple_process_line)
{
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;

  static attribute::list const al0({ {attribute::type::color, glm::vec4(1,0,0,1) }, });
  static attribute::list const al1({ {attribute::type::color, glm::vec4(0,1,0,1) }, });

  viewport const  v(0, 0,  3,  6);
  unsigned const  d(std::max(v. width, v.height));
  glm::vec3 const o(        0,          0, 0);
  glm::vec3 const x(v.width-1,          0, 0);
  glm::vec3 const y(        0, v.height-1, 0);
  glm::vec3 const z(        0,          0, 1);
  
  std::array<std::pair<line const, unsigned const>, 22> const lines = {
    {
      { line(vertex(o), vertex(  x)),    v. width }, { line(vertex(  x), vertex(o)),    v. width },
      { line(vertex(o), vertex( -x)),           1 }, { line(vertex( -x), vertex(o)),           1 },
      { line(vertex(x), vertex( -x)),    v. width }, { line(vertex( -x), vertex(x)),    v. width },
      { line(vertex(o), vertex(  y)),    v.height }, { line(vertex(  y), vertex(o)),    v.height },
      { line(vertex(o), vertex( -y)),           1 }, { line(vertex( -y), vertex(o)),           1 },
      { line(vertex(y), vertex( -y)),    v.height }, { line(vertex( -y), vertex(y)),    v.height },
      { line(vertex(o), vertex(  z)),           1 }, { line(vertex(  z), vertex(o)),           1 },
      { line(vertex(o), vertex( -z)),           1 }, { line(vertex( -z), vertex(o)),           1 },
      { line(vertex(z), vertex( -z)),           1 }, { line(vertex( -z), vertex(z)),           1 },
      { line(vertex(o, al0), vertex(x+y, al1)), d }, { line(vertex(x+y, al0), vertex(o, al1)), d },
      { line(vertex(y, al0), vertex(  x, al1)), d }, { line(vertex(  x, al0), vertex(y, al1)), d },
    }
  };
  
  rasterizer::simple const rs(v);

  for (auto const& lp : lines) {
    using fragment_list = rasterizer::simple::fragment_list_type;
    
    fragment_list const fl(rs.process(lp.first.p0, lp.first.p1));
    
    BOOST_CHECK(lp.second == fl.size());

    {
      std::ostringstream ostr;

      using hugh::support::ostream::delimeter;
      using hugh::support::ostream::operator<<;

      ostr << lp.second << "=?=" << fl.size() << ":\n"
           << glm::io::width(4) << glm::io::precision(2)
           << delimeter<char>('(', ')', '\n')
           << fl;
      
      BOOST_TEST_MESSAGE(ostr.str());
    }
  }

  BOOST_TEST_MESSAGE('\n');
}

template <typename T>
glm::tvec3<T>
two(glm::tvec3<T> const& a)
{
  return a * T(2);
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_rasterizer_simple_process_triangle)
{
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;

  static attribute::list const al0({ {attribute::type::color, glm::vec4(1,0,0,1) }, });
  static attribute::list const al1({ {attribute::type::color, glm::vec4(0,1,0,1) }, });
  static attribute::list const al2({ {attribute::type::color, glm::vec4(0,0,1,1) }, });
  
  viewport const  v(0, 0,  4,  4); // w == h -> 1/2 slope

  unsigned a(0);

  for (unsigned i(0); i < v.height; ++i) {
    a += v.width - i;
  }
  
  glm::vec3 const o(        0,          0, 0);
  glm::vec3 const x(v.width-1,          0, 0);
  glm::vec3 const y(        0, v.height-1, 0);
  glm::vec3 const z(        0,          0, 1);
  
  std::array<std::pair<triangle const, unsigned const>, 18> const triangles = {
    {
      { triangle(vertex(o), vertex(x), vertex(y)), a },
      { triangle(vertex(o), vertex(y), vertex(x)), 0 },
      
      { triangle(vertex(x), vertex(y), vertex(o)), a },
      { triangle(vertex(y), vertex(x), vertex(o)), 0 },
      
      { triangle(vertex(y), vertex(o), vertex(x)), a },
      { triangle(vertex(x), vertex(o), vertex(y)), 0 },

      { triangle(vertex(  x), vertex(x+y), vertex(  y)), a },
      { triangle(vertex(  x), vertex(  y), vertex(x+y)), 0 },
      
      { triangle(vertex(x+y), vertex(  y), vertex(x)), a },
      { triangle(vertex(  y), vertex(x+y), vertex(x)), 0 },
      
      { triangle(vertex(  y), vertex(x), vertex(x+y)), a },
      { triangle(vertex(x+y), vertex(x), vertex(  y)), 0 },
      
      { triangle(vertex(     o), vertex(two(x)), vertex(two(y))), v.width * v.height },
      { triangle(vertex(     o), vertex( 2.f*y), vertex( 2.f*x)),                  0 },

      { triangle(vertex(two(x)), vertex(two(y)), vertex(o)), v.width * v.height },
      { triangle(vertex( 2.f*y), vertex( 2.f*x), vertex(o)),                  0 },
      
      { triangle(vertex(two(y), al0), vertex(o, al1), vertex(two(x), al2)), v.width * v.height },
      { triangle(vertex( 2.f*x, al0), vertex(o, al1), vertex( 2.f*y, al2)),                  0 },
    }
  };
  
  rasterizer::simple const rs(v);

  for (auto const& tp : triangles) {
    using fragment_list = rasterizer::simple::fragment_list_type;
    
    fragment_list const fl(rs.process(tp.first.p0, tp.first.p1, tp.first.p2));
    
    BOOST_CHECK(tp.second == fl.size());

    {
      std::ostringstream ostr;

      using hugh::support::ostream::delimeter;
      using hugh::support::ostream::operator<<;

      ostr << tp.second << "=?=" << fl.size() << ':'
           << glm::io::width(4) << glm::io::precision(2)
           << delimeter<char>('(', ')', '\n')
           << fl;
      
      BOOST_TEST_MESSAGE(ostr.str());
    }
  }

  BOOST_TEST_MESSAGE('\n');
}

BOOST_AUTO_TEST_CASE(test_hugh_render_software_rasterizer_simple_print_on)
{
  using namespace hugh::render::software;
  using viewport = hugh::scene::object::camera::viewport;
  
  rasterizer::simple const rs(viewport(0, 0, 10, 10));
  std::ostringstream       ostr;

  ostr << &rs;

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
