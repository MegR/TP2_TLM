#define ROM_SIZE (320 * 240 / 2)
#define CODE_SIZE (10 * 1024)

const int addr_deb_video = 0x10002800;
const int size_video = 0x4B000; 

const int addr_deb_memory = 0x10000000;
const int size_memory = CODE_SIZE + size_video; 

const int addr_deb_rom = 0x30000000;
const int size_rom = ROM_SIZE;

const int addr_deb_LCDC = 0x20000000;
const int size_LCDC = 0x96000;

const int IMG_SIZE = 76800;
