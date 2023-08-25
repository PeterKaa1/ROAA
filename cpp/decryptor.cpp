#include 
#include 
#include 
#include 
#include 

std::vector find_all_png_data(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return std::vector();
    }

    std::vector data((std::istreambuf_iterator(file)), std::istreambuf_iterator());

    size_t start_idx = 0;
    std::vector> png_data_list;

    while (true) {
        start_idx = data.find("PNG", start_idx);
        if (start_idx == std::string::npos) {
            break;
        }

        size_t end_idx = data.find("IEND\xAE\x42\x60\x82", start_idx + 1);
        if (end_idx == std::string::npos) {
            std::cerr << "End of PNG data not found in the file: " << file_path << std::endl;
            return std::vector();
        }

        std::vector png_data(data.begin() + start_idx, data.begin() + end_idx + 8);
        png_data_list.push_back(png_data);

        start_idx = end_idx + 1;
    }

    return png_data_list;
}

void build_png_files(const std::vector>& png_data_list, const std::string& output_dir) {
    if (mkdir(output_dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
        std::cerr << "Failed to create output directory: " << output_dir << std::endl;
        return;
    }

    for (size_t i = 0; i < png_data_list.size(); ++i) {
        const std::vector& png_data = png_data_list[i];
        std::string output_path = output_dir + "/output_file_" + std::to_string(i + 1) + ".png";
        std::ofstream outfile(output_path, std::ios::binary);
        if (outfile.is_open()) {
            outfile.write(png_data.data(), png_data.size());
            std::cout << "PNG data extracted and saved to: " << output_path << std::endl;
        } else {
            std::cerr << "Failed to write output file: " << output_path << std::endl;
        }
    }
}

int main() {
    std::vector file_paths = {"c1", "c2", "c7", "c8", "c9", "mi", "nm1", "nm3", "nm4", "oi"};

    for (const std::string& input_file_path : file_paths) {
        std::string output_dir = input_file_path.substr(0, input_file_path.find_last_of('.')) + "_output";
        std::vector> png_data_list = find_all_png_data(input_file_path);
        if (!png_data_list.empty()) {
            build_png_files(png_data_list, output_dir);
        } else {
            std::cerr << "No PNG data found in the file: " << input_file_path << std::endl;
        }
    }

    return 0;
}
