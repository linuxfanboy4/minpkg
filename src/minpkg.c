#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define PACKAGE_DIR "./packages/"
#define TMP_DIR "./tmp/"
#define MAX_CMD_LEN 256
#define MAX_PATH_LEN 512

void create_package(const char *url, const char *package_name, const char *command) {
    char package_file[MAX_PATH_LEN];
    snprintf(package_file, sizeof(package_file), "%s%s.minpkg", PACKAGE_DIR, package_name);
    FILE *file = fopen(package_file, "w");
    if (!file) {
        perror("Failed to create package file");
        return;
    }
    fprintf(file, "%s\n%s\n", url, command);
    fclose(file);
    printf("Package %s.minpkg created successfully\n", package_name);
}

void install_package(const char *package_name) {
    char package_file[MAX_PATH_LEN];
    snprintf(package_file, sizeof(package_file), "%s%s", PACKAGE_DIR, package_name);

    FILE *file = fopen(package_file, "r");
    if (!file) {
        perror("Package not found");
        return;
    }

    char url[MAX_PATH_LEN], command[MAX_CMD_LEN];
    fscanf(file, "%s\n%s\n", url, command);
    fclose(file);

    char tmp_file[MAX_PATH_LEN];
    snprintf(tmp_file, sizeof(tmp_file), "%s%s", TMP_DIR, package_name);
    char wget_cmd[MAX_CMD_LEN];
    snprintf(wget_cmd, sizeof(wget_cmd), "wget -O %s %s", tmp_file, url);

    if (system(wget_cmd) == 0) {
        char install_cmd[MAX_CMD_LEN];
        snprintf(install_cmd, sizeof(install_cmd), "chmod +x %s && mv %s %s%s", tmp_file, tmp_file, PACKAGE_DIR, package_name);
        if (system(install_cmd) == 0) {
            printf("Package %s installed successfully\n", package_name);
        } else {
            perror("Failed to install the package");
        }
    } else {
        perror("Failed to download the package");
    }
}

void uninstall_package(const char *package_name) {
    char package_path[MAX_PATH_LEN];
    snprintf(package_path, sizeof(package_path), "%s%s", PACKAGE_DIR, package_name);
    if (remove(package_path) == 0) {
        printf("Package %s uninstalled successfully\n", package_name);
    } else {
        perror("Failed to uninstall package");
    }
}

void list_installed_packages() {
    struct stat st;
    if (stat(PACKAGE_DIR, &st) == -1) {
        mkdir(PACKAGE_DIR, 0777);
    }

    FILE *fp = popen("ls " PACKAGE_DIR, "r");
    if (!fp) {
        perror("Failed to list installed packages");
        return;
    }

    char line[MAX_PATH_LEN];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

void execute_package(const char *package_name) {
    char package_path[MAX_PATH_LEN];
    snprintf(package_path, sizeof(package_path), "%s%s", PACKAGE_DIR, package_name);
    if (access(package_path, F_OK) != -1) {
        if (system(package_path) == -1) {
            perror("Failed to execute package");
        }
    } else {
        printf("Package %s not found\n", package_name);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: minpkg <command> [args]\n");
        return 1;
    }

    if (strcmp(argv[1], "install") == 0 && argc == 3) {
        install_package(argv[2]);
    } else if (strcmp(argv[1], "uninstall") == 0 && argc == 3) {
        uninstall_package(argv[2]);
    } else if (strcmp(argv[1], "list") == 0 && argc == 2) {
        list_installed_packages();
    } else if (strcmp(argv[1], "create") == 0 && argc == 5) {
        create_package(argv[2], argv[3], argv[4]);
    } else if (strcmp(argv[1], "use") == 0 && argc == 3) {
        execute_package(argv[2]);
    } else {
        fprintf(stderr, "Invalid command or arguments\n");
        return 1;
    }

    return 0;
}
