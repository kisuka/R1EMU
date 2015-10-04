/**
 *
 *   ██████╗   ██╗ ███████╗ ███╗   ███╗ ██╗   ██╗
 *   ██╔══██╗ ███║ ██╔════╝ ████╗ ████║ ██║   ██║
 *   ██████╔╝ ╚██║ █████╗   ██╔████╔██║ ██║   ██║
 *   ██╔══██╗  ██║ ██╔══╝   ██║╚██╔╝██║ ██║   ██║
 *   ██║  ██║  ██║ ███████╗ ██║ ╚═╝ ██║ ╚██████╔╝
 *   ╚═╝  ╚═╝  ╚═╝ ╚══════╝ ╚═╝     ╚═╝  ╚═════╝
 *
 * @license GNU GENERAL PUBLIC LICENSE - Version 2, June 1991
 *          See LICENSE file for further information
 */

#include "item_accessory.h"

extern inline float *itemAccessoryGetPr(ItemAccessory *self);
extern inline float *itemAccessoryGetCooldown(ItemAccessory *self);

ItemAccessory *itemAccessoryNew(void) {
    ItemAccessory *self;

    if ((self = malloc(sizeof(ItemAccessory))) == NULL) {
        return NULL;
    }

    if (!itemAccessoryInit(self)) {
        itemAccessoryDestroy(&self);
        error("ItemAccessory failed to initialize.");
        return NULL;
    }

    return self;
}

bool itemAccessoryInit(ItemAccessory *self) {
    memset(self, 0, sizeof(*self));

    return true;
}

void itemAccessoryFree(ItemAccessory *self) {
    // TODO
}

void itemAccessoryDestroy(ItemAccessory **_self) {
    ItemAccessory *self = *_self;

    if (_self && self) {
        itemAccessoryFree(self);
        free(self);
        *_self = NULL;
    }
}

size_t itemAccessoryGetPropertiesCPacketSize(ItemAccessory *self) {
    size_t size = 0;
    size += propertyFloatGetCPacketSize(); // pr
    size += propertyFloatGetCPacketSize(); // cooldown
    return size;
}

void itemAccessoryGetPropertiesCPacket(ItemAccessory *self, PacketStream *stream) {
    propertyFloatGetCPacket(ITEM_ACCESSORY_PROPERTY_ID_PR, self->pr, stream);
    propertyFloatGetCPacket(ITEM_ACCESSORY_PROPERTY_ID_COOLDOWN, self->cooldown, stream);
}
