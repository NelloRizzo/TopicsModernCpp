#include <cstdint>
#include "BitmapCanvas.h"

struct BmpInfoHeader {
	uint32_t sizeOfThisHeader = 40;
	int32_t width = 512; // in pixels
	int32_t height = 512; // in pixels
	uint16_t numberOfColorPlanes = 1; // must be 1
	uint16_t colorDepth = 24;
	uint32_t compressionMethod = 0;
	uint32_t rawBitmapDataSize = 0; // generally ignored
	int32_t horizontalResolution = 3780; // in pixel per meter
	int32_t verticalResolution = 3780; // in pixel per meter
	uint32_t colorTableEntries = 0;
	uint32_t importantColors = 0;
} bmpInfo;

struct BitmapHeader {
	char bitmapSignatureBytes[2] = { 'B', 'M' };
	uint32_t sizeOfBitmapFile = 54 + 786432;
	uint32_t reservedBytes = 0;
	uint32_t pixelDataOffset = 54;
} bmpHeader;

Color operator""_col(unsigned long long col) {
	auto b = static_cast<uint8_t>((col & 0x000000ff));
	auto g = static_cast<uint8_t>((col & 0x0000ff00) >> 8);
	auto r = static_cast<uint8_t>((col & 0x00ff0000) >> 16);
	return Color{ b,g,r };
}

void BitmapCanvas::clear()
{
	Color color = currentColor;
	setCurrentColor(backColor);
	Canvas::clear();
	setCurrentColor(color);
}

void BitmapCanvas::setPoint(int x, int y)
{
	buffer[index(x, y)] = currentColor;
}

void BitmapCanvas::resetPoint(int x, int y)
{
	buffer[index(x, y)] = backColor;
}

bool BitmapCanvas::isOn(int x, int y) const
{
	Color c = buffer[index(x, y)];
	return c.blue != backColor.blue || c.green != backColor.green || c.red != backColor.red;
}


ostream& BitmapCanvas::out(ostream& s)
{
	bmpInfo.width = static_cast<int32_t>(width);
	bmpInfo.height = static_cast<int32_t>(height);
	bmpHeader.sizeOfBitmapFile = static_cast <int32_t>(54 + width * height * 3);
	s.write((char*)&bmpHeader, 14);
	s.write((char*)&bmpInfo, 40);
	for (int r = 0; r < height; ++r)
		for (int c = 0; c < width; ++c)
			s.write((char*)&buffer[index(c, r)], 3);
	return s;
}

