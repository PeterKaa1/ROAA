import os


def find_all_png_data(file_path):
    with open(file_path, "rb") as file:
        data = file.read()

        start_idx = 0
        png_data_list = []

        while True:
            start_idx = data.find(b"\x89PNG", start_idx)
            if start_idx == -1:
                break

            end_idx = data.find(b"\x49\x45\x4E\x44\xAE\x42\x60\x82", start_idx + 1)
            if end_idx == -1:
                print(f"End of PNG data not found in the file: {file_path}")
                return None

            png_data = data[start_idx : end_idx + 8]
            png_data_list.append(png_data)

            start_idx = end_idx + 1

        return png_data_list


def build_png_files(png_data_list, output_dir):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for i, png_data in enumerate(png_data_list, start=1):
        output_path = os.path.join(output_dir, f"output_file_{i}.png")
        with open(output_path, "wb") as outfile:
            outfile.write(png_data)
        print(f"PNG data extracted and saved to: {output_path}")


if __name__ == "__main__":
    file_paths = ["c1", "c2", "c7", "c8", "c9", "mi", "nm1", "nm3", "nm4", "oi"]

    for input_file_path in file_paths:
        output_dir = f"{os.path.splitext(input_file_path)[0]}_output"
        png_data_list = find_all_png_data(input_file_path)
        if png_data_list:
            build_png_files(png_data_list, output_dir)
        else:
            print(f"No PNG data found in the file: {input_file_path}")
          
