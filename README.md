----------------------------------Features----------------------------------

This project entails creating a console application for embedding and extracting 
secret messages from image files. It should be able to modify standard 
graphic files (like .png and .bmp) to hide messages and subsequently read them back.


----------------------------------Supported Operations----------------------------------

The application should handle the following operations via command-line flags:

-i (--info): Inspect the image file and display details like dimensions, size, and last modified timestamp.
-e (--encrypt): Embed a secret message into an image file.
-d (--decrypt): Extract the hidden message from an image file.
-c (--check): Check if an image file can store a given secret message.
-h (--help): Display help information, usage instructions, and supported file formats.


----------------------------------Supported Image Formats----------------------------------

.png
.bmp

----------------------------------Steganography Method----------------------------------

Program modifies two last bits of each pixel chanels - assuming RGBA.

----------------------------------Libraries----------------------------------

fmt - https://github.com/fmtlib/fmt
sfml - https://www.sfml-dev.org/index.php

----------------------------------Contributors----------------------------------

Mateusz Cybruk: Initial implementation, design, and documentation
