#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <glib.h>
#include <dbus/dbus-glib.h>


int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    GMainLoop *loop;
    loop = g_main_loop_new(NULL, false);

    g_main_loop_run(loop);
    return EXIT_SUCCESS;
}
