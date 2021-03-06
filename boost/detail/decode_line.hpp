// Andrew Naplavkov

#ifndef BRIG_BOOST_DETAIL_DECODE_LINE_HPP
#define BRIG_BOOST_DETAIL_DECODE_LINE_HPP

#include <brig/boost/detail/decode_point.hpp>
#include <brig/detail/ogc.hpp>
#include <cstdint>
#include <sstream>

namespace brig { namespace boost { namespace detail {

template <typename InputIterator>
void decode_line(uint8_t byte_order, InputIterator& in_itr, std::ostringstream& out_stream)
{
  out_stream << "(";
  for (uint32_t i(0), count(brig::detail::ogc::read<uint32_t>(byte_order, in_itr)); i < count; ++i)
  {
    if (i > 0) out_stream << ", ";
    decode_point_raw(byte_order, in_itr, out_stream);
  }
  out_stream << ")";
}

} } } // brig::boost::detail

#endif // BRIG_BOOST_DETAIL_DECODE_LINE_HPP
