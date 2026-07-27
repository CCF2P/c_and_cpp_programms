#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>
#include <unistd.h>

struct connected_params
{
  const char *host;
  const char *port;
  const char *user;
  const char *password;
  const char *dbname;
};

int parse_connected_params(struct connected_params *params, int argc, char *argv[]);
char* read_sql_file(const char *filename);
void print_query_result(PGresult *res);

int main(int argc, char *argv[])
{
  char exit_code = 0;
  char *sql_file = NULL;
  struct connected_params *params = NULL;
  PGconn *conn = NULL;
  PGresult *res = NULL;

  params = (struct connected_params*)malloc(sizeof(struct connected_params));
  if (!params) {
    fprintf(stderr, "[ERROR] Memory allocation failed\n");
    exit_code = 1;
    goto cleanup;
  }
  if (parse_connected_params(params, argc, argv) == -1) {
    fprintf(stderr, "[ERROR] Usage: %s -h host -p port -U user -P password -d dbname\n", argv[0]);
    exit_code = 1;
    goto cleanup;
  }

  const char *const keywords[] = {
    "host",
    "port",
    "user",
    "password",
    "dbname",
    NULL
  };
  const char *const values[] = {
    params->host,
    params->port,
    params->user,
    params->password,
    params->dbname,
    NULL
  };
  conn = PQconnectdbParams(keywords, values, 0);
  if (PQstatus(conn) != CONNECTION_OK) {
    fprintf(stderr, "[ERROR] Connection failed: %s\n", PQerrorMessage(conn));
    exit_code = 1;
    goto cleanup;
  }
  printf("[ INFO] Successfully connected to database: %s \n", params->dbname);

  const char filename[256];
  printf("Input filename of sql script $> ");
  scanf("%255[^\n]", filename);

  printf("[ INFO] Start reading sql file: %s\n", filename);
  sql_file = read_sql_file(filename);
  if (sql_file == NULL) {
    fprintf(stderr, "[ERROR] Cannot read or open the file: %s\n", filename);
    exit_code = 1;
    goto cleanup;
  }

  printf("[ INFO] Execute sql file: %s\n", filename);
  res = PQexec(conn, sql_file);
  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    fprintf(stderr, "[ERROR] Query failed: %s\n", PQerrorMessage(conn));
    exit_code = 1;
    goto cleanup;
  }

  print_query_result(res);

cleanup:
  if (params) free(params);
  if (sql_file) free(sql_file);
  if (res) PQclear(res);
  if (conn) PQfinish(conn);
  return exit_code;
}

void print_query_result(PGresult *res)
{
  printf("------ RESULT ------\n");
  int n_fields = PQnfields(res);
  for (int i = 0; i < n_fields; ++i) {
    printf("%-15s", PQfname(res, i));
  }
  printf("\n");

  int n_tuples = PQntuples(res);
  for (int i = 0; i < n_tuples; ++i) {
    for (int j = 0; j < n_fields; ++j) {
      char *v = PQgetvalue(res, i, j);
      if (v == NULL)
        printf("%-15s", "NULL");
      else
        printf("%-15s", v);
    }
    printf("\n");
  }
}

int parse_connected_params(struct connected_params *params, int argc, char *argv[])
{
  int opt = 0;
  while (opt != -1) {
    opt = getopt(argc, argv, "h:p:U:P:d:");
    switch(opt) {
      case 'h':
        params->host = optarg;
        break;
      case 'p':
        params->port = optarg;
        break;
      case 'U':
        params->user = optarg;
        break;
      case 'P':
        params->password = optarg;
        break;
      case 'd':
        params->dbname = optarg;
        break;
      case '?':
        return -1;
    }
  }
  return 0;
}

char* read_sql_file(const char *filename)
{
  FILE *file = fopen(filename, "rb");
  if (!file) return NULL;

  // Определяем размер файла
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  if (file_size < 0) {
    fclose(file);
    return NULL;
  }
  fseek(file, 0, SEEK_SET);

  // Вычисляем память под содержимое файла (+1 для заверщающего нуля)
  char *buffer = (char*)malloc(file_size + 1);
  if (!buffer) {
    fclose(file);
    return NULL;
  }

  size_t bytes_read = fread(buffer, 1, file_size, file);
  buffer[bytes_read] = '\0';

  fclose(file);
  return buffer;
}