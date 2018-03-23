#pragma once

#include <inttypes.h>

namespace qmp
{
struct QtMap
{
    union {
        char space[0x9c4];
    };
};

struct QuadTree
{
    union {
        char space[0x434];
        struct {
            char marker[8]; // 'QUADTREE'
            uint32_t version;
            uint32_t max_level;
            uint32_t unk0; // 0x0000 2000
            uint32_t unk1; // 0x0000 1000
            uint32_t unk2; // 0x0000 2000
            uint32_t unk3; // 0x0000 1000
            uint32_t unk4; // 0x0000 0200
            uint32_t unk5; // 0x0000 0100
            uint32_t unk6; // 0x0
            uint32_t unk7; // 0x0
            uint32_t soi_preview_offset; // 0x0000 40aa
        };
    };
};

struct TileSet
{
    char marker[8]; // 'TILESET '
    uint32_t version;
    uint32_t level;
};

struct Tile
{
    uint32_t level;
    uint32_t tile_x;
    uint32_t tile_y;

    // JFIF SOI offset+1, length
    uint32_t soi_offset;
    uint32_t soi_length;

    // top-left
    uint32_t x0;
    uint32_t y0;

    // bottom-right
    uint32_t x1;
    uint32_t y1;
};
}
