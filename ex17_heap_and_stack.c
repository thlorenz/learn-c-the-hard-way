#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAXDATA 512
#define MAXROWS 100

char *strncpy_term(char *dst, const char *src, const size_t len) {
  // Wrapper that fixes strncpy null terminator problem
  // From: http://www.cplusplus.com/reference/cstring/strncpy/
  // No null-character is implicitly appended at the end of destination if source is longer than num.
  // Thus, in this case, destination shall not be considered a null terminated C string (reading it as such would overflow).

  char *res = strncpy(dst, src, len);
  if (res && len > 0) dst[len -1 ] = '\0';
  return res;
}

struct Address {
  int id;
  int set;
  char name[MAXDATA];
  char email[MAXDATA];
};

void Address_print(struct Address *addr) {
  printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

struct Connection {
  FILE *file;
  struct Database *db;
};

struct Database {
  struct Address rows[MAXROWS];
};

void Database_close(struct Connection *conn) {
  if (conn) {
    if (conn->file) fclose(conn->file);
    if (conn->db) free(conn->db);
    free(conn);
  }
}

void die(const char *msg, struct Connection *conn) {
  if (errno) perror(msg); else printf("Error: %s\n", msg);
  Database_close(conn);
  exit(1);
}

void Database_load(struct Connection *conn) {
  // read one entry of size Database from file
  size_t entries_read = fread(conn->db, sizeof(struct Database), 1, conn->file);
  if (entries_read != 1) die("Failed to load database", conn);
}

struct Connection *Database_open(const char *filename, char mode) {
  struct Connection *conn = malloc(sizeof(struct Connection));
  if (!conn) die("Memory error", NULL);

  conn->db = malloc(sizeof(struct Database));
  if (!conn->db) die("Memory error", conn);

  if (mode == 'c') {
    conn->file = fopen(filename, "w");
  } else {
    conn->file = fopen(filename, "r+");
    if (conn->file) Database_load(conn);
  }
  if (!conn->file) die("Failed to open the file", conn);

  return conn;
}

void Database_create(struct Connection *conn) {
  for (int i = 0; i < MAXROWS; i++) {
    // init addr by creating prototype
    struct Address addr = { .id = i, .set = 0 };
    conn->db->rows[i] = addr;
  }
}

void Database_write(struct Connection *conn) {
  rewind(conn->file);
  size_t rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
  if (rc != 1) die("Failed to write to database", conn);

  rc = fflush(conn->file);
  if (rc == -1) die("Failed to flush database", conn);
}


void Database_set(struct Connection *conn, int id, const char *name, const char *email) {
  struct Address *addr = &conn->db->rows[id];
  if (addr->set) die("Already set, delete it first", conn);

  addr->set = 1;

  char *res = strncpy_term(addr->name, name, MAXDATA);
  if (!res) die("Name copy failed", conn);

  res = strncpy_term(addr->email, email, MAXDATA);
  if (!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id) {
  struct Address *addr = &conn->db->rows[id];
  if (!addr->set) die("id not set", conn);
  Address_print(addr);
}

void Database_delete(struct Connection *conn, int id) {
  // ensures that all fields but .id and .set are initialized to 0
  // assignment handles memcpy under the hood
  conn->db->rows[id] = (struct Address){ .id = id, .set = 0 };
}

void Database_list(struct Connection *conn) {
  struct Database *db = conn->db;
  for (int i = 0; i < MAXROWS; i++) {
    struct Address *addr = &db->rows[i];
    if (addr->set) Address_print(addr);
  }
}

struct Address *Database_find(struct Connection *conn, const char* name) {
  struct Database db = *conn->db;
  for (int i = 0; i < MAXROWS; i++) {
    struct Address *addr = &db.rows[i];
    if (strcmp(name, addr->name) == 0) return addr;
  }
  return NULL;
}

int main(int argc, const char *argv[]) {

  if (argc < 3) die("USAGE: ex17_heap_and_stack <dbfile> <action> [action params]", NULL);

  int id = 0;
  const char *name;
  const char *filename = argv[1];
  const char action = argv[2][0];

  if (argc > 3) {
    // little hacky, but whatever - just an excercise ;)
    if (action != 'f') id = atoi(argv[3]);
    else name = argv[3];
  }

  if (id >= MAXROWS) die("There are not that many records", NULL);

  struct Connection *conn = Database_open(filename, action);

  switch (action) {
    case 'c':
      Database_create(conn);
      Database_write(conn);
      break;

    case 's':
      if(argc != 6) die("Need id, name, email to set a record", conn);

      Database_set(conn, id, argv[4], argv[5]);
      Database_write(conn);
      break;

    case 'g':
      if(argc != 4) die("Need an id to get a record", conn);

      Database_get(conn, id);
      break;

    case 'l':
      Database_list(conn);
      break;

    case 'd':
      if(argc != 4) die("Need id to delete a record", conn);

      Database_delete(conn, id);
      Database_write(conn);
      break;

    case 'f':
      if(argc != 4) die("Need name to find", conn);
      struct Address *addr = Database_find(conn, name);
      if (addr) {
        Address_print(addr);
      } else {
        printf("Unable to find address with name %s\n", name);
      }
      break;

    default:
      die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
  }

  Database_close(conn);
  return 0;
}
