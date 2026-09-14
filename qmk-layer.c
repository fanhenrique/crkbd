#define _GNU_SOURCE

#include <dirent.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <limits.h>
#include <sys/types.h>

#include "keymap/layers.h"

#define DEVICE_VID "4653"
#define DEVICE_PID "0004"
#define USB_INTERFACE "1"

#define HID_REPORT_SIZE 32
#define LAYER_MARK 0x90
#define LAYER_MARK_OFFSET 24
#define LAYER_OFFSET 25

#define DEFINE_LAYER_NAME(name) [name] = #name,

static const char *layer_names[] = {
    LAYER_LIST(DEFINE_LAYER_NAME)
};

#undef DEFINE_LAYER_NAME

#define LAYER_COUNT (sizeof(layer_names) / sizeof(layer_names[0]))


static void print_layer_name(const char *name)
{
    const int width = 15;
    const int length = strlen(name);

    int left = (width - length) / 2;
    int right = width - length - left;

    printf("%*s%s%*s\n", left, "", name, right, "");
}

static const char *find_hidraw(void)
{
    static char device_path[PATH_MAX];

    DIR *dir = opendir("/dev");
    if (!dir)
        return NULL;

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, "hidraw", 6) != 0)
            continue;

        char sysfs_path[PATH_MAX];
        char real_path[PATH_MAX];

        snprintf(
            sysfs_path,
            sizeof(sysfs_path),
            "/sys/class/hidraw/%s/device",
            entry->d_name
        );

        if (!realpath(sysfs_path, real_path))
            continue;

        char device_id[64];

        snprintf(
            device_id,
            sizeof(device_id),
            ":%s:%s.",
            DEVICE_VID,
            DEVICE_PID
        );

        if (!strstr(real_path, device_id))
            continue;

        char interface_id[32];

        snprintf(
            interface_id,
            sizeof(interface_id),
            ":%s.%s/",
            USB_INTERFACE,
            USB_INTERFACE
        );

        if (!strstr(real_path, interface_id))
            continue;

        snprintf(
            device_path,
            sizeof(device_path),
            "/dev/%s",
            entry->d_name
        );

        closedir(dir);

        return device_path;
    }

    closedir(dir);

    return NULL;
}

int main(void)
{
    const char *device = find_hidraw();

    if (!device) {
        fprintf(stderr, "hidraw device not found\n");
        return 1;
    }

    int fd = open(device, O_RDONLY);

    if (fd < 0) {
        perror("open");
        return 1;
    }

    uint8_t report[HID_REPORT_SIZE];

    static int last_layer = -1;

    while (1) {
        ssize_t bytes_read = read(
            fd,
            report,
            sizeof(report)
        );

        if (bytes_read <= 0)
            continue;

        if (bytes_read < HID_REPORT_SIZE)
            continue;

        if (report[LAYER_MARK_OFFSET] != LAYER_MARK)
            continue;

        unsigned int layer = report[LAYER_OFFSET];

        if (layer >= LAYER_COUNT)
            continue;

        if ((int)layer == last_layer)
            continue;

        last_layer = layer;

        print_layer_name(layer_names[layer]);
        fflush(stdout);
    }

    close(fd);

    return 0;
}