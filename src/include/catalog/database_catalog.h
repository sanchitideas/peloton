//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// database_catalog.h
//
// Identification: src/include/catalog/database_catalog.h
//
// Copyright (c) 2015-17, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// pg_database
//
// Schema: (column: column_name)
// 0: database_oid (pkey), 1: database_name
//
// Indexes: (index offset: indexed columns)
// 0: database_oid (unique)
// 1: database_name (unique)
//
//===----------------------------------------------------------------------===//

#pragma once

#include "catalog/abstract_catalog.h"

namespace peloton {
namespace catalog {

class DatabaseCatalog : public AbstractCatalog {
 public:
  // Global Singleton
  static DatabaseCatalog *GetInstance(storage::Database *pg_catalog = nullptr,
                                      type::AbstractPool *pool = nullptr);

  inline oid_t GetNextOid() { return oid_++ | COLUMN_OID_MASK; }

  // Write related API
  bool InsertDatabase(oid_t database_oid, const std::string &database_name,
                      type::AbstractPool *pool, concurrency::Transaction *txn);
  void DeleteDatabase(oid_t database_oid, concurrency::Transaction *txn);

  // Read-only API
  std::string GetDatabaseName(oid_t database_oid,
                              concurrency::Transaction *txn);
  oid_t GetDatabaseOid(const std::string &database_name,
                       concurrency::Transaction *txn);

 private:
  DatabaseCatalog(storage::Database *pg_catalog, type::AbstractPool *pool);

  ~DatabaseCatalog();

  std::unique_ptr<catalog::Schema> InitializeSchema();
};

}  // End catalog namespace
}  // End peloton namespace
