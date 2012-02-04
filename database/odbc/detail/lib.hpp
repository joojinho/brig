// Andrew Naplavkov

#ifndef BRIG_DATABASE_ODBC_DETAIL_LIB_HPP
#define BRIG_DATABASE_ODBC_DETAIL_LIB_HPP

#include <brig/detail/dynamic_loading.hpp>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

namespace brig { namespace database { namespace odbc { namespace detail {

class lib {
  lib();

public:
  decltype(SQLAllocHandle) *p_SQLAllocHandle;
  decltype(SQLBindParameter) *p_SQLBindParameter;
  decltype(SQLColAttributeW) *p_SQLColAttributeW;
  decltype(SQLDataSourcesW) *p_SQLDataSourcesW;
  decltype(SQLDisconnect) *p_SQLDisconnect;
  decltype(SQLDriverConnectW) *p_SQLDriverConnectW;
  decltype(SQLEndTran) *p_SQLEndTran;
  decltype(SQLExecute) *p_SQLExecute;
  decltype(SQLFetch) *p_SQLFetch;
  decltype(SQLFreeHandle) *p_SQLFreeHandle;
  decltype(SQLFreeStmt) *p_SQLFreeStmt;
  decltype(SQLGetData) *p_SQLGetData;
  decltype(SQLGetDiagRecW) *p_SQLGetDiagRecW;
  decltype(SQLGetInfoW) *p_SQLGetInfoW;
  decltype(SQLNumResultCols) *p_SQLNumResultCols;
  decltype(SQLPrepareW) *p_SQLPrepareW;
  decltype(SQLRowCount) *p_SQLRowCount;
  decltype(SQLSetConnectAttr) *p_SQLSetConnectAttr;
  decltype(SQLSetEnvAttr) *p_SQLSetEnvAttr;

  bool empty() const  { return p_SQLSetEnvAttr == 0; }
  static lib& singleton()  { static lib s; return s; }
}; // lib

inline lib::lib() : p_SQLSetEnvAttr(0)
{
  auto handle = BRIG_DL_LIBRARY("odbc32.dll", "libodbc.so.1");
  if (  handle
    && (p_SQLAllocHandle = BRIG_DL_FUNCTION(handle, SQLAllocHandle))
    && (p_SQLBindParameter = BRIG_DL_FUNCTION(handle, SQLBindParameter))
    && (p_SQLColAttributeW = BRIG_DL_FUNCTION(handle, SQLColAttributeW))
    && (p_SQLDataSourcesW = BRIG_DL_FUNCTION(handle, SQLDataSourcesW))
    && (p_SQLDisconnect = BRIG_DL_FUNCTION(handle, SQLDisconnect))
    && (p_SQLDriverConnectW = BRIG_DL_FUNCTION(handle, SQLDriverConnectW))
    && (p_SQLEndTran = BRIG_DL_FUNCTION(handle, SQLEndTran))
    && (p_SQLExecute = BRIG_DL_FUNCTION(handle, SQLExecute))
    && (p_SQLFetch = BRIG_DL_FUNCTION(handle, SQLFetch))
    && (p_SQLFreeHandle = BRIG_DL_FUNCTION(handle, SQLFreeHandle))
    && (p_SQLFreeStmt = BRIG_DL_FUNCTION(handle, SQLFreeStmt))
    && (p_SQLGetData = BRIG_DL_FUNCTION(handle, SQLGetData))
    && (p_SQLGetDiagRecW = BRIG_DL_FUNCTION(handle, SQLGetDiagRecW))
    && (p_SQLGetInfoW = BRIG_DL_FUNCTION(handle, SQLGetInfoW))
    && (p_SQLNumResultCols = BRIG_DL_FUNCTION(handle, SQLNumResultCols))
    && (p_SQLPrepareW = BRIG_DL_FUNCTION(handle, SQLPrepareW))
    && (p_SQLRowCount = BRIG_DL_FUNCTION(handle, SQLRowCount))
    && (p_SQLSetConnectAttr = BRIG_DL_FUNCTION(handle, SQLSetConnectAttr))
     )  p_SQLSetEnvAttr = BRIG_DL_FUNCTION(handle, SQLSetEnvAttr);
} // lib::

} } } } // brig::database::odbc::detail

#endif // BRIG_DATABASE_ODBC_DETAIL_LIB_HPP