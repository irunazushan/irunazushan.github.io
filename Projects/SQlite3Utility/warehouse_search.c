#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

sqlite3 *global_db = NULL;

void execute_query(sqlite3 *db, const char *sql) {
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL ошибка: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

void get_additional_rack_names(int product_id, const char *main_rack_name, char *additional_rack_names, size_t size) {
    char sql[512];
    sprintf(sql, "SELECT GROUP_CONCAT(warehouse.rack_name) AS rack_names "
                 "FROM product "
                 "JOIN product_location ON product.product_id = product_location.product_id "
                 "JOIN warehouse ON product_location.warehouse_id = warehouse.warehouse_id "
                 "WHERE product.product_id = %d", product_id);

    char *err_msg = 0;
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(global_db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Не верное утверждение: %s\n", sqlite3_errmsg(global_db));
        return;
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const unsigned char *rack_names = sqlite3_column_text(stmt, 0);
        if (rack_names) {
            // Copy the concatenated rack names into a temporary buffer
            char temp_rack_names[256];
            strncpy(temp_rack_names, (const char *)rack_names, sizeof(temp_rack_names));

            // Initialize the additional_rack_names string
            additional_rack_names[0] = '\0';

            // Split the concatenated rack names and add them to additional_rack_names if they are not the main_rack_name
            char *rack_name = strtok(temp_rack_names, ",");
            while (rack_name != NULL) {
                if (strcmp(rack_name, main_rack_name) != 0) {
                    strncat(additional_rack_names, rack_name, size - strlen(additional_rack_names) - 1);
                    strncat(additional_rack_names, ", ", 3); // Add a comma and space between rack names
                }
                rack_name = strtok(NULL, ",");
            }

            // Remove the trailing comma and space if any
            if (strlen(additional_rack_names) > 0) {
                additional_rack_names[strlen(additional_rack_names) - 2] = '\0';
            }
        }
    }

    sqlite3_finalize(stmt);
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    if (argv[4] != NULL) {
            printf("\n");
    }
    printf("=== %s\n", argv[4]);
    printf("%s (id=%s)\n", argv[1], argv[2]); // Assuming argv[1] is product_name and argv[2] is product_id
    printf("заказ %s, %s шт\n", argv[0], argv[3]); // Assuming argv[0] is order_id and argv[3] is amount

     char additional_rack_names[256] = "";
    get_additional_rack_names(atoi(argv[2]), argv[4], additional_rack_names, sizeof(additional_rack_names));
    if (strlen(additional_rack_names) > 0) {
        printf("Дополнительно: %s\n", additional_rack_names);
    }

    return 0;
}

void process_orders(sqlite3 *db, const char *order_ids) {
    char sql[1024];
    sprintf(sql, "SELECT order_details.order_id, dt.type_name, product.device_type_id, order_details.amount, w.rack_name "
                 "FROM order_details "
                 "JOIN product ON order_details.product_id = product.product_id "
                 "JOIN device_type dt USING (device_type_id) "
                 "JOIN product_location pl ON product.product_id = pl.product_id "
                 "JOIN warehouse w ON pl.warehouse_id = w.warehouse_id "
                 "WHERE order_details.order_id IN (%s) "
                 "ORDER BY w.rack_name", order_ids);
    char *err_msg = 0;
    global_db = db;
    int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL ошибка: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Использование: %s <order_ids>\n", argv[0]);
        return 1;
    }

    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("warehouse.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Ошибка при открытии базы данных: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char order_ids[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(order_ids, argv[i]);
        if (i < argc - 1) {
            strcat(order_ids, ",");
        }
    }

    process_orders(db, order_ids);

    sqlite3_close(db);
    return 0;
}