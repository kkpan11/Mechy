#include "Mechy.h"

Mechy::Mechy() {
    firstPluginPtr = NULL;
    event = { .key = MCHY_NONE, .keyState = KEY_STATE_NONE, .duration = 0 };
}

inline void Mechy::appendPluginPtr(PluginPtr *ptr) {
    if (firstPluginPtr) {
        PluginPtr *lastPtr = firstPluginPtr;
        while (lastPtr->next) {
            lastPtr = lastPtr->next;
        }
        lastPtr->next = ptr;
    }
    else {
        firstPluginPtr = ptr;
    }
}

void Mechy::add(uint8_t name, Plugin *plugin) {
    PluginPtr *ptr = (PluginPtr*)malloc(sizeof(PluginPtr));
    ptr->name = name;
    ptr->plugin = plugin;
    ptr->next = NULL;
    plugin->mechy = this;

    appendPluginPtr(ptr);
}

void Mechy::_begin() {
    PluginPtr *ptr = firstPluginPtr;
    while (ptr) {
        ptr->plugin->begin();
        ptr = ptr->next;
    }
}

void Mechy::_tick() {
    PluginPtr *ptr = firstPluginPtr;
    while (ptr) {
        ptr->plugin->tick();
        ptr = ptr->next;
    }
}

void Mechy::processKeyEvent(bool isPressed, KBD *currentKey) {
    if (!currentKey->isPressed && isPressed) {
        // if the key was just released, ignore debouncing HIGH signals
        if (millis() - currentKey->started < 10) {
            return;
        }

        currentKey->isPressed = true;
        currentKey->started = millis();
        runPlugin(KEY_STATE_PRESSED, currentKey);
    }
    else if (currentKey->isPressed) {
        // if the key was just pressed, ignore debouncing LOW signals
        if (!isPressed && millis() - currentKey->started < 10) {
            return;
        }

        if (!isPressed) {
            currentKey->isPressed = false;
            runPlugin(KEY_STATE_RELEASED, currentKey);
            currentKey->started = millis();
        }
        else {
            runPlugin(KEY_STATE_HELD, currentKey);
        }
    }
}

void Mechy::runPlugin(uint8_t keyState, KBD *currentKey) {
    event.key = currentKey->key;
    event.keyState = keyState;
    event.duration = millis() - currentKey->started;

    bool processing = KBD_CONTINUE;
    PluginPtr *ptr = firstPluginPtr;
    while (ptr) {
        processing = ptr->plugin->override(currentKey->name, &event) && processing;
        ptr = ptr->next;
    }

    if (processing == KBD_CONTINUE) {
        PluginPtr *ptr = firstPluginPtr;
        while (ptr) {
            if (ptr->name == currentKey->name) {
                ptr->plugin->run(&event);
            }
            ptr = ptr->next;
        }
    }
}
