#include "../../src/firefly.c"

Image image;

BOOT void boot()
{
    // We know the image size in advance.
    // You can see it when running `firefly_cli build`.
    // You could also use `GetFileSize` to detect the file size
    // in runtime but that requires using an allocator.
    const size_t fileSize = 97;
    Buffer buf;
    char head[fileSize];
    buf.head = head;
    buf.size = fileSize;
    image = LoadFile("img", buf);
}

UPDATE void update()
{
    ClearScreen(WHITE);
    Point point = {10, 10};
    DrawImage(image, point);
}
