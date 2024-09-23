import java.util.List;

public class QuickSort2 {

    public static void main(String[] args) {
        List<Integer> numbers = FileUtil.readNumbersFromFile("./input_sort.txt");
        Integer[] arr = numbers.toArray(new Integer[0]);

        long start = System.nanoTime();
        quickSort(arr, 0, arr.length - 1);
        long end = System.nanoTime();

        System.out.println("MS : " + (double) (end - start) / 1_000_000);
        
        FileUtil.writeArrayToFile("./output_quick_sort.txt", arr);
    }

    private static void quickSort(Integer[] A, int p, int r) {
        if (p < r) {
            int q = partition(A, p, r);
            quickSort(A, p, q - 1);
            quickSort(A, q + 1, r);
        }
    }

    private static int partition(Integer[] A, int p, int r) {
        final int mid = (p + r) >>> 1;
        final int x = A[mid];
        int i = p - 1;
        for (int j = p; j <= r - 1; j++) {
            if (A[j] <= x) {
                i++;
                swap(A, i, j);
            }
        }
        swap(A, i + 1, r); // 피벗을 제자리에 놓기
        return i + 1;
    }

    private static void swap(Integer[] A, int i, int j) {
        int temp = A[i];
        A[i] = A[j];
        A[j] = temp;
    }
}

