/*
 * Copyright (c)2018 Ulrich Hertlein <u.hertlein@sandbox.de>
 */

#include "qmp.h"

#include <cmath>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace {
void dump(const uint8_t* data)
{
    printf("%02x %02x %02x %02x : %c%c%c%c\n", data[0], data[1], data[2], data[3],
        data[0], data[1], data[2], data[3]);
}

std::string trim(const std::string& data)
{
    auto first_non_space = data.find_first_not_of(" ");
    auto last_non_space = data.find_last_not_of(" ");
    return data.substr(first_non_space, last_non_space - first_non_space + 1);
}

std::string extract(const char* data, const size_t data_size)
{
    return trim(std::string(data, data_size));
}
}

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf("Usage: %s <file.qmp>\n", argv[0]);
        return 0;
    }

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Failed to open '%s'\n", argv[1]);
        return -1;
    }

    qmp::QtMap qtmap;
    fread(&qtmap, sizeof(qtmap), 1, fp);
    if (strncmp(qtmap.marker, qmp::MARKER_QTMAP, sizeof(qtmap.marker)) != 0) {
        printf("Failed to read QTMAP header\n");
        dump(reinterpret_cast<const uint8_t*>(&qtmap));
        return -1;
    }

    printf("QTMAP\n");
    printf(" version=%d\n", qtmap.version);
    printf(" quadtree_offset=0x%04x\n", qtmap.quadtree_offset);
    printf(" description='%s'\n",
        extract(qtmap.description, sizeof(qtmap.description)).c_str());
    printf(" name='%s'\n", extract(qtmap.name, sizeof(qtmap.name)).c_str());
    printf(" date0='%s'\n", extract(qtmap.date0, sizeof(qtmap.date0)).c_str());
    printf(" date1='%s'\n", extract(qtmap.date1, sizeof(qtmap.date1)).c_str());
    printf(" copyright0='%s'\n",
        extract(qtmap.copyright0, sizeof(qtmap.copyright0)).c_str());
    printf(" copyright1='%s'\n",
        extract(qtmap.copyright1, sizeof(qtmap.copyright1)).c_str());

    qmp::QuadTree quadtree;
    fread(&quadtree, sizeof(quadtree), 1, fp);
    if (strncmp(quadtree.marker, qmp::MARKER_QUADTREE, sizeof(quadtree.marker)) != 0) {
        printf("Failed to read QUADTREE header\n");
        dump(reinterpret_cast<const uint8_t*>(&quadtree));
        return -1;
    }

    printf("QUADTREE\n");
    printf(" version=%d\n", quadtree.version);
    printf(" max_level=%d\n", quadtree.max_level);

    for (uint32_t level = 0; level < quadtree.max_level; ++level) {
        qmp::TileSet tileset;
        fread(&tileset, sizeof(tileset), 1, fp);
        if (strncmp(tileset.marker, qmp::MARKER_TILESET, sizeof(tileset.marker)) != 0) {
            printf("Failed to read TILESET header\n");
            dump(reinterpret_cast<const uint8_t*>(&tileset));
            return -1;
        }

        printf(" TILESET_%u\n", level);
        printf("  version=%d\n", tileset.version);
        printf("  level=%d\n", tileset.level);

        const auto tileCount = static_cast<uint32_t>(std::pow(4, tileset.level));
        for (uint32_t i = 0; i < tileCount; ++i) {
            qmp::Tile tile;
            fread(&tile, sizeof(tile), 1, fp);
            printf("  TILE_%u_%u\n", level, i);
            printf("   level=%u\n", tile.level);
            printf("   tile=%u,%u\n", tile.tile_x, tile.tile_y);
            printf("   soi_offset=0x%04x\n", tile.soi_offset);
            printf("   soi_length=0x%04x\n", tile.soi_length);
            printf("   top_left=%u,%u\n", tile.x0, tile.y0);
            printf("   bottom_right=%u,%u\n", tile.x1, tile.y1);
        }
    }

    fclose(fp);
    return 0;
}
