// Andrew Naplavkov

#ifndef BRIG_DATABASE_DETAIL_GET_RASTERS_POSTGRES_HPP
#define BRIG_DATABASE_DETAIL_GET_RASTERS_POSTGRES_HPP

#include <brig/database/column_definition.hpp>
#include <brig/database/command.hpp>
#include <brig/database/detail/get_rasters.hpp>
#include <brig/database/detail/sql_identifier.hpp>
#include <brig/database/detail/sql_tables.hpp>
#include <brig/database/global.hpp>
#include <brig/database/raster_pyramid.hpp>
#include <brig/database/variant.hpp>
#include <brig/string_cast.hpp>
#include <memory>
#include <vector>

namespace brig { namespace database { namespace detail {

inline std::vector<raster_pyramid> get_rasters_postgres(std::shared_ptr<command> cmd)
{
  using namespace brig::database::detail;
  std::vector<variant> row;
  cmd->exec(sql_tables(Postgres, "raster_columns"));
  while (cmd->fetch(row))
    if (string_cast<char>(row[0]) == "public" && string_cast<char>(row[1]) == "raster_columns")
    {
      cmd->exec("SELECT COALESCE(o.r_table_schema, r.r_table_schema) base_scm, COALESCE(o.r_table_name, r.r_table_name) base_tbl, COALESCE(o.r_raster_column, r.r_raster_column) base_col, abs(r.scale_x) res_x, abs(r.scale_y) res_y, r.r_table_schema, r.r_table_name, r.r_raster_column, r.r_raster_column FROM public.raster_columns r LEFT JOIN public.raster_overviews o ON r.r_table_schema = o.o_table_schema AND r.r_table_name = o.o_table_name AND r.r_raster_column = o.o_raster_column ORDER BY base_scm, base_tbl, base_col, res_x, res_y");
      auto res = get_rasters(cmd);
      for (size_t r(0); r < res.size(); ++r)
        for (size_t l(0); l < res[r].levels.size(); ++l)
        {
          const std::string col_name(res[r].levels[l].raster.name);
          res[r].levels[l].raster.name = col_name + "_as_jpg";
          res[r].levels[l].raster.query_expression = "ST_AsJPEG(" + sql_identifier(Postgres, col_name)  + ")";
        }
      return res;
    }
  return std::vector<raster_pyramid>();
}

} } } // brig::database::detail

#endif // BRIG_DATABASE_DETAIL_GET_RASTERS_POSTGRES_HPP
