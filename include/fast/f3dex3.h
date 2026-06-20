#pragma once

/*
 * F3DEX3 GBI opcodes.
 * Most high-byte opcodes (0xD7–0xFF) are identical to F3DEX2.
 * The low-byte range (0x00–0x0B) differs: 0x08 is G_TRISNAKE instead of
 * G_LINE3D, and 0x0A/0x0B are new commands absent in F3DEX2.
 * 0xD4 (G_FLUSH) and 0xD5 (G_MEMSET) replace F3DEX2's G_SPECIAL_2/1.
 */

/* Low-byte opcodes */
constexpr int8_t F3DEX3_G_NOOP        = OPCODE(0x00);
constexpr int8_t F3DEX3_G_VTX         = OPCODE(0x01); /* same encoding as F3DEX2 */
constexpr int8_t F3DEX3_G_MODIFYVTX   = OPCODE(0x02);
constexpr int8_t F3DEX3_G_CULLDL      = OPCODE(0x03);
constexpr int8_t F3DEX3_G_BRANCH_Z    = OPCODE(0x04);
constexpr int8_t F3DEX3_G_TRI1        = OPCODE(0x05);
constexpr int8_t F3DEX3_G_TRI2        = OPCODE(0x06);
constexpr int8_t F3DEX3_G_QUAD        = OPCODE(0x07);
constexpr int8_t F3DEX3_G_TRISNAKE    = OPCODE(0x08); /* replaces G_LINE3D */
constexpr int8_t F3DEX3_G_LIGHTTORDP  = OPCODE(0x0A); /* new */
constexpr int8_t F3DEX3_G_RELSEGMENT  = OPCODE(0x0B); /* new */

/* High-byte opcodes — shared with F3DEX2 */
constexpr int8_t F3DEX3_G_FLUSH          = OPCODE(0xD4); /* replaces G_SPECIAL_2 */
constexpr int8_t F3DEX3_G_MEMSET         = OPCODE(0xD5); /* replaces G_SPECIAL_1 */
constexpr int8_t F3DEX3_G_DMA_IO         = OPCODE(0xD6);
constexpr int8_t F3DEX3_G_TEXTURE        = OPCODE(0xD7);
constexpr int8_t F3DEX3_G_POPMTX         = OPCODE(0xD8);
constexpr int8_t F3DEX3_G_GEOMETRYMODE   = OPCODE(0xD9);
constexpr int8_t F3DEX3_G_MTX            = OPCODE(0xDA);
constexpr int8_t F3DEX3_G_MOVEWORD       = OPCODE(0xDB);
constexpr int8_t F3DEX3_G_MOVEMEM        = OPCODE(0xDC);
constexpr int8_t F3DEX3_G_LOAD_UCODE     = OPCODE(0xDD);
constexpr int8_t F3DEX3_G_DL             = OPCODE(0xDE);
constexpr int8_t F3DEX3_G_ENDDL          = OPCODE(0xDF);
constexpr int8_t F3DEX3_G_SPNOOP         = OPCODE(0xE0);
constexpr int8_t F3DEX3_G_RDPHALF_1      = OPCODE(0xE1);
constexpr int8_t F3DEX3_G_SETOTHERMODE_L = OPCODE(0xE2);
constexpr int8_t F3DEX3_G_SETOTHERMODE_H = OPCODE(0xE3);

/*
 * G_MTX parameter flags — same numeric values as F3DEX2,
 * but F3DEX3 inverts BOTH PUSH (bit 0) AND LOAD (bit 1) in the command word.
 */
constexpr int8_t F3DEX3_G_MTX_MODELVIEW  = OPCODE(0x00);
constexpr int8_t F3DEX3_G_MTX_PROJECTION = OPCODE(0x04);
constexpr int8_t F3DEX3_G_MTX_MUL        = OPCODE(0x00);
constexpr int8_t F3DEX3_G_MTX_LOAD       = OPCODE(0x02);
constexpr int8_t F3DEX3_G_MTX_NOPUSH     = OPCODE(0x00);
constexpr int8_t F3DEX3_G_MTX_PUSH       = OPCODE(0x01);

/* The XOR mask applied to the raw command byte to decode MTX params */
constexpr int8_t F3DEX3_G_MTX_XOR_MASK   = OPCODE(0x03); /* PUSH | LOAD */

/*
 * G_TRISNAKE direction flags (stored in bit 0 of each encoded byte).
 * G_SNAKE_LAST (0x40) is OR'd into the vertex *index* parameter before
 * it is shifted left by 1, so it ends up as bit 7 of the encoded byte.
 */
constexpr uint8_t F3DEX3_G_SNAKE_RIGHT = 0;
constexpr uint8_t F3DEX3_G_SNAKE_LEFT  = 1;
constexpr uint8_t F3DEX3_G_SNAKE_LAST  = 0x80; /* bit 7 of the encoded byte */

/*
 * MOVEMEM indices — identical to F3DEX2.
 */
constexpr int8_t F3DEX3_G_MV_VIEWPORT = OPCODE(8);
constexpr int8_t F3DEX3_G_MV_LIGHT    = OPCODE(10);

/*
 * F3DEX3 uses 16-byte light slots (vs 24 bytes in F3DEX2).
 * Lookat occupies slot 0 (offset 0x00); directional/point lights start at
 * slot 1 (offset 0x10).  So lightidx = (offset / 16) - 1.
 */
constexpr uint8_t F3DEX3_LIGHT_SLOT_SIZE   = 16;
constexpr uint8_t F3DEX3_LIGHT_SLOT_OFFSET = 1; /* subtract this after dividing */

/*
 * MOVEWORD indices — mostly matching F3DEX2 values.
 * G_MW_FX replaces G_MW_MATRIX (0x00).
 */
constexpr int8_t F3DEX3_G_MW_FX        = 0x00;
constexpr int8_t F3DEX3_G_MW_NUMLIGHT  = 0x02;
constexpr int8_t F3DEX3_G_MW_SEGMENT   = 0x06;
constexpr int8_t F3DEX3_G_MW_FOG       = 0x08;
constexpr int8_t F3DEX3_G_MW_LIGHTCOL  = 0x0A;

/*
 * NUML(n) = n * 16 in F3DEX3 (vs n * 24 in F3DEX2).
 * current_num_lights = data / 16 + 1  (ambient counted separately).
 */
constexpr uint8_t F3DEX3_NUML_DIVISOR = 16;

/*
 * G_MW_FX sub-word offsets (used with G_MOVEWORD index 0x00).
 * Half-word writes use bit 15 of the offset field to signal a 16-bit store.
 */
constexpr uint16_t F3DEX3_G_MW_HALFWORD_FLAG       = 0x8000;
constexpr uint16_t F3DEX3_G_MWO_AO_AMBIENT         = 0x00;
constexpr uint16_t F3DEX3_G_MWO_AO_DIRECTIONAL     = 0x02;
constexpr uint16_t F3DEX3_G_MWO_AO_POINT           = 0x04;
constexpr uint16_t F3DEX3_G_MWO_FRESNEL_SCALE      = 0x0C;
constexpr uint16_t F3DEX3_G_MWO_FRESNEL_OFFSET     = 0x0E;
constexpr uint16_t F3DEX3_G_MWO_ATTR_OFFSET_S      = 0x10;
constexpr uint16_t F3DEX3_G_MWO_ATTR_OFFSET_T      = 0x12;
constexpr uint16_t F3DEX3_G_MWO_ALPHA_COMPARE_CULL = 0x14;
constexpr uint16_t F3DEX3_G_MWO_ATTR_OFFSET_Z      = 0x14; /* full-word write, same address */
constexpr uint16_t F3DEX3_G_MWO_NORMALS_MODE       = 0x18;

constexpr uint8_t F3DEX3_G_NORMALS_MODE_FAST   = 0x00;
constexpr uint8_t F3DEX3_G_NORMALS_MODE_AUTO   = 0x01;
constexpr uint8_t F3DEX3_G_NORMALS_MODE_MANUAL = 0x02;

constexpr int8_t F3DEX3_G_ALPHA_COMPARE_CULL_DISABLE =  0;
constexpr int8_t F3DEX3_G_ALPHA_COMPARE_CULL_BELOW   =  1;
constexpr int8_t F3DEX3_G_ALPHA_COMPARE_CULL_ABOVE   = -1;

/* Half-word G_MOVEWORD: sets bit 15 of the offset field so the RSP stores 2 bytes. */
#define F3DEX3_gsMoveHalfwd(index, offset, data) \
    gsDma1p(G_MOVEWORD, (data), ((offset) & 0xFFF) | F3DEX3_G_MW_HALFWORD_FLAG, (index))

/*
 * Geometry mode flags — F3DEX3 additions not present in the shared lus_gbi.h.
 */
constexpr uint32_t F3DEX3_G_ATTROFFSET_ST_ENABLE = 0x00000080;
constexpr uint32_t F3DEX3_G_AMBOCCLUSION         = 0x00000100;
constexpr uint32_t F3DEX3_G_PACKED_NORMALS        = 0x00000800;
constexpr uint32_t F3DEX3_G_LIGHTTOALPHA          = 0x00001000;
constexpr uint32_t F3DEX3_G_LIGHTING_SPECULAR      = 0x00002000;
constexpr uint32_t F3DEX3_G_FRESNEL_COLOR          = 0x00004000;
constexpr uint32_t F3DEX3_G_FRESNEL_ALPHA          = 0x00008000;
constexpr uint32_t F3DEX3_G_CULL_FRONT             = 0x00000200;
constexpr uint32_t F3DEX3_G_CULL_BACK              = 0x00000400;
constexpr uint32_t F3DEX3_G_CULL_BOTH              = 0x00000600;
