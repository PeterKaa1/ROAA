#include 
#include 
#include 

void find_all_png_data(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char *data = (unsigned char *)malloc(file_size);
    if (data == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return;
    }

    fread(data, 1, file_size, file);
    fclose(file);

    long start_idx = 0;
    long end_idx = 0;
    long search_idx = 0;
    char *png_signature = "\x89PNG";
    char *end_signature = "\x49\x45\x4E\x44\xAE\x42\x60\x82";

    while (search_idx < file_size) {
        start_idx = search_idx;
        while (start_idx < file_size - 3 && memcmp(data + start_idx, png_signature, 4) != 0) {
            start_idx++;
        }

        if (start_idx >= file_size - 3) {
            break;
        }

        end_idx = start_idx + 1;
        while (end_idx < file_size - 7 && memcmp(data + end_idx, end_signature, 8) != 0) {
            end_idx++;
        }

        if (end_idx >= file_size - 7) {
            fprintf(stderr, "End of PNG data not found in the file: %s\n", file_path);
            free(data);
            return;
        }

        // Process png_data from start_idx to end_idx + 7
        printf("PNG data found: %ld to %ld\n", start_idx, end_idx + 7);

        search_idx = end_idx + 8;
    }

    free(data);
}

int main() {
    const char *file_paths[] = {"c1", "c2", "c7", "c8", "c9", "mi", "nm1", "nm3", "nm4", "oi"};
    int num_files = sizeof(file_paths) / sizeof(file_paths[0]);

    for (int i = 0; i < num_files; i++) {
        find_all_png_data(file_paths[i]);
    }

    return 0;
}
