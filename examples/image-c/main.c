#include "../../src/firefly.c"

Image image;

BOOT void boot()
{
    // We know the image size in advance.
    // You can see it when running `firefly_cli build`.
    // You could also use `get_file_size` to detect the file size
    // in runtime but that requires using an allocator.
    const size_t fileSize = 97;
    Buffer buf;
    char head[fileSize];
    buf.head = head;
    buf.size = fileSize;
    image = load_file("img", buf);
}

UPDATE void update()
{
    clear_screen(WHITE);
    Point point = {10, 10};
    draw_image(image, point);
}
