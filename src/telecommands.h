//UPLINK COMMANDS
#define REQUEST_DATA_TELECOMMAND            (0x7764)    /**< uplink command to request whole data orbit - dw    */
#define REQUEST_SHUTDOWN_TELECOMMAND        (0x6473)    /**< uplink command to request a 24 hours shutdown - sd */
#define REQUEST_PING_TELECOMMAND            (0x6770)    /**< ping request - pg                                  */

#define OLDER_PACKAGES_ORIGIN               0
#define NEWER_PACKAGES_ORIGIN               1

typedef struct {
    uint16_t flags;             /**< modules flags to request just the wanted data*/
    uint8_t packages_count;     /**< number of packages to read, from offset */
    uint8_t packages_origin;    /**< position used as reference for the offset */
    int32_t packages_offset;    /**< number of packages to offset from origin */
} request_data_packet_t;

typedef struct {
    uint8_t ID[6];
    uint16_t request_action;    /**< the action (send data, shutdown, ping..) */
    uint8_t arguments[8];
    uint8_t reserved[12];
} telecommand_t;