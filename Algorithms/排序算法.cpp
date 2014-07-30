// 避免与std冲突
namespace TinySort {
	/*--  辅助函数  --*/
	// 交换a[] 中位置 i 和 j
	template<typename Type>
	void exch(Type a[], int i, int j) {
		Type t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	// 比较a[] 中 第i和第j元素
	template<typename Type>
	bool less(Type a[], int i, int j) {
		return a[i] < a[j];
	}

	template<typename Type>
	bool eq(Type v, Type w) {
		return v == w;
	}

	// 比较i 和 j
	template<typename Type>
	bool less(Type i, Type j) {
		return i < j;
	}

	// 打印元素
	template<typename Type>
	void show(Type a[], int N) {
		for (int i = 0; i < N; i++) {
			cout << a[i]  << " ";
		}
		cout << endl;
	}

	// 用于assert判断
	template<typename Type>
	void isSorted(Type a[], int N) {
		for (int i = 1; i < N; i++) {
			if (a[i] < a[i - 1])	return false;
		}
		return true;
	}

	/*---  排序主要算法  ---*/
	/************************************************************************/
	/*                       插入排序版本1                                  */
	/************************************************************************/
	template<typename Type>
	void insert_srot(Type a[], int N) {
		for (int i = 0; i < N; i++) {
			for (int j = i; j > 0 && less(a, j, j - 1); j--) {
				exch(a, j, j - 1);
			}
		}
	}
	/************************************************************************/
	/*                       插入排序版本2                                  */
	/************************************************************************/
	template<typename Type>
	void insert_sortx(Type a[], int N) {
		for (int i = N - 1; i >= 1; i--) {
			if (less(a[i], a[i - 1]))
				exch(a, i, i - 1);
		}
		for (int i = 2; i < N; i++) {
			Type v = a[i];// store the element which will be inserted 
			int j = i; // search from j-1
			while (less(v, a[j - 1])) {
				// move the element j to j-1, if v less than a[j-1]
				a[j] = a[j - 1];
				j--;
			}
			// now find the position where v should be.
			a[j] = v;
		}
	}

	/************************************************************************/
	/*                       选择排序                                       */
	/************************************************************************/
	template<typename Type>
	void select_sort(Type a[], int N) {
		for (int i = 0; i < N - 1; i++) {
			int m = i;
			for (int j = i + 1; j < N; j++) {
				if (less(a, j, m))
					m = j;
			}
			exch(a, i, m);
		}
	}

	/************************************************************************/
	/*                       希尔排序                                       */
	/************************************************************************/ 
	// 分组插入排序， 缩小增量排序，非平凡复杂度。约为O(n^(3/2))
	// 取决于增量的值
	template<typename Type>
	void shell_sort(Type a[], int N) {
		int h = 1;
		// 3x+1 increment sequence
		while (h < N / 3) h = 3 * h + 1;
		while (h >= 1) {
			// h-sort the array;
			// insertion sort
			for (int i = h; i < N; i++) {
				for (int j = i; j >= h && less(a[j], a[j - h]); j -= h) {
					exch(a, j, j - h);
				}
			}
			// move to next increment
			h /= 3;
		}
	}

	/************************************************************************/
	/*                       归并排序                                       */
	/************************************************************************/
	// 需要额外数组空间
	template<typename Type>
	void merge_sort(Type a[], int N) {
		// 这里可以放到外面去定义
		Type *aux = new Type[N];
		for (int i = 0; i < N; i++) aux[i] = a[i];
		merge_help_sort(aux, a, 0, N - 1);
	}

	template<typename Type>
	void merge_help_sort(Type src[], Type dst[], int lo, int hi) {
		if (hi <= lo) return;
		int mid = lo + ((hi - lo) >> 1);
		merge_help_sort(dst, src, lo, mid);
		merge_help_sort(dst, src, mid + 1, hi);
		merge(src, dst, lo, mid, hi);
	}

	template<typename Type>
	void merge(Type src[], Type dst[], int lo, int mid, int hi) {
		int i = lo, j = mid + 1;
		for (int k = lo; k <= hi; k++) {
			if		(i > mid) 			dst[k] = src[j++];
			else if (j > hi) 			dst[k] = src[i++];
			else if (less(src, i, j))	dst[k] = src[i++];
			else 						dst[k] = src[j++];
		}
	}

	/************************************************************************/
	/*                       优化后的快速排序                               */
	/************************************************************************/
	const int CUTOFF = 8;
	template<typename Type>
	void quick_sort(Type a[], int N) {
		quick_help_sort(a, 0, N-1);
	}
	template<typename Type>
	void insertionSort(Type a[], int lo, int hi) {
		for (int i = lo; i <= hi; i++)
		for (int j = i; j > lo && less(a[j], a[j - 1]); j--)
			exch(a, j, j - 1);
	}

	// return the index of the median element among a[i], a[j], and a[k]
	template<typename Type>
	int median3(Type a[], int i, int j, int k) {
		return (less(a[i], a[j]) ?
			(less(a[j], a[k]) ? j : less(a[i], a[k]) ? k : i) :
			(less(a[k], a[j]) ? j : less(a[k], a[i]) ? k : i));
	}

	template<typename Type>
	void quick_help_sort(Type a[], int lo, int hi) {
		int N = hi - lo + 1;
		// cutoff to insertion sort
		if (N <= CUTOFF) {
			insertionSort(a, lo, hi);
			return;
		}
		// use median-of-3 as partitioning element
		else if (N <= 40) {
			int m = median3(a, lo, lo + N / 2, hi);
			exch(a, m, lo);
		}
		// use Tukey ninther as partitioning element
		else  {
			int eps = N / 8;
			int mid = lo + N / 2;
			int m1 = median3(a, lo, lo + eps, lo + eps + eps);
			int m2 = median3(a, mid - eps, mid, mid + eps);
			int m3 = median3(a, hi - eps - eps, hi - eps, hi);
			int ninther = median3(a, m1, m2, m3);
			exch(a, ninther, lo);
		}

		// Bentley-McIlroy 3-way partitioning
		int i = lo, j = hi + 1;
		int p = lo, q = hi + 1;
		Type v = a[lo];
		while (true) {
			while (less(a[++i], v))
			if (i == hi) break;
			while (less(v, a[--j]))
			if (j == lo) break;

			// pointers cross
			if (i == j && eq(a[i], v))
				exch(a, ++p, i);
			if (i >= j) break;

			exch(a, i, j);
			if (eq(a[i], v)) exch(a, ++p, i);
			if (eq(a[j], v)) exch(a, --q, j);
		}

		i = j + 1;
		for (int k = lo; k <= p; k++) exch(a, k, j--);
		for (int k = hi; k >= q; k--) exch(a, k, i++);

		quick_help_sort(a, lo, j);
		quick_help_sort(a, i, hi);
	}
}