/*
 * Copyright (c)2018 Ulrich Hertlein <u.hertlein@sandbox.de>
 */

#pragma once

#include <cinttypes>

namespace qmp {
static const char* MARKER_QTMAP = "QTMAP";
static const char* MARKER_QUADTREE = "QUADTREE";
static const char* MARKER_TILESET = "TILESET ";

#pragma pack(push, 1)
struct QtMap {
    char marker[5]; // 'QTMAP'
    uint32_t version; // 0x0000 0002
    uint32_t quadtree_offset; // 0x0000 09c6
    char description[0x64];
    char name[0x64];
    char date0[0x14];
    char date1[0x14];
    uint32_t unk_a[0xa];
    char creator[0x32];
    char copyright[0x64];
    uint32_t unk_b[0x8];
    uint8_t unk_zero[0x7ea];
};
static_assert(sizeof(QtMap) == 0x9c5, "Invalid QtMap size");

struct QuadTree {
    char marker[8]; // 'QUADTREE'
    uint32_t version; // 0x0000 0001 = 1
    uint32_t max_level; // 0x0000 0004 = 4
    uint32_t unk0; // 0x0000 2000 = 8192
    uint32_t unk1; // 0x0000 1000 = 4096
    uint32_t unk2; // 0x0000 2000
    uint32_t unk3; // 0x0000 1000
    uint32_t unk4; // 0x0000 0200 = 512
    uint32_t unk5; // 0x0000 0100 = 256
    uint32_t unk6; // 0x0000 0000
    uint32_t unk7; // 0x0000 0000
    uint32_t soi_preview_offset; // 0x0000 40aa
    uint8_t unk_zero[0x400];
};
static_assert(sizeof(QuadTree) == 0x434, "Invalid QuadTree size");

struct TileSet {
    char marker[8]; // 'TILESET '
    uint32_t version;
    uint32_t level;
    uint8_t unk_zero[0x7c];
};
static_assert(sizeof(TileSet) == 0x8c, "Invalid TileSet size");

struct Tile {
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
static_assert(sizeof(Tile) == 0x24, "Invalid Tile size");

#pragma pack(pop)
}
