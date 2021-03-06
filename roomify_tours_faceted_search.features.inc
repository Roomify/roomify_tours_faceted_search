<?php
/**
 * @file
 * roomify_tours_faceted_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function roomify_tours_faceted_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_search_api_index().
 */
function roomify_tours_faceted_search_default_search_api_index() {
  $items = array();
  $items['tours'] = entity_import('search_api_index', '{
    "name" : "Tours",
    "machine_name" : "tours",
    "description" : null,
    "server" : "db1",
    "item_type" : "rooms_unit",
    "options" : {
      "datasource" : { "bundles" : [] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "base_price" : { "type" : "decimal" },
        "bookable" : { "type" : "integer" },
        "changed" : { "type" : "integer" },
        "created" : { "type" : "integer" },
        "field_category" : { "type" : "integer", "entity_type" : "taxonomy_term" },
        "max_children" : { "type" : "integer" },
        "max_sleeps" : { "type" : "integer" },
        "min_children" : { "type" : "integer" },
        "min_sleeps" : { "type" : "integer" },
        "name" : { "type" : "text" },
        "search_api_language" : { "type" : "string" },
        "status" : { "type" : "integer" },
        "type" : { "type" : "string" },
        "unit_id" : { "type" : "integer" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 1,
          "weight" : "-10",
          "settings" : {
            "default" : "1",
            "bundles" : { "single_day_tour_slot" : "single_day_tour_slot" }
          }
        },
        "search_api_alter_add_hierarchy" : { "status" : 0, "weight" : "0", "settings" : { "fields" : [] } },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "Tokens" } },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 0,
          "weight" : "0",
          "settings" : { "fields" : { "name" : true } }
        },
        "search_api_html_filter" : {
          "status" : 0,
          "weight" : "10",
          "settings" : {
            "fields" : { "name" : true },
            "title" : 0,
            "alt" : 1,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : { "name" : true },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : { "name" : true },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_highlighting" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : [],
            "highlight" : "always"
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function roomify_tours_faceted_search_default_search_api_server() {
  $items = array();
  $items['db1'] = entity_import('search_api_server', '{
    "name" : "DB1",
    "machine_name" : "db1",
    "description" : "",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "1",
      "partial_matches" : 0,
      "indexes" : { "tours" : {
          "unit_id" : {
            "table" : "search_api_db_tours",
            "column" : "unit_id",
            "type" : "integer",
            "boost" : "1.0"
          },
          "type" : {
            "table" : "search_api_db_tours",
            "column" : "type",
            "type" : "string",
            "boost" : "1.0"
          },
          "name" : { "table" : "search_api_db_tours_text", "type" : "text", "boost" : "1.0" },
          "created" : {
            "table" : "search_api_db_tours",
            "column" : "created",
            "type" : "integer",
            "boost" : "1.0"
          },
          "changed" : {
            "table" : "search_api_db_tours",
            "column" : "changed",
            "type" : "integer",
            "boost" : "1.0"
          },
          "base_price" : {
            "table" : "search_api_db_tours",
            "column" : "base_price",
            "type" : "decimal",
            "boost" : "1.0"
          },
          "bookable" : {
            "table" : "search_api_db_tours",
            "column" : "bookable",
            "type" : "integer",
            "boost" : "1.0"
          },
          "min_sleeps" : {
            "table" : "search_api_db_tours",
            "column" : "min_sleeps",
            "type" : "integer",
            "boost" : "1.0"
          },
          "max_sleeps" : {
            "table" : "search_api_db_tours",
            "column" : "max_sleeps",
            "type" : "integer",
            "boost" : "1.0"
          },
          "min_children" : {
            "table" : "search_api_db_tours",
            "column" : "min_children",
            "type" : "integer",
            "boost" : "1.0"
          },
          "max_children" : {
            "table" : "search_api_db_tours",
            "column" : "max_children",
            "type" : "integer",
            "boost" : "1.0"
          },
          "status" : {
            "table" : "search_api_db_tours",
            "column" : "status",
            "type" : "integer",
            "boost" : "1.0"
          },
          "search_api_language" : {
            "table" : "search_api_db_tours",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "field_category" : {
            "table" : "search_api_db_tours",
            "column" : "field_category",
            "type" : "integer",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1",
    "rdf_mapping" : []
  }');
  return $items;
}
