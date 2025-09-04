#include <zephyr/kernel.h>
#include <zmk/event_manager.h>
#include <zmk/keymap.h>
#include <raw_hid/events.h>

// Adjust to your layer name/index for Russian
#define RU_LAYER 11

// Keep host/app enum in sync with your sender
enum { DATA_LAYOUT = 0xAC };

static int on_rawhid(const zmk_event_t *eh) {
    const struct raw_hid_received_event *ev = as_raw_hid_received_event(eh);
    if (!ev) return ZMK_EV_EVENT_BUBBLE;
    const uint8_t *buf = ev->data;
    if (buf[0] == DATA_LAYOUT) {
        uint8_t idx = buf[1];      // 0 = EN, 1 = RU (your choice)
        if (idx == 1) zmk_layer_activate(RU_LAYER);
        else          zmk_layer_deactivate(RU_LAYER);
    }
    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(host_layout_listener, on_rawhid);
ZMK_SUBSCRIPTION(host_layout_listener, raw_hid_received_event);
