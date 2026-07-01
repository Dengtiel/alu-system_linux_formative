#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define SOURCE_DIR "/tmp/source"
#define DEST_DIR   "/tmp/dest"
#define LOG_FILE   "/tmp/data_sync.log"

void log_event(const char *message) {
    FILE *log = fopen(LOG_FILE, "a");
    if (log) {
        fprintf(log, "[LOG] %s\n", message);
        fclose(log);
    }
}

int file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0;
}

void sync_file(const char *filename) {
    char src_path[256], dst_path[256];
    snprintf(src_path, sizeof(src_path), "%s/%s", SOURCE_DIR, filename);
    snprintf(dst_path, sizeof(dst_path), "%s/%s", DEST_DIR, filename);

    FILE *src = fopen(src_path, "r");
    if (!src) {
        fprintf(stderr, "[ERROR] Cannot open source: %s\n", src_path);
        log_event("Failed to open source file");
        return;
    }

    FILE *dst = fopen(dst_path, "w");
    if (!dst) {
        fprintf(stderr, "[ERROR] Cannot open dest: %s\n", dst_path);
        fclose(src);
        log_event("Failed to open destination file");
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dst);
    }

    fclose(src);
    fclose(dst);

    printf("[SYNC] Copied %s -> %s\n", src_path, dst_path);
    log_event("File synced successfully");
}

int main(int argc, char *argv[]) {
    printf("[data_sync] File Synchronization Tool v1.0\n");

    mkdir(SOURCE_DIR, 0755);
    mkdir(DEST_DIR, 0755);

    // Create a demo source file
    FILE *demo = fopen(SOURCE_DIR "/demo.txt", "w");
    if (demo) {
        fprintf(demo, "Hello from data_sync!\n");
        fclose(demo);
    }

    log_event("data_sync started");
    sync_file("demo.txt");
    log_event("data_sync completed");

    printf("[data_sync] Sync complete.\n");
    return 0;
}
