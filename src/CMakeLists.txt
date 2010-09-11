ADD_EXECUTABLE(gnome-displaypower main.c)
TARGET_LINK_LIBRARIES(gnome-displaypower ${GLIB_LIBRARIES})
TARGET_LINK_LIBRARIES(gnome-displaypower ${DBUS_GLIB_LIBRARIES})
