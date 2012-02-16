// Andrew Naplavkov

#ifndef BRIG_WKT_DETAIL_PRINT_LINE_HPP
#define BRIG_WKT_DETAIL_PRINT_LINE_HPP

#include <brig/detail/ogc.hpp>
#include <brig/wkt/detail/print_point.hpp>
#include <cstdint>
#include <sstream>

namespace brig { namespace wkt { namespace detail {

template <typename InputIterator>
void print_line(uint8_t byte_order, InputIterator& in_iter, std::ostringstream& out_stream)
{
  out_stream << '(';
  for (uint32_t i(0), count(brig::detail::ogc::read<uint32_t>(byte_order, in_iter)); i < count; ++i)
  {
    if (i > 0) out_stream << ", ";
    print_point_raw(byte_order, in_iter, out_stream);
  }
  out_stream << ')';
}

} } } // brig::wkt::detail

#endif // BRIG_WKT_DETAIL_PRINT_LINE_HPP
