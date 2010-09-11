#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <glib.h>
#include <dbus/dbus-glib.h>


static DBusGConnection *setup_dbus() {
    DBusGConnection *bus;
    GError *error = NULL;

    bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (!bus) {
        g_warning("Failed to connection to DBus session daemon: %s", error->message);
        g_error_free(error);
        return NULL;
    }

    return bus;
}


int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    GMainLoop *loop;
    DBusGConnection *bus;

    // Must be called prior to any object access. Initializes the thread system,
    // as well.
    g_type_init();

    loop = g_main_loop_new(NULL, false);
    bus = setup_dbus();
    if (bus == NULL) {
        return EXIT_FAILURE;
    }

    g_main_loop_run(loop);

    return EXIT_SUCCESS;
}
