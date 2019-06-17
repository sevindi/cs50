# Questions

## What's `stdint.h`?

It is a header file which allows people to write more compact codes by defining integer types. In this way we can make sure that integer type has the size that we exactly want.

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

These are fixed width integeres which allows us to determine size of the integer as 8, 16 or 32. While int means assigned integere, uint means unassigned integere. Difference between these two is that unassigned integeres cannot store negative values.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

8 bits is a BYTE. 
DWORD and LONG has 32 bits, so it is 4 bytes. 
WORD has 16 bits, so it is 2 bytes.

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM in ASCII, 0 in decimal and 00 in hexadecimal.

## What's the difference between `bfSize` and `biSize`?

While bfSize is the size of the entries bmp, biSize is the size of the BITMAPINFOHEADER and it constantly 40 bytes.

## What does it mean if `biHeight` is negative?

It means bmp has top-down DIBs and order of the rows are reversed. The top row of the image is the first row in memory, followed by the next row down. 

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount specifies number of bits per pixel.

## Why might `fopen` return `NULL` in `copy.c`?

It might not stored the value which is supposed to returned.

## Why is the third argument to `fread` always `1` in our code?

I believe it reads a red, green, blue group at once in a pixel.

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

Since each pixel is 3 bytes and width is 3, the value is 9 bytes. In order to complete it to multiple of 4, we need to assign 3 bytes of padding.

## What does `fseek` do?

fseek used in this programme to skip over padding and find pixels.

## What is `SEEK_CUR`?

I should move file pointer position to given location. I don't know how it works in this particular programme but it looks like it doesn't do anything.
