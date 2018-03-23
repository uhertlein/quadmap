# QuadMap

This repository aims to analyse the SeeYou `qmp` file format.

The minimum goal is to extract images from a given `qmp` file.  The stretch goal is to create `qmp` files that will be accepted by SeeYou.

## QMP File Format

- QTMAP
  - at `0x000000`, end `0x0009c5`, len `0x9c5`
    - char marker[5]
    - uint32_t version = 0x02
    - uint32_t quadtree_offset? = 0x0000 09c6 // off-by-one?
    - char description[0x64] // not null-terminated
    - char name[0x64] // not null-terminated
    - char date0[0x14] // not null-terminated
    - char date1[0x14] // not null-terminated
    - uint8_t unk[0x28]
    - char copyright0[0x32] // not null-terminated
    - char copyright1[0x64] // not null-terminated
- QUADTREE
  - at `0x0009c5`, end `0x00df8`, len `0x434`
    - char marker[8]
    - uint32_t version = 0x01
    - uint32_t max_level = 0x04
    - uint32_t unk = 0x2000 
    - uint32_t unk = 0x1000
    - uint32_t unk = 0x2000
    - uint32_t unk = 0x1000
    - uint32_t unk = 0x0200
    - uint32_t unk = 0x0100
    - uint32_t unk = 0x0
    - uint32_t unk = 0x0
    - uint32_t soi_preview_offset? = 0x0000 40aa
  - at `0x0009f5` rel `0x30`: `0x000040aa`
- TILESET
  - total count 5
  - level 0, 1x1=1
    - at `0x000df9`, end `0x000ea8`, length=`0xb0`
    - at `0x000e91` rel `0x98`: `0x000040aa`=SOI `0x00002689`=length
      - from `0x000e85` rel `0x8c`
      - uint32_t level = 0x0000 0000
      - uint32_t tile_x = 0x0000 0001
      - uint32_t tile_y = 0x0000 0001
      - uint32_t soi_offset = 0x0000 40aa
      - uint32_t soi_length = 0x0000 2689
      - uint32_t x0 = 0x0000 0000 = 0
      - uint32_t y0 = 0x0000 0000 = 0
      - uint32_t x1 = 0x0000 01ff = 511
      - uint32_t y1 = 0x0000 00ff = 255
  - level 1, 2x2=4
    - at `0x000ea9`, length=`0x11c`
    - at `0x000f41`: `0x00006733`=SOI `0x0000218e`=length
      - from `0x000f35` rel `0x8c`
      - uint32_t level = 0x0000 0001
      - uint32_t tile_x = 0x0000 0001
      - uint32_t tile_y = 0x0000 0001
      - uint32_t soi_offset = 0x0000 6733
      - uint32_t soi_length = 0x0000 218e
      - uint32_t x0 = 0x0000 0000 = 0
      - uint32_t y0 = 0x0000 0000 = 0
      - uint32_t x1 = 0x0000 01ff = 511
      - uint32_t y1 = 0x0000 00ff = 255
    - at `0x000f65`: `0x000088c1`=SOI `0x000018e4`=length
      - from `0x000f59`
      - uint32_t level = 0x0000 0001
      - uint32_t tile_x = 0x0000 0002
      - uint32_t tile_y = 0x0000 0001
      - uint32_t soi_offset = 0x0000 88c1
      - uint32_t soi_length = 0x0000 18e4
      - uint32_t x0 = 0x0000 0200 = 512 // top-left
      - uint32_t y0 = 0x0000 0000 = 0
      - uint32_t x1 = 0x0000 03ff = 1023 // bottom-right
      - uint32_t y1 = 0x0000 00ff = 255
    - at `0x000f89`: `0x0000a1a5`=SOI `0x00002794`=length
      - from `0x000f7d`
      - uint32_t level = 0x0000 0001
      - uint32_t tile_x = 0x0000 0001
      - uint32_t tile_y = 0x0000 0002
      - uint32_t soi_offset = 0x0000 a1a5
      - uint32_t soi_length = 0x0000 2794
      - uint32_t x0 = 0x0000 0000 = 0
      - uint32_t y0 = 0x0000 0100 = 256
      - uint32_t x1 = 0x0000 01ff = 511
      - uint32_t y1 = 0x0000 01ff = 511
    - at `0x000fad`: `0x0000c939`=SOI `0x00001b23`=length
      - from `0x000fa1`
      - uint32_t level = 0x0000 0001
      - uint32_t tile_x = 0x0000 0002
      - uint32_t tile_y = 0x0000 0002
      - uint32_t soi_offset = 0x0000 c939
      - uint32_t soi_length = 0x0000 1b23
      - uint32_t x0 = 0x0000 0200 = 512
      - uint32_t y0 = 0x0000 0100 = 256
      - uint32_t x1 = 0x0000 03ff = 1023
      - uint32_t y1 = 0x0000 01ff = 511
  - level 2, 4x4=16
    - at `0x000fc5`, length=`0x2cc`
    - at `0x00105d`: `0x0000e45c`=SOI `0x000020b1`=length
      - from `0x001051` rel `0x8c`
      - uint32_t level = 0x0000 0002
      - uint32_t tile_x = 0x0000 0001
      - uint32_t tile_y = 0x0000 0001
      - uint32_t soi_offset = 0x0000 e45c
      - uint32_t soi_length = 0x0000 20b1
      - uint32_t x0 = 0x0000 0000 = 0
      - uint32_t y0 = 0x0000 0000 = 0
      - uint32_t x1 = 0x0000 01ff = 511
      - uint32_t y1 = 0x0000 00ff = 255
    - ...
  - level 3, 8x8=64
    - at `0x001291`, length=`0x98c`
  - level 4, 16x16=254
    - at `0x001c1d`, length=`0x248c`
- JFIF 4a 46 49 46
  - count 341 from `strings | grep JFIF | wc -l`
  - 341 = 1 + 4 + 16 + 64 + 256, 5 levels :-)
- level 0
  - at `0x0040a9` -> `0xffd8`=SOI `0xffe0`=JFIF-APP0, length=`0x2689`
- level 1
  - at `0x006732` -> SOI header, length=`0x218e`
  - at `0x0088c0` -> SOI header, length=`0x18e4`
  - at `0x00a1a4` -> SOI header, length=`0x2794`
  - at `0x00c938` -> SOI header, length=`0x1b23`
- level 2
  - at `0x00e45b` -> SOI header
  - at `0x01051c` -> SOI header
  - at `0x0117ff` -> SOI header
  - at `0x0122a5` -> SOI header
  - at `0x013c9a` -> SOI header
  - at `0x015f81` -> SOI header
  - at `0x017832` -> SOI header
  - at `0x018cf1` -> SOI header
