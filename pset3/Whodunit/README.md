## Requirements: 
Your host, Mr. John Boddy, has met an untimely end—he’s the victim of foul play. It is your job to determine whodunit (i.e., who has done it).
Unfortunately for you (though even more unfortunately for Mr. Boddy), the only evidence you have is a 24-bit BMP file called clue.bmp,
pictured below, that Mr. Boddy whipped up on his computer in his final moments. Hidden among this file’s red “noise” is a drawing of whodunit.
Plus, the questions. 

[Link to the CS50 lab](https://lab.cs50.io/cs50/labs/2019/x/whodunit/)

# Questions

## What's `stdint.h`?

stdint.h is a header file in the C standard library introduced in the C99 standard library section 7.18 to allow programmers to write more portable code by providing a
set of typedefs that specify exact-width integer types, together with the defined minimum and maximum allowable values for each type, using macros

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

**u** stands for **unsigned**, **int** stands for **integer**, **N** stands for **widtth**, **_t** stands for **"type"** (not variable for example)
* int32_t designates a signed integer type with width of exactly 32 bits, no padding bits, and a two's-complement representation.
* uint8_t designates an unsigned integer type with width of exactly 8 bits.
* uint32_t designates an unsigned integer type with width of exactly 32 bits.
* uint16_t designates an unsigned integer type with width of exactly 16 bits.


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

* BYTE - 8 bits or 1 byte 
* WORD - 16bits (unsigned) or 2 bytes
* DWORD - 32bits (unsigned) or 4 bytes
* LONG - 32bits (signed) or 4 bytes 

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

* The first of these headers, called BITMAPFILEHEADER, is 14 bytes long. 
* The second of these headers, called BITMAPINFOHEADER, is 40 bytes long

So the first two bytes are WORD and it is associated with bftype. Furthermore, BMP bftype first two bytes should be these (in hexadecimal): 
**0x4d42** // "BM" or short for bitmap
4D is 'M' and 42 is 'B'

Why the BM is in reverse: 
Intel processors use what is called "little endian" to store bytes in memory. That means that the least significant byte is stored in the first memory address in the word.
So gdb is showing you the decimal value 19778 (even though, in reality, bfType is 2 chars (B and M) and not an integer). If you convert to hex (which I think you've done) it is  0x4D42. 
That is the value that copy.c is testing against.The value 0x4D42 in a little endian system will be stored in byte order as 424D (how xxd is showing you).
// [Full answer here](https://cs50.stackexchange.com/questions/2061/surprise-with-gdb-way-of-reading-bftype-bmp-headers)


## What's the difference between `bfSize` and `biSize`?

**bfSize** should store the size of the whole BMP file — the size of the BMP image + the size of the headers. *(it's in the BITMAPFILEHEADER struct)*
**biSize** is the number of bytes required by the structure. // [From microsoft](https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-tagbitmapinfoheader) 
*(it's in the BITMAPINFOHEADER struct)*
In more details, biSize is the size of the BITMAPINFOHEADER only, not anything else. It is 40 bytes.

## What does it mean if `biHeight` is negative?

If biHeight is negative, the bitmap is a top-down DIB with the origin at the upper left corner. // [From microsoft](https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-tagbitmapinfoheader)

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

**biBitCount**

Specifies the number of bits per pixel (bpp). For uncompressed formats, this value is the average number of bits 
per pixel. For compressed formats, this value is the implied bit depth of the uncompressed image, after the image 
has been decoded. // [From microsoft](https://docs.microsoft.com/en-us/windows/desktop/api/wingdi/ns-wingdi-tagbitmapinfoheader)

## Why might `fopen` return `NULL` in `copy.c`?

If the file with given name does not exist. Or the file is not reachable. 

## Why is the third argument to `fread` always `1` in our code?

On success, fread() and fwrite() return the **number of items** read or written. This number equals the number of 
bytes transferred only when size is 1. Which means that we read just one item at the time. 
If an error occurs, or the end of the file is reached, the return value 
is a short item count (or zero).

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

000000 

## What does `fseek` do?

*sets file position*
Use fseek when you want to change the offset of the file pointer fp. This is an extremely useful tool. 
Normally, when reading in from a file, the pointer continues in one direction, from the start of the 
file to the end. fseek, however, allows you to change the location of the file pointer.

## What is `SEEK_CUR`?
**SEEK_CUR**
Specifies that offset is a count of characters from the current file position. This count may be positive or negative.


The fseek() function sets the file position indicator for the stream pointed to by stream. The new position, measured in bytes, is obtained by adding offset bytes to the position specified by whence. If whence is set to *SEEK_SET\*, *SEEK_CUR\*, or *SEEK_END\*, the offset is relative to the start of the file, the current position indicator, or end-of-file, respectively. A successful call to the fseek() function clears the end-of-file indicator for the stream and undoes any effects of the ungetc(3) function on the same stream.
