#include <zmk/display.h>
#include <zmk/battery.h>
#include <zmk/keymap.h>
#include <zmk/event_manager.h>
#include <zmk/events/layer_state_changed.h>

static void update_display() {
    char buffer[32];
    int battery = zmk_battery_state_of_charge();
    int layer = zmk_keymap_layer_active();

    snprintf(buffer, sizeof(buffer), "Battery: %d%%\nLayer: %d", battery, layer);
    zmk_display_write(buffer);
}

static int layer_state_changed_listener(const zmk_event_t *eh) {
    update_display();
    return 0;
}

ZMK_LISTENER(layer_state_changed_listener, layer_state_changed_listener);
ZMK_SUBSCRIPTION(layer_state_changed_listener, zmk_layer_state_changed);
