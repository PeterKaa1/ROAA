import java.io.*;
import java.nio.file.*;
import java.util.*;

public class Main {

    public static List find_all_png_data(String file_path) throws IOException {
        byte[] data = Files.readAllBytes(Paths.get(file_path));
        int start_idx = 0;
        List png_data_list = new ArrayList<>();

        while (true) {
            start_idx = findBytes(data, new byte[]{(byte) 0x89, (byte) 'P', (byte) 'N', (byte) 'G'}, start_idx);
            if (start_idx == -1) {
                break;
            }

            int[] end_pattern = {0x49, 0x45, 0x4E, 0x44, 0xAE, 0x42, 0x60, 0x82};
            int end_idx = findBytes(data, intArrayToByteArray(end_pattern), start_idx + 1);
            if (end_idx == -1) {
                System.out.println("End of PNG data not found in the file: " + file_path);
                return null;
            }

            byte[] png_data = Arrays.copyOfRange(data, start_idx, end_idx + 8);
            png_data_list.add(png_data);

            start_idx = end_idx + 1;
        }

        return png_data_list;
    }

    public static void build_png_files(List png_data_list, String output_dir) throws IOException {
        File dir = new File(output_dir);
        if (!dir.exists()) {
            dir.mkdirs();
        }

        for (int i = 0; i < png_data_list.size(); i++) {
            byte[] png_data = png_data_list.get(i);
            String output_path = Paths.get(output_dir, "output_file_" + (i + 1) + ".png").toString();
            Files.write(Paths.get(output_path), png_data);
            System.out.println("PNG data extracted and saved to: " + output_path);
        }
    }

    public static int findBytes(byte[] data, byte[] pattern, int start_idx) {
        for (int i = start_idx; i < data.length - pattern.length; i++) {
            boolean found = true;
            for (int j = 0; j < pattern.length; j++) {
                if (data[i + j] != pattern[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return i;
            }
        }
        return -1;
    }

    public static byte[] intArrayToByteArray(int[] array) {
        byte[] result = new byte[array.length];
        for (int i = 0; i < array.length; i++) {
            result[i] = (byte) array[i];
        }
        return result;
    }

    public static void main(String[] args) {
        String[] file_paths = {"c1", "c2", "c7", "c8", "c9", "mi", "nm1", "nm3", "nm4", "oi"};

        for (String input_file_path : file_paths) {
            String output_dir = Paths.get(Paths.get(input_file_path).getFileName().toString()).toString() + "_output";
            try {
                List png_data_list = find_all_png_data(input_file_path);
                if (png_data_list != null) {
                    build_png_files(png_data_list, output_dir);
                } else {
                    System.out.println("No PNG data found in the file: " + input_file_path);
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
