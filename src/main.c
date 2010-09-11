#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include <glib.h>
#include <dbus/dbus-glib.h>


void gdp_enable_dpms_suspend(void) {
    system("xset dpms force standby");
    printf("Activated DPMS.\n");
}


static DBusGConnection *setup_dbus() {
    DBusGConnection *bus;
    GError *error = NULL;

    bus = dbus_g_bus_get(DBUS_BUS_SESSION, &error);
    if (!bus) {
        g_warning("Failed to connection to DBus session daemon: %s",
                error->message);
        g_error_free(error);
        return NULL;
    }

    return bus;
}


static void on_screensaver_active_changed(DBusGProxy *proxy,
        bool active) {

    // Suppress unused parameter warning.
    (void) proxy;
    if (active) {
        gdp_enable_dpms_suspend();
    }
}


static DBusGProxy *setup_dbus_proxy(DBusGConnection *bus) {
    DBusGProxy *proxy;

    proxy = dbus_g_proxy_new_for_name(bus, "org.gnome.ScreenSaver",
            "/org/gnome/ScreenSaver", "org.gnome.ScreenSaver");
    dbus_g_proxy_add_signal(proxy, "ActiveChanged", G_TYPE_BOOLEAN);
    dbus_g_proxy_connect_signal(proxy, "ActiveChanged",
            G_CALLBACK(on_screensaver_active_changed), NULL, NULL);

    return proxy;
}


int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    GMainLoop *loop;
    DBusGConnection *bus;
    DBusGProxy *proxy;

    // Must be called prior to any object access. Initializes the thread system,
    // as well.
    g_type_init();

    loop = g_main_loop_new(NULL, false);
    bus = setup_dbus();
    proxy = setup_dbus_proxy(bus);
    if (bus == NULL) {
        return EXIT_FAILURE;
    }

    g_main_loop_run(loop);
    g_main_loop_unref(loop);

    g_object_unref(bus);
    g_object_unref(proxy);

    return EXIT_SUCCESS;
}
