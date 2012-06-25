// Andrew Naplavkov

#ifndef BRIG_DATABASE_CUBRID_DETAIL_GET_DATA_STRING_HPP
#define BRIG_DATABASE_CUBRID_DETAIL_GET_DATA_STRING_HPP

#include <brig/database/cubrid/detail/get_data.hpp>
#include <brig/database/cubrid/detail/lib.hpp>
#include <brig/database/variant.hpp>
#include <string>

namespace brig { namespace database { namespace cubrid { namespace detail {

struct get_data_string : get_data {
  virtual int operator()(int req, size_t col, variant& var);
}; // get_data_string

inline int get_data_string::operator()(int req, size_t col, variant& var)
{
  char* data;
  int ind(-1);
  const int r(lib::singleton().p_cci_get_data(req, col + 1, CCI_A_TYPE_STR, &data, &ind));
  if (lib::error(r) || ind < 0)
    var = null_t();
  else
  {
    var = std::string();
    std::string& str(::boost::get<std::string>(var));
    str = data;
  }
  return r;
} // get_data_string::

} } } } // brig::database::cubrid::detail

#endif // BRIG_DATABASE_CUBRID_DETAIL_GET_DATA_STRING_HPP