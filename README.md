# VNC-Al-e
Dự án triển khai các thuật toán thay đổi kích thước ảnh phổ biến
theo giới thiệu trên [Wiki](https://en.wikipedia.org/wiki/Image_scaling).

![Alt text](doc/Pixel-Art_Scaling_Comparison.png)

# Khung dự án
Sử dụng thư viện [stb](https://github.com/nothings/stb) để dọc ghi ảnh mẫu.
![Alt text](data/Lenna.png)

# [File bitmap](https://en.wikipedia.org/wiki/BMP_file_format)

```
void Image::save(string path) {
    // Header file cho tệp tin bitmap mặc định dài 14 + 40 byte.
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    // Thông tin ảnh 1 khung mỗi điểm ảnh 24 bit R-G-B
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    // Vá để mỗi mảng là bội của 4 byte.
    unsigned char bmppad[3] = {0,0,0};

    // Ghi thông tin dung lượng file.
    int filesize = 54 + this->width * this->height * 3;
    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    // Ghi thông tin kích thước file.
    bmpinfoheader[ 4] = (unsigned char)(       this->width     );
    bmpinfoheader[ 5] = (unsigned char)(       this->width>> 8 );
    bmpinfoheader[ 6] = (unsigned char)(       this->width>>16 );
    bmpinfoheader[ 7] = (unsigned char)(       this->width>>24 );
    bmpinfoheader[ 8] = (unsigned char)(       this->height    );
    bmpinfoheader[ 9] = (unsigned char)(       this->height>> 8);
    bmpinfoheader[10] = (unsigned char)(       this->height>>16);
    bmpinfoheader[11] = (unsigned char)(       this->height>>24);

    // Mở file.
    FILE *fileHanle = fopen(path.c_str(), "wb");
    if (fileHanle == nullptr) {
        throw runtime_error("Error open file " + path);
    }

    // Ghi thông tin file.
    fwrite(bmpfileheader, 1, 14, fileHanle);
    fwrite(bmpinfoheader, 1, 40, fileHanle);

    // Tính độ dài vá.
    auto padSize = (4 - (this->width * 3) % 4) % 4;
    for (int index = 0; index < this->height; index++) {
        // Ghi từng dong ảnh.
        fwrite(this->data + (this->width * (this->height - index - 1) * 3), 3, this->width, fileHanle);
        // Vá đủ bội của 4 byte.
        fwrite(bmppad , 1, padSize, fileHanle);
    }

    // Hoàn thành ghi file.
    fflush(fileHanle);
    fclose(fileHanle);
}
```