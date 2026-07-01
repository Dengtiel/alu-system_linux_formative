#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define BACKUP_FILE  "/tmp/backup_data.txt"
#define LOG_FILE     "/tmp/backup_log.txt"
#define READ_FILE    "/tmp/backup_data.txt"

void write_log(const char *message) {
    FILE *log = fopen(LOG_FILE, "a");
    if (!log) {
        perror("fopen log");
        return;
    }

    time_t now = time(NULL);
    char *ts = ctime(&now);
    ts[strlen(ts) - 1] = '\0'; // remove newline

    fprintf(log, "[%s] %s\n", ts, message);
    fclose(log);
}

void create_backup_file() {
    FILE *f = fopen(BACKUP_FILE, "w");
    if (!f) {
        perror("fopen backup");
        return;
    }
    fprintf(f, "user_data=Alice,Bob,Charlie\n");
    fprintf(f, "config=production\n");
    fprintf(f, "version=3.2.1\n");
    fclose(f);
    printf("[BACKUP] Backup file created: %s\n", BACKUP_FILE);
    write_log("Backup file created successfully");
}

void read_backup_file() {
    FILE *f = fopen(READ_FILE, "r");
    if (!f) {
        perror("fopen read");
        return;
    }

    char line[256];
    printf("[BACKUP] Reading backup contents:\n");
    while (fgets(line, sizeof(line), f)) {
        printf("  %s", line);
    }
    fclose(f);
    write_log("Backup file read successfully");
}

int main() {
    printf("[backup_tool] Starting backup process (PID: %d)\n", getpid());
    write_log("backup_tool started");

    create_backup_file();
    read_backup_file();

    write_log("backup_tool finished");
    printf("[backup_tool] Done.\n");
    return 0;
}
