#include "TIA.hpp"

std::map<int, int> TIA::Colors::NTSC = {
		{ 0x00, 0x000000 },
		{ 0x02, 0x1A1A1A },
		{ 0x04, 0x393939 },
		{ 0x06, 0x5B5B5B },
		{ 0x08, 0x7E7E7E },
		{ 0x0A, 0xA2A2A2 },
		{ 0x0C, 0xC7C7C7 },
		{ 0x0E, 0xEDEDED },

		{ 0x10, 0x190200 },
		{ 0x12, 0x3A1F00 },
		{ 0x14, 0x5D4100 },
		{ 0x16, 0x826400 },
		{ 0x18, 0xA78800 },
		{ 0x1A, 0xCCAD00 },
		{ 0x1C, 0xF2D219 },
		{ 0x1E, 0xFEFA40 },

		{ 0x20, 0x370000 },
		{ 0x22, 0x5E0800 },
		{ 0x24, 0x832700 },
		{ 0x26, 0xA94900 },
		{ 0x28, 0xCF6C00 },
		{ 0x2A, 0xF58F17 },
		{ 0x2C, 0xFEB438 },
		{ 0x2E, 0xFEDF6F },

		{ 0x30, 0x470000 },
		{ 0x32, 0x730000 },
		{ 0x34, 0x981300 },
		{ 0x36, 0xBE3216 },
		{ 0x38, 0xE45335 },
		{ 0x3A, 0xFE7657 },
		{ 0x3C, 0xFE9C81 },
		{ 0x3E, 0xFEC6BB },

		{ 0x40, 0x440008 },
		{ 0x42, 0x6F001F },
		{ 0x44, 0x960640 },
		{ 0x46, 0xBB2462 },
		{ 0x48, 0xE14585 },
		{ 0x4A, 0xFE67AA },
		{ 0x4C, 0xFE8CD6 },
		{ 0x4E, 0xFEB7F6 },

		{ 0x50, 0x2D004A },
		{ 0x52, 0x570067 },
		{ 0x54, 0x7D058C },
		{ 0x56, 0xA122B1 },
		{ 0x58, 0xC743D7 },
		{ 0x5A, 0xED65FE },
		{ 0x5C, 0xFE8AF6 },
		{ 0x5E, 0xFEB5F7 },

		{ 0x60, 0x0D0082 },
		{ 0x62, 0x3300A2 },
		{ 0x64, 0x550FC9 },
		{ 0x66, 0x782DF0 },
		{ 0x68, 0x9C4EFE },
		{ 0x6A, 0xC372FE },
		{ 0x6C, 0xEB98FE },
		{ 0x6E, 0xFEC0F9 },

		{ 0x70, 0x000091 },
		{ 0x72, 0x0A05BD },
		{ 0x74, 0x2822E4 },
		{ 0x76, 0x4842FE },
		{ 0x78, 0x6B64FE },
		{ 0x7A, 0x908AFE },
		{ 0x7C, 0xB7B0FE },
		{ 0x7E, 0xDFD8FE },

		{ 0x80, 0x000072 },
		{ 0x82, 0x001CAB },
		{ 0x84, 0x033CD6 },
		{ 0x86, 0x205EFD },
		{ 0x88, 0x4081FE },
		{ 0x8A, 0x64A6FE },
		{ 0x8C, 0x89CEFE },
		{ 0x8E, 0xB0F6FE },

		{ 0x90, 0x00103A },
		{ 0x92, 0x00316E },
		{ 0x94, 0x0055A2 },
		{ 0x96, 0x0579C8 },
		{ 0x98, 0x239DEE },
		{ 0x9A, 0x44C2FE },
		{ 0x9C, 0x68E9FE },
		{ 0x9E, 0x8FFEFE },

		{ 0xA0, 0x001F02 },
		{ 0xA2, 0x004326 },
		{ 0xA4, 0x006957 },
		{ 0xA6, 0x008D7A },
		{ 0xA8, 0x1BB19E },
		{ 0xAA, 0x3BD7C3 },
		{ 0xAC, 0x5DFEE9 },
		{ 0xAE, 0x86FEFE },

		{ 0xB0, 0x002403 },
		{ 0xB2, 0x004A05 },
		{ 0xB4, 0x00700C },
		{ 0xB6, 0x09952B },
		{ 0xB8, 0x28BA4C },
		{ 0xBA, 0x49E06E },
		{ 0xBC, 0x6CFE92 },
		{ 0xBE, 0x97FEB5 },

		{ 0xC0, 0x002102 },
		{ 0xC2, 0x004604 },
		{ 0xC4, 0x086B00 },
		{ 0xC6, 0x289000 },
		{ 0xC8, 0x49B509 },
		{ 0xCA, 0x6BDB28 },
		{ 0xCC, 0x8FFE49 },
		{ 0xCE, 0xBBFE69 },

		{ 0xD0, 0x001501 },
		{ 0xD2, 0x103600 },
		{ 0xD4, 0x305900 },
		{ 0xD6, 0x537E00 },
		{ 0xD8, 0x76A300 },
		{ 0xDA, 0x9AC800 },
		{ 0xDC, 0xBFEE1E },
		{ 0xDE, 0xE8FE3E },

		{ 0xE0, 0x1A0200 },
		{ 0xE2, 0x3B1F00 },
		{ 0xE4, 0x5E4100 },
		{ 0xE6, 0x836400 },
		{ 0xE8, 0xA88800 },
		{ 0xEA, 0xCEAD00 },
		{ 0xEC, 0xF4D218 },
		{ 0xEE, 0xFEFA40 },

		{ 0xF0, 0x380000 },
		{ 0xF2, 0x5F0800 },
		{ 0xF4, 0x842700 },
		{ 0xF6, 0xAA4900 },
		{ 0xF8, 0xD06B00 },
		{ 0xFA, 0xF68F18 },
		{ 0xFC, 0xFEB439 },
		{ 0xFE, 0xFEDF70 },
};

TIA::TIA(RAM* ram)
{
	this->ram = ram;
}

void TIA::draw(SDL_Renderer* renderer, short int clock, short int scanline)
{
   int color = TIA::Colors::NTSC[this->ram->get(0x09)];
   SDL_SetRenderDrawColor(renderer, color >> (0x08 * 2), color >> 0x08 & 0xFF, color & 0xFF, 255);
   SDL_RenderDrawPoint(renderer, clock - 68, scanline - 30);
   SDL_RenderDrawPoint(renderer, clock - 68 + 1, scanline - 30);
   SDL_RenderDrawPoint(renderer, clock - 68 + 2, scanline - 30);
}

bool TIA::getVsync()
{
    return this->vsync;
}

void TIA::setVsync(bool vsync)
{
    this->vsync = vsync;
}
